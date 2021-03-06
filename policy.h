/* policy.h
   Configuration file for policy decisions.  To be edited on site.

   Copyright (C) 1991, 1992, 1993, 1994, 1995 Ian Lance Taylor

   This file is part of the Taylor UUCP package.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA.

   The author of the program may be contacted at ian@airs.com.
   */

/* This header file contains macro definitions which must be set by
   each site before compilation.  The first few are system
   characteristics that can not be easily discovered by the
   configuration script.  Most are configuration decisions that must
   be made by the local administrator.  */

/* System characteristics.  */

/* This code tries to use several ANSI C features, including
   prototypes, stdarg.h, the const qualifier and the types void
   (including void * pointers) and unsigned char.  By default it will
   use these features if the compiler defines __STDC__.  If your
   compiler supports these features but does not define __STDC__, you
   should set ANSI_C to 1.  If your compiler does not support these
   features but defines __STDC__ (no compiler should do this, in my
   opinion), you should set ANSI_C to 0.  In most cases (or if you're
   not sure) just leave the line below commented out.  */
/* #define ANSI_C 1 */

/* Set USE_STDIO to 1 if data files should be read using the stdio
   routines (fopen, fread, etc.) rather than the UNIX unbuffered I/O
   calls (open, read, etc.).  Unless you know your stdio is really
   rotten, you should leave this as 1.  */
#define USE_STDIO 1

/* On some systems a write to a serial port will block even if the
   file descriptor has been set to not block.  File transfer can be
   more efficient if the package knows that a write to the serial port
   will not block; however, if the write does block unexpectedly then
   data loss is possible at high speeds.

   If writes to a serial port always block even when requested not to,
   you should set HAVE_UNBLOCKED_WRITES to 0; otherwise you should set
   it to 1.  In general on System V releases without STREAMS-based
   ttys (e.g., before SVR4) HAVE_UNBLOCKED_WRITES should be 0 and on
   modern systems it should be 1.

   If HAVE_UNBLOCKED_WRITES is set to 1 when it should be 0 you may
   see an unexpectedly large number of transmission errors, or, if you
   have hardware handshaking, transfer times may be lower than
   expected (but then, they always are).  If HAVE_UNBLOCKED_WRITES is
   set to 0 when it should be 1, file transfer will use more CPU time
   than necessary.  If you are unsure, setting HAVE_UNBLOCKED_WRITES
   to 0 should always be safe.  */
#define HAVE_UNBLOCKED_WRITES 1

/* When the code does do a blocking write, it wants to write the
   largest amount of data which the kernel will accept as a single
   unit.  On BSD this is typically the value of OBUFSIZ in
   <sys/tty.h>, usually 100.  On System V before SVR4 this is
   typically the size of a clist, CLSIZE in <sys/tty.h>, which is
   usually 64.  On SVR4, which uses STREAMS-based ttys, 2048 is
   reasonable.  Define SINGLE_WRITE to the correct value for your
   system.  If SINGLE_WRITE is too large, data loss may occur.  If
   SINGLE_WRITE is too small, file transfer will use more CPU time
   than necessary.  If you have no idea, 64 should work on most modern
   systems.  */
#define SINGLE_WRITE 64

/* Some tty drivers, such as those from SCO and AT&T's Unix PC, have a
   bug in the implementation of ioctl() that causes CLOCAL to be
   ineffective until the port is opened a second time.  If
   HAVE_CLOCAL_BUG is set to 1, code will be added to do this second
   open on the port.  Set this if you are getting messages that say
   "Line disconnected" while in the dial chat script after only
   writing the first few characters to the port.  This bug causes the
   resetting of CLOCAL to have no effect, so the "\m" (require
   carrier) escape sequence won't function properly in dialer chat
   scripts.  */
#define HAVE_CLOCAL_BUG 0

