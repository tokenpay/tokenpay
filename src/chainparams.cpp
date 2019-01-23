// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"
#include "chainparamsseeds.h"
#include "chainparams.h"
#include "main.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

int64_t CChainParams::GetProofOfWorkReward(int nHeight, int64_t nFees) const
{
	if (1 == nHeight)
    {
        return 18750000 * COIN; // 18.75 million coins
    }

    return 0;
};

int64_t CChainParams::GetProofOfStakeReward(const CBlockIndex* pindexPrev, int64_t nCoinAge, int64_t nFees) const
{
    // miner's coin stake reward based on coin age spent (coin-days)
    int64_t nSubsidy;

    if (IsProtocolV3(pindexPrev->nHeight))
    {
        nSubsidy = (pindexPrev->nMoneySupply / COIN) * COIN_YEAR_REWARD / (365 * 24 * (60 * 60 / 64));
    }
    else
    {
        nSubsidy = nCoinAge * COIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    }

    if (fDebug && GetBoolArg("-printcreation"))
        LogPrintf("GetProofOfStakeReward(): create=%s nCoinAge=%d\n", FormatMoney(nSubsidy).c_str(), nCoinAge);

    return nSubsidy + nFees;
}

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;

        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CBaseChainParams : public CChainParams {
public:
    CBaseChainParams() {
        const char* pszTimestamp = "TokenPay - August 2017";
        CTransaction txNew;
        txNew.nTime = GENESIS_BLOCK_TIME;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = GENESIS_BLOCK_TIME;

        vSeeds.push_back(CDNSSeedData("188.226.145.190", "188.226.140.132"));
      }
    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual const std::vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    std::vector<CAddress> vFixedSeeds;
};

class CMainParams : public CBaseChainParams
{
public:
    CMainParams()
    {
        strNetworkID = "main";

        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xf1;
        pchMessageStart[2] = 0xe2;
        pchMessageStart[3] = 0xb1;

        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 8801;
        nRPCPort = 8800;
        nBIP44ID = 0x80000109;

        //nLastPOWBlock = 2016; // Running for 1 Week after ICO
        nLastPOWBlock = 20000;
	    nFirstPosv2Block = 20001;
        nFirstPosv3Block = 20011;

        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20); // "standard" scrypt target limit for proof of work, results with 0,000244140625 proof-of-work difficulty
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimitV2 = CBigNum(~uint256(0) >> 48);

	    genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 517899;

	    hashGenesisBlock = genesis.GetHash();
	    assert(hashGenesisBlock == uint256("0x000008b71ab32e585a23f0de642dc113740144e94c0ece047751e9781f953ae9"));
        assert(genesis.hashMerkleRoot == uint256("0x0a2d4ac9cc16ab3d88ddcb53b368cfd866692d05ccdf79da4ad94efcf471e254"));

        base58Prefixes[PUBKEY_ADDRESS]      = list_of(65).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SCRIPT_ADDRESS]      = list_of(126).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SECRET_KEY]          = list_of(179).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[STEALTH_ADDRESS]     = list_of(40).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_PUBLIC_KEY]      = list_of(0x2C)(0x51)(0x3B)(0xD7).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY]      = list_of(0x2C)(0x51)(0xC1)(0x5A).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_KEY_HASH]        = list_of(137).convert_to_container<std::vector<unsigned char> >();         // x
        base58Prefixes[EXT_ACC_HASH]        = list_of(83).convert_to_container<std::vector<unsigned char> >();          // a
        base58Prefixes[EXT_PUBLIC_KEY_BTC]  = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >(); // xprv
        base58Prefixes[EXT_SECRET_KEY_BTC]  = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >(); // xpub

        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);
    }

    virtual Network NetworkID() const
    {
        return CChainParams::MAIN;
    }
};
static CMainParams mainParams;

//
// Testnet
//

