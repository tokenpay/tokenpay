## Dual-key Stealth Addresses
### Introduction, History and Acknowlegements

Dual-key stealth addresses is one of the cornerstones of most anonymous cryptocurrencies currently available. The usage allows the recipient to remain anonymous, even after sharing his stealth address publicly.

Once the stealth address has been revealed to the payer(s), it will enable the payee to receive infinite unlinkable payments.

**That means that each payment to a Stealth address computes a new unused normal address into which the funds will be received. Any eavesdropper will be unable to link the two addresses.**

The original visionaries were the creators of Bytecoin, for whom we are thankful. Their technical documentation link has been included in the references *[1]*.

- The information they provide may not always apply to TokenPay.

We would also like to thank **Peter Todd**. Peter figured out how to implement stealth addresses into Bitcoin. You can find a link to his white paper in the references *[2]*.
He is a Bitcoin core developer and has done amazing work on Bitcoin and deserves the mention.

Peter is also associated with DarkWallet, whose wiki provided lots of information on the working of stealth addresses. Again, the link can be found in the references *[3]*.

The documentation at *sx* can also be very helpful to understand the concept of stealth addresses. They also provide tools that explain how they work. *[4]*.


### Address Encoding
```cpp
//formatting function of stealth address
std::string CEKAStealthKey::ToStealthAddress() const
{
// - return base58 encoded public stealth address

std::vector<uint8_t> raw;
raw = Params().Base58Prefix(CChainParams::STEALTH_ADDRESS);

raw.push_back(nFlags);
raw.insert(raw.end(), pkScan.begin(), pkScan.end());
raw.push_back(1); // number of spend pubkeys is 1
raw.insert(raw.end(), pkSpend.begin(), pkSpend.end());
raw.push_back(0); // number of signatures
raw.push_back(0); // ?
AppendChecksum(raw);

return EncodeBase58(raw);
}; //extkey.cpp
```

Stealth addresses are generated in a different way than normal bitcoin addresses, but they have a similair structure.
A dual-key stealth address contains a lot more information than a normal Bitcoin address because it requires the sender of a transaction to know the public scan key and the public spend key **which is not stored on the blockchain**.
All data required to perform such transaction is derivable from the stealth address itself.

![available languages](images/cpp.png)

Just like a Bitcoin address, all data below is **Base-58** encoded, which also explains the familiar looking form.


Version | Options | Public Scan Key | # Public Spend Keys | Public Spend Key | # of signatures | Length of prefix | Prefix | Checksum
--- | --- |--- | --- |--- | --- |--- | --- | ---
0x28 | 0  | 33 bytes | 1 | 33 bytes | 0 | 0 | (not used) |  4 bytes

