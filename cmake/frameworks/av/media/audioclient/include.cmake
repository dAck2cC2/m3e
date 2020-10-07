
DLL_PUBLIC(AUDIOCLIENT)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libaudioclient/include)

# for VolumeShaper.h which is included by IAudioTrack.h
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/include)

# for IAudioRecord.h
include_directories(AFTER ${TMP_PATH}/${AIDL_HEADER_PATH}/audioclient)
