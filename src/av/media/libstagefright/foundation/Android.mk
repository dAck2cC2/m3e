LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:=                 \
    AAtomizer.cpp                 \
    ABitReader.cpp                \
    ABuffer.cpp                   \
    ADebug.cpp                    \
    AHandler.cpp                  \
    AHierarchicalStateMachine.cpp \
    ALooper.cpp                   \
    ALooperRoster.cpp             \
    AMessage.cpp                  \
    AString.cpp                   \
    AStringUtils.cpp              \
    ColorUtils.cpp                \
    MediaBuffer.cpp               \
    MediaBufferGroup.cpp          \
    MetaData.cpp                  \
    ParsedMessage.cpp             \
    base64.cpp                    \
    hexdump.cpp

#ANetworkSession.cpp	\
#AWakeLock.cpp                 \

LOCAL_C_INCLUDES:= \
    src/native/include \
    src/av/external \
    src/av/include \
    src/av/include/media/stagefright/foundation

LOCAL_SHARED_LIBRARIES := \
    libutils \
    libmisc


LOCAL_CFLAGS += -Wno-multichar -Wno-attributes -Wall
LOCAL_CLANG := true
#LOCAL_SANITIZE := unsigned-integer-overflow signed-integer-overflow

LOCAL_MODULE:= libstagefright_foundation

ifdef BUILD_CYGWIN
LOCAL_NO_PIC := true
endif


include $(BUILD_SHARED_LIBRARY)
