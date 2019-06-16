from random import *

f = open('data.txt', 'w')
f.write('70000 ')
for i in range(70000):
   f.write(str(randrange(10000)) + ' ')
f.close()