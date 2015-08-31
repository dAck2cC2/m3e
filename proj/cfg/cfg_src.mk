#
#  Created by Jeremy on 2015-08-08.
#  Copyright 2015. All rights reserved.  
#

# **************************************
# Source Path and Code
# **************************************

SRC_DIR := ../../src

CSRC += utils/atomic.c \
        utils/log.c

CPPSRC += main.cpp \
          engine/CEngineFactory.cpp \
          utils/RefBase.cpp \
          utils/SharedBuffer.cpp \
          utils/VectorImpl.cpp \
          utils/String8.cpp \
          utils/Unicode.cpp \
          utils/Static.cpp \
          utils/Timers.cpp \
          utils/Threads.cpp \
          utils/hexdump.cpp \
          utils/AString.cpp \
          utils/ABuffer.cpp \
          utils/AAtomizer.cpp \
          utils/AMessage.cpp \
          utils/AHandler.cpp \
          utils/ALooper.cpp \
          utils/ALooperRoster.cpp \
          omxil/SoftOMXComponent.cpp \
          omxil/SimpleSoftOMXComponent.cpp \
          media/CPathScanner.cpp \
          media/CMediaFileScanner.cpp \
          media/CDataSource.cpp \
          media/CFileSource.cpp \
          media/CFileSink.cpp \
          media/MediaSource.cpp \
          media/MediaDefs.cpp \
          media/MetaData.cpp \
          media/MediaExtractor.cpp \
          media/MediaBuffer.cpp \
          media/MediaBufferGroup.cpp \
          media/WAVExtractor.cpp \
          media/MediaCodecList.cpp \
          impl/CEngineAnalyzer.cpp \
          impl/CEngineMonitor.cpp \
          impl/CAsyncEncoder.cpp \
          impl/CAsyncEncoderGroup.cpp \
          impl/CEncoderClient.cpp \
          impl/CEncoderLame.cpp 
          
# **************************************
# Build Path
# **************************************
          
BUILD_DIR += $(BUILD_ROOT)/engine \
             $(BUILD_ROOT)/utils \
             $(BUILD_ROOT)/media \
             $(BUILD_ROOT)/omxil \
             $(BUILD_ROOT)/impl

