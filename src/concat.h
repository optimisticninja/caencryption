#pragma once

#include <bitset>

using namespace std;

template<size_t N = 16>
bitset<N * 4> concat4(const bitset<N>& b1, const bitset<N>& b2, const bitset<N>& b3, const bitset<N>& b4,
                      bool reverse = false)
{
    string s1 = b1.to_string();
    string s2 = b2.to_string();
    string s3 = b3.to_string();
    string s4 = b4.to_string();
    return !reverse ? bitset<N * 4>(s1 + s2 + s3 + s4) : bitset<N * 4>(s4 + s3 + s2 + s1);
}
