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
  fixmath.c : Common Fixed-Point Library: math routine tables

  $Log$
******************************************************************************/

#include "typedef.h"

namespace bds {

/* Table for 2^x, x=[-1; 0] in Q15 - generated in Matlab with:    */
/* N=65;                                                          */
/* Q=15;                                                          */
/* x=linspace(-1.0, 0.0, N);                                      */
/* pow2tab=max(min(round30To16(2^Q.*2.^x),32767),-32768);               */

Word16 tabpow[65] = {
 16384,  16562,  16743,  16925,  17109,  17296,  17484,  17674,  17867,  
 18061,  18258,  18457,  18658,  18861,  19066,  19274,  19484,  19696,  
 19911,  20127,  20347,  20568,  20792,  21019,  21247,  21479,  21713,  
 21949,  22188,  22430,  22674,  22921,  23170,  23423,  23678,  23936,  
 24196,  24460,  24726,  24995,  25268,  25543,  25821,  26102,  26386,  
 26674,  26964,  27258,  27554,  27855,  28158,  28464,  28774,  29088,  
 29405,  29725,  30048,  30376,  30706,  31041,  31379,  31720,  32066,  
 32415,  32767};

/* Table for log2(x), x=[1; 2] in Q15 - generated in Matlab with: */
/* N=65;                                                          */
/* Q=15;                                                          */
/* x=linspace(1.0, 2.0, N);                                       */
/* log2tab=max(min(round30To16(2^Q.*log2(x)),32767),-32768);            */

Word16 tablog[65] = {
     0,    733,   1455,   2166,   2866,   3556,   4236,   4907,   5568,   
  6220,   6863,   7498,   8124,   8742,   9352,   9954,  10549,  11136,  
 11716,  12289,  12855,  13415,  13968,  14514,  15055,  15589,  16117,  
 16639,  17156,  17667,  18173,  18673,  19168,  19658,  20143,  20623,  
 21098,  21568,  22034,  22495,  22952,  23404,  23852,  24296,  24736,  
 25172,  25604,  26031,  26455,  26876,  27292,  27705,  28114,  28520,  
 28922,  29321,  29717,  30109,  30498,  30884,  31267,  31647,  32024,  
 32397,  32767};

/* cos(x), x=[0; pi] in Q15 - generated in Matlab with:  */
/* N=65;                                                 */
/* Q=15;                                                 */
/* x=linspace(0, pi, N);                                 */
/* cosx=min(max(round30To16((2^Q)*cos(x)),32767),-32768);      */

Word16 costable[65] = {
    32767,  32729,  32610,  32413,  32138,  31786,  
    31357,  30853,  30274,  29622,  28899,  28106,  
    27246,  26320,  25330,  24279,  23170,  22006,  
    20788,  19520,  18205,  16846,  15447,  14010,  
    12540,  11039,   9512,   7962,   6393,   4808,
     3212,   1608,      0,  -1608,  -3212,  -4808, 
    -6393,  -7962,  -9512, -11039, -12540, -14010, 
   -15447, -16846, -18205, -19520, -20788, -22006, 
   -23170, -24279, -25330, -26320, -27246, -28106, 
   -28899, -29622, -30274, -30853, -31357, -31786, 
   -32138, -32413, -32610, -32729, -32768};

/* slope of acos(x), Q12 - generated in Matlab with:                       */
/* Qa=12;                                                                  */
/* z=round30To16((2^Qa)*(x(2:N)-x(1:N-1))./(cos(x(2:N))-cos(x(1:N-1)))/(2*pi));  */
/* in addition to above Matlab commands to generate cosx.                  */

Word16 acosslope[64] = {
   -26566,  -8862,  -5326,  -3814,  -2976,  -2444,
    -2078,  -1812,  -1609,  -1450,  -1323,  -1219,
    -1132,  -1060,   -998,   -946,   -900,   -861,
     -827,   -797,   -772,   -749,   -730,   -713,
     -699,   -687,   -676,   -668,   -662,   -657,
     -654,   -652,   -652,   -654,   -657,   -662,
     -668,   -676,   -687,   -699,   -713,   -730,
     -749,   -772,   -797,   -827,   -861,   -900,
     -946,   -998,  -1060,  -1132,  -1219,  -1323,
    -1450,  -1609,  -1812,  -2078,  -2444,  -2976, 
    -3814,  -5326,  -8862, -26566};

/* sqrt(x), Q15 - generated in Matlab with :            */
/* N=65;                                                */
/* Q=15;                                                */
/* x=linspace(0, 1, N);                                 */
/* sqrttab=max(min(round30To16((2^Q)*sqrt(x)),32767),-32768); */

Word16 tabsqrt[65] = {
        0,   4096,   5793,   7094,   8192,   9159,  10033,  
    10837,  11585,  12288,  12953,  13585,  14189,  14768,  
    15326,  15864,  16384,  16888,  17378,  17854,  18318,  
    18770,  19212,  19644,  20066,  20480,  20886,  21283,  
    21674,  22058,  22435,  22806,  23170,  23530,  23884,  
    24232,  24576,  24915,  25249,  25580,  25905,  26227,  
    26545,  26859,  27170,  27477,  27780,  28081,  28378,  
    28672,  28963,  29251,  29537,  29819,  30099,  30377,  
    30652,  30924,  31194,  31462,  31727,  31991,  32252,  
    32511,  32767};

}