class CTestNetParams : public CBaseChainParams
{
public:
    CTestNetParams()
    {
        const char* pszTimestamp = "TokenPay Testnet - 22nd of January 2019 - The Times 22/Jan/2019 Dozens of ministers ready to quit over no‑deal Brexit";
        CTransaction txNew;
        txNew.nTime = TESTNET_GENESIS_BLOCK_TIME;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.clear();
        genesis.vtx.push_back(txNew);
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nTime = TESTNET_GENESIS_BLOCK_TIME;

        strNetworkID = "test";
        strDataDir = "testnet";

        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa3;
        pchMessageStart[1] = 0x2c;
        pchMessageStart[2] = 0x44;
        pchMessageStart[3] = 0xb4;

        vAlertPubKey = ParseHex("042245fcbce048cb5a93c26dc1cdb613f2d866c66ede4bb806eb6ea373d8378775984d36905c9c8b1ba891901324351ac0d8c49bb46f937fa3c57eaae4da1e54aa");
                
        nDefaultPort = 16601;
        nRPCPort = 16600;
        nBIP44ID = 0x80000001;

        nLastPOWBlock = 215;
        nFirstPosv2Block = 190;
        nFirstPosv3Block = 199;

        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 5);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimitV2 = CBigNum(~uint256(0) >> 48);

        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 120930;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("04f622af0c331e6e6b2477468f7c33202a607b865daa3536a3dbe3fb61714d6d"));
        assert(genesis.hashMerkleRoot == uint256("2369d11bba0ebb4dde473781031188b0a4b27170e240e9ebcdac92df787664e4"));

        base58Prefixes[PUBKEY_ADDRESS]      = list_of(127).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SCRIPT_ADDRESS]      = list_of(196).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SECRET_KEY]          = list_of(255).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[STEALTH_ADDRESS]     = list_of(40).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_PUBLIC_KEY]      = list_of(0x76)(0xC0)(0xFD)(0xFB).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY]      = list_of(0x76)(0xC1)(0x07)(0x7A).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_KEY_HASH]        = list_of(75).convert_to_container<std::vector<unsigned char> >();          // X
        base58Prefixes[EXT_ACC_HASH]        = list_of(23).convert_to_container<std::vector<unsigned char> >();          // A
        base58Prefixes[EXT_PUBLIC_KEY_BTC]  = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >(); // tprv
        base58Prefixes[EXT_SECRET_KEY_BTC]  = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >(); // tpub

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);
    }

    virtual Network NetworkID() const
    {
        return CChainParams::TESTNET;
    }
};
static CTestNetParams testNetParams;


//
// Regression test
//
//class CRegTestParams : public CTestNetParams {
//public:
//    CRegTestParams() {
//        strNetworkID = "regtest";
//        strDataDir = "regtest";
//
//        nFirstPosv2Block = -1;
//        nFirstPosv3Block = -1;
//
//        pchMessageStart[0] = 0x05;
//        pchMessageStart[1] = 0xc5;
//        pchMessageStart[2] = 0x04;
//        pchMessageStart[3] = 0x3a;
//        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
//        genesis.nTime = 1479594600;
//        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
//        genesis.nNonce = 2;        
//		
//        hashGenesisBlock = genesis.GetHash();
//        nDefaultPort = 26601;

//        assert(hashGenesisBlock == uint256("0x0"));

//        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
//    }

//    virtual bool RequireRPCPassword() const { return false; }
//    virtual Network NetworkID() const { return CChainParams::REGTEST; }
//};
//static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

const CChainParams &TestNetParams() {
    return testNetParams;
}

const CChainParams &MainNetParams() {
    return mainParams;
}

void SelectParams(CChainParams::Network network)
{
    switch (network)
    {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
       // case CChainParams::REGTEST:
       //     pCurrentParams = &regTestParams;
       //     break;
        default:
            assert(false && "Unimplemented network");
            return;
    };
};

bool SelectParamsFromCommandLine()
{
    //bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    //if (fTestNet && fRegTest)
   // {
   //     return false;
   // };

    //if (fRegTest)
   // {
   //     SelectParams(CChainParams::REGTEST);
   // } else
    if (fTestNet)
    {
        SelectParams(CChainParams::TESTNET);
    } else
    {
        SelectParams(CChainParams::MAIN);
    };

    return true;
}
