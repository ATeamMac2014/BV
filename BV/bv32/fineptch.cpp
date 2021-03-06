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
  fineptch.c : Fine pitch search functions.

  $Log$
******************************************************************************/

#include "typedef.h"
#include "bvcommon.h"
#include "bv32cnst.h"
#include "bv32strct.h"
#include "basop32.h"

namespace bds {

#define  FS	(XOFF+1)	/* Frame Starting index */
#define	 FE	(XOFF+FRSZ)	/* Frame Ending index	*/
#define  DEV	6

Word16  refinepitch(
                    Word16	*x,		/* (i) Q1 */
                    Word16 	cpp,
                    Word16	*ppt)	/* (o) Q9 */
{
   Word32	a0, a1;
   Word32	cor, energy, cormax, enermax32;			/* Q3 */
   Word16	energymax, energymax_exp, ener, ener_exp;
   Word16 	cor2, cor2_exp, cor2max, cor2max_exp;
   Word16	*sp0, *sp1, *sp2, *sp3;
   Word16	s, t;
   Word16 	lb, ub;
   Word16 	pp, i, j;
   
   if (cpp >= MAXPP) cpp = MAXPP-1;
   if (cpp < MINPP) cpp = MINPP;
   lb=sub((Word16)cpp,DEV); 
   if (lb < MINPP) lb = MINPP; /* lower bound of pitch period search range */
   ub=add((Word16)cpp,DEV);
   /* to avoid selecting MAXPP as the refined pitch period */
   if (ub >= MAXPP) ub = MAXPP-1;/* lower bound of pitch period search range */
   
   i=lb;				/* start the search from lower bound	    */
   
   sp0 = x+FS-1;
   sp1 = x+FS-1-i;
   cor = energy = 0;
   for (j=0;j<(FE-FS+1); j++) {
      s = *sp1++;
      t = *sp0++;
      energy = L_mac0(energy, s, s);
      cor = L_mac0(cor, s, t);
   }
   
   pp=i;
   cormax=cor;
   enermax32 = energy;
   energymax_exp = norm_l(enermax32);
   energymax = extract_h(L_shl(enermax32, energymax_exp));
   a0 = cor;
   cor2max_exp = norm_l(a0);
   s = extract_h(L_shl(a0, cor2max_exp));
   cor2max_exp = shl(cor2max_exp, 1);
   cor2max = extract_h(L_mult(s, s));
   
   sp0 = x+FE-lb-1;
   sp1 = x+FS-lb-2;
   for (i=lb+1;i<=ub;i++) {
      sp2 = x+FS-1;
      sp3 = x+FS-i-1;
      cor = 0;
      for (j=0;j<(FE-FS+1);j++) 
         cor = L_mac0(cor, *sp2++, *sp3++);
      
      a0 = cor;
      cor2_exp = norm_l(a0);
      s = extract_h(L_shl(a0, cor2_exp));
      cor2_exp = shl(cor2_exp, 1);
      cor2 = extract_h(L_mult(s, s));
      
      s = *sp1--;
      t = *sp0--;
      energy = L_msu0(energy, t, t);
      energy = L_mac0(energy, s, s);
      a0 = energy;
      ener_exp = norm_l(a0);
      ener = extract_h(L_shl(a0, ener_exp));
      
      a0 = L_mult(cor2, energymax);
      a1 = L_mult(cor2max, ener);
      if ((a0!=0)&&(a1!=0)) {
         s = add(cor2_exp, energymax_exp);
         t = add(cor2max_exp, ener_exp);
         if (s>=t) a0 = L_shr(a0, sub(s,t));
         else a1 = L_shr(a1, sub(t,s));
      }
      
      if ((a0 > a1)&&(ener>0)) {
         pp = i;
         cormax = cor;
         enermax32 = energy;	
         cor2max = cor2; cor2max_exp = cor2_exp;
         energymax = ener; energymax_exp = ener_exp;
      }
   }
   
   if ((enermax32 == 0) || (cormax<=0)) *ppt = 0;
   else {
      ub = sub(norm_l(cormax),1);
      lb = norm_l(enermax32);
      s = extract_h(L_shl(cormax,ub));
      t = extract_h(L_shl(enermax32,lb));
      s = div_s(s, t);
      lb = sub(sub(lb,ub),6);
      *ppt = shl(s, lb);
   }
   
   return pp;
}

}

