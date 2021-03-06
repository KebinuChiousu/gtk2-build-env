## Process this file with automake to produce Makefile.in

INCLUDES = -I$(top_srcdir) -I$(top_srcdir)/gmodule \
	-DG_LOG_DOMAIN=g_log_domain_gmodule @GLIB_DEBUG_FLAGS@

EXTRA_DIST =	\
		gmoduleconf.h.in \
		gmodule.def	\
		gmodule-dl.c	\
		gmodule-dld.c	\
		gmodule-win32.c	\
		gmoduleconf.h.win32

BUILT_SOURCES = gmoduleconf.h
gmoduleconf.h:	gmoduleconf.h.in

noinst_HEADERS = \
		gmodule.h

libglib = $(top_builddir)/libglib.la # -lglib

noinst_LTLIBRARIES = libgmodule.la libgplugin_a.la libgplugin_b.la

libgmodule_la_SOURCES = gmodule.c
libgmodule_la_LDFLAGS = \
	@G_MODULE_LDFLAGS@ \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
	-release $(LT_RELEASE) \
	-export-dynamic

libgmodule_la_LIBADD = @G_MODULE_LIBS@ # $(libglib)
# we should really depend on $(libglib) for libgmodule.la, but libtool has a
# problem with this ;(

libgplugin_a_la_SOURCES = libgplugin_a.c
libgplugin_a_la_LDFLAGS = @G_MODULE_LDFLAGS@ -avoid-version -module
libgplugin_a_la_LIBADD = @G_MODULE_LIBS@ # $(libglib)

libgplugin_b_la_SOURCES = libgplugin_b.c
libgplugin_b_la_LDFLAGS = @G_MODULE_LDFLAGS@ -avoid-version -module
libgplugin_b_la_LIBADD = @G_MODULE_LIBS@ # $(libglib)

noinst_PROGRAMS = testgmodule
testgmodule_LDFLAGS = @G_MODULE_LDFLAGS@
testgmodule_LDADD = libgmodule.la $(libglib) @G_MODULE_LIBS@

.PHONY: files release

files:
	@files=`ls $(DISTFILES) 2> /dev/null `; for p in $$files; do \
	  echo $$p; \
	done

install-libLTLIBRARIES: libgmodule.la
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(libdir)
	@list='libgmodule.la'; for p in $$list; do \
	 if test -f $$p; then \
	  echo "$(LIBTOOL)  --mode=install $(noinst_DATA) $$p $(DESTDIR)$(libdir)/$$p"; \
	  $(LIBTOOL)  --mode=install $(noinst_DATA) $$p $(DESTDIR)$(libdir)/$$p; \
	 else :; fi; \
	done

release:
	$(MAKE) dist distdir=$(PACKAGE)`date +"%y%m%d"`
