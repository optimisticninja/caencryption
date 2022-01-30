# caencryption

Alleged encryption algorithm using elementary cellular automata. Reference paper has many errors.

## Errata (thus far, need to fix alternating blocks)

* There are unspecified CA boundaries
* Selected rule 204 is essentially a NOP
* 16x4 bit split in decryption should be 4x6
    * Correct in diagram (figure 3), not algorithm listing (figure 3 in paper, which is 4x16)
* Decryption needs to invert the even/odd segment check

# References

* [Encryption Based on Cellular Automata for Wireless Devices in IoT Environment](./19736.pdf)
