/*****************************************************************************/
/* BroadVoice(R)32 (BV32) Fixed-Point ANSI-C Source Code                     */
/* Revision Date: November 13, 2009                                          */
/* Version 1.1                                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Copyright 2000-2009 Broadcom Corporation                                  */
/*                                                                           */
/* This software is provided under the GNU Lesser General Public License,    */
/* version 2.1, as published by the Free Software Foundation ("LGPL").       */
/* This program is distributed in the hope that it will be useful, but       */
/* WITHOUT ANY SUPPORT OR WARRANTY; without even the implied warranty of     */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the LGPL for     */
/* more details.  A copy of the LGPL is available at                         */
/* http://www.broadcom.com/licenses/LGPLv2.1.php,                            */
/* or by writing to the Free Software Foundation, Inc.,                      */
/* 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                 */
/*****************************************************************************/


/*****************************************************************************
  bitpack.h: BV32 bit packing routines

  $Log$
******************************************************************************/

#ifndef BITPACK_H
#define BITPACK_H

namespace bds {

void BV32_BitPack(UWord8 * PackedStream, struct BV32_Bit_Stream * BitStruct);
void BV32_BitUnPack(UWord8 * PackedStream, struct BV32_Bit_Stream * BitStruct);

}

#endif
