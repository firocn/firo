#ifndef ZCOIN_BIP47UTIL_H
#define ZCOIN_BIP47UTIL_H
#include "key.h"
#include <iostream>
#include <list>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <openssl/sha.h>
#include "GroupElement.h"

#define HARDENED_BIT 0x80000000

class CWallet;
class CTxOut;
class CTxIn;
class CTransaction;

namespace bip47 {

class CPaymentCode;
class CPaymentAddress;
class CAccount;

namespace utils {
void arraycopy(const std::vector<unsigned char> &source_arr,size_t sourcePos,unsigned char* dest_arr, size_t destPos, size_t len);
void arraycopy(const unsigned char *source_arr,size_t sourcePos,std::vector<unsigned char> &dest_arr, size_t destPos, size_t len);
void arraycopy(const std::vector<unsigned char> &source_arr,size_t sourcePos,std::vector<unsigned char> &dest_arr, size_t destPos, size_t len);
void copyOfRange(const std::vector<unsigned char> &original, size_t from, size_t to,std::vector<unsigned char> &result);

bool doublehash(const std::vector<unsigned char> &input,std::vector<unsigned char> &result);
bool isValidNotificationTransactionOpReturn(CTxOut txout);
bool getOpCodeOutput(const CTransaction& tx, CTxOut& txout);
bool getPaymentCodeInNotificationTransaction(std::vector<unsigned char> const & privKeyBytes, CTransaction const & tx, CPaymentCode &paymentCode);
bool getOpCodeData(CTxOut const & txout, vector<unsigned char>& op_data);
bool getScriptSigPubkey(CTxIn const & txin, vector<unsigned char>& pubkeyBytes);
CPaymentAddress getPaymentAddress(CPaymentCode const & pcode, int idx, CExtKey const & extkey);
CPaymentAddress getReceiveAddress(CAccount* v_bip47Account, CWallet* pbip47Wallet, CPaymentCode const & pcode_from, int idx);
CPaymentAddress getSendAddress(CWallet* pbip47Wallet, CPaymentCode const & pcode_to, int idx);

CExtKey derive(CExtKey const & source, std::vector<uint32_t> const & path);

GroupElement GeFromPubkey(CPubKey const & pubKey);
CPubKey PubkeyFromGe(GroupElement const & ge);
} }

#endif // ZCOIN_BIP47UTIL_H
