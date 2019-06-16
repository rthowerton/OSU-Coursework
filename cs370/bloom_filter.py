import hashlib
import pyhash
import sys
from bitarray import bitarray
import time

if len(sys.argv) != 8:
   print('Program usage: python bloom_filter.py -d dictionary.txt -i input.txt -o output3.txt output5.txt')
   sys.exit(1)
if (sys.argv[1] != "-d") | (sys.argv[3] != "-i") | (sys.argv[5] != "-o"):
   print('Program usage: python bloom_filter.py -d dictionary.txt -i input.txt -o output3.txt output5.txt')
   sys.exit(2)

# create output files if the do not exist, erase them if they do
output3 = open(sys.argv[6], 'w')
output3.close()
output5 = open(sys.argv[7], 'w')
output5.close()

# create 3 and 5 hash function bloom filter arrays
filter3 = bitarray(7750000)
filter5 = bitarray(6150000)
filter3.setall(False)
filter5.setall(False)

# hash a password 3 times and set the corresponding bits in the 3 function bloom filter
def hash3(password):
   murmur = pyhash.murmur3_x64_128()
   index3 = murmur(password) % 7750000
   filter3[index3] = True
   sha = hashlib.sha256()
   sha.update(password)
   index3 = int(sha.hexdigest(), 16) % 7750000
   filter3[index3] = True
   mdfive = hashlib.md5()
   mdfive.update(password)
   index3 = int(mdfive.hexdigest(), 16) % 7750000
   filter3[index3] = True

# check if a word is in the 3 function bloom filter
def checkHash3(check):
   output3 = open(sys.argv[6], 'a')
   check1 = False
   check2 = False
   check3 = False
   murmur = pyhash.murmur3_x64_128()
   index3 = murmur(check) % 7750000
   if filter3[index3] == True:
      check1 = True
   sha = hashlib.sha256()
   sha.update(check)
   index3 = int(sha.hexdigest(), 16) % 7750000
   if filter3[index3] == True:
      check2 = True
   mdfive = hashlib.md5()
   mdfive.update(check)
   index3 = int(mdfive.hexdigest(), 16) % 7750000
   if filter3[index3] == True:
      check3 = True
   if check1 == check2 == check3 == True:
      output3.write('maybe\n')
   else:
      output3.write('no\n')
   output3.close()

# hash a password 5 times and set the corresponding bits in the 5 function bloom filter
def hash5(password):
   murmur = pyhash.murmur3_x64_128()
   index5 = murmur(password) % 6150000
   filter5[index5] = True
   sha1 = hashlib.sha256()
   sha1.update(password)
   index5 = int(sha1.hexdigest(), 16) % 6150000
   filter5[index5] = True
   mdfive = hashlib.md5()
   mdfive.update(password)
   index5 = int(mdfive.hexdigest(), 16) % 6150000
   filter5[index5] = True
   sha2 = hashlib.sha384()
   sha2.update(password)
   index5 = int(sha2.hexdigest(), 16) % 6150000
   filter5[index5] = True
   sha3 = hashlib.sha512()
   sha3.update(password)
   index5 = int(sha3.hexdigest(), 16) % 6150000
   filter5[index5] = True

# hash a password 5 times and set the corresponding bits in the 5 function bloom filter
def checkHash5(check):
   output5 = open(sys.argv[7], 'a')
   check1 = False
   check2 = False
   check3 = False
   check4 = False
   check5 = False
   murmur = pyhash.murmur3_x64_128()
   index5 = murmur(check) % 6150000
   if filter5[index5] == True:
      check1 = True
   sha1 = hashlib.sha256()
   sha1.update(check)
   index5 = int(sha1.hexdigest(), 16) % 6150000
   if filter5[index5] == True:
      check2 = True
   mdfive = hashlib.md5()
   mdfive.update(check)
   index5 = int(mdfive.hexdigest(), 16) % 6150000
   if filter5[index5] == True:
      check3 = True
   sha2 = hashlib.sha384()
   sha2.update(check)
   index5 = int(sha2.hexdigest(), 16) % 6150000
   if filter5[index5] == True:
      check4 = True
   sha3 = hashlib.sha512()
   sha3.update(check)
   index5 = int(sha3.hexdigest(), 16) % 6150000
   if filter5[index5] == True:
      check5 = True
   if check1 == check2 == check3 == check4 == check5 == True:
      output5.write('maybe\n')
   else:
      output5.write('no\n')
   output5.close()

# main operation of the script
dictionary = open(sys.argv[2])
for password in dictionary:
   hash3(password)
print("Done with hash3")
dictionary.seek(0)
for password in dictionary:
   hash5(password)
print("Done with hash5")
# count = 623518
dictionary.close()
inp = open(sys.argv[4])
i = 0
for check in inp:
   if i == 0:
      i += 1
   else:
      #start = time.time()
      checkHash3(check)
      #end = time.time()
      #print(end - start)
      #start2 = time.time()
      checkHash5(check)
      #end2 = time.time()
      #print(end2 - start2)
