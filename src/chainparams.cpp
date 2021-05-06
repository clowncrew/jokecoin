// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The Pivx developers
// Copyright (c) 2021+ The JokeCoin developers =)
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
/*
 * chainparams.cpp
 * 
 * dear reader,
 * 
 * as you prolly know, this file sets the parameters that largely govern the individual characteristics of this particular blockchain
 * 
 * change this file, and you're on your own chain, good luck and have fun
 * 
 * if you get a group to follow you, you've probably hard-forked
 * 
 * this file and the associated code has been refactored in the most recent JokeCoin update, based on pivx v4.3.0
 * this represents a hard fork for main
 * 
 * this file is a dev version, and should be assumbed to be total garbage ;)
 * gentle reader, of course my apologies for any errors, flaws, or deficiences 
 * which, alas, are all but sure to be numberous
 * 
 * first, we invoke the local sourcecode environment to begin. */
#include "chainparams.h"
#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "util.h"
#include "utilstrencodings.h"
#include <boost/assign/list_of.hpp>
#include <assert.h>
/*
 * now, we define a static block object for the genesis block according to the refactor'd design
 * only one of these is created, and it's always the same - it should be a singleton, i believe. 
 * this code does not yet specify the unique characteristics of the particular genesis block used in the application
 * rather, it just defines the form the block will take, to simplify the actual instantiation in memory 
 * the number 486604799 in "CScrip() << 486604799" is just a magic number; 
 * its not a parameter modified between jokecoin and pivx */
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
/* now, we define the actual genesis block
 * of course, it cannot be spent as it did not originally exist in the database
 * according to the old method, this was performed, for example,  as follows.
 * 
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 * 
 * as may be observed, this is a little ugly
 * 
 * the current version more or less packs everything into a short defintion to specify the unique genesis block for this chain.
 * if you compile this source with this block, you're on the specified chain with an initial block as follows.
 * however, some further parameters still need to be provided later when the function is called */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward) {
    const char* pszTimestamp = "Hindustan Times 01 Mar 2021 Its no joke humour an act of aggression";
    const CScript genesisOutputScript = CScript() << ParseHex("04089cfe44b6e4f52ed66fab40b61543eec19e7835c92184aa2a2ac4b0eed1688fc9ce0e44fcec2f076a2ed8d8dcf51ca7cc229b61284a1d365e78c91d982aac2d") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);}
/* where the vaules "Hindustan times ...aggression " and "04089...2d" are taken from lines 164 and 170 
 * of the present jokecoin version of this file
 * 
 * below, we assign a single checkpoint to specify the existing operational chain */
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of (0, uint256S("00000785a8752330bc13b72f9ede0039f0b4378834ba8894cf2bf7bd408c21eb"));
/* where the value "000...21eb" is from line 56 of the jokecoin v1.0.2
 * a few further parameters are still required to define the checkpoint graph, as follows. */
static const Checkpoints::CCheckpointData data = { &mapCheckpoints, 1614602714, 0, 0 };
/* these values represent the unix timestamp of the last checkpoint block, 
 * the total number of transactions between the genesis block and last checkpoint,
 * which is the value of tx= in the UpdateTip.debug.log lines,
 * and the estimated number of transactions per day after the checkpoint, respectively.
 * (evidently this last is irrelevant or s/t, lol)
 * these values are taken from lines 59-62 of jokecoin v1.0.2
 * similarly, we provide values for testnet and regnet taken from lines 65-80 */
