#include "Coin.h"
#include "util.h"

namespace sigma{

bool DenominationToInteger(CoinDenominationV3 denom, int& denom_out, CValidationState &state) {
    switch (denom) {
        default:
            return state.DoS(100, error("CheckZerocoinTransaction : invalid denomination value, unable to convert to integer"));
        case CoinDenominationV3::ZQ_LOVELACE:
            denom_out = 1;
        case CoinDenominationV3::ZQ_GOLDWASSER:
            denom_out = 10;
        case CoinDenominationV3::ZQ_RACKOFF:
            denom_out = 25;
        case CoinDenominationV3::ZQ_PEDERSEN:
            denom_out = 50;
        case CoinDenominationV3::ZQ_WILLIAMSON:
            denom_out = 100;
    }
return true;
}

bool IntegerToDenomination(int value, CoinDenominationV3& denom_out, CValidationState &state) {
    switch (value) {
        default:
            return state.DoS(100, error("CheckZerocoinTransaction : invalid denomination value, unable to convert to enum"));
        case 1:
            denom_out = CoinDenominationV3::ZQ_LOVELACE;
        case 10:
            denom_out = CoinDenominationV3::ZQ_GOLDWASSER;
        case 25:
            denom_out = CoinDenominationV3::ZQ_RACKOFF;
        case 50:
            denom_out = CoinDenominationV3::ZQ_PEDERSEN;
        case 100:
            denom_out = CoinDenominationV3::ZQ_WILLIAMSON;
    }
return true;
}

//class PublicCoin
PublicCoinV3::PublicCoinV3()
    : denomination(ZQ_LOVELACE) 
{

}

PublicCoinV3::PublicCoinV3(const GroupElement& coin, const CoinDenominationV3 d)
    : value(coin)
    , denomination(d)
{
}

const GroupElement& PublicCoinV3::getValue() const{
    return this->value;
}

CoinDenominationV3 PublicCoinV3::getDenomination() const {
    return static_cast<CoinDenominationV3>(this->denomination);
}

bool PublicCoinV3::operator==(const PublicCoinV3& other) const{
    return (*this).value == other.value;
}

bool PublicCoinV3::operator!=(const PublicCoinV3& other) const{
    return (*this).value != other.value;
}

bool PublicCoinV3::validate() const{
    return this->value.isMember();
}

size_t PublicCoinV3::GetSerializeSize(int nType, int nVersion) const{
    return value.memoryRequired() + sizeof(int);
}

//class PrivateCoin
PrivateCoinV3::PrivateCoinV3(const ParamsV3* p,CoinDenominationV3 denomination, int version):
    params(p) {
        this->version = version;
        this->mintCoin(denomination);
}

const PublicCoinV3& PrivateCoinV3::getPublicCoin() const{
    return this->publicCoin;
}

const Scalar& PrivateCoinV3::getSerialNumber() const{
    return this->serialNumber;
}

const Scalar& PrivateCoinV3::getRandomness() const{
    return this->randomness;
}

unsigned int PrivateCoinV3::getVersion() const{
    return this->version;
}

void PrivateCoinV3::setPublicCoin(PublicCoinV3 p){
    publicCoin = p;
}

void PrivateCoinV3::setRandomness(Scalar n){
    randomness = n;
}

void PrivateCoinV3::setSerialNumber(Scalar n){
    serialNumber = n;
}

void PrivateCoinV3::setVersion(unsigned int nVersion){
    version = nVersion;
}

void PrivateCoinV3::mintCoin(const CoinDenominationV3 denomination){
    serialNumber.randomize();
    randomness.randomize();
    GroupElement commit = SigmaPrimitives<Scalar, GroupElement>::commit(
            params->get_g(), serialNumber, params->get_h0(), randomness);
    publicCoin = PublicCoinV3(commit, denomination);
}

}//namespace sigma