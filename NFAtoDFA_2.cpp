#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <queue>

using namespace std;

using StateSet = set<string>; // A set of NFA states

map<StateSet, map<char, StateSet>> convertNFAtoDFA(const map<string, pair<string, string>> &nfaTransitions)
{
    map<StateSet, map<char, StateSet>> dfaTransitions; // DFA transition table
    vector<StateSet> unmarkedStates;                   // States to process

    // Initial DFA state is the set containing only the NFA start state (assuming it's "A")
    StateSet startState = {"A"};
    unmarkedStates.push_back(startState);

    while (!unmarkedStates.empty())
    {
        StateSet currentSet = unmarkedStates.back();
        unmarkedStates.pop_back();

        // Transition computation for current DFA state on inputs '0' and '1'
        for (char input : {'0', '1'})
        {
            StateSet newSet;

            // Compute the set of states reachable from any state in currentSet on this input
            for (const string &state : currentSet)
            {
                string nextState = (input == '0') ? nfaTransitions.at(state).first : nfaTransitions.at(state).second;

                // Split the string into individual states and add to the new set
                if (nextState != "-")
                {
                    for (char ch : nextState)
                    {
                        newSet.insert(string(1, ch));
                    }
                }
            }
            for (auto it = currentSet.begin(); it != currentSet.end(); it++)
            {
                cout << *it << " ";
            }
            cout << "  on " << input << " : ";
            for (auto it = newSet.begin(); it != newSet.end(); it++)
            {
                cout << *it << " ";
            }
            cout << endl;
            // If newSet is non-empty and not already in the DFA, add it to the list of unmarked states
            if (!newSet.empty() && dfaTransitions.find(newSet) == dfaTransitions.end())
            {
                unmarkedStates.push_back(newSet);
            }

            // Add the transition to the DFA transition table
            dfaTransitions[currentSet][input] = newSet;
        }
    }

    return dfaTransitions;
}

int main()
{
    // Example NFA transition table
    map<string, pair<string, string>> nfaTransitions = {
        {"A", {"B", "AB"}},
        {"B", {"-", "C"}},
        {"C", {"B", "C"}},
    };

    // Convert NFA to DFA
    auto dfaTransitions = convertNFAtoDFA(nfaTransitions);

    // Print DFA transitions for verification
    cout << "DFA State Transitions:" << endl;
    for (const auto &[dfaState, transitions] : dfaTransitions)
    {
        cout << "DFA State {";
        for (const string &state : dfaState)
        {
            cout << state << " ";
        }
        cout << "}:" << endl;

        for (const auto &[input, targetSet] : transitions)
        {
            cout << "  On " << input << ": {";
            for (const string &state : targetSet)
            {
                cout << state << " ";
            }
            cout << "}" << endl;
        }
    }

    return 0;
}

// #include <iostream>
// #include <bits/stdc++.h>
// using namespace std;

// int main()
// {
//     int numStates;
//     cin >> numStates; // Read the number of states

//     map<string, pair<string, string>> transitions;

//     // Read the transition table
//     for (int i = 0; i < numStates; ++i)
//     {
//         string state;
//         string transition0, transition1;
//         cin >> state >> transition0 >> transition1;

//         if (transition0 == "-")
//             transition0 = "-";
//         if (transition1 == "-")
//             transition1 = "-";

//         transitions[state] = {transition0, transition1};
//     }

//     // Display the transitions for verification
//     cout << "State transitions:" << endl;
//     for (const auto &[state, transition] : transitions)
//     {
//         cout << "State " << state << ": " << endl;
//         cout << "  On 0: " << transition.first << endl;
//         cout << "  On 1: " << transition.second << endl;
//     }

//     return 0;
// }
