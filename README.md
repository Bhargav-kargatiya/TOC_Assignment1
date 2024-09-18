535002846795
# How to Run the DFA Minimization Code

## Requirements
- You need a C++ compiler like **GCC**, or you can use an **online compiler** (e.g., [Replit](https://replit.com)).

## Running the Code

### Option 1: Command Line
1. Save the code as `dfa_minimization.cpp`.
2. Open your terminal/command prompt and navigate to the file location.
3. Compile the code using:
    ```bash
    g++ dfa_minimization.cpp -o dfa_minimization
    ```
4. Run the program:
    ```bash
    ./dfa_minimization
    ```

### Option 2: Online Compiler
1. Go to [Replit](https://replit.com/).
2. Paste the code into the editor.
3. Click "Run."

## What You’ll See
- The DFA transition table.
- Matrix of distinguishable states.
- Merged states and the minimized DFA transition table.

## Additional Notes:
- The input is currently hardcoded within the program for a 5-state DFA example. You can modify the `numStates`, `states`, `transitionTable`, and `acceptingStates` in the code if you want to test with different inputs.
- If you need to handle custom input via the command line or file, adjustments can be made to the input section of the code.

# How to Run the NFA to DFA Conversion Code

## Requirements
- You need a **C++ compiler** like **GCC**, or you can use an **online compiler** (e.g., [Replit](https://replit.com)).

## Running the Code

### Option 1: Command Line
1. Save the code as `nfa_to_dfa.cpp`.
2. Open your terminal/command prompt and navigate to the file location.
3. Compile the code using:
    ```bash
    g++ nfa_to_dfa.cpp -o nfa_to_dfa
    ```
4. Run the program:
    ```bash
    ./nfa_to_dfa
    ```

### Option 2: Online Compiler
1. Go to [Replit](https://replit.com/).
2. Paste the code into the editor.
3. Click "Run."

## What You’ll See
- The NFA transitions and their corresponding DFA transitions.
- The program will output DFA state transitions for each input symbol ('0' and '1').

## Example NFA Input:
The example hardcoded in the code uses the following NFA transition table:

| State | On '0' | On '1' |
|-------|--------|--------|
| A     | A      | AB     |
| B     | C      | C      |
| C     | D      | D      |
| D     | -      | -      |

This NFA will be converted into the corresponding DFA and the transitions will be displayed.
