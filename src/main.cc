#include <bitset>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

#include "ca.h"
#include "concat.h"

using namespace std;

void schedule_key(bitset<64>& round_key, const string& key, uint8_t round)
{
    // Create 80 bits of key material from key
    bitset<80> whole;
    for (unsigned i = 0; i < key.length(); ++i) {
        char c = key[i];
        for (int j = 7; j >= 0 && c; --j) {
            if (c & 0x1)
                whole.set(8 * i + j);
            c >>= 1;
        }
    }

    // Divide key into 20 bit sections
    vector<bitset<20>> key_segments(4);
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 20; j++)
            key_segments[i][j] = whole[i * 20 + j];

    for (unsigned segment = 0; segment < key_segments.size(); segment++) {
        CA<20> ca(key_segments[segment]);
        key_segments[segment] = (segment + 1) % 2 == 0 ? ca.step(102) : ca.step(60);
    }

    bitset<80> merged = concat4<20>(key_segments[0], key_segments[1], key_segments[2], key_segments[3]);

    bool even = round % 2 == 0;
    unsigned limit = even ? whole.size() : 64;
    unsigned start = even ? 16 : 0;

    for (unsigned round_bit = 0; start < limit; start++, round_bit++)
        round_key[round_bit] = merged[start];
}

uint64_t encrypt(uint64_t plaintext, const char* key)
{
    // Divide plaintext into 4 16 bit sections
    vector<bitset<16>> segments(4);
    for (size_t i = 0; i < segments.size(); i++) {
        segments[i] = plaintext >> (64 - (16 * (i + 1)));
    }

    // Diffusion of plaintext for 4 rounds
    for (unsigned i = 0; i < 4; i++) {
        for (unsigned segment = 0; segment < segments.size(); segment++) {
            CA<16> ca(segments[segment]);
            segments[segment] = (segment + 1) % 2 == 0 ? ca.step(51) : ca.step(153);
        }
    }

    bitset<64> encrypted = concat4<16>(segments[0], segments[1], segments[2], segments[3]);

    for (unsigned round = 1; round <= 15; round++) {
        bitset<64> scheduled_key;
        schedule_key(scheduled_key, key, round);
        encrypted ^= scheduled_key;

        CA<encrypted.size()> ca_reversible(encrypted);
        // Confusion of XORd result with reversible rules
        ca_reversible.step(170);
        ca_reversible.step(204);
        ca_reversible.step(15);
        encrypted = ca_reversible.state();
    }

    return encrypted.to_ulong();
}

uint64_t decrypt(uint64_t encrypted, const char* key)
{
    bitset<64> encrypted_bits(encrypted);

    for (int round = 15; round >= 1; round--) {
        bitset<64> scheduled_key;
        schedule_key(scheduled_key, key, round);
        encrypted_bits ^= scheduled_key;

        CA<encrypted_bits.size()> ca(encrypted_bits);
        ca.step(240);
        ca.step(204);
        ca.step(80);
        encrypted_bits = ca.state();
    }

    // Divide plaintext into 16 4 bit segments
    vector<bitset<4>> segments(16);
    for (unsigned i = 0; i < segments.size(); i++)
        for (size_t j = 0; j < segments[0].size(); j++)
            segments[i][j] = encrypted_bits[i * 4 + j];

    for (unsigned i = 1; i <= 4; i++) {
        for (unsigned segment = 0; segment <= segments.size(); segment++) {
            CA<4> ca(segments[segment], BOUNDARY_ZERO);
            // Run rule 153 for odd sections and 51 for even
            segments[segment] = (segment + 1) % 2 == 0 ? ca.step(51) : ca.step(153);
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
    const uint64_t plaintext = 0xDEADBEEFCAFEBABE;
    // TODO: Derive 80 bit digest from key string
    const char* key = "CAFEBABEEE";

    cout << "P: " << hex << plaintext << endl;
    bitset<64> encrypted = encrypt(plaintext, key);
    cout << "E: " << hex << encrypted.to_ulong() << endl;
    bitset<64> decrypted = decrypt(encrypted.to_ulong(), key);
    cout << "D: " << hex << decrypted.to_ulong() << endl;
}
