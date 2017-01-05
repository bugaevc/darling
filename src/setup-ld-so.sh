#! /bin/bash

# This runs as root,
# with the current directory set to ${CMAKE_INSTALL_PREFIX}/libexec/darling

for file in /etc/ld.so.conf $(find /etc/ld.so.conf.d/ -type f); do
    # Copy lines from e.g. /etc/ld.so.conf into ./etc/ld.so.conf,
    # prepending "/Volumes/SystemRoot" to each line that starts with a slash
    awk '/^\// { print "/Volumes/SystemRoot" $0 }; /^[^/]/' $file > .$file
done

echo /Volumes/SystemRoot$1 > ./etc/ld.so.conf.d/z-darling.conf

unshare --mount bash -c "mount --rbind / Volumes/SystemRoot && ldconfig -r ."
