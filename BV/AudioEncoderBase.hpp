//
//  AudioEncoderBase.hpp
//  SDKTester
//
//  Created by lappi on 1/8/16.
//  Copyright © 2016 baidu. All rights reserved.
//

#ifndef AudioEncoderBase_hpp
#define AudioEncoderBase_hpp

#include "bds_int_types.h"

#define ENCODER_OK 0
#define ENCODER_ERROR_ALLOC_FAIL -1
#define ENCODER_ERROR_BAD_INPUT_SIZE -2
#define ENCODER_ERROR_OUTPUT_BUFFER_TOO_SMALL -3
#define ENCODER_ERROR_UNSUPPORTED_SAMPLERATE -4

namespace bds{
    class AudioEncoderBase
    {
    public:
        virtual int getEncoderFrameSize_bytes()
        {
            return this->m_frameSize_Bytes;
        }
        virtual int encoderInit() = 0;
        virtual void encoderExit() = 0;
        virtual int encodeSamples(const uint8_t* src_pcm, int src_len, uint8_t* dest_encoded, int dest_len) = 0;
    protected:
        AudioEncoderBase(int sampleRate){
            m_isInitialized = false;
            m_waitingFirstAudio = false;
            m_frameSize_Bytes = 0;
            m_sampleRate = sampleRate;
        }
        /*
         * Need to be virtual protected to allow a limited subset of friend
         * classes to directly call delete on the base class
         */
        virtual ~AudioEncoderBase()
        {
            
        }
        int m_sampleRate;
        int m_frameSize_Bytes;
        bool m_isInitialized;
        bool m_waitingFirstAudio;
    };
}
#endif /* AudioEncoderBase_hpp */
