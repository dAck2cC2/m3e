/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#include <utils/String8.h>
#include <binder/IServiceManager.h>
#include <drm/DrmManagerClient.h>

//#include "DrmManagerClientImpl.h"

using namespace android;

DrmManagerClient::DrmManagerClient() {
}

DrmManagerClient::~DrmManagerClient() {

}

status_t DrmManagerClient::setOnInfoListener(
                    const sp<DrmManagerClient::OnInfoListener>& infoListener) {
    return NO_ERROR;
}

DrmConstraints* DrmManagerClient::getConstraints(const String8* path, const int action) {
    return NULL;
}

DrmMetadata* DrmManagerClient::getMetadata(const String8* path) {
    return NULL;
}

bool DrmManagerClient::canHandle(const String8& path, const String8& mimeType) {
    return false;
}

DrmInfoStatus* DrmManagerClient::processDrmInfo(const DrmInfo* drmInfo) {
    return NULL;
}

DrmInfo* DrmManagerClient::acquireDrmInfo(const DrmInfoRequest* drmInfoRequest) {
    return NULL;
}

status_t DrmManagerClient::saveRights(
        const DrmRights& drmRights, const String8& rightsPath, const String8& contentPath) {
    return NO_ERROR;
}

String8 DrmManagerClient::getOriginalMimeType(const String8& path, int fd) {
    return path;
}

int DrmManagerClient::getDrmObjectType(const String8& path, const String8& mimeType) {
    return 0;
}

int DrmManagerClient::checkRightsStatus(const String8& path, int action) {
    return 0;
}

status_t DrmManagerClient::consumeRights(
            sp<DecryptHandle> &decryptHandle, int action, bool reserve) {
    return NO_ERROR;
}

status_t DrmManagerClient::setPlaybackStatus(
            sp<DecryptHandle> &decryptHandle, int playbackStatus, int64_t position) {
    return NO_ERROR;
}

bool DrmManagerClient::validateAction(
            const String8& path, int action, const ActionDescription& description) {
    return false;
}

status_t DrmManagerClient::removeRights(const String8& path) {
    return NO_ERROR;
}

status_t DrmManagerClient::removeAllRights() {
    return NO_ERROR;
}

int DrmManagerClient::openConvertSession(const String8& mimeType) {
    return 0;
}

DrmConvertedStatus* DrmManagerClient::convertData(int convertId, const DrmBuffer* inputData) {
    return NULL;
}

DrmConvertedStatus* DrmManagerClient::closeConvertSession(int convertId) {
    return NULL;
}

status_t DrmManagerClient::getAllSupportInfo(int* length, DrmSupportInfo** drmSupportInfoArray) {
    return NO_ERROR;
}

sp<DecryptHandle> DrmManagerClient::openDecryptSession(
        int fd, off64_t offset, off64_t length, const char* mime) {

    return NULL;
}

sp<DecryptHandle> DrmManagerClient::openDecryptSession(
        const char* uri, const char* mime) {

    return NULL;
}

sp<DecryptHandle> DrmManagerClient::openDecryptSession(
            const DrmBuffer& buf, const String8& mimeType) {
    return NULL;
}

status_t DrmManagerClient::closeDecryptSession(sp<DecryptHandle> &decryptHandle) {
    return NO_ERROR;
}

status_t DrmManagerClient::initializeDecryptUnit(
            sp<DecryptHandle> &decryptHandle, int decryptUnitId, const DrmBuffer* headerInfo) {
    return NO_ERROR;
}

status_t DrmManagerClient::decrypt(
            sp<DecryptHandle> &decryptHandle, int decryptUnitId,
            const DrmBuffer* encBuffer, DrmBuffer** decBuffer, DrmBuffer* IV) {
    return NO_ERROR;
}

status_t DrmManagerClient::finalizeDecryptUnit(
            sp<DecryptHandle> &decryptHandle, int decryptUnitId) {
    return NO_ERROR;
}

ssize_t DrmManagerClient::pread(
            sp<DecryptHandle> &decryptHandle, void* buffer, ssize_t numBytes, off64_t offset) {
    return NO_ERROR;
}

