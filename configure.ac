
AC_INIT([src/main.cpp])
AM_INIT_AUTOMAKE([gamediameter], [0.4.0])

#CFLAGS=""
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
#cpu="`uname -m`"
#if test $cpu == "x86_64"; then
#    cpu="x86-64"
#fi
#CFLAGS="$CFLAGS -Wall -march=$cpu"
AM_CONFIG_HEADER(config.h)

if test x"${prefix}" = x"NONE"; then
    AC_DEFINE_UNQUOTED(PREFIX,"$ac_default_prefix","prefix to files")
else
    AC_DEFINE_UNQUOTED(PREFIX,"$prefix","prefix to files")
fi

case "$target" in *-*-cygwin* | *-*-mingw32*) pkgdatadir="data/" ;; *) ;;
esac
CFLAGS="$CFLAGS -DPKGDATADIR='\"\$(pkgdatadir)/\"'"



#AC_PYTHON_DEVEL
CFLAGS="$CFLAGS $PYTHON_CPPFLAGS -I/usr/include/python2.7/"
LIBS="$LIBS $PYTHON_LDFLAGS $PYTHON_EXTRA_LIBS -lpython2.7 -lpthread -ldl -lutil -lm"

#AC_CHECK_LIB(SDL, SDL_Init, have_SDL=yes)
#if test x$have_SDL != xyes; then
#     AC_MSG_ERROR([*** SDL library not found!
#Try: http://www.libsdl.org/
#])
#fi
LIBS="$LIBS `sdl-config --libs`"
CXXFLAGS="$CFLAGS `sdl-config --cflags`"
LIBS="$LIBS $SDL_LIBS"

#AC_CHECK_LIB(png,png_read_image, [], [
#        echo "libpng required!"
#        exit -1
#        ])
#PKG_CHECK_MODULES(LIBPNG, libpng >= 1.2.8)

AC_CHECK_LIB(SDL_image, IMG_Load, have_SDL_image=yes)
#if test x$have_SDL_image != xyes; then
#    AC_MSG_ERROR([*** SDL_image library not found!
#Try: http://www.libsdl.org/projects/SDL_image/
#])

#fi
LIBS="$LIBS -lSDL_image"

AC_CHECK_LIB(SDL_mixer, Mix_OpenAudio, have_SDL_mixer=yes)
#if test x$have_SDL_mixer != xyes; then
#    AC_MSG_ERROR([*** SDL_mixer library not found!
#Try: http://www.libsdl.org/projects/SDL_mixer/
#])
#fi
LIBS="$LIBS -lSDL_mixer"

LIBS="$LIBS -L/usr/X11R6/lib/"
AC_CHECK_LIB(GL, glFlush, have_GL=yes)
if test x$have_GL != xyes; then
    AC_MSG_ERROR([*** OpenGL library not found!
Try: http://www.opengl.org/ or http://www.mesa3d.org/
])
fi
LIBS="$LIBS -lGL"

AC_CHECK_LIB(GLU, gluPerspective, have_GLU=yes)
if test x$have_GLU != xyes; then
    AC_MSG_ERROR([*** GLU library not found!
Try: http://www.opengl.org/ or http://www.mesa3d.org/
])
fi
LIBS="$LIBS -lGLU"

#PKG_CHECK_MODULES(LIBGUICHAN, libguichan >= 0.4)
AC_CHECK_LIB(guichan, main, have_guichan=yes)
if test x$have_guichan != xyes; then
    AC_MSG_ERROR([*** guichan library not found!
Try: http://guichan.sf.net
])
fi
LIBS="$LIBS -lguichan"

AC_CHECK_LIB(guichan_sdl, main, have_guichan=yes)
if test x$have_guichan != xyes; then
    AC_MSG_ERROR([*** guichan_sdl library not found!
Try: http://guichan.sf.net
])
fi
LIBS="$LIBS -lguichan_sdl"

AC_CHECK_LIB(guichan_opengl, main, have_guichan=yes)
if test x$have_guichan != xyes; then
    AC_MSG_ERROR([*** guichan_opengl library not found!
Try: http://guichan.sf.net
])
fi
LIBS="$LIBS -lguichan_opengl"

#LIBS="$LIBS -lXext -lXmu -lX11 -lm"
AC_OUTPUT([Makefile src/Makefile data/Makefile data/world/Makefile \
data/fonts/Makefile data/models/Makefile data/models/Rockets/Makefile \
data/models/Ships/Makefile data/models/Ships/ship2/Makefile \
data/models/Ships/ship3/Makefile data/models/Ships/ship4/Makefile \
data/music/Makefile data/music/sample/Makefile \
data/sprites/Makefile data/texture/Makefile \
data/texture/Rockets/Makefile data/texture/ship1/Makefile \
data/texture/ship2/Makefile data/texture/ship3/Makefile \
data/texture/ship4/Makefile data/texture/gui/Makefile \
data/texture/gui/curs/Makefile data/texture/gui/curs/weapons/Makefile \
data/texture/gui/eng/Makefile data/texture/gui/eng/main/Makefile \
data/texture/gui/rus/Makefile data/texture/gui/rus/main/Makefile \
data/texture/gui/other/Makefile \
data/pyscripts/Makefile])