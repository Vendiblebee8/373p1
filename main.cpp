#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <getopt.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <bits/stdc++.h>
#include <sstream>
#include <set>
#include <unordered_set>
#include <functional>

using namespace std;

vector<string> transitions;
vector<string> endpoints;
vector<string> accepts;
int start;
int local;

bool fileOpen(string file, ifstream &fileObj)
{
    fileObj.open(file);
    if (fileObj.is_open())
    {
        return true;
    }
    else
    {
        cout << "does not open" << endl;
        return false;
    }
}

int main(int argc, char *argv[]) {
    int current_state = -1;
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <input_string>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Failed to open input file: " << argv[1] << endl;
        return 1;
    }

    string input = argv[2]; 

    map<pair<int, char>, unordered_set<int>> transitionTable;

    set<int> acceptStates;

    auto addTransition = [&](int fromState, char input, int toState) {
        transitionTable[make_pair(fromState, input)].insert(toState);
    };

    auto addAcceptState = [&](int state) {
        acceptStates.insert(state);
    };

    auto isValidCharacter = [&](char c) {
        return (isdigit(c) || isalpha(c));
    };

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string keyword;
        iss >> keyword;

        if (keyword == "state") {
            int state;
            string type1, type2;
            iss >> state >> type1 >> type2;
            if (type1 == "start" || type2 == "start") {
                current_state = state;
            }
            if (type1 == "accept" || type2 == "accept") {
                addAcceptState(state);
            }
        } else if (keyword == "transition") {
            int fromState, toState;
            char inputChar;
            iss >> fromState >> inputChar >> toState;
            addTransition(fromState, inputChar, toState);
        }
    }

    unordered_set<int> reachableStates;

    function<void(int, const string&)> computeReachableStates;
    computeReachableStates = [&](int state, const string& remainingInput) {
        if (remainingInput.empty()) {
            reachableStates.insert(state);
            return;
        }

        char inputChar = remainingInput[0];
        string remaining = remainingInput.substr(1);

        auto transitions = transitionTable.find(make_pair(state, inputChar));
        if (transitions != transitionTable.end()) {
            for (int nextState : transitions->second) {
                computeReachableStates(nextState, remaining);
            }
        }
    };

    computeReachableStates(current_state, input);

    bool accepts = false;
    for (int state : reachableStates) {
        if (acceptStates.count(state) > 0) {
            accepts = true;
            break;
        }
    }

    if (accepts) {
        cout << "accept";
        for (int state : acceptStates) {
            if (reachableStates.count(state) > 0) {
                cout << " " << state;
            }
        }
        cout << endl;
    } else {
        if (reachableStates.empty()) {
            cout << "reject" << endl;
        } else {
            cout << "reject";
            for (int state : reachableStates) {
                cout << " " << state;
            }
            cout << endl;
        }
    }

    return 0;
}

