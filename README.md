This is my setup for [dwm](http://dwm.suckless.org). I keep a copy of upstream in the `upstream` branch, to which I fetch the lastest source every now and again. On `master`, I keep what I use on my computer. Here, I apply patches and edit my config.h and merge from `upstream`.

My version updates the status bar internally. Here, I keep some stuff like a clock and battery life. This is appended to the regular status message, set through the X root window name, and is updated regularly internally. The base functionality was built on the `builtin-status` branch, where you can see how it works and from which you can generate a patch.

Since I use Arch Linux, I keep a PKGBUILD to build and install the package from the local source. `install.sh` is a small helper that updates the version number if needed, and cleans up the directory after `makepkg`.
