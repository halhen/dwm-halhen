#!/bin/bash

die() {
    echo "$@" >&2
    exit 1
}

setup_builddir() {
    tmpdir=$(mktemp -d)
    trap "rm -rf \"$tmpdir\"" EXIT

    cp -r * "$tmpdir" || die "Failed to copy files to tmpdir"
    cd "$tmpdir" || die "Failed to cd to tmpdir"
}

apply_patches() {
    cd src
    for patchfile in ../patch/*; do
        echo "Applying $(basename "$patchfile")"
        patch -p1 <"$patchfile" || die "Failed to apply $patchfile"
    done
    cd ..
}

build_install() {
    _version=$(sed -n 's/VERSION = \(.*\)/\1/p' src/config.mk)
    sed -i "s/pkgver=.*/pkgver=$_version/" PKGBUILD

    echo "Building version $_version"

    makepkg -f -i
    rm -rf pkg
    rm -rf build
    rm *.pkg.tar.xz
}

# Go home
cd "$(dirname "$0")"

setup_builddir
apply_patches
build_install
