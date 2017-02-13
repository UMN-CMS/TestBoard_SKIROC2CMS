# Generates a random bitstream. This file is just for testing.

import random

f = open('programming.txt', 'w')

i = 0
while i < 384:
    f.write(str(random.randint(0,1)))
    f.write('\n')
    i += 1

f.close()
