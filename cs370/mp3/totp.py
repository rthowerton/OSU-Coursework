#This program was adapted entirely from the RFC
import hmac, hashlib, time, base64, struct

#generate HMAC-SHa-1 value
def dynamic_truncation(String):
   offset = int(format(ord(String[19]), 'b'), 2) & 0b1111
   bin_code_1 = (int(format(ord(String[offset]), 'b')) & 0x7f) << 24
   bin_code_2 = (int(format(ord(String[offset+1]), 'b')) & 0xff) << 16
   bin_code_3 = (int(format(ord(String[offset+2]), 'b')) & 0xff) << 8
   bin_code_4 = (int(format(ord(String[offset+3]), 'b')) & 0xff)
   bin_code = bin_code_1 | bin_code_2 | bin_code_3 | bin_code_4
   return bin_code

#Generate an HMAC-SHA-1 value using key K and counter C.
totp = int(time.time())//30
key = base64.b32decode('7777777777777777')
hs = hmac.new(key, str(totp), hashlib.sha1)
String = hs.hexdigest()
#Generate a 4-byte string Sbits (31 bits, in this case)
Sbits = dynamic_truncation(String)
Snum = Sbits % 1000000
print('key = ' + '7777777777777777')
while True:
   print(str(Snum))
   time.sleep(30)
