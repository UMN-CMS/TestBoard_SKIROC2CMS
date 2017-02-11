#
#   Author: Ryan Quinn
#   Email: quinn.ryanx@gmail.com
#
#       Provides a user interface. The user navigates through the
#       main menu first, and then through other submenus to send
#       commands, read data, etc... to/from the FPGA.
#

import readwrite as rw
import binary as bn

def printOptions():
    print('\nOPTIONS:-[Note: Only one of the options below are valid, No protection for any other option]\n')
    print('1) Write a command\n')
    print('2) Read operation\n')
    print('3) Programming\n')
    print('0) Quit\n')

def writeOptions():
    print('\nOPTIONS:-[Note: Only one of the options below are valid, No protection for any other option]\n')
    print('1) NOP 0000\n')
    print('2) RstB pulse 0001\n')
    print('3) SetProgMode 0010\n')
    print('4) SetDAQMode 0011\n')
    print('5) ArmTrigger 0100\n')
    print('6) Trigger 0101\n')
    print('7) StartConv 0110\n')
    print('8) StartReadOut 0111\n')
    print('9) ReadEvent 1000\n')
    print('10) SetSelect 1001\n')
    print('11) WrConf3Bit 1010\n')
    print('12) ReadStatus 1011\n')
    print('0)  Exit\n')
    choice = int(input("Choice: "))
    if choice == 0:
        exit()
    else:
        command = bn.toBinary(choice-1)
        print(command)
        rw.sendcommand(command)

def readOptions():
    pass

def programming():
    pass

def main():
    funcs = [exit, writeOptions, readOptions, programming]
    printOptions()
    choice = int(input("Choice: "))
    funcs[choice]()

main()
