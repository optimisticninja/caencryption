#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sys/stat.h>
#include <fstream>

#include "../src/ca.h"

using namespace ::testing;

static const auto WOLFRAM_START_STATE = 0b0000000000000001000000000000000;

/**
 * Write state history to image file using state over time
 * @param state_history: 2D state history where rows are states over time
 * @param rule: rule to use as output filename
 */
// TODO: Use compressed image format (preferably PNG)
void write_pgm(const vector<bitset<31>>& state_history, int rule,
               const char* directory = "img", const char* suffix = "")
{
    if (state_history.empty()) {
        cerr << "ERROR: CA1D::write_pgm(): empty state history" << endl;
        exit(1);
    }

    // Create directory if doesn't exist
    struct stat st;
    if (stat(directory, &st) == -1) {
        // TODO: Correct permissions
        mkdir(directory, 0700);
    }

    ofstream pgm(string(directory) + "/" + to_string(rule) + string(suffix) + ".pgm", ios::out | ios::binary);
    pgm << "P2\n" << state_history[0].size() << " " << state_history.size() << "\n" << 1 << "\n";

    for (unsigned i = 0; i < state_history.size(); i++) {
        for (unsigned j = 0; j < state_history[0].size(); j++)
            pgm << !state_history[i][j] << " ";
        pgm << "\n";
    }

    pgm.close();
};

void test_rule(unsigned rule)
{
    bitset<31> state = WOLFRAM_START_STATE;
    ElementaryCA<31> ca(state);
    vector<bitset<31>> history;
    history.push_back(state);

    for (auto epochs = 0; epochs < 15; epochs++)
        history.push_back(ca.step(rule));

    write_pgm(history, rule);
}

TEST(CA, Rules)
{
    for (unsigned i = 0; i < 256; i++)
        test_rule(i);
}
