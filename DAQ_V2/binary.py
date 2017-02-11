#
#   Author: Ryan Quinn
#   Email: quinn.ryanx@gmail.com
#
#       Provides functions to convert numbers into binary arrays
#       and vice-versa for use in other modules.
#

def to4Binary(num):
    '''
        Converts a number less than 16 into
        a 4-bit binary array.
    '''

    if num > 15:
        raise ValueError('{} is too large to be converted into a 4-bit binary array.'.format(num))

    binary = []
    while num != 0:
        bit = num % 2
        binary.append(bit)
        num = num // 2

    binary.reverse()

    while len(binary) < 4:
        binary.insert(0,0)

    return binary
