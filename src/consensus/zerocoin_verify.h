// Copyright (c) 2020 The JokeCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef JokeCoin_CONSENSUS_ZEROCOIN_VERIFY_H
#define JokeCoin_CONSENSUS_ZEROCOIN_VERIFY_H

#include "consensus/consensus.h"
#include "script/interpreter.h"
#include "zjokechain.h"

// Fake Serial attack Range
bool isBlockBetweenFakeSerialAttackRange(int nHeight);
// Public coin spend
bool CheckPublicCoinSpendEnforced(int blockHeight, bool isPublicSpend);
int CurrentPublicCoinSpendVersion();
bool CheckPublicCoinSpendVersion(int version);
bool ContextualCheckZerocoinTx(const CTransactionRef& tx, CValidationState& state, const Consensus::Params& consensus, int nHeight);
bool ContextualCheckZerocoinSpend(const CTransaction& tx, const libzerocoin::CoinSpend* spend, int nHeight, const uint256& hashBlock);
bool ContextualCheckZerocoinSpendNoSerialCheck(const CTransaction& tx, const libzerocoin::CoinSpend* spend, int nHeight, const uint256& hashBlock);

#endif //JokeCoin_CONSENSUS_ZEROCOIN_VERIFY_H
