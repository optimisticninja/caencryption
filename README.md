# caencryption

Elementary CA-based encryption algorithm based on paper in references. Reference paper has errors, this is my identification and fixing of errata.

## Output of implementation

```
PLAINTEXT: deadbeefcafebabe
KEY      : f6c78663f3578746
ENCRYPTED: ce09bfd34be8a898
DECRYPTED: deadbeefcafebabe
```

## Rules used

**Key Scheduling**

Rule 60
![rule 60](img/scheduling/60.png)

Rule 102
![rule 102](img/scheduling/102.png)

**Encryption**

Rule 15
![rule 15](img/encrypt/15.png)

Rule 170
![rule 170](img/encrypt/170.png)

**Decryption**

Rule 85
![rule 85](img/decrypt/85.png)

Rule 24
![rule 240](img/decrypt/240.png)

**Common (encryption and decryption)**

In encryption/decryption round rule chains

Rule 204
![rule 204](img/common/204.png)

For diffusion

Rule 29
![rule 29](img/common/29.png)

Rule 51
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
