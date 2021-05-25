// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The Pivx developers
// Copyright (c) 2021+ The JokeCoin developers =)
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "chainparams.h"
#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "util.h"
#include "utilstrencodings.h"
#include <boost/assign/list_of.hpp>
#include <assert.h>
static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward) {
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;
    CBlock genesis;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;}
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward) {
    const char* pszTimestamp = "Hindustan Times 01 Mar 2021 Its no joke humour an act of aggression";
    const CScript genesisOutputScript = CScript() << ParseHex("04089cfe44b6e4f52ed66fab40b61543eec19e7835c92184aa2a2ac4b0eed1688fc9ce0e44fcec2f076a2ed8d8dcf51ca7cc229b61284a1d365e78c91d982aac2d") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);}
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of (0, uint256S("00000785a8752330bc13b72f9ede0039f0b4378834ba8894cf2bf7bd408c21eb"));
static const Checkpoints::CCheckpointData data = { &mapCheckpoints, 1614602714, 0, 0 };
static Checkpoints::MapCheckpoints mapCheckpointsTestnet = boost::assign::map_list_of(0, uint256S("0x001")); 
static const Checkpoints::CCheckpointData dataTestnet = { &mapCheckpointsTestnet, 1614602714, 0, 0 };
static Checkpoints::MapCheckpoints mapCheckpointsRegtest = boost::assign::map_list_of(0, uint256S("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = { &mapCheckpointsRegtest, 1614602714, 0, 0 };
class CMainParams : public CChainParams {
public: CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        genesis = CreateGenesisBlock(1614602714, 21336943, 0x1e0ffff0, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000785a8752330bc13b72f9ede0039f0b4378834ba8894cf2bf7bd408c21eb"));
        assert(genesis.hashMerkleRoot == uint256S("0xafcc0078a384cc21ed8bb0bbe432f738c7fda818e82e730810ff5a33aa8df028"));
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // PIVX starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 4320;       
        consensus.nBudgetFeeConfirmations = 6;     
        consensus.nCoinbaseMaturity = 25;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24; 
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 600;
        consensus.nTargetTimespan = 10 * 60;
        consensus.nTargetTimespanV2 = 10 * 60;
        consensus.nTargetSpacing = 10 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.strSporkPubKey = "042a90e857788567bb5178a9e6c4f4aed15757b8d686fe033866b294da2bdbfe64cee48faf90ec6b9f4f676f94d2abba6593aaf161c4b80e3ee49e901dc78b40e5";
        consensus.strSporkPubKeyOld = "04B433E6598390C992F4F022F20D3B4CBBE691652EE7C48243B81701CBDB7CC7D7BF0EE09E154E6FCBF2043D65AF4E9E97B89B5DBAF830D83B9B7F469A6C45A717";
        consensus.nTime_EnforceNewSporkKey = 1614602714;    //!> from the chain begining?
        consensus.nTime_RejectOldSporkKey = 1527811200;     //!> September 26, 2019 11:00:00 PM GMT, arbitrary ig
        consensus.height_last_ZC_AccumCheckpoint = 999999999;
        consensus.height_last_ZC_WrappedSerials = 0;
        consensus.height_start_InvalidUTXOsCheck = 999999999;
        consensus.height_start_ZC_InvalidSerials = 999999999;
        consensus.height_start_ZC_SerialRangeCheck = 1;
        consensus.height_ZC_RecalcAccumulators = 999999999;
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input l220
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input l219
        consensus.ZC_MinMintConfirmations = 20;     // l222
        consensus.ZC_MinMintFee = 1 * CENT;         // l221
        consensus.ZC_MinStakeDepth = 200;           // l226
        consensus.ZC_TimeStart = 1614602714;        // jokecoin v1 line 135
        consensus.ZC_WrappedSerialsSupply = 0;   // line 152
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =  Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 10001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 999999999;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight = 999999999;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight = 999999999;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight = 8100;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight = 0;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 0;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight = 0; // might wanna come back and change this?
        consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock = uint256S("0x00");
        pchMessageStart[0] = 0xd0;
        pchMessageStart[1] = 0xb1;
        pchMessageStart[2] = 0x9d;
        pchMessageStart[3] = 0x6a;
        nDefaultPort = 30504;
        vFixedSeeds.clear();
        vSeeds.clear();
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 43);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 44);
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 63);     // starting with 'S'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 171);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ps";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "pviews";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivks";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "p-secret-spending-key-main";}
    const Checkpoints::CCheckpointData& Checkpoints() const { return data; }};
