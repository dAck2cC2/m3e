#ifndef HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V2_0_BSPRIMARYDEVICE_H
#define HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V2_0_BSPRIMARYDEVICE_H

#include <android-base/macros.h>
#include <cutils/trace.h>
#include <future>
#include <android/hardware/audio/2.0/IPrimaryDevice.h>

#include <hidl/HidlPassthroughSupport.h>
#include <hidl/TaskRunner.h>
namespace android {
namespace hardware {
namespace audio {
namespace V2_0 {

struct BsPrimaryDevice : IPrimaryDevice, ::android::hardware::details::HidlInstrumentor {
    explicit BsPrimaryDevice(const ::android::sp<IPrimaryDevice> impl);

    typedef IPrimaryDevice Pure;

    typedef android::hardware::details::bs_tag _hidl_tag;

    // Methods from ::android::hardware::audio::V2_0::IDevice follow.
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> initCheck() {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::initCheck::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "initCheck", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->initCheck();

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "initCheck", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setMasterVolume(float volume) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::setMasterVolume::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&volume);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "setMasterVolume", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->setMasterVolume(volume);

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "setMasterVolume", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> getMasterVolume(getMasterVolume_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::getMasterVolume::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "getMasterVolume", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->getMasterVolume([&](const auto &_hidl_out_retval, const auto &_hidl_out_volume) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_retval);
                _hidl_args.push_back((void *)&_hidl_out_volume);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "getMasterVolume", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_retval, _hidl_out_volume);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setMicMute(bool mute) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::setMicMute::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&mute);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "setMicMute", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->setMicMute(mute);

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "setMicMute", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> getMicMute(getMicMute_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::getMicMute::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "getMicMute", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->getMicMute([&](const auto &_hidl_out_retval, const auto &_hidl_out_mute) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_retval);
                _hidl_args.push_back((void *)&_hidl_out_mute);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "getMicMute", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_retval, _hidl_out_mute);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setMasterMute(bool mute) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::setMasterMute::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&mute);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "setMasterMute", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->setMasterMute(mute);

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "setMasterMute", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> getMasterMute(getMasterMute_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::getMasterMute::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "getMasterMute", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->getMasterMute([&](const auto &_hidl_out_retval, const auto &_hidl_out_mute) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_retval);
                _hidl_args.push_back((void *)&_hidl_out_mute);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "getMasterMute", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_retval, _hidl_out_mute);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<void> getInputBufferSize(const ::android::hardware::audio::common::V2_0::AudioConfig& config, getInputBufferSize_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::getInputBufferSize::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&config);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "getInputBufferSize", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->getInputBufferSize(config, [&](const auto &_hidl_out_retval, const auto &_hidl_out_bufferSize) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_retval);
                _hidl_args.push_back((void *)&_hidl_out_bufferSize);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "getInputBufferSize", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_retval, _hidl_out_bufferSize);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<void> openOutputStream(int32_t ioHandle, const ::android::hardware::audio::V2_0::DeviceAddress& device, const ::android::hardware::audio::common::V2_0::AudioConfig& config, ::android::hardware::audio::common::V2_0::AudioOutputFlag flags, openOutputStream_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::openOutputStream::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&ioHandle);
            _hidl_args.push_back((void *)&device);
            _hidl_args.push_back((void *)&config);
            _hidl_args.push_back((void *)&flags);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "openOutputStream", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->openOutputStream(ioHandle, device, config, flags, [&](const auto &_hidl_out_retval, const auto &_hidl_out_outStream, const auto &_hidl_out_suggestedConfig) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_retval);
                _hidl_args.push_back((void *)&_hidl_out_outStream);
                _hidl_args.push_back((void *)&_hidl_out_suggestedConfig);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "openOutputStream", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            ::android::sp<::android::hardware::audio::V2_0::IStreamOut> _hidl_out_wrapped_outStream;
            if (_hidl_out_outStream != nullptr && !_hidl_out_outStream->isRemote()) {
                _hidl_out_wrapped_outStream = ::android::hardware::details::wrapPassthrough(_hidl_out_outStream);
                if (_hidl_out_wrapped_outStream == nullptr) {
                    _hidl_error = ::android::hardware::Status::fromExceptionCode(
                            ::android::hardware::Status::EX_TRANSACTION_FAILED,
                            "Cannot wrap passthrough interface.");
                    return;
                }
            } else {
                _hidl_out_wrapped_outStream = _hidl_out_outStream;
            }

