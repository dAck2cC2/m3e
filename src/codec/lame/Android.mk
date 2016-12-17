###############################################################################
# 0.  You need lame(mp3 encoder) at first. You can download source code 
#     from the website below, and build "libmp3lame.a" on your platform.
# 
#     http://lame.sourceforge.net/
# 
# 1.  Copy the header files to the "src/codec/lame/include" directory.
#
# 2.  Copy the "libmp3lame.a" to the "src/codec/lame/lib" directory.
#
###############################################################################

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libmp3lame
LOCAL_MODULE_STEM := libmp3lame.a
LOCAL_SRC_FILES := lib/libmp3lame.a
LOCAL_MODULE_CLASS := STATIC_LIBRARIES

LOCAL_NOTICE_FILE := LICENSE


include $(BUILD_PREBUILT)
include $(BUILD_NOTICE_FILE)
