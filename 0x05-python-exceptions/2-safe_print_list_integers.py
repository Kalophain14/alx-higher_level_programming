#!/usr/bin/python3
def safe_print_list_integers(value_list=[], total_elements=0):
    printed_elements = 0
    for index in range(total_elements):
        try:
            print("{:d}".format(value_list[index]), end="")
            printed_elements += 1
        except(ValueError, TypeError):
            continue
    print()
    return printed_elements