            _hidl_cb(_hidl_out_retval, _hidl_out_wrapped_outStream, _hidl_out_suggestedConfig);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<void> openInputStream(int32_t ioHandle, const ::android::hardware::audio::V2_0::DeviceAddress& device, const ::android::hardware::audio::common::V2_0::AudioConfig& config, ::android::hardware::audio::common::V2_0::AudioInputFlag flags, ::android::hardware::audio::common::V2_0::AudioSource source, openInputStream_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::openInputStream::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&ioHandle);
            _hidl_args.push_back((void *)&device);
            _hidl_args.push_back((void *)&config);
            _hidl_args.push_back((void *)&flags);
            _hidl_args.push_back((void *)&source);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "openInputStream", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->openInputStream(ioHandle, device, config, flags, source, [&](const auto &_hidl_out_retval, const auto &_hidl_out_inStream, const auto &_hidl_out_suggestedConfig) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_retval);
                _hidl_args.push_back((void *)&_hidl_out_inStream);
                _hidl_args.push_back((void *)&_hidl_out_suggestedConfig);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "openInputStream", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            ::android::sp<::android::hardware::audio::V2_0::IStreamIn> _hidl_out_wrapped_inStream;
            if (_hidl_out_inStream != nullptr && !_hidl_out_inStream->isRemote()) {
                _hidl_out_wrapped_inStream = ::android::hardware::details::wrapPassthrough(_hidl_out_inStream);
                if (_hidl_out_wrapped_inStream == nullptr) {
                    _hidl_error = ::android::hardware::Status::fromExceptionCode(
                            ::android::hardware::Status::EX_TRANSACTION_FAILED,
                            "Cannot wrap passthrough interface.");
                    return;
                }
            } else {
                _hidl_out_wrapped_inStream = _hidl_out_inStream;
            }

