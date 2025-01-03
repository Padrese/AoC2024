import numpy as np
import time

def read_mul_ops_in_data(filename, part2):

    ops1 = []
    ops2 = []

    def read_op(initial_idx, op_position):
        current_idx = initial_idx
        current_char = file_content[current_idx]
        if not current_char.isnumeric():
            return None, None #These situations represent continue behaviors of the for loop in the code below
        while current_char.isnumeric():
            current_idx += 1
            current_char = file_content[current_idx]
        char_to_parse = "," if op_position == "first" else ")"
        if current_char != char_to_parse:
            return None, None
        op = int(file_content[initial_idx:current_idx])
        return op, current_idx

    with open(filename, 'r') as f:
        file_content = f.read()
        f.close()

    mul_occurences_idx = [i for i in range(len(file_content)) if file_content.startswith("mul", i)]
    do_occurences_idx = [i for i in range(len(file_content)) if file_content.startswith("do()", i)]
    dont_occurences_idx = [i for i in range(len(file_content)) if file_content.startswith("don't()", i)]

    for i in mul_occurences_idx:

        if part2:
            #We identify whether a do() or a don't() comes before the mul index
            valid_do_idx = [x for x in do_occurences_idx if x <= i] 
            valid_dont_idx = [x for x in dont_occurences_idx if x <= i]
            do_largest_idx = np.max(valid_do_idx) if len(valid_do_idx) != 0 else None
            dont_largest_idx = np.max(valid_dont_idx) if len(valid_dont_idx) != 0 else None

        if file_content[i+3] != "(":
            continue
        
        first_op, current_idx_first_op = read_op(initial_idx=i+4, op_position="first")
        if first_op is None:
            continue

        second_op, _ = read_op(initial_idx=current_idx_first_op+1, op_position="second")
        if second_op is None:
            continue

        if part2:
            #If there is none of these instructions coming beforehand, we count the mul instruction
            #If we see a valid mul but a don't() instruction comes before or is the only defined operation, we do nothing
            #Otherwise, don't() is not defined before the current mul and the instruction is counted
            if do_largest_idx != None and dont_largest_idx != None:
                if dont_largest_idx > do_largest_idx: 
                    continue
            elif do_largest_idx == None and dont_largest_idx != None:
                continue

        ops1.append(first_op)
        ops2.append(second_op)

    #ops1 and ops2 should be the arrays of operands found in the mul instructions
    return np.array(ops1), np.array(ops2)

def main():
    start_time = time.time()
    input = "input.txt"
    ops1, ops2 = read_mul_ops_in_data(filename=input, part2=False)
    print("Result part 1:", ops1@ops2)
    ops1, ops2 = read_mul_ops_in_data(filename=input, part2=True)
    print("Result part 2:", ops1@ops2)
    end_time = time.time()
    print("Time:", end_time-start_time, "seconds")

if __name__ == "__main__":
    main()