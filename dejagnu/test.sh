#!/usr/bin/env bash
set -o errexit
set -o nounset

# Find GNU Make
if type gmake > /dev/null 2>&1 ; then
        gmake=gmake
else
        gmake=make
fi

SCRIPTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ASDFTOP="$( readlink -f "${SCRIPTDIR}/..")"

pushd $ASDFTOP/build-gcc/gcc
DEJAGNU=$ASDFTOP/dejagnu/dejagnurc $gmake -j4 check-gcc//vamos/{-m68000,-m68020/-msoft-float}
popd

echo "----"
echo "Test log files:"
find $ASDFTOP/build-gcc/gcc/testsuite* -name gcc.sum -o -name gcc.log

