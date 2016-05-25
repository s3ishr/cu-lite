/* spool.c
   Find a file in the spool directory.

   Copyright (C) 1991, 1992, 1993, 2002 Ian Lance Taylor

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

#include "uucp.h"

#if USE_RCS_ID
const char spool_rcsid[] = "$Id: spool.c,v 1.14 2002/03/05 19:10:42 ian Rel $";
#endif

#include "uudefs.h"
#include "sysdep.h"
#include "system.h"

/*ARGSUSED*/
char *
zsfind_file (zsimple, zsystem, bgrade)
     const char *zsimple;
     const char *zsystem;
     int bgrade ATTRIBUTE_UNUSED;
{
  /* zsysdep_spool_commands calls this with TMPXXX which we must treat
     as a C. file.  */
  if ((zsimple[0] != 'T'
       || zsimple[1] != 'M'
       || zsimple[2] != 'P')
      && ! fspool_file (zsimple))
    {
      ulog (LOG_ERROR, "Unrecognized file name %s", zsimple);
      return NULL;
    }

  switch (*zsimple)
    {
    case 'C':
    case 'T':
      return zsappend3 (zsystem, "C.", zsimple);

    case 'D':
      if (zsimple[2] == 'X')
	return zsappend3 (zsystem, "D.X", zsimple);
      else
	return zsappend3 (zsystem, "D.", zsimple);

    case 'X':
      return zsappend3 (zsystem, "X.", zsimple);
    }

  /* This is just to avoid warnings; it will never be executed.  */
  return NULL;
}
