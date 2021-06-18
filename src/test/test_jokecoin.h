// Copyright (c) 2015-2019 The JokeCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef JokeCoin_TEST_TEST_JokeCoin_H
#define JokeCoin_TEST_TEST_JokeCoin_H

#include "fs.h"
#include "scheduler.h"
#include "txdb.h"

#include <boost/thread.hpp>

extern FastRandomContext insecure_rand_ctx;

/**
 * Flag to make GetRand in random.h return the same number
 */
extern bool g_mock_deterministic_tests;

static inline void SeedInsecureRand(bool deterministic = false)
{
    insecure_rand_ctx = FastRandomContext(deterministic);
}

static inline uint32_t InsecureRand32() { return insecure_rand_ctx.rand32(); }
static inline uint256 InsecureRand256() { return insecure_rand_ctx.rand256(); }
static inline uint64_t InsecureRandBits(int bits) { return insecure_rand_ctx.randbits(bits); }
static inline uint64_t InsecureRandRange(uint64_t range) { return insecure_rand_ctx.randrange(range); }
static inline bool InsecureRandBool() { return insecure_rand_ctx.randbool(); }
static inline std::vector<unsigned char> InsecureRandBytes(size_t len) { return insecure_rand_ctx.randbytes(len); }

/** Basic testing setup.
 * This just configures logging and chain parameters.
 */
struct BasicTestingSetup {
    ECCVerifyHandle globalVerifyHandle;

    BasicTestingSetup(const std::string& chainName = CBaseChainParams::MAIN);
    ~BasicTestingSetup();

    fs::path SetDataDir(const std::string& name);

private:
    const fs::path m_path_root;
};

/** Testing setup that configures a complete environment.
 * Included are data directory, coins database, script check threads
 * and wallet (if enabled) setup.
 */
class CConnman;
class EvoNotificationInterface;
struct TestingSetup: public BasicTestingSetup
{
    CCoinsViewDB *pcoinsdbview;
    boost::thread_group threadGroup;
    CConnman* connman;
    EvoNotificationInterface* pEvoNotificationInterface;
    CScheduler scheduler;

    TestingSetup(const std::string& chainName = CBaseChainParams::MAIN);
    ~TestingSetup();
};

struct RegTestingSetup : public TestingSetup
{
    RegTestingSetup() : TestingSetup(CBaseChainParams::REGTEST) {}
};

class CBlock;
struct CMutableTransaction;
class CScript;

// Test chain only available on regtest
struct TestChainSetup : public TestingSetup
{
    TestChainSetup(int blockCount);
    ~TestChainSetup();

    // Create a new block with coinbase paying to scriptPubKey, and try to add it to the current chain.
    // Include given transactions, and, if fNoMempoolTx=true, remove transactions coming from the mempool.
    CBlock CreateAndProcessBlock(const std::vector<CMutableTransaction>& txns, const CScript& scriptPubKey, bool fNoMempoolTx = true);
    CBlock CreateAndProcessBlock(const std::vector<CMutableTransaction>& txns, const CKey& scriptKey);
    CBlock CreateBlock(const std::vector<CMutableTransaction>& txns, const CScript& scriptPubKey, bool fNoMempoolTx = true);
    CBlock CreateBlock(const std::vector<CMutableTransaction>& txns, const CKey& scriptKey);

    std::vector<CTransaction> coinbaseTxns; // For convenience, coinbase transactions
    CKey coinbaseKey; // private/public key needed to spend coinbase transactions
};

// Testing fixture that pre-creates a 100-block REGTEST-mode blockchain
struct TestChain100Setup : public TestChainSetup
{
    TestChain100Setup() : TestChainSetup(100) {}
};

// Testing fixture that pre-creates a 400-block REGTEST-mode blockchain
// all 400 blocks are PoW. PoS starts at height 500
struct TestChain400Setup : public TestChainSetup
{
    TestChain400Setup() : TestChainSetup(400) {}
};

class CTxMemPoolEntry;
class CTxMemPool;

struct TestMemPoolEntryHelper
{
    // Default values
    CAmount nFee;
    int64_t nTime;
    double dPriority;
    unsigned int nHeight;
    bool hadNoDependencies;
    bool spendsCoinbaseOrCoinstake;
    unsigned int sigOpCount;

    TestMemPoolEntryHelper() :
        nFee(0), nTime(0), dPriority(0.0), nHeight(1),
        hadNoDependencies(false), spendsCoinbaseOrCoinstake(false), sigOpCount(1) { }

    CTxMemPoolEntry FromTx(CMutableTransaction &tx, CTxMemPool *pool = NULL);

    // Change the default value
    TestMemPoolEntryHelper &Fee(CAmount _fee) { nFee = _fee; return *this; }
    TestMemPoolEntryHelper &Time(int64_t _time) { nTime = _time; return *this; }
    TestMemPoolEntryHelper &Priority(double _priority) { dPriority = _priority; return *this; }
    TestMemPoolEntryHelper &Height(unsigned int _height) { nHeight = _height; return *this; }
    TestMemPoolEntryHelper &HadNoDependencies(bool _hnd) { hadNoDependencies = _hnd; return *this; }
    TestMemPoolEntryHelper &SpendsCoinbaseOrCoinstake(bool _flag) { spendsCoinbaseOrCoinstake = _flag; return *this; }
    TestMemPoolEntryHelper &SigOps(unsigned int _sigops) { sigOpCount = _sigops; return *this; }
};

// define an implicit conversion here so that uint256 may be used directly in BOOST_CHECK_*
std::ostream& operator<<(std::ostream& os, const uint256& num);

#endif
