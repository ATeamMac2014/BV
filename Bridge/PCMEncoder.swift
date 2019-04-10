//
//  BVBridge.swift
//  BV
//
//  Created by Brad on 2018/11/14.
//  Copyright © 2018年 Wenbo,Hu. All rights reserved.
//

import Foundation

public class PCMEncoder {
    private let bvEncoder: BVEncoder
    
    public init(rate: Int32) {
        bvEncoder = initBV(rate)
    }
    
    public func encode(src: UnsafePointer<UInt8>, srcLen: Int32, dest: UnsafeMutablePointer<UInt8>, destLen: Int32) {
        encodeData(bvEncoder, src, srcLen, dest, destLen)
    }
}
