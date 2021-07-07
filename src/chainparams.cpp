// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021+     The JokeCoin developers =)
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "chainparams.h"
#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "tinyformat.h"
#include "utilstrencodings.h"
#include <assert.h>
static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward){
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;
    CBlock genesis;
    genesis.vtx.push_back(std::make_shared<const CTransaction>(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;}
void CChainParams::UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight){
    assert(IsRegTestNet()); // only available for regtest
    assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
    consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;}
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward){
    const char* pszTimestamp = "Hindustan Times 01 Mar 2021 Its no joke humour an act of aggression";
    const CScript genesisOutputScript = CScript() << ParseHex("04089cfe44b6e4f52ed66fab40b61543eec19e7835c92184aa2a2ac4b0eed1688fc9ce0e44fcec2f076a2ed8d8dcf51ca7cc229b61284a1d365e78c91d982aac2d") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);}
static Checkpoints::MapCheckpoints mapCheckpoints = {
    { 0, uint256S("00000785a8752330bc13b72f9ede0039f0b4378834ba8894cf2bf7bd408c21eb")}};
static const Checkpoints::CCheckpointData data = { &mapCheckpoints, 1614602714, 0, 0 };
static Checkpoints::MapCheckpoints mapCheckpointsTestnet = {{0, uint256S("0x001")},};
static const Checkpoints::CCheckpointData dataTestnet = { &mapCheckpointsTestnet, 1614602714, 0, 0 };
static Checkpoints::MapCheckpoints mapCheckpointsRegtest = {{0, uint256S("0x001")}};
static const Checkpoints::CCheckpointData dataRegtest = { &mapCheckpointsRegtest, 1614602714, 0, 0 };
class CMainParams : public CChainParams{
public: CMainParams() {
        strNetworkID = "main";
        genesis = CreateGenesisBlock(1614602714, 21336943, 0x1e0ffff0, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000785a8752330bc13b72f9ede0039f0b4378834ba8894cf2bf7bd408c21eb"));
        assert(genesis.hashMerkleRoot == uint256S("0xafcc0078a384cc21ed8bb0bbe432f738c7fda818e82e730810ff5a33aa8df028"));
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.powLimit   = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV1 = uint256S("0x000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV2 = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 25;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nMNCollateralAmt = 10000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 600;
        consensus.nTargetTimespan = 10 * 60;
        consensus.nTargetTimespanV2 = 10 * 60;
        consensus.nTargetSpacing = 10 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 6;
        // spork keys
        consensus.strSporkPubKey = "0420f7a0bbdd1edcccc71b9cc06ccc3099c9427fc7ef375f977d74243548d5d816ea33f8e7c091c5944180f684c2ebb7681248d77d78812defb56b255803d09519";
        consensus.strSporkPubKeyOld = "042a90e857788567bb5178a9e6c4f4aed15757b8d686fe033866b294da2bdbfe64cee48faf90ec6b9f4f676f94d2abba6593aaf161c4b80e3ee49e901dc78b40e5";
        consensus.nTime_EnforceNewSporkKey = 1614602714;    //!> December 21, 2020 01:00:00 AM GMT
        consensus.nTime_RejectOldSporkKey = 1527811200;     //!> March 1, 2021 01:00:00 AM GMT
        // height-based activations
        consensus.height_last_invalid_UTXO = 999999999;
        consensus.height_last_ZC_AccumCheckpoint = 999999999;
        consensus.height_last_ZC_WrappedSerials = 0;
        consensus.height_ZC_RecalcAccumulators = 999999999;
        // validation by-pass
        consensus.nJokeCoinBadBlockTime = 1621503368;    // Skip nBit validation of Block 10001 per PR #915 */
        consensus.nJokeCoinBadBlockBits = 1c2469ac;    // Skip nBit validation of Block 10001 per PR #915 */
        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1614602714;        // October 17, 2017 4:30:00 AM
        consensus.ZC_HeightStart = 999999999;
        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 10001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 999999999;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            = 999999999;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         = 999999999;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         = 8100;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     = 0;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 999999999;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          = 999999999;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight          = 999999999;
        consensus.vUpgrades[Consensus::UPGRADE_V6_0].nActivationHeight = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock = uint256S("0x5b2482eca24caf2a46bb22e0545db7b7037282733faa3a42ec20542509999a64");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock =  uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock =  uint256S("0x00");
        pchMessageStart[0] = 0xd0;
        pchMessageStart[1] = 0xb1;
        pchMessageStart[2] = 0x9d;
        pchMessageStart[3] = 0x6a;
        nDefaultPort = 30504;
        vFixedSeeds.clear();
        vSeeds.clear();
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 43);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 4);
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 63);     // starting with 'S'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 171);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x02, 0x2D, 0x25, 0x33};
        base58Prefixes[EXT_SECRET_KEY] = {0x02, 0x21, 0x31, 0x2B};
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = {0x80, 0x00, 0x00, 0x77};
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
        // Reject non-standard transactions by default
        fRequireStandard = true;
        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ps";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "pviews";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivks";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "p-secret-spending-key-main";
        bech32HRPs[SAPLING_EXTENDED_FVK]         = "pxviews";}
    const Checkpoints::CCheckpointData& Checkpoints() const {return data;}};
