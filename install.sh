#!/bin/bash

_version=$(sed -n 's/VERSION = \(.*\)/\1/p' src/config.mk)
sed -i "s/pkgver=.*/pkgver=$_version/" PKGBUILD

echo "Building version $_version"

makepkg -f -i
rm -rf pkg
rm *.pkg.tar.xz
