//
//  BVExtern.h
//  BV
//
//  Created by Brad on 2018/11/14.
//  Copyright © 2018年 Wenbo,Hu. All rights reserved.
//

#ifndef BVExtern_h
#define BVExtern_h

#include <stdio.h>
#include <stdlib.h>

typedef void* BVEncoder;

#ifdef __cplusplus
extern "C"{
#endif
    //在这里写上c的代码
    BVEncoder initBV(int rate);
    int encodeData(BVEncoder encoder,const uint8_t* src_pcm, int src_len, uint8_t* dest_encoded, int dest_len);
#ifdef __cplusplus
}
#endif

#endif /* BVExtern_h */
