#include <bits/stdc++.h>
using namespace std;

int main()
{
    // Hardcoded example
    int numStates = 5;
    vector<string> states = {"q1", "q2", "q3", "q4", "q5"};

    // Fixed alphabet with two symbols: '0' and '1'
    vector<char> alphabet = {'0', '1'};

    // Hardcoded transition table
    map<string, map<char, string>> transitionTable = {
        {"q0", {{'0', "q2"}, {'1', "q4"}}},
        {"q1", {{'0', "q2"}, {'1', "q4"}}},
        {"q2", {{'0', "q3"}, {'1', "q5"}}},
        {"q3", {{'0', "q2"}, {'1', "q5"}}},
        {"q4", {{'0', "q3"}, {'1', "q5"}}},
        {"q5", {{'0', "q3"}, {'1', "q5"}}}};

    // Hardcoded accepting states
    set<string> acceptingStates = {"q5"};
    cout << "DFA Transition Table:" << endl;
    for (const auto &state : states)
    {
        cout << "State " << state << ": ";
        for (char sym : alphabet)
        {
            cout << "On " << sym << " -> " << transitionTable[state][sym] << " ";
        }
        cout << endl;
    }
    // Create a matrix for marking pairs of states as distinguishable
    vector<vector<int>> distinguishable(numStates, vector<int>(numStates, 0));

    // Mark pairs where one is accepting and the other is not as distinguishable
    for (int i = 0; i < numStates; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            if ((acceptingStates.count(states[i]) > 0) != (acceptingStates.count(states[j]) > 0))
                distinguishable[i][j] = 1;
            if (i == j)
                distinguishable[i][j] = 2;
        }
    }
    for (int i = 0; i < numStates; ++i)
    {
        for (int j = 0; j < numStates; ++j)
        {
            cout << distinguishable[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    bool updated;
    do
    {
        updated = false;
        for (int i = 0; i < numStates; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (!distinguishable[i][j])
                {
                    for (char symbol : alphabet)
                    {
                        string nextStateI = transitionTable[states[i]][symbol];
                        string nextStateJ = transitionTable[states[j]][symbol];

                        // Find the indexes of the next states
                        int idxNextStateI = find(states.begin(), states.end(), nextStateI) - states.begin();
                        int idxNextStateJ = find(states.begin(), states.end(), nextStateJ) - states.begin();
                        // cout << i << " " << j << " " << nextStateI << " " << idxNextStateI << "  " << nextStateJ << " " << idxNextStateJ << endl;
                        // If the transitions lead to distinguishable states, mark the current pair as distinguishable
                        if (distinguishable[max(idxNextStateI, idxNextStateJ)][min(idxNextStateI, idxNextStateJ)] == 1)
                        {
                            distinguishable[i][j] = 1;
                            updated = true;
                            break;
                        }
                    }
                }
            }
        }
    } while (updated);

    cout << "Minimized DFA Transition Table:" << endl;
    for (int i = 0; i < numStates; ++i)
    {
        for (int j = 0; j < numStates; ++j)
        {
            cout << distinguishable[i][j] << " ";
        }
        cout << endl;
    }
    // Merge non-distinguishable states
    vector<set<string>> mergedSets(numStates);

    // Initialize mergedSets with individual states
    for (int i = 0; i < numStates; ++i)
        mergedSets[i].insert(states[i]);

    // Merge states based on the distinguishable matrix
    for (int i = 0; i < numStates; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (!distinguishable[i][j])
            {
                // Merge set j into set i
                mergedSets[i].insert(mergedSets[j].begin(), mergedSets[j].end());
                mergedSets[j].clear(); // Clear the set after merging
            }
        }
    }

    // Print final merged states
    cout << "\nMerged States:" << endl;
    for (int i = 0; i < numStates; ++i)
    {
        if (!mergedSets[i].empty())
        {
            cout << "{ ";
            for (const string &state : mergedSets[i])
            {
                cout << state << " ";
            }
            cout << "}" << endl;
        }
    }
    map<set<string>, map<char, set<string>>> minimizedTransitions;
    for (int i = 0; i < numStates; ++i)
    {
        if (!mergedSets[i].empty())
        {
            set<string> mergedState = mergedSets[i];
            string representative = *mergedState.begin(); // Pick a representative state from the set
            for (char symbol : alphabet)
            {
                string nextState = transitionTable[representative][symbol];
                // Find the merged state that contains the next state
                for (int k = 0; k < numStates; ++k)
                {
                    if (!mergedSets[k].empty() && mergedSets[k].count(nextState))
                    {
                        minimizedTransitions[mergedState][symbol] = mergedSets[k];
                        break;
                    }
                }
            }
        }
    }
    // Print the minimized DFA transition table
    cout << "\nMinimized DFA Transition Table:" << endl;
    for (const auto &entry : minimizedTransitions)
    {
        cout << "State { ";
        for (const string &state : entry.first)
        {
            cout << state << " ";
        }
        cout << "}: ";
        cout << endl;
        for (const auto &[symbol, nextStateSet] : entry.second)
        {
            cout << "On " << symbol << " -> { ";
            for (const string &nextState : nextStateSet)
            {
                cout << nextState << " ";
            }
            cout << "} ";
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}

// int numStates;
// cout << "Enter the number of states: ";
// cin >> numStates;

// vector<string> states(numStates);
// cout << "Enter the states: ";
// for (int i = 0; i < numStates; ++i)
// {
//     cin >> states[i];
// }

// // Fixed alphabet with two symbols: '0' and '1'
// vector<char> alphabet = {'0', '1'};

// map<string, map<char, string>> transitionTable;
// cout << "Enter the transition table (state followed by transitions on '0' and '1'):" << endl;
// for (int i = 0; i < numStates; ++i)
// {
//     string currentState;
//     cin >> currentState;

//     string nextState0, nextState1;
//     cin >> nextState0 >> nextState1;

//     transitionTable[currentState]['0'] = nextState0;
//     transitionTable[currentState]['1'] = nextState1;
// }

// int numAcceptingStates;
// cout << "Enter the number of accepting states: ";
// cin >> numAcceptingStates;

// set<string> acceptingStates;
// cout << "Enter the accepting states: ";
// for (int i = 0; i < numAcceptingStates; ++i)
// {
//     string state;
//     cin >> state;
//     acceptingStates.insert(state);
// }

// // Display the DFA for verification
// cout << "\nDFA Transition Table:" << endl;
// for (const auto &state : states)
// {
//     cout << "State " << state << ": ";
//     for (char sym : alphabet)
//     {
//         cout << "On " << sym << " -> " << transitionTable[state][sym] << " ";
//     }
//     cout << endl;
// }

// cout << "Accepting states: ";
// for (const auto &state : acceptingStates)
// {
//     cout << state << " ";
// }
// cout << endl;