/* On some systems, such as SCO Xenix, resetting DTR on a port
   apparently prevents getty from working on the port, and thus
   prevents anybody from dialing in.  If HAVE_RESET_BUG is set to 1,
   DTR will not be reset when a serial port is closed.  */
#define HAVE_RESET_BUG 0

/* The Sony NEWS reportedly handles no parity by clearing both the odd
   and even parity bits in the sgtty structure, unlike most BSD based
   systems in which no parity is indicated by setting both the odd and
   even parity bits.  Setting HAVE_PARITY_BUG to 1 will handle this
   correctly.  */
#define HAVE_PARITY_BUG 0

#if HAVE_BSD_TTY
#ifdef sony
#undef HAVE_PARITY_BUG
#define HAVE_PARITY_BUG 1
#endif
#endif

/* On Ultrix 4.0, at least, setting CBREAK causes input characters to
   be stripped, regardless of the setting of LPASS8 and LLITOUT.  This
   can be worked around by using the termio call to reset ISTRIP.
   This probably does not apply to any other operating system.
   Setting HAVE_STRIP_BUG to 1 will use this workaround.  */
#define HAVE_STRIP_BUG 0

#if HAVE_BSD_TTY
#ifdef __ultrix__
#ifndef ultrix
#define ultrix
#endif
#endif
#ifdef ultrix
#undef HAVE_STRIP_BUG
#define HAVE_STRIP_BUG 1
#endif
#endif

/* If your system implements full duplex pipes, set
   HAVE_FULLDUPLEX_PIPES to 1.  Everything should work fine if you
   leave it set to 0, but setting it to 1 can be slightly more
   efficient.  */
#define HAVE_FULLDUPLEX_PIPES 0

/* TIMES_TICK is the fraction of a second which times(2) returns (for
   example, if times returns 100ths of a second TIMES_TICK should be
   set to 100).  On a true POSIX system (one which has the sysconf
   function and also has _SC_CLK_TCK defined in <unistd.h>) TIMES_TICK
   may simply be left as 0.  On some systems the environment variable
   HZ is what you want for TIMES_TICK, but on some other systems HZ
   has the wrong value; check the man page.  If you leave this set to
   0, the code will try to guess; it will doubtless be wrong on some
   non-POSIX systems.  If TIMES_TICK is wrong the code may report
   incorrect file transfer times in the statistics file, but on many
   systems times(2) will actually not be used and this value will not
   matter at all.  */
#define TIMES_TICK 0

/* If your system does not support saved set user ID, set
   HAVE_SAVED_SETUID to 0.  However, this is ignored if your system
   has the setreuid function.  Most modern Unixes have one or the
   other.  If your system has the setreuid function, don't worry about
   this define, or about the following discussion.

   If you set HAVE_SAVED_SETUID to 0, you will not be able to use uucp
   to transfer files that the uucp user can not read.  Basically, you
   will only be able to use uucp on world-readable files.  If you set
   HAVE_SAVED_SETUID to 1, but your system does not have saved set
   user ID, uucp will fail with an error message whenever anybody
   other than the uucp user uses it.  */
#define HAVE_SAVED_SETUID 1

/* On some systems, such as 4.4BSD-Lite, NetBSD, the DG Aviion and,
   possibly, the RS/6000, the setreuid function is broken.  It should
   be possible to use setreuid to swap the real and effective user
   ID's, but on some systems it will not change the real user ID (I
   believe this is due to a misreading of the POSIX standard).  On
   such a system you must set HAVE_BROKEN_SETREUID to 1; if you do
   not, you will get error messages from setreuid.  Systems on which
   setreuid exists but is broken pretty much always have saved setuid.  */
#define HAVE_BROKEN_SETREUID 0

/* On a few systems, such as NextStep 3.3, the POSIX macro F_SETLKW is
   defined, but does not work.  On such systems, you must set
   HAVE_BROKEN_SETLKW to 1.  If you do not, uux will hang, or log
   peculiar error messages, every time it is run.  */