Parameter | value
--- | ---
**Version:**  | The hexadecimal representation (= 0x28) of '40' is used for the current release on the mainnet. The version field to keep track of updates of the protocol.
**Options:** | Field is always set to 0.
**Public scan key:** | This fields holds the public scan key, 33 bytes of data.
**Amount of public spend keys:** | The current protocol uses one public spend key for each Stealth address. The ability to specify multiple spend keys remains in the protocol because it is useful for the implementation of multi-signature addresses.
**Public spend keys:** | This fields holds the public spend key, 33 bytes of data.
**Amount of signatures:** | Field is always set to 0.
**Length of prefix:** | Field is always set to 0.
**Prefix:** | No prefix is used, since length is equal to zero. Other coins do make use of this field, more information can be found [here](https://wiki.unsystem.net/en/index.php/DarkWallet/Stealth#Computing_prefixes)
**Checksum:** | Contains the first 4 bytes of the SHA-256 hash provided by the operation: SHA256(SHA256(previous_data_concatenated)). The same checksum function used in Bitcoin addresses.

### Address Computation and Transaction Format
```

Bob (receiver)
publicSpendKeyBob = public spend key
privateSpendKeyBob = private spend key

publicScanKeyBob = EC point, 33 bytes
privateScanKeyBob = integer, 32 bytes

This is where it gets a bit more complicated, but no magic, just math!
G = Generator, the primitive root

To continue on, we have to understand how the public addresses are generated.
A public key is the private key multiplied by the primitive root G.

publicSpendKeyBob = privateSpendKeyBob * G
publicScanKeyBob = privateScanKeyBob * G

Amy (sender)
e = ephem secret key = ephem private key
publicEphemKey = e * G
Knows the public scan key of Bob (publicScanKeyBob)!

Ephem is short for ephemeral, which means “short lived”. The ephem secret and public key are only used once and change on every stealth transaction.

Amy now publishes the public ephem key (publicEphemKey) to the receiver Bob.

Because of the diffie-hellman algorithm ONLY THE RECEIVER AND SENDER can deduct the shared secret from the public ephem key.

SharedSecret = SHA256(ephem private key  * publicScanKeyBob) (Formula for Sender)
SharedSecret = SHA256(privateScanKeyBob * publicEphemKey) (Formula for Receiver)

Amy can now generate the public key to where it should send the coins.
publicKeyToPay = publicSpendKeyBob + SharedSecret * G

Bob has two different ways of find out the the public key where the coins will go to.
When the wallet is encrypted:
publicKeyToPay = publicSpendKeyBob + SharedSecret * G

When the wallet is decrypted:
publicKeyToPay = (privateSpendKeyBob + SharedSecret)* G
```

If Bob would post a normal address publicly, anyone can explore the blockchain and see the transactions that belong to her. Stealth addresses solve this privacy issue. Bob can post her Stealth address publicly, and nobody will be any wiser of what transactions belong to her.

**It's extremely important to note that the payer derives a new NORMAL address from the Stealth address, to which the funds will be sent and in that process only allowing the payee to compute the corresponding private key.**

It uses a clever mathematical principle called the "Diffie-Hellman Key Exchange", which allows two entities to generate a shared secret based on their keypairs. An eavesdropper is unable to compute the shared secret, enabling private communication between the two. In the case an eavesdropper has full control over one of the keypairs (private and public key) then privacy is obviously broken.

It is important to mention that we can not use the ```SharedSecret``` directly to generate the keypair, because that would also allow the sender control over the private key. Instead a bit of mathematical "magic" (BIP32-style derivation) is applied: the ```SharedSecret``` is added to ```PrivateKeyBob``` and we use that to generate the new keypair.

It uses a system of dual-keys to allow the wallet software to scan for stealth payments (using ```ScanKeyBob```) but not make any transactions, because that would require decryption of the wallet/stealth key.
All transactions have to be made with the ```SpendKey```, only available after decrypting your wallet.
The dual-key is more of a security practice, it allows a wallet (while encrypted) to scan for transactions. If it weren't implemented, the wallet would have to remain decrypted, rendering the protection provided by the encryption useless.

The payee has to know the ephem public key to compute the ```SharedSecret```, but how is that data transferred from payer to payee? The ephem public key is embedded in the *stealth metadata*.

Any stealth transaction will require at least 2 outputs, the stealth metadata and the actual spendable output.

Each spendable output in a stealth transaction will be preceded by the metadata for that output. Regular spends do not need metadata, because there is no use of ephem keys in normal transactions.

Format goes as following:

Output | Content
--- | ---
out #1 | **metadata for spend A**
out #2 | **stealth spend A**
out #3 | metadata for spend B
out #4 | stealth spend B
out #5 | *regular spend C*
out #6 | metadata for spend D
out #7 | stealth spend D


### References
[1] ByteCoin, *Technical Documentation*, 2015, Available at [https://bytecoin.org/documentation/](https://bytecoin.org/documentation/

[2] Peter Todd, *[Bitcoin-development] Stealth Addresses*, 2014,  Available at  [https://sourceforge.net/p/bitcoin/mailman/message/31813471/](https://sourceforge.net/p/bitcoin/mailman/message/31813471/)

[3] Dark Wallet, *Stealth*, 2015,  Available at [https://wiki.unsystem.net/en/index.php/DarkWallet/Stealth](https://wiki.unsystem.net/en/index.php/DarkWallet/Stealth)

[4] Sx, *Stealth*, 2015,  Available at [https://sx.dyne.org/stealth.html](https://sx.dyne.org/stealth.html)
