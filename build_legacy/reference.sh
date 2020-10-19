#!/bin/bash

TARGET_TAG="android-10.0.0_r45"

TARGET_DIR="\
frameworks/av \
frameworks/base \
frameworks/native \
frameworks/rs \
frameworks/compile/slang \
frameworks/wilhelm \
hardware/libhardware \
hardware/interfaces \
hardware/google/av \
hardware/google/interfaces \
system/core \
system/media \
system/netd \
system/libhidl \
system/libhwbinder \
system/libfmq \
system/tools/hidl \
system/tools/aidl \
libnativehelper \
"

TARGET_SRC="https://android.googlesource.com/platform"

for d in $TARGET_DIR
do
  if [ ! -d $d ] ; then
    mkdir -p $d
    cd $d/..
    git clone $TARGET_SRC/$d
    cd -
  fi
  cd $d
  pwd
  git checkout .
  git pull
  git checkout tags/$TARGET_TAG
  cd -
done

