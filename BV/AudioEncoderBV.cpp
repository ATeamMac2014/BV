//
//  AudioEncoderBV.cpp
//  SDKTester
//
//  Created by lappi on 1/8/16.
//  Copyright © 2016 baidu. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "AudioEncoderBV.hpp"

#include    "bv32/bv32.h"
#include    "bv32/bitpack.h"

#define BV_ENCODER_FRAME_SIZE_BYTES (80*2)

namespace bds{
    
    AudioEncoderBase* AudioEncoderBV::createEncoder(int sampleRate)
    {
        AudioEncoderBase* ret = new AudioEncoderBV(sampleRate);
        return ret;
    }

    int AudioEncoderBV::encoderInit()
    {
        Reset_BV32_Encoder(&m_BV32EncoderState);
        this->m_isInitialized = true;
        this->m_waitingFirstAudio = true;
        return ENCODER_OK;
    }
    
    void AudioEncoderBV::encoderExit()
    {
        this->m_isInitialized = false;
    }
    
    int AudioEncoderBV::encodeSamples(const uint8_t* src_pcm, int src_len, uint8_t* dest_encoded, int dest_len)
    {
        if(!this->m_isInitialized)
            encoderInit();
        if (NULL == src_pcm || 0 == src_len || NULL == dest_encoded || 0 == dest_len) {
            return 0;
        }
        int cur_pos = 0;
        Word16 *x = (Word16*)malloc((sizeof(Word16)*this->m_frameSize_Bytes)/2);
        if(x == NULL)
        {
            return ENCODER_ERROR_ALLOC_FAIL;
        }
        int nSegNum = int(src_len/this->m_frameSize_Bytes);
        if (src_len != nSegNum * this->m_frameSize_Bytes) {
            fprintf(stderr, "src_len: %d, nSegNum: %d, frsz: %d\n",src_len,nSegNum,this->m_frameSize_Bytes);
            return ENCODER_ERROR_BAD_INPUT_SIZE;
        }
        
        if(dest_len < 4)
        {
            return ENCODER_ERROR_OUTPUT_BUFFER_TOO_SMALL;
        }
        // add header at the beginning of encoded audio
        /*
        if(m_waitingFirstAudio)
        {
            m_waitingFirstAudio = false;
            dest_encoded[0] = 0;
            if (this->m_sampleRate == 16000) {
                dest_encoded[0] = 4;
            }
            dest_encoded[1] = 0;
            dest_encoded[2] = 0;
            dest_encoded[3] = 0;
            cur_pos = 4;
        }
        */
        
        UWord8  PackedStream[20] = {0};
        int frame = 0;
        while(frame < nSegNum)
        {
            /** @brief Frame Counter */
            int iFrameLoc = frame * (this->m_frameSize_Bytes/2);
            frame++;
            
            /** @brief Read in One Frame Data */
            for(int i = 0; i < (this->m_frameSize_Bytes/2); i++)
            {
                x[i] = ((short*)src_pcm)[iFrameLoc + i];
            }
            
            /** @brief BV32 Coding */
            BV32_Encode(&this->m_BV32bitStream, &this->m_BV32EncoderState, x);
            BV32_BitPack(PackedStream, &this->m_BV32bitStream);
            
            for(int i = 0; i < 20; i++)
            {
                if((cur_pos+1) == dest_len)
                {
                    encoderExit();
                    return ENCODER_ERROR_OUTPUT_BUFFER_TOO_SMALL;
                }
                dest_encoded[cur_pos++] = PackedStream[i];
            }
        }
        free(x);
        return cur_pos;
    }

    AudioEncoderBV::AudioEncoderBV(int sampleRate):
    AudioEncoderBase(sampleRate)
    {
        this->m_frameSize_Bytes = BV_ENCODER_FRAME_SIZE_BYTES;
    }

    AudioEncoderBV::~AudioEncoderBV()
    {
        
    }
}