static Checkpoints::MapCheckpoints mapCheckpointsTestnet = boost::assign::map_list_of(0, uint256S("0x001")); 
static const Checkpoints::CCheckpointData dataTestnet = { &mapCheckpointsTestnet, 1614602714, 0, 0 };
static Checkpoints::MapCheckpoints mapCheckpointsRegtest = boost::assign::map_list_of(0, uint256S("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = { &mapCheckpointsRegtest, 1614602714, 0, 0 };
/* now we're getting to the main controls. there's a bunch of stuff
 * however, it's perhaps slightly better organized in this code refactor
 * mostly everything is controlled by the new consensus code in src/consensus
 * specifically, most of these values are defined in in src/consensus/params.h
 * the mainnet parameters are defined first, followed by similar values for testnet and regnet
 * to begin, w're going to instantiate the genesis block in memory and tell the consensus sytem to use it for mainnet */
class CMainParams : public CChainParams {
public: CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        genesis = CreateGenesisBlock(1614602714, 21336943, 0x1e0ffff0, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000785a8752330bc13b72f9ede0039f0b4378834ba8894cf2bf7bd408c21eb"));
        assert(genesis.hashMerkleRoot == uint256S("0xafcc0078a384cc21ed8bb0bbe432f738c7fda818e82e730810ff5a33aa8df028"));
/* where the values in the createGenesisBlock call represent the unix timestamp of the genesis block, the nonce value, the number of bits, bitcoin 
 * genesis version used, and the genesis block reward, "COIN" is an arbitrary value from Satoshi indicating the value 100 000 000,
 * which is defined in src/amount.h.
 * these values for the genesis block are taken from lines 164-177 of this file from jokecoin v1.0.2
 * 
 * the following parameter disallows the mining protocol in miner.cpp from accepting blocks of the minimum work amount
 * during the PoW phase
 * it may be noted that all of these parmeters are defined in consensus/params.h
 * you can find where they're each called in the code with 'git grep whatever' if you wish to */
        consensus.fPowAllowMinDifficultyBlocks = false;
/* now we define the maximum work required to obtain a block in the proof of work phase and subsequent phases*/
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // PIVX starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
/* however, please note that the subsequent phases are not used - they are set in this file and defined in src/consensus/params.h
 * but otherwise never called! 
 * the powLimit value is taken from line 118 of jokecoin-chainparams-v1, but was not changed between jokecoin and pivx 3
 * 
 * the parameters below define the amount of blocks expected to be minted in a budget cycle period, ie. a month
 * this was reduced by an order of magnitude from pivx 3
 * and the number of confirmations required for the system to process the budget finalization fee */
        consensus.nBudgetCycleBlocks = 4320;       
        consensus.nBudgetFeeConfirmations = 6;     
/* these values are taken from lines 206 and 228 of jokecoinv1-chainparams
 * 
 * now we set i think - the number of confirmations required for coins generated to become mature and thus spendable 
 * this is 100 in pivx 
 * taken from line 127 in jokecoin v1 */
        consensus.nCoinbaseMaturity = 25;
/* the following paramters are specific the new time calculations introduced in this version of pivx
 * they are used in main, but frankly, i don't know exactly what they are doing
 * because these values are not used in pivx 3 and thus not in jokecoin 1,
 * im just retaining the values from pivx 4 here, which may not be our desired values, i have no idea 
 * it seems to be related to the new consensus system; somthing about modifying the time mechanisms used by the network
 * under certain conditions, or something? this one might benefit from some additional digging in the pivx code revision history */
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
/* this one is the number of masternodes that we allow the the see-saw payments to be off by
 * no, i don't know what sea-saw payments means lol
 * this value is taken from line 128 in jokecoin 1, but it's the same as pivx */
        consensus.nMasternodeCountDrift = 20;  
/* this next determines the minimum transaction fee
 * this value sis from line 129 of jokecoin 1
 * in contrast, pivx uses 21000000 */
        consensus.nMaxMoneyOut = 9999999999 * COIN;
/* this next value doesn't seem to be used by anything in the code, frankly.
 * its also present in pivx 3, and jokecoin 1 just used the same value on line 205 */
        consensus.nPoolMaxTransactions = 3;
/* proposals must be at least a day old to make it into a budget, pivx3 and jokecoin1 have same value as this */
        consensus.nProposalEstablishmentTime = 60 * 60 * 24; 
/* if im not mis-staken, this determines the minimum age for a valid stake in the normal proof of work phase
 * this value is not used in pivx3, so not antecedant to guess what it should be */
        consensus.nStakeMinAge = 60 * 60;
/* if "stake modifer v2" is active, then stakes are checked to to a certain dept in the chain versus an age
 * this was added as a 'network upgrade' in pivx4, and im not exactly sure when it becomes active, maybe never */
        consensus.nStakeMinDepth = 600;
/* this stuff sets the expected time taken to create a block for some arbitrary computational power
 * then a different timespan for the v2 pos phase, still idk when that becomes active?
 * and then spacing i think represents the relation between calculated blocks? 
 * the timespan value and spacing values are from jokecoin1 lines 125-126, but the timespanv2 i just made up a value
 * pivx3 had 1*60 and 1*60 for these values, ommiting v2, and pivx4 has 40*60, 30*60, and 1*60, so i kinda guessed here */
        consensus.nTargetTimespan = 10 * 60;
        consensus.nTargetTimespanV2 = 10 * 60;
        consensus.nTargetSpacing = 10 * 60;
/* as far as i can tell this value is unique to pivx4, and it seems to do something in the new consensus code
 * not sure exactly what, so ive retained pivx4's value here */
        consensus.nTimeSlotLength = 15;
/* now, we define the spork keys for this chain below.
 * the first values are taken from jokecoin1 lines 207-208, and the enforcement dates from 144-145 */
        consensus.strSporkPubKey = "042a90e857788567bb5178a9e6c4f4aed15757b8d686fe033866b294da2bdbfe64cee48faf90ec6b9f4f676f94d2abba6593aaf161c4b80e3ee49e901dc78b40e5";
        consensus.strSporkPubKeyOld = "04B433E6598390C992F4F022F20D3B4CBBE691652EE7C48243B81701CBDB7CC7D7BF0EE09E154E6FCBF2043D65AF4E9E97B89B5DBAF830D83B9B7F469A6C45A717";
        consensus.nTime_EnforceNewSporkKey = 1614602714;    //!> from the chain begining?
        consensus.nTime_RejectOldSporkKey = 1527811200;     //!> September 26, 2019 11:00:00 PM GMT, arbitrary ig
/* the following garbage, if im not mistaken, cleans up a zerocoin exploit
 * there must have been some kind of fake serial attack on the zerocoin procotol,
 * this is supposed to fix that, i think.
 * values are taken from lines 139, 151, 140, 138, 136, and 137, respectively */
        consensus.height_last_ZC_AccumCheckpoint = 999999999;
        consensus.height_last_ZC_WrappedSerials = 0;
        consensus.height_start_InvalidUTXOsCheck = 999999999;
        consensus.height_start_ZC_InvalidSerials = 999999999;
        consensus.height_start_ZC_SerialRangeCheck = 1;
        consensus.height_ZC_RecalcAccumulators = 999999999;
/* the next part, i've left turned off as yet
 * what it does it, it skips the validation on the first block after the PoW phase
 * since this block hasn't occured yet, there's no way to fir to have a timestamp yet, right?
 *     consensus.nPivxBadBlockTime = 1471401614;    // Skip nBit validation of Block 259201 per PR #915
 *     consensus.nPivxBadBlockBits = 0x1c056dac;    // Skip nBit validation of Block 259201 per PR #915
 * if this has to be turned on to get it to compile, im not sure what we would use here. 
 * i guess maybe just 999999999 and some random bit number
 * 
 * now we have the zerocoin values
 * im leaving this in for now, but id' like to remove all the zc stuff later on as much as possible
 * these values are taken from jokecoin 1 lines 213, 220, 219, 222, 221, 226, 135, and 152, respectively*/
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
/* this stuff is like, a bunch of switches that flip on at the specifed block
 * the first couple are just necessary ... */
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =  Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
/* now, this one should define the first PoS block after PoW is completed
 * so this is the value from line 132, "nLastPOWBlock" which was 10000, + 1 */
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 10001;
/* i think this one modifies the staking hash? or possibily the staking code itself more directly. value from l133 jc-v1 */
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 0;
/* the two aren't present in pivx3, set them to 0 as a guess */
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight = 0;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight = 0;
/* used value from jc-v1 l142, i think this has something to do with how consensus majority is calculated */
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight = 8100;
/* set this one to zero too as a zc, idk if this is correct */
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight = 0;
/* didn't edit this values, gotta poke around more and find out what these 'network upgrades' do */
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 1967000;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight = 2153200;
/* boilerplate of some sort */
        consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
/* these give block hashes of some of the above values. ideally, this could simply ommitted or have dummy values sub'd in */
        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock =
            uint256S("0x5b2482eca24caf2a46bb22e0545db7b7037282733faa3a42ec20542509999a64");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock =
                uint256S("0x37ea75fe1c9314171cff429a91b25b9f11331076d1c9de50ee4054d61877f8af");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock =
                uint256S("0x82629b7a9978f5c7ea3f70a12db92633a7d2e436711500db28b97efd48b1e527");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock =
                uint256S("0xe2448b76d88d37aba4194ffed1041b680d779919157ddf5cbf423373d7f8078e");
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock =
                uint256S("0x0ef2556e40f3b9f6e02ce611b832e0bbfe7734a8ea751c7b555310ee49b61456");
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock =
                uint256S("0x14e477e597d24549cac5e59d97d32155e6ec2861c1003b42d0566f9bf39b65d5");
/* this seems like some funky cryptographic thing, used values from lines 112-115 */
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xd0;
        pchMessageStart[1] = 0xb1;
        pchMessageStart[2] = 0x9d;
        pchMessageStart[3] = 0x6a;
/* taken from jc-v1 l117 */
        nDefaultPort = 30504;
/* clear out the seed nodes, we aren't using any. l183-184 */
        vFixedSeeds.clear();
        vSeeds.clear();
/* some kinds of magic keys or something, values taken from l186-192, which the exception of "staking address"
 * which is not in pivx3, so i left this at default*/
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 43);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 44);
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 63);     // starting with 'S'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 171);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();
/* give the seeds to the vector containers, but there aren't any anyway */
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
/* don't know what this does - Sapling??. id like to turn this off? */
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ps";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "pviews";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivks";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "p-secret-spending-key-main";}
/* wire it up */
    const Checkpoints::CCheckpointData& Checkpoints() const { return data; }};
