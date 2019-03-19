#!/bin/bash
wget https://ftp.gtk.org/pub/gtk/v2.10/gtk+-2.10.14.tar.bz2
wget https://ftp.gtk.org/pub/gtk/v2.10/dependencies/atk-1.9.1.tar.bz2
wget https://ftp.gtk.org/pub/gtk/v2.10/dependencies/cairo-1.2.6.tar.gz
wget https://ftp.gtk.org/pub/gtk/v2.10/dependencies/jpegsrc.v6b.tar.gz
wget https://ftp.gtk.org/pub/gtk/v2.10/dependencies/pkg-config-0.20.tar.gz
wget https://ftp.gtk.org/pub/gtk/v2.10/dependencies/tiff-3.7.4.tar.gz
wget https://ftp.gtk.org/pub/glib/2.34/glib-2.34.0.tar.xz
wget https://ftp.gtk.org/pub/pango/1.21/pango-1.21.5.tar.gz
wget https://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.15.tar.gz
wget http://ftp.gnu.org/pub/gnu/gettext/gettext-0.19.tar.gz
wget https://www.freedesktop.org/software/fontconfig/release/fontconfig-2.13.1.tar.gz
wget https://download.savannah.gnu.org/releases/freetype/freetype-2.9.tar.gz
wget https://www.cairographics.org/releases/cairo-1.16.0.tar.xz
wget https://www.cairographics.org/releases/pixman-0.38.0.tar.gz

git clone --progress --verbose https://gitlab.gnome.org/GNOME/gobject-introspection.git
cd gobject-introspection
git checkout 1.59.5
cd ..

wget http://freedesktop.org/~hadess/shared-mime-info-1.10.tar.xz
wget https://download.sourceforge.net/libpng/libpng-1.6.36.tar.xz
