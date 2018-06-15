
# TokenPay RPC Commands

## anoninfo

```json
anoninfo [recalculate]
```

## anonoutputs

```json
anonoutputs [systemTotals] [show_immature_outputs]
```

## checkwallet
Check wallet for integrity.

## clearwallettransactions
Delete all transactions from wallet - reload with reloadanondata
Warning: Backup your wallet first!

## estimateanonfee

```json
estimateanonfee <amount> <ring_size> [narration]
```

<amount> is a real and is rounded to the nearest 0.000001
Used to estimate the anon fee with a given amount and ring size.


## getnewpubkey

```json
getnewpubkey [account]
```

## getnewstealthaddress

```json
getnewstealthaddress [label]
```

## getstakinginfo

## getsubsidy

```json
getsubsidy [nTarget]
```

## getwork

```json
getwork [data]
```

## getworkex

```json
getworkex [data, coinbase]
```

## help

```json
help [command]
```

## importstealthaddress

```json
importstealthaddress <scan_secret> <spend_secret> [label]
```

## liststealthaddresses

```json
liststealthaddresses [show_secrets=0]
```

List owned stealth addresses.

When used with show_secrets=1 it will return a list of all stealth addresses, the labels, the scan secrets and spend secrets.

## listtransactions

```json
listtransactions [account] [count=10] [from=0] [show_coinstake=1]
```

Returns up to [count] most recent transactions skipping the first [from] transactions for account [account].
If you want to process Stealth transactions (SDT) then you want to use this function.

There a bit of a trick necessary to get the stealth transactions, easier explained in an example:
Stealth address = "smYmoN9xyenTSow9RP4ecf172sdKTeN9k4ZVCiUhFY6MTQRqSS2LRSZSZECwnZSb1a7EaCNc4aPrmrkexBXEs4qeJTZ6m9NjJBgnQE"
=> Account name = "ao smYmoN9xyenTSow9..."

When stealth addresses are generated their account name is "ao first_16_chars...", the 3 dots at the end are important!

## makekeypair

```json
makekeypair [prefix]
```

## nextorphan

```json
nextorphan [connecthash]
```

## reloadanondata
Removes all wallet transactions, anon cache, and rebuilds everything from zero.

## repairwallet
Repair wallet if checkwallet reports any problem

## resendtx

## reservebalance

```json
reservebalance [<reserve> [amount]]
```

## rewindchain

```json
rewindchain <number>
```

## scanforalltxns
Scans for all transactions and overwrites prior history and does update.
```json
scanforalltxns [fromHeight]
```

## scanforstealthtxns
Scans for all Stealth transactions and overwrites prior history and does update.
```json
scanforstealthtxns [fromHeight]
```

## sendalert

```json
sendalert <message> <privatekey> <minver> <maxver> <priority> <id> [cancelupto]
```

## sendanontoanon

```json
sendanontoanon <stealth_address> <amount> <ring_size> [narration] [comment] [comment-to]
```

## sendanontopay

```json
sendanontopay <stealth_address> <amount> <ring_size> [narration] [comment] [comment-to]
```


## sendtpaytoanon

```json
sendtpaytoanon <stealth_address> <amount> [narration] [comment] [comment-to]
```


## sendtostealthaddress

```json
sendtostealthaddress <stealth_address> <amount> [comment] [comment-to] [narration]
```


## setbestblockbyheight <height>

```json
setbestblockbyheight <height>
```


## settxfee

```json
settxfee <amount>
```

## stop

Stop the tokenpay server


## thinscanmerkleblocks

```json
thinscanmerkleblocks <height>
```

## txnreport

```json
txnreport [collate_amounts] [show_key_images]
```

## thinforcestate

```json
thinforcestate <state>
```

## thinscanmerkleblocks

```json
thinscanmerkleblocks <height>
```

## txnreport

```json
txnreport [collate_amounts] [show_key_images]
```

## validatepubkey

```json
validatepubkey <tokenpaycashpubkey>
```

# SMSG API
## smsgaddkey
smsgaddkey <address> <pubkey>

```json
smsgaddkey <address> <pubkey>
```

## smsgbuckets [stats|dump]

```json
smsgbuckets [stats|dump]
```

Display some statistics.

## smsgdisable

Disable secure messaging

## smsgenable

Enable secure messaging

## smsggetpubkey

```json
smsggetpubkey <address>
```

Returns the public key for a given address.

