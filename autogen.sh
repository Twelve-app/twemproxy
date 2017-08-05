#!/bin/sh
# please ensure the GNU autotools suite has been installed
# libtool autoconf automake
libtoolize --automake --copy --force
aclocal
autoheader
automake --add-missing --force-missing --copy
autoconf
