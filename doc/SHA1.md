# SHA-1 Algorithm

SHA-1 (Secure Hash Algorithm 1) is a cryptographic hash function that produces a 160-bit (20-byte) hash value from an input message. It is widely used in security applications and protocols, such as SSL/TLS and digital signatures. However, SHA-1 is considered weak due to vulnerabilities, and its usage is discouraged in favor of stronger algorithms like SHA-256.

## Key Characteristics:

- **Output size**: 160 bits (20 bytes).
- **Input size**: Can process messages of any length.
- **Deterministic**: Same input always produces the same hash output.
- **Fast and efficient**: Computationally efficient, but vulnerable to collision attacks.
- **Pre-image resistant**: Hard to reverse-engineer the original message from the hash.

## Steps:

1. **Padding**: The message is padded to ensure its length is 512-bit.
2. **Parsing**: The padded message is divided into blocks of 512 bits.
3. **Initialization**: 5 constant hash values are initialized.
4. **Processing**: Each block is processed through 80 rounds of hashing using bitwise operations and logical functions.
5. **Finalization**: The resulting hash value is concatenated and output as a 160-bit digest.

## Security Considerations:

- SHA-1 is no longer considered secure for digital certificates or cryptographic signatures.
- It is vulnerable to collision attacks (two different inputs producing the same hash).

## Modern Usage:

- SHA-1 is being phased out in favor of more secure algorithms like SHA-256, particularly in TLS and HTTPS protocols.
