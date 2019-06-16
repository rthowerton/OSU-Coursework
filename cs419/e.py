#!/usr/bin/env python
import hmac
import hashlib
import base64

ip = '0a004db5' # in hex
otp = '124142'
print(hmac.new(base64.b32decode("S4IZME34EM3HM3WCB4ZWMWZEH3OZUH43"), bytes.fromhex(ip) + otp.encode(), hashlib.sha256).hexdigest())
