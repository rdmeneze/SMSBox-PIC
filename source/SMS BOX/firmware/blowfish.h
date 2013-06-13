/***********************************************************************************************
 * blowfish.h:  Header file for blowfish.c
 * 
 * Copyright (C) 1997 by Paul Kocher
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 * 
 * See blowfish.c for more information about this file.
 *
 ***********************************************************************************************/

#ifndef __BLOWFISH__
#define __BLOWFISH__
  
#include "defs.h"

//typedef struct {
//  unsigned long P[16 + 2];
//  unsigned long S[4][256];
//} BLOWFISH_CTX;

void Blowfish_Init( BYTE *key,  BYTE keyLen );
void Blowfish_Encrypt(  DWORD *xl,  DWORD *xr   );
void Blowfish_Decrypt(  DWORD *xl,  DWORD *xr   );

#endif  // __BLOWFISH__



