Specifications:
==========================
* Total number of coins: 25,000,000 TPAY
* Stake interest: 5% annual static inflation
* Confirmations: 6 blocks
* Coinbase Maturity: 100 blocks
* Min stake age: 2 hours
* 10 minute PoSv3 difficulty retarget
* RPC Port = 8800
* P2P Port = 8801
* TESTNET RPC Port = 16600
* TESTNET P2P Port = 16601


Inside:
==========================
* Tor Network on start up
* Ring Signatures for anonymous transactions
* Dual key stealth addresses
* ‘Zero Knowledge’ proofs
* Full decentralization

UNIX BUILD NOTES
================

To Build  (tested on ubuntu 17.10)
--------
```
Install dependencies: 

(first we will install openssl 1.1)

wget https://www.openssl.org/source/openssl-1.1.0e.tar.gz

tar xzf openssl-1.1.0e.tar.gz

cd openssl-1.1.0e

./config -Wl,--enable-new-dtags,-rpath,'$(LIBRPATH)'

make && make install

(now, we clone and compile the tokenpay source code!)

git clone --recurse-submodules https://github.com/tokenpay/tokenpay && cd tokenpay

sudo apt-get install build-essential \
    libtool autotools-dev automake pkg-config zlib1g-dev libevent-dev \
    bsdmainutils git libboost-all-dev libseccomp-dev libcap-dev libminiupnpc-dev libqt5gui5 \
    libqt5core5a libqt5webkit5-dev libqt5dbus5 qttools5-dev \
    qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev

./autogen.sh && ./configure && make
```



LINKS
==========================
* [Official Website](http://www.tokenpay.com/)

