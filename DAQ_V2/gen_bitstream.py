# Generates a random bitstream. This file is just for testing.

import random

f = open('bitstream.txt', 'w')

i = 0
while i < 384:
    f.write(str(random.randint(0,1)))
    i += 1

f.close()
