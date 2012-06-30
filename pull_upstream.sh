#!/bin/bash

die() {
    echo "$@" >&2
    exit 1
}

cd "$(dirname "$0")"
rootdir="$(pwd)"

type hg &>/dev/null || die "Must install mercurial"

tmpdir=$(mktemp -d)
trap "rm -rf \"$tmpdir\"" EXIT

cd "$tmpdir" || die "Can't cd to temp dir"
hg clone http://hg.suckless.org/dwm || die "Failed to clone dwm"

cd "$rootdir"/src || die "Failed to cd to project src directory"
cp -r "$tmpdir"/dwm/* . || die "Failed to copy files to src directory"

echo "Done"
