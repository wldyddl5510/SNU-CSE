# For managing path
import os.path
from pathlib import Path

# For arguments
import sys

# BFS -> for epsilon traversal
import collections

# For debug
# import pdb

# Define relative path
PROJECT_PATH = Path(__file__).resolve().parent.as_posix()
#DATA_PATH = os.path.join(PROJECT_PATH, "sample1")

# Define component of expression
ALPHABET = ['0','1']
OPERATOR = ['*', '.', '+']

# pt.1: to postfix
"""
    TODO:
        * convert infix regex to postfix regex
    Args:
        * regex(str): infix string representing regex
    Returns:
        * result(str): postfix string representing same regex
"""
def infix2postfix(regex: str) -> str:
    result = "" # Result string
    stack = [] # Stack to convert postfix

    # Read each char in string
    for char in regex:
        
        # append to result string if char is alphabet
        if char in ALPHABET:
            result += char
        # keep in stack if char is operator
        elif (char in OPERATOR) or (char is '('):
            stack.append(char)
        # append stacked operators to result string if parentheses are paired
        elif char is ')':
            while(True):
                # if all operators are parsed
                if len(stack) == 0:
                    break
                else:
                    oper = stack.pop()
                    # if parentheses are paired
                    if oper is '(':
                        break
                    # append to result string
                    else:
                        result += oper
        # if unvalid input is given
        else:
            return "INVALID"

    return result

# Constructing NFA Transition table
"""
    TODO:
        * translate the regular expression to NFA
    Args:
        * postfix_regex(str): regex string
    Returns:
        * state_arr(array): n * 5 array that defines NFA. 
        * n stands for number of states.
        * each column is (state_num, isfinal, 0, 1, epsilon)
"""
def NFATransition(postfix_regex: str):
    # Define stack to calculate the operator
    stack = []

    # list that contains the information about transition -> return
    state_arr = []
    head = 0
    for char in postfix_regex:

        # new states are needed except for concatenation: denote them as (head, tail)
        if char is not '.':
            tail = head + 1

        # if alphabet -> construct independent 2-states automata
        if char in ALPHABET:

            # push (head, tail) into stack
            stack.append((head, tail))
            # [state, isfinal, 0-transition, 1-transition, e-transition]
            if char is '0':
                state_arr.append([head, False, tail, -1, set([])])
                state_arr.append([tail, True, -1, -1, set([])])
            elif char is '1':
                state_arr.append([head, False, -1, tail, set([])])
                state_arr.append([tail, True, -1, -1, set([])])
        elif char in OPERATOR:
            if (char is '+') or (char is '.'):
                operand2 = stack.pop()
                operand1 = stack.pop()
                if char is '+':
                    # make two new states: head and tail
                    # 'head' goes to starts of operands by epsilon
                    state_arr.append([head, False, -1, -1, set([operand1[0], operand2[0]])])
                    # 'tail' receives ends of operands by epsilon
                    state_arr[operand1[1]][4].add(tail)
                    state_arr[operand2[1]][4].add(tail)
                    
                    # ends of operands are no more terminal state
                    state_arr[operand1[1]][1] = False
                    state_arr[operand2[1]][1] = False

                    # create state 'tail'
                    state_arr.append([tail, True, -1, -1, set([])])

                    #push new states into stack
                    stack.append((head, tail))
                elif char is '.':
                    # merge end of operand1 and start of operand2 by epsilon
                    state_arr[operand1[1]][4].add(operand2[0])
                    state_arr[operand1[1]][1] = False

                    # now, 'head' is start of first operand, 'tail' is end of second operand
                    stack.append((operand1[0], operand2[1]))
            elif char is '*':
                operand = stack.pop()
                # tail goes head by epsilon
                state_arr[operand[1]][4] = state_arr[operand[1]][4].union(set([operand[0], tail]))

                # tail is no more terminal state
                state_arr[operand[1]][1] = False

                # 'head'' goes start of operand and 'tail' by epsilon
                state_arr.append([head, False, -1, -1, set([operand[0], tail])])

                # 'tail' is now terminal state
                state_arr.append([tail, True, -1, -1, set([])])

                # push new (head, tail) into stack
                stack.append((head, tail))
        
        # update new 'head' and 'tail' except for concatenation
        if char is not '.':
            head = tail + 1
    # state_arr and (initial, terminal) information
    return (state_arr, stack.pop())

