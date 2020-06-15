/*
AppleWin : An Apple //e emulator for Windows

Copyright (C) 1994-1996, Michael O'Brien
Copyright (C) 1999-2001, Oliver Schmidt
Copyright (C) 2002-2005, Tom Charlesworth
Copyright (C) 2006-2010, Tom Charlesworth, Michael Pohoreski

AppleWin is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

AppleWin is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with AppleWin; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* Description: 6502/65C02 emulation
 *
 * Author: Various
 */

 /****************************************************************************
*
*  RAM ACCESS MACROS (except debug mode)
*
***/

#undef READ
#define READ   (    \
		((addr & 0xF000) == 0xC000)  \
		? IORead[(addr >> 4) & 0xFF](regs.pc, addr, 0, 0, uExecutedCycles)  \
		: *(mem + addr) \
		)

#undef WRITE
#define WRITE(a) {							    \
		   memdirty[addr >> 8] = 0xFF;				    \
		   LPBYTE page = memwrite[addr >> 8];		    \
		   if (page)						    \
		     *(page+(addr & 0xFF)) = (BYTE)(a);			    \
		   else if ((addr & 0xF000) == 0xC000)			    \
		     IOWrite[(addr>>4) & 0xFF](regs.pc,addr,1,(BYTE)(a),uExecutedCycles); \
		 }

