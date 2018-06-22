# Encrypted Messaging


## Key Sharing

The Elliptic Curve Diffie-Hellman (ECDH) key exchange method allows a secret key for encryption to be shared between the sender and recipient using the data embedded in the message along with the private keys of TokenPay addresses held by the sender and recipient.

This allows for distributing messages, of whom nobody knows the recipient of.

In order to send an encrypted message, you must possess the public key of the intended recipient. The public keys embedded in the TokenPay transaction blockchain when any amount is spent. If you are sending to an address that has not spent a transaction in the blockchain, the public key to that address must be provided manually.

TokenPay uses curve secp256k1 for all elliptic curve functions. This is the same curve used by bitcoin along with the vast majority of altcoins. With such widespread use underpinning systems of immense value it is extremely unlikely that curve secp256k1 is not secure.

Messages are signed by the keys they were sent with, this allows you to be confident of the origin of the messages you receive and also allows the public key of the sender to be extracted from the message, providing you all the information needed to send a reply.

## Encryption

**Detailed Procedure**

- Get public key *K* from destination address
- Find in database created from scanning for public keys in the blockchain and user additions.
- Generate 16 random bytes using a secure random number generator. Call them *IV*. Generate a new random EC key pair with private key called *r* and public key called *R*.
- Generate shared secret key *P* using public key *K* and private key *r*.
- Elliptic Curve Diffie-Hellman
- Use the shared secret key *P* and calculate the SHA512 hash *H*.
- ECDH_compute_key of OpenSSL
- Call the first 32 bytes of *H key_e* and the last 32 bytes *key_m*.
- Calculate a 32 byte MAC with HMACSHA256, using *key_m* as salt and (timestamp + destination + cipher text).
- Message authentication code used
- By also checking time-stamp and destination, recipients can be certain that these fields have not been tampered with.
- Generate a compact signature from the message data and sender's address.
- Only if not sending anonymously
- Recipient can verify that the message came from the sender
- Also allows the public key to be reconstructed (useful to reply)
- Include address and compact signature in the payload to be encrypted.
- Compress the plain-text message with lz4 if the message is larger than 128 bytes.
- Encrypt the payload data with AES-256-CBC, using *IV* as initialization vector, *key_e* as encryption key.

## Message Propagation 
Encrypted Messages are duplicated on every participating node in the TokenPay network – this prevents adversaries form uncovering the recipient of an encrypted message by using network traffic analysis.

The messages are stored on each node for a maximum period of 48 hours, after which the message is deleted. If the recipient is absent from the network for 48 hours or more the possibility exists that they may not receive messages sent to them. It is recommended to connect to the network each day in order to prevent such an occurrence.

Stored messages are grouped by time in divisions of 1 hour. The system operates on the grouped buckets of messages to save bandwidth.

## Synchronization of buckets between peer nodes 

Elliptic Curve Diffie-Hellman Key Exchange P2P Messaging
All of the messages sent and received are encrypted by the proven
AES-256-CBC algorithm and distributed between nodes in such a way as to
prevent the recipient's messages from being hacked or viewed by anyone that
it was not intended to, even if the hacker can view the entire network and run
nodes of the network.
To reduce the risk and inconvenience of sharing passwords, TokenPay has
implemented the proven and trusted method of Elliptic Curve Die-Hellman
or also known as an ECDH key exchange. This level of encryption is at the
same level as what a government security agency would use to protect top
secret files and documents.
The Elliptic Curve Digital Signature Algorithm or ECDSA is used to provide
confidence that the messages being transmitted arrive at the intended
destination. Messages are distributed over the existing TokenPay peer-to-peer
network, and a copy of each encrypted message is stored on each node for
48 hours. Following this period, the messages are permanently deleted with
no chance of retrieval by any party

## Decryption 
For each incoming message a node will attempt to decode the message with every owned address contained in the nodes white-list of addresses to receive messages on.

To speed up the process and allow for any payload format to be used, the Message Authentication Code (MAC) is calculated for the generated shared secret key, if it does not match the MAC provided in the message, decryption will fail and the function ends.

## Detailed Procedure

Get IV and R from the message block
Get the private key k of the recipient used to decrypt.
Generate shared secret key P using with private key k and public key R.
Elliptic Curve Diffie-Hellman
Use the shared secret key P to generate the SHA512 hash H.
Call the first 32 bytes of H key_e and the last 32 bytes key_m.
Calculate MAC' with HMACSHA256, using key_m as salt and hash of (time-stamp + destination + cipher text).
Compare MAC with MAC'.
Return if not equal, decryption will fail.
Decrypt the encrypted payload with AES-256-CBC, using IV as initialization vector, key_e as decryption key.
Decompress message portion with lz4 if message is larger than 128 bytes.
If address and compact signature were included then verify the message Address and compact signature are not included when message is sent anonymously strip the sender's public key and add it to the public key database.