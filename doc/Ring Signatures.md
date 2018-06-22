## Ring signatures
The ring signatures are a crucial part to anonymize the sender of a transaction.

As previously mentioned, all tokens have their own public and private key. It consists of the public key of the token being spent, plus the public keys from 3 to 200 other tokens of the same value as the token being spent. The nature of ring signatures makes it impossible to discover member of the coins in the ring signature is being spent, and transactions are no longer traceable.

[](http://www.texpaste.com/n/xaypn9ni)

<aside class="notice">TO COMPLETE</aside>

### Double Spend Prevention

The ring signature tags (keyImage) of the spent TokenPay tokens are embedded in the transaction to prevent double spends. Each tag is unique to the
token, regardless of the other members of the ring signature.

When a new transaction contains a keyImage that has already been used, and thus is present in the blockchain, the new transaction will be rejected by the network.

## Spending TokenPay Tokens

There are two ways in which TokenPay tokens (TPAY) can be spent:

1. TPAY can be sent as TPAY.

* When sent as TokenPay tokens, new tokens are minted for the recipient to the value of the input TokenPay minus the transaction fee.*

2. TPAY can be redeemed as TPAY.

* When redeemed as TPAY, new TPAY is created to the value of the input TokenPay minus the transaction fee.*

In both cases the input tokens become unspendable. The transaction fee for spending TokenPay tokens is 100x greater than the fee for standard transactions. This is to cover the cost of the extra activity required by the network to transmit, verify and store TPAY transactions, which are larger and require more processing than standard transactions.

In order to spend TokenPay, we use ring signatures to sign the transaction. Our scheme consists of three functions, ```generateRingSignature```, ```generateKeyImage```, ```verifyRingSignature```.

For efficiency’s sake, when spending TokenPay, we get a list of all anonymous outputs in the system, then we remove coins that don't have enough same value outputs in the system, then we choose the smallest coin or least number of smallest coins that can cover the amount + transaction fee.

Each TokenPay Token consist of a unique private key and public key, so what happens when you spend your TokenPay Token? When doing a **normal** transaction (like in Bitcoin), you would prove you received an amount of coins by pointing to the transaction that got you the coins in the first place. That's signed with the private to prove you hold the keys to the address. Now for an **anonymous** transaction that procedure is different: we do not point to previous transactions. Rather we take a pool of coins (public keys of other people their coins) that have the same value as the coin we're trying to spend and then we drop our public key. We then say "we own one of the public keys in this pool of coins", or in cryptographical terms: a ring signature.