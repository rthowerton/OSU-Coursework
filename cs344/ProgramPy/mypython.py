import random

random.seed()

#create 3 random files, clear them if they exist
file1 = open('hello.txt', 'w')
file2 = open('quintessential.txt', 'w')
file3 = open('world.txt', 'w')

#close them temporarily
file1.close()
file2.close()
file3.close()

#write to file1
file1 = open('hello.txt', 'a')
for i in range(10):
   file1.write(chr(random.randint(97, 122)))
file1.write('\n')
file1.close()

#read contents
file1 = open('hello.txt')
print(file1.readline(),  end='')
file1.close()

#write to file2
file2 = open('quintessential.txt', 'a')
for j in range(10):
   file2.write(chr(random.randint(97, 122)))
file2.write('\n')
file2.close()

#read contents
file2 = open('quintessential.txt')
print(file2.readline(), end='')
file2.close()

#write to file3
file3 = open('world.txt', 'a')
for k in range(10):
   file3.write(chr(random.randint(97, 122)))
file3.write('\n')
file3.close()

#read contents
file3 = open('world.txt')
print(file3.readline(), end='')
file3.close()

#print 2 random integers
int1 = random.randint(1, 42)
print(int1)
int2 = random.randint(1, 42)
print(int2)

#print their product
print(int1 * int2)
