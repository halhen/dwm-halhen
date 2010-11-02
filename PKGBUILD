# Adapted from the extra/dwm PKGBUILD
#
# Uses local files for installed. These local files
# are managed manually

pkgname=dwm-halhen
pkgver=5.8.2
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama')
provides=("dwm")
conflicts=("dwm")

build() {
  cp -R $startdir/src $startdir/build
  cd $startdir/build

  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 || return 1
  make PREFIX=/usr DESTDIR=$pkgdir install || return 1

  install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE && \
  install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README

  cd ..
  rm -rf build
}
