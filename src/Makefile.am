irc_nomodedir = $(PURPLE_LIBDIR)

irc_nomode_la_LDFLAGS = -module -avoid-version

if HAVE_PURPLE

irc_nomode_LTLIBRARIES = irc-nomode.la

irc_nomode_la_SOURCES = \
	irc-nomode.c

irc_nomode_la_LIBADD = \
	$(PURPLE_LIBS) \
	$(GLIB_LIBS)

endif

AM_CPPFLAGS = \
	-DLIBDIR=\"$(PURPLE_LIBDIR)\" \
	-DDATADIR=\"$(PURPLE_DATADIR)\" \
	$(GLIB_CFLAGS) \
	$(DEBUG_CFLAGS) \
	$(PURPLE_CFLAGS)
