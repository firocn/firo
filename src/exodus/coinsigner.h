// Copyright (c) 2020 The Zcoin Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZCOIN_EXODUS_COINSIGNER_H
#define ZCOIN_EXODUS_COINSIGNER_H

#include "hash.h"

#include "../libzerocoin/Zerocoin.h"
#include "../sigma/openssl_context.h"

namespace exodus {

typedef std::array<uint8_t, 32> ECDSAPrivateKey;
typedef std::array<uint8_t, 33> ECDSAPublicKey;
typedef std::array<uint8_t, 64> ECDSASignature;

class CoinSigner
{
public:
    CoinSigner(ECDSAPrivateKey priv);

protected:
    ECDSAPrivateKey key;

public:
    ECDSAPublicKey GetPublicKey() const;
    ECDSASignature Sign(unsigned char const *start, unsigned char const *end);
};

}

#endif // ZCOIN_EXODUS_WALLET_H