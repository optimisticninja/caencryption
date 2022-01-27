#pragma once

#include <bitset>

using namespace std;

template<size_t N = 16>
bitset<N * 4> concat4(const bitset<N>& b1, const bitset<N>& b2, const bitset<N>& b3, const bitset<N>& b4)
{
    string s1 = b1.to_string();
    string s2 = b2.to_string();
    string s3 = b3.to_string();
    string s4 = b4.to_string();
    return bitset<N * 4>(s1 + s2 + s3 + s4);
}

template<size_t N = 4>
bitset<N * 16> concat16(const bitset<N>& b1, const bitset<N>& b2, const bitset<N>& b3, const bitset<N>& b4,
                       const bitset<N>& b5, const bitset<N>& b6, const bitset<N>& b7, const bitset<N>& b8,
                       const bitset<N>& b9, const bitset<N>& b10, const bitset<N>& b11, const bitset<N>& b12,
                       const bitset<N>& b13, const bitset<N>& b14, const bitset<N>& b15, const bitset<N>& b16)
{
    string s1 = b1.to_string();
    string s2 = b2.to_string();
    string s3 = b3.to_string();
    string s4 = b4.to_string();
    string s5 = b5.to_string();
    string s6 = b6.to_string();
    string s7 = b7.to_string();
    string s8 = b8.to_string();
    string s9 = b9.to_string();
    string s10 = b10.to_string();
    string s11 = b11.to_string();
    string s12 = b12.to_string();
    string s13 = b13.to_string();
    string s14 = b14.to_string();
    string s15 = b15.to_string();
    string s16 = b16.to_string();
    return bitset<N * 16>(s16 + s15 + s14 + s13 + s12 + s11 + s10 + s9 + s8 + s7 + s6 + s5 + s4 + s3 + s2 +
                          s1);
}