#define HAVE_BROKEN_SETLKW 0

/* On the 3B2, and possibly other systems, nap takes an argument in
   hundredths of a second rather than milliseconds.  I don't know of
   any way to test for this.  Set HAVE_HUNDREDTHS_NAP to 1 if this is
   true on your system.  This does not matter if your system does not
   have the nap function.  */
#define HAVE_HUNDREDTHS_NAP 0

/* If you use other programs that also lock devices, such as cu or
   uugetty, the other programs and UUCP must agree on whether a device
   is locked.  This is typically done by creating a lock file in a
   specific directory; the lock files are generally named
   LCK..something or LK.something.  If the LOCKDIR macro is defined,
   these lock files will be placed in the named directory; otherwise
   they will be placed in the default spool directory.  On some HDB
   systems the lock files are placed in /etc/locks.  On some they are
   placed in /usr/spool/locks.  On the NeXT they are placed in
   /usr/spool/uucp/LCK.  */
/* #define LOCKDIR "/usr/spool/uucp" */
/* #define LOCKDIR "/etc/locks" */
/* #define LOCKDIR "/usr/spool/locks" */
/* #define LOCKDIR "/usr/spool/uucp/LCK" */
/* #define LOCKDIR "/var/spool/lock" */
/* #define LOCKDIR "/var/lock" */

/* Adminstrative decisions.  */

/* Set USE_RCS_ID to 1 if you want the RCS ID strings compiled into
   the executable.  Leaving them out will decrease the executable
   size.  Leaving them in will make it easier to determine which
   version you are running.  */
#define USE_RCS_ID 1

/* DEBUG controls how much debugging information is compiled into the
   code.  If DEBUG is defined as 0, no sanity checks will be done and
   no debugging messages will be compiled in.  If DEBUG is defined as
   1 sanity checks will be done but there will still be no debugging
   messages.  If DEBUG is 2 than debugging messages will be compiled
   in.  When initially testing, DEBUG should be 2, and you should
   probably leave it at 2 unless a small reduction in the executable
   file size will be very helpful.  */
#define DEBUG 2

/* Set HAVE_ENCRYPTED_PASSWORDS to 1 if you want login passwords to be
   encrypted before comparing them against the values in the file.
   This only applies when uucico is run with the -l or -e switches and
   is doing its own login prompting.  Note that the passwords used are
   from the UUCP password file, not the system /etc/passwd file.  See
   the documentation for further details.  If you set this, you are
   responsible for encrypting the passwords in the UUCP password file.
   The function crypt will be used to do comparisons.  */
#define HAVE_ENCRYPTED_PASSWORDS 0

/* Set the default grade to use for a uucp command if the -g option is
   not used.  The grades, from highest to lowest, are 0 to 9, A to Z,
   a to z.  */
#define BDEFAULT_UUCP_GRADE ('N')

/* Set the default grade to use for a uux command if the -g option is
   not used.  */
#define BDEFAULT_UUX_GRADE ('N')

/* If you would like the log, debugging and statistics files to be
   closed after each message, set CLOSE_LOGFILES to 1.  This will
   permit the log files to be easily moved.  If a log file does not
   exist when a new message is written out, it will be created.
   Setting CLOSE_LOGFILES to 1 will obviously require slightly more
   processing time.  */
#define CLOSE_LOGFILES 0

/* The name of the default spool directory.  If HAVE_TAYLOR_CONFIG is
   set to 1, this may be overridden by the ``spool'' command in the
   configuration file.  */
#define SPOOLDIR "/usr/spool/uucp"
/* #define SPOOLDIR "/var/spool/uucp" */

/* The name of the default public directory.  If HAVE_TAYLOR_CONFIG is
   set to 1, this may be overridden by the ``pubdir'' command in the
   configuration file.  Also, a particular system may be given a
   specific public directory by using the ``pubdir'' command in the
   system file.  */
