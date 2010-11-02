This is my setup for [dwm](http://dwm.suckless.org). I keep a copy of upstream in the `upstream` branch, to which I fetch the lastest source every now and again. On `master`, I keep what I use on my computer. Here, I apply patches and edit my config.h and merge from `upstream`.

Since I use Arch Linux, I keep a PKGBUILD to build and install the package from the local source. `install.sh` is a small helper that updates the version number if needed, and cleans up the directory after `makepkg`.
