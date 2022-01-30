#pragma once

#include <bitset>

using namespace std;

template<size_t NumBits> bitset<NumBits> string_to_bitset(const string& str)
{
    bitset<NumBits> whole;
    for (unsigned i = 0; i < str.length(); ++i) {
        char c = str[i];
        for (int j = 7; j >= 0 && c; --j) {
            if (c & 0x1)
                whole.set(8 * i + j);
            c >>= 1;
        }
    }
    return whole;
}
