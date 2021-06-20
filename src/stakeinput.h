// Copyright (c) 2017-2020 The JokeCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef JokeCoin_STAKEINPUT_H
#define JokeCoin_STAKEINPUT_H

#include "chain.h"
#include "streams.h"
#include "uint256.h"

class CKeyStore;
class CWallet;
class CWalletTx;

class CStakeInput
{
protected:
    const CBlockIndex* pindexFrom = nullptr;

public:
    CStakeInput(const CBlockIndex* _pindexFrom) : pindexFrom(_pindexFrom) {}
    virtual ~CStakeInput(){};
    virtual bool InitFromTxIn(const CTxIn& txin) = 0;
    virtual const CBlockIndex* GetIndexFrom() const = 0;
    virtual bool GetTxOutFrom(CTxOut& out) const = 0;
    virtual CAmount GetValue() const = 0;
    virtual bool IsZJOKE() const = 0;
    virtual CDataStream GetUniqueness() const = 0;
    virtual bool ContextCheck(int nHeight, uint32_t nTime) = 0;
};


class CPivStake : public CStakeInput
{
private:
    const CTxOut outputFrom;
    const COutPoint outpointFrom;

public:
    CPivStake(const CTxOut& _from, const COutPoint& _outPointFrom, const CBlockIndex* _pindexFrom) :
            CStakeInput(_pindexFrom), outputFrom(_from), outpointFrom(_outPointFrom) {}

    static CPivStake* NewPivStake(const CTxIn& txin);

    bool InitFromTxIn(const CTxIn& txin) override { return pindexFrom; }
    const CBlockIndex* GetIndexFrom() const override;
    bool GetTxOutFrom(CTxOut& out) const override;
    CAmount GetValue() const override;
    CDataStream GetUniqueness() const override;
    CTxIn GetTxIn() const;
    bool CreateTxOuts(const CWallet* pwallet, std::vector<CTxOut>& vout, CAmount nTotal) const;
    bool IsZJOKE() const override { return false; }
    bool ContextCheck(int nHeight, uint32_t nTime) override;
};


#endif //JokeCoin_STAKEINPUT_H
