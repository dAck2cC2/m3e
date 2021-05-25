
#include <log/log.h>
#include <hardware/hardware.h>

#include <android/hardware/graphics/common/1.1/types.h>
#include <android/hardware/graphics/composer/2.3/IComposer.h>
#include <android/hardware/graphics/composer/2.3/IComposerClient.h>

#define TEST_MAIN   1
#define TEST_THREAD 2

#define TEST_NODE  TEST_MAIN

namespace types = android::hardware::graphics::common;

namespace V2_1 = android::hardware::graphics::composer::V2_1;
namespace V2_2 = android::hardware::graphics::composer::V2_2;
namespace V2_3 = android::hardware::graphics::composer::V2_3;

using V2_1::Config;
using V2_1::Display;
using V2_1::Error;
using V2_1::IComposerCallback;
using V2_1::Layer;
using V2_3::IComposer;
using V2_3::IComposerClient;


android::sp<V2_1::IComposer> mComposer;
android::sp<V2_1::IComposerClient> mClient;
android::sp<V2_2::IComposerClient> mClient_2_2;
android::sp<IComposerClient> mClient_2_3;


#if TEST_NODE == TEST_THREAD

#include <pthread.h>

static pthread_t mGUIThread = NULL;

void* _threadLoop(void* user)
{
    Error error = Error::NO_RESOURCES;
    mClient->createLayer(0, 64,
        [&](const auto& tmpError, const auto& tmpLayer) {
            error = tmpError;
            if (error != Error::NONE) {
                return;
            }
        });

    while (true) {
    }

    return nullptr;
}
#endif // TEST_THREAD


int main(int argc, char** argv)
{
    const hw_module_t* module = nullptr;

    hw_get_module("hidlservice", &module);
    if (module && module->methods && module->methods->open) {
        (*(module->methods->open))(module, "hidlservice", nullptr);
    }
    else {
        return 1;
    }

    mComposer = V2_1::IComposer::getService("default");

    if (mComposer == nullptr) {
        LOG_ALWAYS_FATAL("failed to get hwcomposer service");
    }

    if (android::sp<IComposer> composer_2_3 = IComposer::castFrom(mComposer)) {
        composer_2_3->createClient_2_3([&](const auto& tmpError, const auto& tmpClient) {
            if (tmpError == Error::NONE) {
                mClient = tmpClient;
                mClient_2_2 = tmpClient;
                mClient_2_3 = tmpClient;
            }
            });
    }
    else {
        mComposer->createClient([&](const auto& tmpError, const auto& tmpClient) {
            if (tmpError != Error::NONE) {
                return;
            }

            mClient = tmpClient;
            if (android::sp<V2_2::IComposer> composer_2_2 = V2_2::IComposer::castFrom(mComposer)) {
                mClient_2_2 = V2_2::IComposerClient::castFrom(mClient);
                LOG_ALWAYS_FATAL_IF(mClient_2_2 == nullptr,
                    "IComposer 2.2 did not return IComposerClient 2.2");
            }
            });
    }

    if (mClient == nullptr) {
        LOG_ALWAYS_FATAL("failed to create composer client");
    }

    Error error = Error::NO_RESOURCES;

#if TEST_NODE == TEST_MAIN
    mClient->createLayer(0, 64,
        [&](const auto& tmpError, const auto& tmpLayer) {
            error = tmpError;
            if (error != Error::NONE) {
                return;
            }
        });
#elif TEST_NODE == TEST_THREAD
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int result = pthread_create(&(mGUIThread), &attr,
        _threadLoop,
        NULL);
    pthread_attr_destroy(&attr);
#else
#error Please define test node.
#endif

    while (true) {
        android::hardware::Return<void> ret;
        uint32_t commandLength = 0;
        android::hardware::hidl_vec<android::hardware::hidl_handle> commandHandles;
        auto hidl_callback = [&](const auto& tmpError, const auto& tmpOutChanged,
            const auto& tmpOutLength, const auto& tmpOutHandles)
        {
            error = tmpError;
        };

        if (mClient_2_2) {
            ret = mClient_2_2->executeCommands_2_2(commandLength, commandHandles, hidl_callback);
        }
        else {
            ret = mClient->executeCommands(commandLength, commandHandles, hidl_callback);
        }
    }

    return 0;
}