static CMainParams mainParams;
/* testnet, values not guaranteed to be right? */
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
        consensus.strSporkPubKey = "04f64424cb7a30a32f524a0010fe9291391cb17076fdb96422b9f5c30b65dd8acc52cf7f13370abeee899cbada3ddb47883876e28e941f2dd94f1b1c5fad104666";
        consensus.strSporkPubKeyOld = "04348C2F50F90267E64FACC65BFDC9D0EB147D090872FB97ABAE92E9A36E6CA60983E28E741F8E7277B11A7479B626AC115BA31463AC48178A5075C5A9319D4A38";
        consensus.nTime_EnforceNewSporkKey = 1614602714;
        consensus.nTime_RejectOldSporkKey = 1522454400;
        consensus.height_last_ZC_AccumCheckpoint = 999999999;
        consensus.height_last_ZC_WrappedSerials = -1;
        consensus.height_start_InvalidUTXOsCheck = 999999999;
        consensus.height_start_ZC_InvalidSerials = 999999999;
        consensus.height_start_ZC_SerialRangeCheck = 1;
        consensus.height_ZC_RecalcAccumulators = 999999999;
        //consensus.nPivxBadBlockTime = 1489001494; // Skip nBit validation of Block 201 per PR #915
        //consensus.nPivxBadBlockBits = 0x1e0a20bd; // Skip nBit validation of Block 201 per PR #915
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
       /* these blocks are prolly invalid? idk?*/
       consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock =
                uint256S("0x258c489f42f03cb97db2255e47938da4083eee4e242853c2d48bae2b1d0110a6");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock =
                uint256S("0xfcc6a4c1da22e4db2ada87d257d6eef5e6922347ca1bb7879edfee27d24f64b5");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock =
                uint256S("0xc54b3e7e8b710e4075da1806adf2d508ae722627d5bcc43f594cf64d5eef8b30");
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock =
                uint256S("0x1822577176173752aea33d1f60607cefe9e0b1c54ebaa77eb40201a385506199");
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock =
                uint256S("0x30c173ffc09a13f288bf6e828216107037ce5b79536b1cebd750a014f4939882");
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
        // this probably isnt' correct - i used the spork key from jokecoin testnet above, but jokecoin v1 doesn't have a spork key for regnet
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
/* 
 * 
 * that's all, folks!
 * 
 * anything i fucked up here, you my sincere apologies, naturally
 * peace out, gentle reader
 * end */
