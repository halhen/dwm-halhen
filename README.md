This is my setup for [dwm](http://dwm.suckless.org). In src/, the original dwm source is kept. It can be updated through `./pull_upstream.h`. Changes to vanilla dwm are kept as individual patches in `patch/`.

My version updates the status bar internally (`status-bar.patch`). Here, I keep some stuff like a clock and battery life. This is appended to the regular status message, set through the X root window name, and is updated regularly internally.

Since I use Arch Linux, I keep a PKGBUILD to build and install the package from the local source. `install.sh` is a small helper that updates the version number if needed, copies all source to a temporary directory, applies the patches in patch/, and finally builds and installs everything.
