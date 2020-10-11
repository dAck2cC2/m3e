
#ifndef IMPL_HIDL_MANAGER_V1_1_ISERVICEMANAGER_H
#define IMPL_HIDL_MANAGER_V1_1_ISERVICEMANAGER_H

#include <utils/Mutex.h>
#include <utils/KeyedVector.h>

#include <hidl/Status.h>
#include <android/hidl/manager/1.1/IServiceManager.h>

namespace android {
namespace hidl {
namespace manager {
namespace V1_1 {

struct ImplServiceManager : public IServiceManager
{
public:
	virtual ::android::hardware::Return<::android::sp<::android::hidl::base::V1_0::IBase>> get(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name) override
	{
		ALOGI("Get service : %s, %s", fqName.c_str(), name.c_str());

		::std::string strName(name.c_str());
		::std::string strFQ(fqName.c_str());
		::std::string strFull = strName + "@" + strFQ;
		::android::hardware::hidl_string fullName(strFull.c_str());

		::android::AutoMutex _l(mLockAPI);

		if (mServices.indexOfKey(fullName) < 0) {
			ALOGE("No service of %s", fullName.c_str());
			return nullptr;
		}

		return mServices.valueFor(fullName);;
	} // get

	virtual ::android::hardware::Return<bool> add(const ::android::hardware::hidl_string& name, const ::android::sp<::android::hidl::base::V1_0::IBase>& service) override
	{
		LOG_ALWAYS_FATAL_IF((service == nullptr), "Invalid service !");

		::android::hardware::hidl_string fqName;
		service->interfaceChain(
			[&](const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& descriptors)
			{
				/* for DEBUG
				for (::android::hardware::hidl_string desc : descriptors) {
					ALOGD("%s", desc.c_str());
				}
				*/

				fqName = descriptors[0];
			});

		::std::string strName(name.c_str());
		::std::string strFQ(fqName.c_str());
		::std::string strFull = strName + "@" + strFQ;
		::android::hardware::hidl_string fullName(strFull.c_str());

		::android::AutoMutex _l(mLockAPI);

		LOG_ALWAYS_FATAL_IF((mServices.indexOfKey(fullName) >= 0), "service of %s already exists", fullName.c_str());

		if (mServices.add(fullName, service) < 0) {
			LOG_ALWAYS_FATAL("failed to add service");
			return false;
		}

		return true;
	} // add

	virtual ::android::hardware::Return<::android::hidl::manager::V1_0::IServiceManager::Transport> getTransport(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name) override
	{
		return Transport::EMPTY;
	} // getTransport

	virtual ::android::hardware::Return<void> list(list_cb _hidl_cb) override
	{
		return android::hardware::Void();
	} // list

	virtual ::android::hardware::Return<void> listByInterface(const ::android::hardware::hidl_string& fqName, listByInterface_cb _hidl_cb) override
	{
		return android::hardware::Void();
	} // listByInterface

	virtual ::android::hardware::Return<bool> registerForNotifications(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name, const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification>& callback) override
	{
		return false;
	} // registerForNotifications

	virtual ::android::hardware::Return<void> debugDump(debugDump_cb _hidl_cb) override
	{
		return android::hardware::Void();
	} // debugDump

	virtual ::android::hardware::Return<void> registerPassthroughClient(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name) override
	{
		return android::hardware::Void();

	} // registerPassthroughClient

	virtual ::android::hardware::Return<bool> unregisterForNotifications(const ::android::hardware::hidl_string& fqName, const ::android::hardware::hidl_string& name, const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification>& callback) override
	{
		return false;
	} // unregisterForNotifications


private:
	::android::Mutex  mLockAPI;
	::android::KeyedVector< ::android::hardware::hidl_string, ::android::sp<::android::hidl::base::V1_0::IBase> > mServices;
}; // ImplServiceManager

}  // namespace V1_1
}  // namespace manager
}  // namespace hidl
}  // namespace android

#endif // IMPL_HIDL_MANAGER_V1_1_ISERVICEMANAGER_H
