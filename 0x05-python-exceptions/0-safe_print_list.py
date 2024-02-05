#!/usr/bin/python3
def safe_print_list(input_list=[], total_items=0):
    printed_count = 0
    for index in range(total_items):
        try:
            print(input_list[index], end="")
            printed_count += 1
        except IndexError:
            break
    print()
    return printed_count