# Only for debug
"""
def pretty_print(matrix: list) -> None:
    print('\n'.join(['\t'.join([str(cell) for cell in row]) for row in matrix]))
"""

# pt.2: run NFA for given input string
"""
    TODO:
        * validate whether the given string is NFA
    Args:
        * NFA(list): transition table of NFA for given regular expression
        * input_string(str): input string that needs to be validated whether it is in given NFA or not
    Returns:
        * True: if given string is in given NFA
        * False: if given string is not in given NFA
"""
def run_NFA(NFA: list, initial_terminal: tuple, input_string: str) -> bool:
    # Add epsilon states to initial state
    current_states = append_epsilon_states(set([initial_terminal[0]]), NFA)
    final = initial_terminal[1]
    
    # read input
    for char in input_string:
        
        # candidate for next states
        next_states = set([])

        # look all current states
        for state in current_states:
            
            if char is '0':
                # goto 'read 0'
                next_state = NFA[state][2]
            elif char is '1':
                # goto 'read 1'
                next_state = NFA[state][3]
            
            # check whether there really is next state
            if next_state is not -1:
                next_states.add(next_state)

            # append epsilon states
            current_states = append_epsilon_states(next_states, NFA)

    # After read all inputs, validate
    return validate_final_states(current_states, NFA, final)

"""
    TODO:
        * from current states C -> get E(C)
        * Using BFS
    Args:
        * current_states(list): list of current states
        * NFA(list): running NFA
    Returns:
        * current_States(list): append epsilon states to current states
"""

def append_epsilon_states(current_states: set, NFA: list) -> set:

    # result set that aggregate all epsilon states of my current states
    seen_aggregate= set([])

    # traverse for all my states
    for state in current_states:
        # epsilon states for each current state
        seen, queue = set([state]), collections.deque([state])

        # BFS: using queue

        while queue:

            # dequeue
            next_state = queue.popleft()

            # traverse epsilon states
            for epsilon_state in NFA[next_state][4]:
                
                if epsilon_state not in seen:
                    seen.add(epsilon_state)
                    queue.append(epsilon_state)
                
        seen_aggregate = seen_aggregate.union(seen)

    return seen_aggregate

"""
    TODO: 
        * determine whether current state includes final
    Args:
        * current_states(list): list of current states
        * NFA(list): running NFA
    Returns:
        * Bool: True if it has final states; False o.w.
"""
def validate_final_states(current_states: set, NFA: list, final: int) -> bool:
    if final in current_states:
        return True
    return False
    """
    # iterate my all states
    for state in current_states:
        
        # is terminal?
        if NFA[state][1] is True:
            return True
    return False
    """

"""
    TODO:
        * Read input file
        * Parse regex to postfix
        * create NFA Table based on postfix
        * Read input string
        * validate input string
        * write result to new file and compare with the answer
    
    Args:
        * python3 hw1.py --<input.txt>
"""

def main():

    # Read argument
    input_name = sys.argv[1]
    output_name = sys.argv[2]

    # set the path
    inputpath = os.path.join(PROJECT_PATH, input_name)

    # Read input file file
    with open(inputpath, 'r') as f:

        # write result in one string: Only for debug
        result = ""

        # Read regex
        regex = f.readline()[:-1]

        # Convert to postfix
        postfix_regex = infix2postfix(regex)
       
        #print(postfix_regex)

        # Construct NFA based on postfix
        nfa = NFATransition(postfix_regex)
        nfa_transition = nfa[0]
        # pretty_print(nfa_transition)
        initial_terminal = nfa[1]
        # print(initial_terminal)
        del nfa

        # Read num of inputs
        num_of_input = int(f.readline()[:-1])

        # Read each input string
        for i in range(0, num_of_input):
            # omit newline
            input_string = f.readline()[:-1]
            #print(input_string)

            # Validate the input
            if run_NFA(nfa_transition, initial_terminal, input_string):
                result += "Yes\n"
                # print("Yes")
            else:
                result += 'No\n'
                # print("No")


    # Write the answer
    outputpath = os.path.join(PROJECT_PATH, output_name)

    with open(outputpath, 'w') as f:
        f.write(result)

# Run function
if __name__ == "__main__":
    main()