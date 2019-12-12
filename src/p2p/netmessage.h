//
// Created by yehuan on 2019-12-11.
//

#ifndef P2P_NETMESSAGE_H
#define P2P_NETMESSAGE_H

#include "commons/serialize.h"
#include "p2p/protocol.h"

class CNetMessage {
public:
    bool in_data;  // parsing header (false) or data (true)

    CDataStream hdrbuf;  // partially received header
    CMessageHeader hdr;  // complete header
    uint32_t nHdrPos;

    CDataStream vRecv;  // received message data
    uint32_t nDataPos;

    CNetMessage(int32_t nTypeIn, int32_t nVersionIn) : hdrbuf(nTypeIn, nVersionIn), vRecv(nTypeIn, nVersionIn) {
        hdrbuf.resize(24);
        in_data  = false;
        nHdrPos  = 0;
        nDataPos = 0;
    }

    bool complete() const {
        if (!in_data)
            return false;
        return (hdr.nMessageSize == nDataPos);
    }

    void SetVersion(int32_t nVersionIn) {
        hdrbuf.SetVersion(nVersionIn);
        vRecv.SetVersion(nVersionIn);
    }

    int32_t readHeader(const char* pch, uint32_t nBytes);
    int32_t readData(const char* pch, uint32_t nBytes);
};



#endif //WAYKICHAIN_NETMESSAGE_H
