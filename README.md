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

![rule 60](img/scheduling/60.png)

![rule 102](img/scheduling/102.png)

**Encryption**

![rule 15](img/encrypt/15.png)

![rule 170](img/encrypt/170.png)

**Decryption**

![rule 85](img/encrypt/15.png)

![rule 240](img/encrypt/204.png)

**Common (encryption and decryption)**

In encryption/decryption round rule chains

![rule 204](img/encrypt/204.png)

For diffusion

![rule 29](img/common/29.png)

![rule 51](img/common/51.png)

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
