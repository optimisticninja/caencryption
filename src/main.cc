#include <bitset>
#include <cstdint>
#include <iomanip>
#include <iostream>

#include "ca.h"
#include "concat.h"
#include "split.h"
#include "util.h"

using namespace std;

uint64_t schedule_key(const bitset<80>& key_material)
{
    bitset<64> round_key;

    for (unsigned round = 1; round <= 15; round++) {
        vector<bitset<20>> segments = split<80, 20, 4>(key_material);
        bool even = round % 2 == 0 ? true : false;
        bool alternate = false;

        for (unsigned segment = 0; segment < segments.size(); segment++) {
            ElementaryCA<20> ca(segments[segment]);
            segments[segment] = ca.step(alternate ? 102 : 60);
            alternate = !alternate;
        }

        bitset<80> merged = concat4<20>(segments[0], segments[1], segments[2], segments[3], true);
        unsigned limit = even ? key_material.size() : 64;
        unsigned start = even ? 16 : 0;

        for (unsigned round_bit = 0; start < limit; start++, round_bit++)
            round_key[round_bit] = merged[start];
    }

    return round_key.to_ulong();
}

uint64_t encrypt(uint64_t plaintext, uint64_t key)
{
    vector<bitset<16>> segments = split<64, 16, 4>(plaintext);

    for (unsigned round = 0; round < 4; round++) {
        for (unsigned segment = 0; segment < segments.size(); segment++) {
            ElementaryCA<16> ca(segments[segment], BOUNDARY_ZERO);
            segments[segment] = (segment % 2 == 0) ? ca.step(51) : ca.step(153);
        }
    }

    bitset<64> p2 = concat4<16>(segments[0], segments[1], segments[2], segments[3]);

    for (unsigned round = 1; round <= 15; round++) {
        uint64_t round_key = schedule_key(key);
        p2 ^= round_key;
        ElementaryCA<64> ca(p2);
        p2 = ca.step(170);
        p2 = ca.step(204);
        p2 = ca.step(15);
    }

    return p2.to_ulong();
}

uint64_t decrypt(uint64_t ciphertext, uint64_t key)
{
    for (unsigned round = 1; round <= 15; round++) {
        ciphertext ^= key;
        ElementaryCA<64> ca(ciphertext);
        ciphertext = ca.step(240).to_ulong();
        ciphertext = ca.step(204).to_ulong();
        ciphertext = ca.step(85).to_ulong();
    }

    vector<bitset<4>> segments = split<64, 4, 16>(ciphertext);

    for (unsigned round = 0; round < 4; round++) {
        for (unsigned segment = 0; segment < segments.size(); segment++) {
            ElementaryCA<4> ca(segments[segment], BOUNDARY_ZERO);
            segments[segment] = (segment % 2 == 0) ? ca.step(51) : ca.step(153);
        }
    }

    // Concatenate 4-bit sections
    return concat16(segments[0], segments[1], segments[2], segments[3], segments[4], segments[5], segments[6],
                    segments[7], segments[8], segments[9], segments[10], segments[11], segments[12],
                    segments[13], segments[14], segments[15])
        .to_ulong();
}

int main()
{
    uint64_t plaintext = 0xDEADBEEFCAFEBABE;
    const string key_str = "CAFEBABEEE";
    bitset<80> key_material = string_to_bitset<80>(key_str);
    uint64_t key = schedule_key(key_material);
    uint64_t ciphertext = encrypt(plaintext, key);
    uint64_t decrypted = decrypt(ciphertext, key);
    cout << "P: " << hex << plaintext << endl;
    cout << "K: " << hex << key << endl;
    cout << "E: " << hex << ciphertext << endl;
    cout << "D: " << hex << decrypted << endl;
}
