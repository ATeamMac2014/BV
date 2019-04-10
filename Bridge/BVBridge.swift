//
//  BVBridge.swift
//  BV
//
//  Created by Brad on 2018/11/14.
//  Copyright © 2018年 Wenbo,Hu. All rights reserved.
//

import Foundation

public class BVBridge {
    private let encoder: BVEncoder
    private let bufferSize = 160
    private var encodedData: Data
    public init(rate: Int32) {
        encoder = initBV(rate)
        encodedData = Data()
    }

    public func encodeSamples(src_pcm: UnsafePointer<UInt8>, src_len: Int32, dest_encoded: UnsafeMutablePointer<UInt8>, dest_len: Int32) {
        encodeData(encoder, src_pcm, src_len, dest_encoded, dest_len)
    }
    
}
