/* unk.c
   Get information about an unknown system.

   Copyright (C) 1992 Ian Lance Taylor

   This file is part of the Taylor UUCP uuconf library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License
   as published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA.

   The author of the program may be contacted at ian@airs.com.
   */

#include "uucnfi.h"

#if USE_RCS_ID
const char _uuconf_unk_rcsid[] = "$Id: unk.c,v 1.6 2002/03/05 19:10:43 ian Rel $";
#endif

#include <errno.h>

/* Get information about an unknown system.  If we are using
   HAVE_TAYLOR_CONFIG, we just use it.  Otherwise if we are using
   HAVE_HDB_CONFIG, we use it.  Otherwise we return a default system.
   This isn't right for HAVE_V2_CONFIG, because it is possible to
   specify default directories to read and write in USERFILE.
   However, I'm not going to bother to write that code unless somebody
   actually wants it.  */

/*ARGSUSED*/
int
uuconf_system_unknown (pglobal, qsys)
     pointer pglobal;
     struct uuconf_system *qsys;
{
  return uuconf_taylor_system_unknown (pglobal, qsys);
}
