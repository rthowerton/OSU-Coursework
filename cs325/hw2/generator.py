from random import *

f = open('data.txt', 'w')
f.write('4000 ')
for i in range(4000):
   f.write(str(randrange(10000)) + ' ')
f.close()
