#!/usr/bin/env bash
#
# This script downloads and installs Native Developer Kit for AmigaOS 3.9 from
# "HAAGE & PARTNER". Files are put in the script directory.
#
# Use "$0 force" to remove old files and re-download.

set -o errexit
set -o nounset
EXTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

NDK_VER=3.9
NDK_FILE=ndk-3.9.lha
NDK_URL=http://www.haage-partner.de/download/AmigaOS/NDK39.lha

do_force=${1-"keep"}
if [ $do_force = "force" ]; then
        echo "removing old files..."
        pushd $EXTDIR >/dev/null
        rm -rf ndk-$NDK_VER
        rm -f $NDK_FILE
        popd >/dev/null
fi

mustexist() {
    if ! hash $1 2>/dev/null; then
        echo "$0: '$1' is required to run this script (FAIL)"
        exit 1
    fi
}

mustexist lha
mustexist curl

pushd $EXTDIR >/dev/null
echo $0: "Installing NDK in $EXTDIR"

if [ ! -f $NDK_FILE ]; then
        curl -R -o $NDK_FILE $NDK_URL
fi

if [ ! -d ndk-$NDK_VER ]; then
        lha x $NDK_FILE > /dev/null
        # fixup ndk filenames
        mv NDK_$NDK_VER ndk-$NDK_VER
        mv ndk_$NDK_VER/* ndk-$NDK_VER
        rmdir ndk_$NDK_VER
        rm -f NDK_$NDK_VER.info
else
        echo "$0: directory exists (OK) $EXTDIR/ndk-$NDK_VER"
fi

popd > /dev/null

