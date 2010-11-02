#!/bin/bash

makepkg -f -i
rm -rf pkg
rm *.pkg.tar.xz
