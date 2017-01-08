#!/bin/bash


TARGET_TAG="android-7.1.0_r7"

TARGET_DIR="\
build \
external/expat \
frameworks/av \
frameworks/native \
frameworks/rs \
frameworks/compile/slang \
hardware/libhardware \
system/core \
system/media \
system/netd \
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
  #git pull
  git checkout tags/$TARGET_TAG
  cd -
done

