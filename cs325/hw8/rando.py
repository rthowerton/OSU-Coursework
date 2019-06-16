from random import *

seed()
f = open('bin.txt', 'w')
f.write('5' + '\n')
for x in range(5):
   bins = randint(5, 20)
   f.write(str(bins) + '\n')
   items = randint(1, 20)
   f.write(str(items) + '\n')
   for y in range(items):
      f.write(str(randint(1, bins)) + ' ')
   f.write('\n')
