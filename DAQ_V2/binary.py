#
#   Author: Ryan Quinn
#   Email: quinn.ryanx@gmail.com
#
#       Provides functions to convert numbers into binary arrays
#       and vice-versa for use in other modules.
#

def toBinary(num, bits):
    '''
        Converts a number 'num' into a
        binary array of length 'bits'.
    '''

    if num > (2**bits - 1):
        raise ValueError('{0} is too large to be converted into a {1}-bit binary array.'.format(num, bits))

    binary = []
    while num != 0:
        bit = num % 2
        binary.append(bit)
        num = num // 2

    binary.reverse()

    while len(binary) < bits:
        binary.insert(0,0)

    return binary



def toStr(arr, bits):
    '''
        Converts a binary array 'arr'
        into a string of length 'bits'.
    '''

    if len(arr) > bits:
        raise ValueError('The array {0} is more than {1} bits.'.format(arr, bits))

    string = ''.join(str(bit) for bit in arr)

    while len(string) < bits:
        string = '0' + string

    return string
