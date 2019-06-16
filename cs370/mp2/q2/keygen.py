import sys
import random

random.seed()

for i in range(int(sys.argv[1])):
   print(chr(random.randint(97, 122)), end='')
