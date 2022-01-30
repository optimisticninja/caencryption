# caencryption

Alleged encryption algorithm using elementary cellular automata. Reference paper has errors.

## Errata (thus far, need to fix alternating blocks)

* There are unspecified CA boundaries
* Selected rule 204 is essentially a NOP
* 16x4 bit split in decryption should be 4x6
    * Correct in diagram (figure 3), not algorithm listing (figure 3 in paper, which is 4x16)
* Decryption needs to invert the even/odd segment check
* Does rule 153 actually work for reversing the automata during decryption? I think not

## Current State

Need to fix the first and third 16 bit segments for decryption (see rule 153 note above)

```
PLAIN : deadbeefcafebabe
KEY   : f6c78663f3578746
ENC   : ce09ac834be8ba8d
DEC   : df8cbeefcbcbbabe
```

# References

* [Encryption Based on Cellular Automata for Wireless Devices in IoT Environment](./19736.pdf)
* [Invertible Wolfram automata](https://cell-auto.com/inv_wolfram/)
