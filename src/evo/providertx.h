// Copyright (c) 2018-2021 The Dash Core developers
// Copyright (c) 2021 The JokeCoin Core developers
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef JokeCoin_PROVIDERTX_H
#define JokeCoin_PROVIDERTX_H

#include "primitives/transaction.h"
#include "consensus/validation.h"

#include "netaddress.h"
#include "pubkey.h"

#include <univalue.h>

class CBlockIndex;

// Provider-Register tx payload

class ProRegPL
{
public:
    static const uint16_t CURRENT_VERSION = 1;

public:
    uint16_t nVersion{CURRENT_VERSION};                         // message version
    uint16_t nType{0};                                          // only 0 supported for now
    uint16_t nMode{0};                                          // only 0 supported for now
    COutPoint collateralOutpoint{UINT256_ZERO, (uint32_t)-1};   // if hash is null, we refer to a ProRegTx output
    CService addr;
    CKeyID keyIDOwner;
    CKeyID keyIDOperator;
    CKeyID keyIDVoting;
    CScript scriptPayout;
    uint16_t nOperatorReward{0};
    CScript scriptOperatorPayout;
    uint256 inputsHash; // replay protection
    std::vector<unsigned char> vchSig;

public:
    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action)
    {
        READWRITE(nVersion);
        READWRITE(nType);
        READWRITE(nMode);
        READWRITE(collateralOutpoint);
        READWRITE(addr);
        READWRITE(keyIDOwner);
        READWRITE(keyIDOperator);
        READWRITE(keyIDVoting);
        READWRITE(scriptPayout);
        READWRITE(nOperatorReward);
        READWRITE(scriptOperatorPayout);
        READWRITE(inputsHash);
        if (!(s.GetType() & SER_GETHASH)) {
            READWRITE(vchSig);
        }
    }

    // When signing with the collateral key, we don't sign the hash but a generated message instead
    // This is needed for HW wallet support which can only sign text messages as of now
    std::string MakeSignString() const;

    std::string ToString() const;
    void ToJson(UniValue& obj) const;
};

bool CheckProRegTx(const CTransaction& tx, const CBlockIndex* pindexPrev, CValidationState& state);

// If tx is a ProRegTx, return the collateral outpoint in outRet.
bool GetProRegCollateral(const CTransactionRef& tx, COutPoint& outRet);


#endif  //JokeCoin_PROVIDERTX_H