/* Testnet (v5) */
class CTestNetParams : public CChainParams{
public: CTestNetParams() {
        strNetworkID = "test";
        genesis = CreateGenesisBlock(1614602714, 21336943, 0x1e0ffff0, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000785a8752330bc13b72f9ede0039f0b4378834ba8894cf2bf7bd408c21eb"));
        assert(genesis.hashMerkleRoot == uint256S("0xafcc0078a384cc21ed8bb0bbe432f738c7fda818e82e730810ff5a33aa8df028"));
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.powLimit   = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV1 = uint256S("0x000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV2 = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nMNCollateralAmt = 10000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 10 * 60;
        consensus.nTargetTimespanV2 = 10 * 60;
        consensus.nTargetSpacing = 10 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 20;
        // spork keys
        consensus.strSporkPubKey = "04019a8940636e61b444142fc827c8fab51af4571ad9b235ae61b71795da2b2340c795e6637f8f229f2c1407d422340c615e00461693c55d8d9f4e6ed0d319e317";
        consensus.strSporkPubKeyOld = "040329f801481d1f3665a776bf085bd05768ab1321a830e40dbcc1b60cb7004633a1db2cb0fe611db5c18655389af36583ad3b5f4186277689fa45dc0e488a9d02";
        consensus.nTime_EnforceNewSporkKey = 1614602714;    //!> December 21, 2020 01:00:00 AM GMT
        consensus.nTime_RejectOldSporkKey = 1522454400;     //!> March 1, 2021 01:00:00 AM GMT
        // height based activations
        consensus.height_last_invalid_UTXO = -1;
        consensus.height_last_ZC_AccumCheckpoint = -1;
        consensus.height_last_ZC_WrappedSerials = -1;
        consensus.height_ZC_RecalcAccumulators = 999999999;
        consensus.ZC_HeightStart = 0; // change to 9999?
        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1614602714;        // October 17, 2017 4:30:00 AM
        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 201;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            = 201;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         = 201;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         = 201;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     = 201;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 201;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          = 201;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight          = 201;
        consensus.vUpgrades[Consensus::UPGRADE_V6_0].nActivationHeight = 
        pchMessageStart[0] = 0x65;
        pchMessageStart[1] = 0x3a;
        pchMessageStart[2] = 0x88;
        pchMessageStart[3] = 0xfd;
        nDefaultPort = 40504;
        // nodes with support for servicebits filtering should be at the top
        vFixedSeeds.clear();
        vSeeds.clear();
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65); // Testnet pivx addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 6);  // Testnet pivx script addresses start with '8' or '9'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73);     // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet pivx BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x3a, 0x80, 0x61, 0xa0};
        // Testnet pivx BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = {0x3a, 0x80, 0x58, 0x37};
        // Testnet pivx BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = {0x80, 0x00, 0x00, 0x01};
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
        fRequireStandard = false;
        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ptestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "pviewtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivktestsapling";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "p-secret-spending-key-test";
        bech32HRPs[SAPLING_EXTENDED_FVK]         = "pxviewtestsapling"; }
    const Checkpoints::CCheckpointData& Checkpoints() const  {return dataTestnet;}};
/* Regression test */
class CRegTestParams : public CChainParams{
public: CRegTestParams() {
        strNetworkID = "regtest";
        genesis = CreateGenesisBlock(1614602714, 21336943, 0x1e0ffff0, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000785a8752330bc13b72f9ede0039f0b4378834ba8894cf2bf7bd408c21eb"));
        assert(genesis.hashMerkleRoot == uint256S("0xafcc0078a384cc21ed8bb0bbe432f738c7fda818e82e730810ff5a33aa8df028"));
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.powLimit   = uint256S("0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV1 = uint256S("0x000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV2 = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nMNCollateralAmt = 100 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 10 * 60;
        consensus.nTargetTimespanV2 = 10 * 60;
        consensus.nTargetSpacing = 10 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 20;
        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        consensus.strSporkPubKey = "04e0d06a69061c598354c606c29232b9b7179165d3cedaa6870f362a740dbc27232fc347a0d6ed2f1934c114e425907bec41c47843ca8943efb1da8dd2cfcb7844";
        consensus.strSporkPubKeyOld = "04f64424cb7a30a32f524a0010fe9291391cb17076fdb96422b9f5c30b65dd8acc52cf7f13370abeee899cbada3ddb47883876e28e941f2dd94f1b1c5fad104666";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;
        // height based activations
        consensus.height_last_invalid_UTXO = 999999999;
        consensus.height_last_ZC_AccumCheckpoint = 310;     // no checkpoints on regtest
        consensus.height_last_ZC_WrappedSerials = -1;
        consensus.height_ZC_RecalcAccumulators = 999999999;
        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 10;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 10;
        consensus.ZC_TimeStart = 0;                 // not implemented on regtest
        consensus.ZC_HeightStart = 0;
        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     = 400;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 251;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight          = 300;
        consensus.vUpgrades[Consensus::UPGRADE_V6_0].nActivationHeight = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        pchMessageStart[0] = 0x65;
        pchMessageStart[1] = 0x3a;
        pchMessageStart[2] = 0x88;
        pchMessageStart[3] = 0xfd;
        nDefaultPort = 51476; // same as pivx, wb never changed, also didn't change values below bc not in prev version, prolly could be as aboe
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet pivx addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet pivx script addresses start with '8' or '9'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73);     // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet pivx BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x3a, 0x80, 0x61, 0xa0};
        // Testnet pivx BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = {0x3a, 0x80, 0x58, 0x37};
        // Testnet pivx BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = {0x80, 0x00, 0x00, 0x01};
        // Reject non-standard transactions by default
        fRequireStandard = true;
        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ptestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "pviewtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivktestsapling";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "p-secret-spending-key-test";
        bech32HRPs[SAPLING_EXTENDED_FVK]         = "pxviewtestsapling"; }
    const Checkpoints::CCheckpointData& Checkpoints() const {return dataRegtest; }};
static std::unique_ptr<CChainParams> globalChainParams;
const CChainParams &Params(){
    assert(globalChainParams);
    return *globalChainParams;}
std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain){
    if (chain == CBaseChainParams::MAIN) return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET) return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST) return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));}
void SelectParams(const std::string& network){
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);}
void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight){
    globalChainParams->UpdateNetworkUpgradeParameters(idx, nActivationHeight);}
/* end */
