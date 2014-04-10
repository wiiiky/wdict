## Process this file with automake to produce Makefile.in

## Created by Anjuta



AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	-DPACKAGE_BUILD_DIR=\""$(builddir)"\" \
	$(WDICT_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = wdict


wdict_SOURCES =  \
	main.c \
	wldictwindow.c \
	wldictwindow.h \
	wldictquery.c \
	wldictquery.h

wdict_LDFLAGS = \
	-Wl,--export-dynamic

wdict_LDADD = $(WDICT_LIBS)




