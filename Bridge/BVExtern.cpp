
//
//  BVExtern.c
//  BV
//
//  Created by Brad on 2018/11/14.
//  Copyright © 2018年 Wenbo,Hu. All rights reserved.
//

#include "BVExtern.h"
#include "AudioEncoderBV.hpp"

using namespace bds;

BVEncoder initBV(int rate) {
    AudioEncoderBase* bv = AudioEncoderBV::createEncoder(rate);
    return bv;
}

int encodeData(BVEncoder encoder,const uint8_t* src_pcm, int src_len, uint8_t* dest_encoded, int dest_len) {
    AudioEncoderBase* audioEncoder = (AudioEncoderBase*)encoder;
    return audioEncoder->encodeSamples(src_pcm, src_len, dest_encoded, dest_len);
}