            _hidl_cb(_hidl_out_retval, _hidl_out_wrapped_inStream, _hidl_out_suggestedConfig);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<bool> supportsAudioPatches() {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::supportsAudioPatches::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "supportsAudioPatches", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->supportsAudioPatches();

        #ifdef __ANDROID_DEBUGGABLE__
        bool _hidl_out_supports = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_supports);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "supportsAudioPatches", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> createAudioPatch(const ::android::hardware::hidl_vec<::android::hardware::audio::common::V2_0::AudioPortConfig>& sources, const ::android::hardware::hidl_vec<::android::hardware::audio::common::V2_0::AudioPortConfig>& sinks, createAudioPatch_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::createAudioPatch::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&sources);
            _hidl_args.push_back((void *)&sinks);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "createAudioPatch", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->createAudioPatch(sources, sinks, [&](const auto &_hidl_out_retval, const auto &_hidl_out_patch) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_retval);
                _hidl_args.push_back((void *)&_hidl_out_patch);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "createAudioPatch", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_retval, _hidl_out_patch);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> releaseAudioPatch(int32_t patch) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::releaseAudioPatch::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&patch);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "releaseAudioPatch", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->releaseAudioPatch(patch);

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "releaseAudioPatch", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> getAudioPort(const ::android::hardware::audio::common::V2_0::AudioPort& port, getAudioPort_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::getAudioPort::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&port);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "getAudioPort", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->getAudioPort(port, [&](const auto &_hidl_out_retval, const auto &_hidl_out_resultPort) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_retval);
                _hidl_args.push_back((void *)&_hidl_out_resultPort);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "getAudioPort", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_retval, _hidl_out_resultPort);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setAudioPortConfig(const ::android::hardware::audio::common::V2_0::AudioPortConfig& config) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::setAudioPortConfig::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&config);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "setAudioPortConfig", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->setAudioPortConfig(config);

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "setAudioPortConfig", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<uint32_t> getHwAvSync() {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::getHwAvSync::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "getHwAvSync", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->getHwAvSync();

        #ifdef __ANDROID_DEBUGGABLE__
        uint32_t _hidl_out_hwAvSync = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_hwAvSync);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "getHwAvSync", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setScreenState(bool turnedOn) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::setScreenState::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&turnedOn);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "setScreenState", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->setScreenState(turnedOn);

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "setScreenState", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> getParameters(const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& keys, getParameters_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::getParameters::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&keys);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "getParameters", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->getParameters(keys, [&](const auto &_hidl_out_retval, const auto &_hidl_out_parameters) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_retval);
                _hidl_args.push_back((void *)&_hidl_out_parameters);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "getParameters", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_retval, _hidl_out_parameters);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setParameters(const ::android::hardware::hidl_vec<::android::hardware::audio::V2_0::ParameterValue>& parameters) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::setParameters::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&parameters);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "setParameters", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->setParameters(parameters);

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "setParameters", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> debugDump(const ::android::hardware::hidl_handle& fd) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::debugDump::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&fd);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "debugDump", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->debugDump(fd);

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "debugDump", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }

    // Methods from ::android::hardware::audio::V2_0::IPrimaryDevice follow.
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setVoiceVolume(float volume) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::setVoiceVolume::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&volume);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "setVoiceVolume", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->setVoiceVolume(volume);

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "setVoiceVolume", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setMode(::android::hardware::audio::common::V2_0::AudioMode mode) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::setMode::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&mode);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "setMode", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->setMode(mode);

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "setMode", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> getBtScoNrecEnabled(getBtScoNrecEnabled_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::getBtScoNrecEnabled::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "getBtScoNrecEnabled", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->getBtScoNrecEnabled([&](const auto &_hidl_out_retval, const auto &_hidl_out_enabled) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_retval);
                _hidl_args.push_back((void *)&_hidl_out_enabled);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "getBtScoNrecEnabled", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_retval, _hidl_out_enabled);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setBtScoNrecEnabled(bool enabled) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::setBtScoNrecEnabled::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&enabled);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "setBtScoNrecEnabled", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->setBtScoNrecEnabled(enabled);

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "setBtScoNrecEnabled", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> getBtScoWidebandEnabled(getBtScoWidebandEnabled_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::getBtScoWidebandEnabled::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "getBtScoWidebandEnabled", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->getBtScoWidebandEnabled([&](const auto &_hidl_out_retval, const auto &_hidl_out_enabled) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_retval);
                _hidl_args.push_back((void *)&_hidl_out_enabled);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "getBtScoWidebandEnabled", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_retval, _hidl_out_enabled);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setBtScoWidebandEnabled(bool enabled) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::setBtScoWidebandEnabled::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&enabled);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "setBtScoWidebandEnabled", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->setBtScoWidebandEnabled(enabled);

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "setBtScoWidebandEnabled", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> getTtyMode(getTtyMode_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::getTtyMode::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "getTtyMode", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->getTtyMode([&](const auto &_hidl_out_retval, const auto &_hidl_out_mode) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_retval);
                _hidl_args.push_back((void *)&_hidl_out_mode);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "getTtyMode", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_retval, _hidl_out_mode);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setTtyMode(::android::hardware::audio::V2_0::IPrimaryDevice::TtyMode mode) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::setTtyMode::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&mode);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "setTtyMode", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->setTtyMode(mode);

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "setTtyMode", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> getHacEnabled(getHacEnabled_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::getHacEnabled::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "getHacEnabled", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->getHacEnabled([&](const auto &_hidl_out_retval, const auto &_hidl_out_enabled) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_retval);
                _hidl_args.push_back((void *)&_hidl_out_enabled);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "getHacEnabled", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_retval, _hidl_out_enabled);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<::android::hardware::audio::V2_0::Result> setHacEnabled(bool enabled) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::setHacEnabled::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&enabled);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "setHacEnabled", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->setHacEnabled(enabled);

        #ifdef __ANDROID_DEBUGGABLE__
        ::android::hardware::audio::V2_0::Result _hidl_out_retval = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_retval);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "setHacEnabled", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    ::android::hardware::Return<void> interfaceChain(interfaceChain_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::interfaceChain::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "interfaceChain", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->interfaceChain([&](const auto &_hidl_out_descriptors) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_descriptors);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "interfaceChain", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_descriptors);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::debug::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&fd);
            _hidl_args.push_back((void *)&options);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "debug", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->debug(fd, options);

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "debug", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::interfaceDescriptor::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "interfaceDescriptor", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->interfaceDescriptor([&](const auto &_hidl_out_descriptor) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_descriptor);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "interfaceDescriptor", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_descriptor);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<void> getHashChain(getHashChain_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::getHashChain::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "getHashChain", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->getHashChain([&](const auto &_hidl_out_hashchain) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_hashchain);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "getHashChain", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_hashchain);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<void> setHALInstrumentation() {
        configureInstrumentation();
        return ::android::hardware::Void();
    }

    ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::linkToDeath::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&recipient);
            _hidl_args.push_back((void *)&cookie);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "linkToDeath", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->linkToDeath(recipient, cookie);

        #ifdef __ANDROID_DEBUGGABLE__
        bool _hidl_out_success = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_success);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "linkToDeath", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> ping() {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::ping::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "ping", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->ping();

        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "ping", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }
    ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) {
        if (_hidl_cb == nullptr) {
            return ::android::hardware::Status::fromExceptionCode(
                    ::android::hardware::Status::EX_ILLEGAL_ARGUMENT,
                    "Null synchronous callback passed.");
        }

        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::getDebugInfo::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "getDebugInfo", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->getDebugInfo([&](const auto &_hidl_out_info) {
            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                _hidl_args.push_back((void *)&_hidl_out_info);
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "getDebugInfo", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

            _hidl_cb(_hidl_out_info);
        });

        return _hidl_return;
    }
    ::android::hardware::Return<void> notifySyspropsChanged() {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::notifySyspropsChanged::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "notifySyspropsChanged", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = addOnewayTask([mImpl = this->mImpl
        #ifdef __ANDROID_DEBUGGABLE__
        , mEnableInstrumentation = this->mEnableInstrumentation, mInstrumentationCallbacks = this->mInstrumentationCallbacks
        #endif // __ANDROID_DEBUGGABLE__
        ] {
            mImpl->notifySyspropsChanged();

            atrace_end(ATRACE_TAG_HAL);
            #ifdef __ANDROID_DEBUGGABLE__
            if (UNLIKELY(mEnableInstrumentation)) {
                std::vector<void *> _hidl_args;
                for (const auto &callback: mInstrumentationCallbacks) {
                    callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "notifySyspropsChanged", &_hidl_args);
                }
            }
            #endif // __ANDROID_DEBUGGABLE__

        });
        return _hidl_return;
    }
    ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) {
        atrace_begin(ATRACE_TAG_HAL, "HIDL::IPrimaryDevice::unlinkToDeath::passthrough");
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&recipient);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_ENTRY, "android.hardware.audio", "2.0", "IPrimaryDevice", "unlinkToDeath", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        auto _hidl_error = ::android::hardware::Void();
        auto _hidl_return = mImpl->unlinkToDeath(recipient);

        #ifdef __ANDROID_DEBUGGABLE__
        bool _hidl_out_success = _hidl_return;
        #endif // __ANDROID_DEBUGGABLE__
        atrace_end(ATRACE_TAG_HAL);
        #ifdef __ANDROID_DEBUGGABLE__
        if (UNLIKELY(mEnableInstrumentation)) {
            std::vector<void *> _hidl_args;
            _hidl_args.push_back((void *)&_hidl_out_success);
            for (const auto &callback: mInstrumentationCallbacks) {
                callback(InstrumentationEvent::PASSTHROUGH_EXIT, "android.hardware.audio", "2.0", "IPrimaryDevice", "unlinkToDeath", &_hidl_args);
            }
        }
        #endif // __ANDROID_DEBUGGABLE__

        return _hidl_return;
    }

private:
    const ::android::sp<IPrimaryDevice> mImpl;
    ::android::hardware::details::TaskRunner mOnewayQueue;

    ::android::hardware::Return<void> addOnewayTask(std::function<void(void)>);

};

}  // namespace V2_0
}  // namespace audio
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_AUDIO_V2_0_BSPRIMARYDEVICE_H
