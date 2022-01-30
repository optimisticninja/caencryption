#pragma once

#include <bitset>
#include <vector>

using namespace std;

template<size_t TotalBits, size_t NumBits, size_t NumSegments>
vector<bitset<NumBits>> split(const bitset<TotalBits>& whole)
{
    // Divide key into 20 bit sections
    vector<bitset<NumBits>> segments(NumSegments);
    for (unsigned i = 0; i < NumSegments; i++)
        for (unsigned j = 0; j < NumBits; j++)
            segments[i][j] = whole[i * NumBits + j];
    return segments;
}
