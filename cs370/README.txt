The following are requirements and instructions for running bloom_filter.py by Ryan Howerton.

Before running the script, be sure to download and install the python modules bitarray and pyhash (I used pip install --user {bitarray|pyhash} on the OSU flip servers).
  -->  bitarray is used for generating the arrays of bits that compose the two bloom filters.
  -->  pyhash is needed for using the murmur3 hash function.

To execute the script, enter the command python bloom_filter.py -d (dictionary file) -i (input file) -o (3 function output file) (5 filter output file)
  - My program makes the assumption that arguments will be provided in this order.
  - (dictionary file) should contain the list of "bad" passwords.
  - (input file) should contain a list of passwords to test against the bloom filter.
  - (3 function output file) should be the name of the file where you want the output of the 3 function bloom filter to be printed.
  - (5 function output file) should be the name of the file where you want the output of the 5 function bloom filter to be printed.
  - If the arguments are not all provided, or are not provided in the correct order, the script will print the proper usage and exit before fully executing.



Supplementary Questions:

1. What hash functions did you choose and why (Hint: Cryptographic or non-cryptographic)?What is the output range of the hash functions? What is the size of the Bloom filter in each case? If you used a library for your hash function, make sure to cite it.

 - I chose primarily Cryptographic hash functions (md5, sha256, sha384, and sha512), and one non-cryptographic hash function (MurmurHash 3). I chose these functions primarily for their uniformity of results (the cryptographic hash functions all follow the rules of pre-image resistance and collision resistance, some quick research showed me that murmur3 was a very uniform function).
 - md5 outputs a 128-bit value, sha256-outputs a 256-value, sha384 outputs a 384-bit value, sha512 outputs a 512-bit value. MurmurHash 3 outputs a 128-bit value.
 - For my 3 function bloom filter, I made a 7,750,000-bit array, and for my 5 function bloom filter I made a 6,150,000-bit array.
 - I used the pyfasthash library for MurmurHash 3: https://github.com/flier/pyfasthash


2. How long does it take for your Bloom Filter to check 1 password in each case? Why does one perform better than other?

 - Both of my bloom filter checkers take approximately 2-3 ms to check a password, there is no clear better checke. Timing commands have been commented out.
 - It may be the case that the 5 function filter is usually a fraction of a millisecond faster than the 3 function filter. My theory is that this is because the 3 function bloom filter array is 1.65 million bits larger, and the time spent going to each index in that array takes more time than the two extra hash functions, which are efficient cryptographic hash functions, take to compute their hashes.


3. What is the probability of False Positive in your Bloom FIlter in each case? What is the probability of False Negative in your Bloom Filter?

 - I chose my bit-array sizes to make the probability for False Positive in both filters to be approximately 1%.
   > (1 - e^((-3*623518)/7750000))^3 = 0.00986
   > (1 - e^((-5*623518)/6150000))^5 = 0.00994
 - The nature of bloom filters says that False Negatives are impossible.


4. How can you reduce the rate of False Positives?

 - You can reduce the rate of False Positives by increasing the number of hash functions used, or increasing the size of the bit array.