#define PUBDIR "/usr/spool/uucppublic"
/* #define PUBDIR "/var/spool/uucppublic" */

/* The default command path.  This is a space separated list of
   directories.  Remote command executions requested by uux are looked
   up using this path.  If you are using HAVE_TAYLOR_CONFIG, the
   command path may be overridden for a particular system.  For most
   systems, you should just make sure that the programs rmail and
   rnews can be found using this path.  */
#define CMDPATH "/bin /usr/bin /usr/local/bin"

/* The default amount of free space to require for systems that do not
   specify an amount with the ``free-space'' command.  This is only
   used when talking to another instance of Taylor UUCP; if accepting
   a file would not leave at least this many bytes free on the disk,
   it will be refused.  */
#define DEFAULT_FREE_SPACE (50000)

/* While a file is being received, Taylor UUCP will periodically check
   to see if there is enough free space remaining on the disk.  If
   there is not enough space available on the disk (as determined by
   DEFAULT_FREE_SPACE, above, or the ``free-space'' command for the
   system) the communication will be aborted.  The disk will be
   checked each time FREE_SPACE_DELTA bytes are received.  Lower
   values of FREE_SPACE_DELTA are less likely to fill up the disk, but
   will also waste more time checking the amount of free space.  To
   avoid checking the disk while the file is being received, set
   FREE_SPACE_DELTA to 0.  */
#define FREE_SPACE_DELTA (10240)

/* It is possible for an execute job to request to be executed using
   sh(1), rather than execve(2).  This is such a security risk, it is
   being disabled by default; to allow such jobs, set the following
   macro to 1.  */
#define ALLOW_SH_EXECUTION 0

/* If a command executed on behalf of a remote system takes a filename
   as an argument, a security breach may be possible (note that on my
   system neither of the default commands, rmail and rnews, take
   filename arguments).  If you set ALLOW_FILENAME_ARGUMENTS to 0, all
   arguments to a command will be checked; if any argument
   1) starts with ../
   2) contains the string /../
   3) begins with a / but does not name a file that may be sent or
      received (according to the specified ``remote-send'' and
      ``remote-receive'')
   the command will be rejected.  By default, any argument is
   permitted. */
#define ALLOW_FILENAME_ARGUMENTS 1

/* If you set FSYNC_ON_CLOSE to 1, all output files will be forced out
   to disk using the fsync system call when they are closed.  This can
   be useful if you can not afford to lose people's mail if the system
   crashes.  However, not all systems have the fsync call, and it is
   always less efficient to use it.  Note that some versions of SCO
   Unix, and possibly other systems, make fsync a synonym for sync,
   which is extremely inefficient.  */
#define FSYNC_ON_CLOSE 0

/* The default log file when using HAVE_TAYLOR_LOGGING.  When using
   HAVE_TAYLOR_CONFIG, this may be overridden by the ``logfile''
   command in the configuration file.  */
#define LOGFILE "/usr/spool/uucp/Log"
/* #define LOGFILE "/var/spool/uucp/Log" */
/* #define LOGFILE "/var/log/uucp/Log" */

/* The default statistics file when using HAVE_TAYLOR_LOGGING.  When
   using HAVE_TAYLOR_CONFIG, this may be overridden by the
   ``statfile'' command in the configuration file.  */
#define STATFILE "/usr/spool/uucp/Stats"
/* #define STATFILE "/var/spool/uucp/Stats" */
/* #define STATFILE "/var/log/uucp/Stats" */

/* The default debugging file when using HAVE_TAYLOR_LOGGING.  When
   using HAVE_TAYLOR_CONFIG, this may be overridden by the
   ``debugfile'' command in the configuration file.  */
#define DEBUGFILE "/usr/spool/uucp/Debug"
/* #define DEBUGFILE "/var/spool/uucp/Debug" */
/* #define DEBUGFILE "/var/log/uucp/Debug" */

