import sys

file1 = open(sys.argv[1])
file2 = open(sys.argv[2])
file3 = open(sys.argv[3], 'w')
file3.write(bin(int(file1.readline(), 16) ^ int(file2.readline(), 16)))
file3.close()
file3 = open(sys.argv[3])
to_count = file3.readline()
print('proportion of different values = ' + str(to_count.count('1')) + ' / ' + str(len(to_count)))
