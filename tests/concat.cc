#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/concat.h"

using namespace ::testing;


TEST(Concat, Concat4_16)
{
    uint64_t expected = 0xDEADBEEFCAFEBABE;

    // Divide plaintext into 4 16 bit sections
    vector<bitset<16>> segments(4);
    for (size_t i = 0; i < segments.size(); i++) {
        segments[i] = expected >> (64 - (16 * (i + 1)));
    }

    bitset<64> actual = concat4<16>(segments[0], segments[1], segments[2], segments[3]);
    ASSERT_EQ(expected, actual.to_ulong());
}

TEST(Concat, Concat4_20)
{
    const string key = "CAFEBABEEE";
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

    bitset<80> merged = concat4<20>(key_segments[0], key_segments[1], key_segments[2], key_segments[3], true);

    ASSERT_EQ(whole, merged);
}