```json
Example:
smsggetpubkey tFyq452LPtDotWat8PFwEV5oPoWDqagLNv
Output:
{
"result" : "Success.",
"address in wallet" : "tFyq452LPtDotWat8PFwEV5oPoWDqagLNv",
"compressed public key" : "26S8iEiv2754RskjkWqRZkbZ22iNRYPgK7sUPyRPueXni"
}
```

## smsginbox

```json
smsginbox [all|unread|clear]
```

Decrypt and display all received messages.
"all" will show all messages, "unread" will only show the unread messages.

<aside class="warning">Warning: clear will delete all messages.</aside>

# Support
For support please visit one of the links below:

Email: Team@tokenpay.com

# General Reference

# JSON-RPC API Reference
TokenPay has many new components meaning we also added extra API calls on top of the original [Bitcoin API.](¶https://bitcoin.org/en/developer-reference#bitcoin-core-apis)

- ```addmultisigaddress``` *adds a P2SH multisig address to the wallet.*
- ```addnode``` *attempts to add or remove a node from the addnode list, or to try a connection to a node once.*
- ```backupwallet``` *safely copies `wallet.dat`<!--noref--> to the specified file, which can be a directory or a path with filename.*
- ```createmultisig``` *creates a P2SH multi-signature address.*
- ```createrawtransaction``` *creates an unsigned serialized transaction that spends a previous output to a new output with a P2PKH or P2SH address. The transaction is not stored in the wallet or transmitted to the network.*
- ```decoderawtransaction``` *decodes a serialized transaction hex string into a JSON object describing the transaction.*
- ```decodescript``` *decodes a hex-encoded P2SH redeem script.*
- ```dumpprivkey``` *returns the wallet-import-format (WIP) private key corresponding to an address. (But does not remove it from the wallet.)*
- ```dumpwallet``` *creates or overwrites a file with all wallet keys in a human-readable format.*
- ```encryptwallet``` *encrypts the wallet with a passphrase.  This is only to enable encryption for the first time. After encryption is enabled, you will need to enter the passphrase to use private keys.*
- ```estimatefee``` *estimates the transaction fee per kilobyte that needs to be paid for a transaction to be included within a certain number of blocks.*
- ```estimatepriority``` *estimates the priority that a transaction needs in order to be included within a certain number of blocks as a free high-priority transaction.*
- ```generate``` *nearly instantly generates blocks (in regtest mode only)*
- ```getaccount``` *returns the name of the account associated with the given address.*
- ```getaccountaddress``` *returns the current Bitcoin address for receiving payments to this account. If the account doesn't exist, it creates both the account and a new address for receiving payment.  Once a payment has been received to an address, future calls to this RPC for the same account will return a different address.*
- ```getaddednodeinfo``` *returns information about the given added node, or all added nodes (except onetry nodes). Only nodes which have been manually added using the `addnode` RPC will have their information displayed.*
- ```getaddressesbyaccount``` *returns a list of every address assigned to a particular account.*
- ```getbalance``` *gets the balance in decimal bitcoins across all accounts or for a particular account.*
- ```getbestblockhash``` *returns the header hash of the most recent block on the best block chain.*
- ```getblock``` *gets a block with a particular header hash from the local block database either as a JSON object or as a serialized block.*
- ```getblockchaininfo``` *provides information about the current state of the block chain.*
- ```getblockcount``` *returns the number of blocks in the local best block chain.*
- ```getblockhash``` *returns the header hash of a block at the given height in the local best block chain.*
- ```getblocktemplate``` *gets a block template or proposal for use with mining software.*
- ```getchaintips``` *returns information about the highest-height block (tip) of each local block chain.*
- ```getconnectioncount``` *returns the number of connections to other nodes.*
- ```getdifficulty``` *returns the proof-of-work difficulty as a multiple of the minimum difficulty.*
- ```getgenerate``` *returns true if the node is set to generate blocks using its CPU.*
- ```getmempoolinfo``` *returns information about the node's current transaction memory pool.*
- ```getmininginfo``` *returns various mining-related information.*
- ```getnettotals``` *returns information about network traffic, including bytes in, bytes out, and the current time.*
- ```getnetworkhashps``` *returns the estimated current or historical network hashes per second based on the last 'n' blocks.*
- ```getnetworkinfo``` *returns information about the node's connection to the network.*
- ```getnewaddress``` *returns a new TokenPay address for receiving payments. If an account is specified, payments received with the address will be credited to that account.*
- ```getpeerinfo``` *returns data about each connected network node.*
- ```getrawchangeaddress``` *returns a new TokenPay address for receiving change. This is for use with raw transactions, not normal use.*
- ```getrawmempool``` *returns all transaction identifiers (TXIDs) in the memory pool as a JSON array, or detailed information about each transaction in the memory pool as a JSON object.*
- ```getrawtransaction``` *gets a hex-encoded serialized transaction or a JSON object describing the transaction.*
- ```getreceivedbyaccount``` *returns the total amount received by addresses in a particular account from transactions with the specified number of confirmations.*
- ```getreceivedbyaddress``` *returns the total amount received by the specified address in transactions with the specified number of confirmations.*
- ```gettransaction``` *gets detailed information about an in-wallet transaction.*
- ```gettxout``` *returns details about a transaction output.  Only unspent transaction outputs (UTXOs) are guaranteed to be available.*
- ```gettxoutsetinfo``` *returns statistics about the confirmed unspent transaction output (UTXO) set.*
- ```getunconfirmedbalance``` *returns the wallet's total unconfirmed balance.*
- ```getwalletinfo``` *provides information about the wallet.*
- ```help``` *lists all available public RPC commands, or gets help for the specified RPC.  Commands which are unavailable will not be listed, such as wallet RPCs if wallet support is disabled.*
- ```importaddress``` *adds an address or pubkey script to the wallet without the associated private key, allowing you to watch for transactions affecting that address or pubkey script without being able to spend any of its outputs.*
- ```importprivkey``` *adds a private key to your wallet. The key should be formatted in the wallet import format created by the `dumpprivkey` RPC.*
- ```importwallet``` *imports private keys from a file in wallet dump file format (see the `dumpwallet` RPC). These keys will be added to the keys currently in the wallet.*
- ```keypoolrefill``` *fills the cache of unused pre-generated keys (the keypool).*
- ```listaccounts``` *lists accounts and their balances.*
- ```listaddressgroupings``` *lists groups of addresses that may have had their common ownership made public by common use as inputs in the same transaction or from being used as change from a previous transaction.*
- ```listlockunspent``` *returns a list of temporarily unspendable (locked) outputs.*
- ```listreceivedbyaccount``` *lists the total number of bitcoins received by each account.*
- ```listreceivedbyaddress``` *lists the total number of bitcoins received by each address.*
- ```listsinceblock``` *gets all transactions affecting the wallet which have occurred since a particular block, plus the header hash of a block at a particular depth.*
- ```listtransactions``` *returns the most recent transactions that affect the wallet.*
- ```listunspent``` *returns an array of unspent transaction outputs belonging to this wallet.*
- ```lockunspent``` *temporarily locks or unlocks specified transaction outputs.*
- ```move``` *moves a specified amount from one account in your wallet to another using an off-block-chain transaction.*
- ```ping``` *sends a P2P ping message to all connected nodes to measure ping time.*
- ```prioritisetransaction``` *adds virtual priority or fee to a transaction, allowing it to be accepted into blocks mined by this node (or miners which use this node) with a lower priority or fee.*
- ```sendfrom``` *spends an amount from a local account to a TokenPay address.*
- ```sendmany``` *creates and broadcasts a transaction which sends outputs to multiple addresses.*
- ```sendrawtransaction``` *validates a transaction and broadcasts it to the peer-to-peer network.*
- ```sendtoaddress``` *sends an amount to a given address.*
- ```setaccount``` *puts the specified address in the given account.*
- ```setgenerate``` *enables or disables hashing to attempt to find the next block.*
- ```settxfee``` *sets the transaction fee per kilobyte paid by transactions created by this wallet.*
- ```signmessage``` *signs a message with the private key of an address.*
- ```signrawtransaction``` *signs a transaction in the serialized transaction format using private keys stored in the wallet or provided in the call.*
- ```stop``` *safely shuts down the TokenPay Core server.*
- ```submitblock``` *accepts a block, verifies it is a valid addition to the block chain, and broadcasts it to the network.*
- ```validateaddress``` *returns information about the given TokenPay address.*
- ```verifychain``` *verifies each entry in the local block chain database.*
- ```verifymessage``` *verifies a signed message.*
- ```walletlock``` *removes the wallet encryption key from memory, locking the wallet. After calling this method, you will need to call `walletpassphrase` again before being able to call any methods which require the wallet to be unlocked.*
- ```walletpassphrase``` *stores the wallet decryption key in memory for the indicated number of seconds. Issuing the `walletpassphrase` command while the wallet is already unlocked will set a new unlock time that overrides the old one.*
- ```walletpassphrasechange``` *changes the wallet passphrase from 'old passphrase' to 'new passphrase'.*