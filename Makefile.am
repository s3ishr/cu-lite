# This is the auto-Makefile for Taylor UUCP
# This is processed by automake to create Makefile.in.

SUBDIRS = lib uuconf unix

bin_PROGRAMS = cu
info_TEXINFOS = uucp.texi
man_MANS = cu.1

# If you do not have the mkdir system call, this will install uudir as
# an suid root program.  This is necessary because invoking /bin/mkdir
# from an suid program will leave the directories owned by the wrong
# user.
if HAVE_MKDIR
uudirdir =
uudir_PROGRAMS =
else
uudirdir = $(sbindir)/util
uudir_PROGRAMS = uudir
endif

AM_CFLAGS = $(WARN_CFLAGS) $(UUDIRFLAGS)

LDADD = unix/libunix.a uuconf/libuuconf.a lib/libuucp.a

UUHEADERS = uucp.h uudefs.h uuconf.h policy.h system.h sysdep.h getopt.h

cu_SOURCES = cu.h cu.c prot.c log.c chat.c conn.c copy.c $(UUHEADERS)

uuconv_CFLAGS = -I$(srcdir)/uuconf $(AM_CFLAGS)

EXTRA_DIST = cu.1 contrib sample

dist-hook:
	-rm -rf $(distdir)/contrib/CVS $(distdir)/sample/CVS

install-exec-hook:
	for f in uucp cu; do \
	  chown $(OWNER) $(DESTDIR)$(bindir)/$${f}; \
	  chmod 4555 $(DESTDIR)$(bindir)/$${f}; \
	done
if HAVE_MKDIR
else
	chown $(OWNER) $(DESTDIR)$(uudirdir)
	chmod 100 $(DESTDIR)$(uudirdir)
	chown root $(DESTDIR)$(uudirdir)/uudir
	chmod 4555 $(DESTDIR)$(uudirdir)/uudir
endif