static CMainParams mainParams;
/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public: CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        genesis = CreateGenesisBlock(1614602714, 21336943, 0x1e0ffff0, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000785a8752330bc13b72f9ede0039f0b4378834ba8894cf2bf7bd408c21eb"));
        assert(genesis.hashMerkleRoot == uint256S("0xafcc0078a384cc21ed8bb0bbe432f738c7fda818e82e730810ff5a33aa8df028"));
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // PIVX starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 10 * 60;
        consensus.nTargetTimespanV2 = 10 * 60;
        consensus.nTargetSpacing = 10 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.strSporkPubKey = "040329f801481d1f3665a776bf085bd05768ab1321a830e40dbcc1b60cb7004633a1db2cb0fe611db5c18655389af36583ad3b5f4186277689fa45dc0e488a9d02";
        consensus.strSporkPubKeyOld = "04348C2F50F90267E64FACC65BFDC9D0EB147D090872FB97ABAE92E9A36E6CA60983E28E741F8E7277B11A7479B626AC115BA31463AC48178A5075C5A9319D4A38";
        consensus.nTime_EnforceNewSporkKey = 1614602714;
        consensus.nTime_RejectOldSporkKey = 1522454400;
        consensus.height_last_ZC_AccumCheckpoint = 999999999;
        consensus.height_last_ZC_WrappedSerials = -1;
        consensus.height_start_InvalidUTXOsCheck = 999999999;
        consensus.height_start_ZC_InvalidSerials = 999999999;
        consensus.height_start_ZC_SerialRangeCheck = 1;
        consensus.height_ZC_RecalcAccumulators = 999999999;
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
        consensus.ZC_TimeStart = 1614602714;
        consensus.ZC_WrappedSerialsSupply = 0;   // WrappedSerials only on main net
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 51197;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            = 201576;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         = 444020;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         = 851019;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     = 1106100;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 1214000;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          = 1347000;
        consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock = uint256S("0x00");
        pchMessageStart[0] = 0x65;
        pchMessageStart[1] = 0x3a;
        pchMessageStart[2] = 0x88;
        pchMessageStart[3] = 0xfd;
        nDefaultPort = 40504;
        vFixedSeeds.clear();
        vSeeds.clear();
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65); // Testnet pivx addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 6);  // Testnet pivx script addresses start with '8' or '9'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73);     // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet pivx BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet pivx BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet pivx BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ptestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "pviewtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivktestsapling";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "p-secret-spending-key-test";}
    const Checkpoints::CCheckpointData& Checkpoints() const { return dataTestnet; }};
static CTestNetParams testNetParams;
/* regnet */
class CRegTestParams : public CTestNetParams {
public: CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000785a8752330bc13b72f9ede0039f0b4378834ba8894cf2bf7bd408c21eb"));
        assert(genesis.hashMerkleRoot == uint256S("0xafcc0078a384cc21ed8bb0bbe432f738c7fda818e82e730810ff5a33aa8df028"));
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // PIVX starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 10 * 60;
        consensus.nTargetTimespanV2 = 10 * 60;
        consensus.nTargetSpacing = 10 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.strSporkPubKey = "04f64424cb7a30a32f524a0010fe9291391cb17076fdb96422b9f5c30b65dd8acc52cf7f13370abeee899cbada3ddb47883876e28e941f2dd94f1b1c5fad104666";
        consensus.strSporkPubKeyOld = "";
        // this probably isnt' correct - i used the spork key from jokecoin testnet, but jokecoin v1 doesn't have a spork key for regnet
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;
        consensus.height_last_ZC_AccumCheckpoint = 310;     // no checkpoints on regtest
        consensus.height_last_ZC_WrappedSerials = -1;
        consensus.height_start_InvalidUTXOsCheck = 999999999;
        consensus.height_start_ZC_InvalidSerials = 999999999;
        consensus.height_start_ZC_SerialRangeCheck = 300;
        consensus.height_ZC_RecalcAccumulators = 999999999;
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
        consensus.ZC_WrappedSerialsSupply = 0;
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     = 400;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 251;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight       = 300;
        consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock = uint256S("0x00");
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock = uint256S("0x00");
        pchMessageStart[0] = 0x65;
        pchMessageStart[1] = 0x3a;
        pchMessageStart[2] = 0x88;
        pchMessageStart[3] = 0xfd;
        nDefaultPort = 51476;
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();}      //! Testnet mode doesn't have any DNS seeds.
    const Checkpoints::CCheckpointData& Checkpoints() const { return dataRegtest; }
    void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight) {
        assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
        consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;}};
static CRegTestParams regTestParams;
static CChainParams* pCurrentParams = 0;
const CChainParams& Params() {
    assert(pCurrentParams);
    return *pCurrentParams;}
CChainParams& Params(CBaseChainParams::Network network){
    switch (network) {
    case CBaseChainParams::MAIN: return mainParams;
    case CBaseChainParams::TESTNET: return testNetParams;
    case CBaseChainParams::REGTEST: return regTestParams;
    default: assert(false && "Unimplemented network"); return mainParams;}}
void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);}
bool SelectParamsFromCommandLine() {
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES) return false;
    SelectParams(network);
    return true;}
void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight) {
    regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);}
/* end */
