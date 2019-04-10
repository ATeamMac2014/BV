//
//  AudioEncoderBV.hpp
//  SDKTester
//
//  Created by lappi on 1/8/16.
//  Copyright © 2016 baidu. All rights reserved.
//

#ifndef AudioEncoderBV_hpp
#define AudioEncoderBV_hpp

#include "AudioEncoderBase.hpp"
#include    "bv32/bv32cnst.h"
#include    "bvcommon/typedef.h"
#include    "bvcommon/bvcommon.h"
#include    "bv32/bv32strct.h"

namespace bds {
    class AudioEncoderBV:public AudioEncoderBase{
    public:
        static AudioEncoderBase* createEncoder(int sampleRate);
        virtual int encoderInit();
        virtual void encoderExit();
        virtual int encodeSamples(const uint8_t* src_pcm, int src_len, uint8_t* dest_encoded, int dest_len);
    protected:
        AudioEncoderBV(int sampleRate);
        ~AudioEncoderBV();
    private:
        struct BV32_Encoder_State m_BV32EncoderState;
        struct BV32_Bit_Stream m_BV32bitStream;
    };
}

#endif /* AudioEncoderBV_hpp */
