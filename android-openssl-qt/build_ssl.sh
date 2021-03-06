#!/bin/bash

VERSION=1.1.1d
export ANDROID_NDK_HOME=/home/bensuperpc/android-ndk-r20/
ANDROID_API=21

if [ ! -f "openssl-$VERSION.tar.gz" ]; then
    wget https://www.openssl.org/source/openssl-$VERSION.tar.gz
fi

for arch in "x86_64" "x86" "arm64" "arm"
do
    rm -fr $arch
    mkdir $arch
    rm -fr openssl-$VERSION
    tar xfa openssl-$VERSION.tar.gz
    cd openssl-$VERSION

    case $arch in
        arm)
            ANDROID_API=21
            ;;
        x86)
            ANDROID_API=21
            ;;
        arm64)
            ANDROID_API=21
            ;;
        x86_64)
            ANDROID_API=21
            ;;
    esac
    ANDROID_TOOLCHAIN=""
    for host in "linux-x86_64" "linux-x86" "darwin-x86_64" "darwin-x86"
    do
        if [ -d "$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/$host/bin" ]; then
            ANDROID_TOOLCHAIN="$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/$host/bin"
            break
        fi
    done

    export PATH="$ANDROID_TOOLCHAIN":"$PATH"

    ./Configure shared android-${arch} -D__ANDROID_API__=${ANDROID_API} || exit 1
    make depend
    make -j$(nproc) SHLIB_VERSION_NUMBER= SHLIB_EXT=.so build_libs || exit 1
    llvm-strip -strip-all libcrypto.so
    llvm-strip -strip-all libssl.so
    cp libcrypto.so ../$arch
    cp libssl.so ../$arch
    cd ..
done
