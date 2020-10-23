
#ifndef ZCOIN_BIP47ACCOUNT_H
#define ZCOIN_BIP47ACCOUNT_H
#include "bip47/common.h"
#include "bip47/paymentcode.h"
#include "key.h"
#include "pubkey.h"

class CBIP47Account {

    public:
        CBIP47Account() {accountId=0;}
        CBIP47Account(CExtKey &coinType, int identity);
        CBIP47Account(std::string strPaymentCode);

        bool SetPaymentCodeString(std::string strPaymentCode);
        std::string const & getStringPaymentCode() const;

        CBitcoinAddress getNotificationAddress() const;

        CExtPubKey getNotificationKey();
        CExtKey getNotificationPrivKey();

        CPaymentCode const & getPaymentCode() const;

        CBIP47ChannelAddress addressAt(int idx);

        CExtPubKey keyAt(int idx) const;
        CExtKey keyPrivAt(int idx) const;
        bool isValid() const;

    private:
        CExtKey prvkey;
        CExtPubKey key;
        int accountId;
        CPaymentCode paymentCode;

};

#endif // ZCOIN_BIP47ACCOUNT_H
