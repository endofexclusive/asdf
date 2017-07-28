#!/usr/bin/env bash

set -o errexit
set -o nounset

HERE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

SIM="fs-uae $HERE/a500.fs-uae"

usage() {
    echo "USAGE: $(basename $0) HUNKFILE"
}

if [[ $# -lt 1 ]]; then
    usage
    exit 1
fi

hunkfile="$1"
if [ ! -f $hunkfile ]; then
        echo "$hunkfile: no such file"
        exit 1
fi

hunkfile=`readlink -f $hunkfile`
rm -f $HERE/fs/test
ln -s $hunkfile $HERE/fs/test
$SIM

