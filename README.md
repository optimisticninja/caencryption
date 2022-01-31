# caencryption

Elementary CA-based encryption algorithm using elementary cellular automata. Reference paper has errors.

## Output of implementation

```
PLAINTEXT: deadbeefcafebabe
KEY      : f6c78663f3578746
ENCRYPTED: ce09bfd34be8a898
DECRYPTED: deadbeefcafebabe
```

## Rules used

**Key Scheduling**

**Encryption**

**Decryption**

**Common**

## Errata from paper

* There are unspecified CA boundaries
* Selected rule 204 is essentially a NOP
* 16x4 bit split in decryption should be 4x6
    * Correct in diagram (figure 3), not algorithm listing (figure 3 in paper, which is 4x16)
* Decryption needs to invert the even/odd segment check
* Rule 153 does not work for the diffusion as it is not reversible, linear rule 29 has been used instead.

# References

* [Encryption Based on Cellular Automata for Wireless Devices in IoT Environment](./19736.pdf)
* [Invertible Wolfram automata](https://cell-auto.com/inv_wolfram/)
