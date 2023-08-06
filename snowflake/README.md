This is my solution to the problem "Snowflakes". 

Problem Statement: Given a collection of between 1 and 100,000 snowflakes, each represented by 6 integers, do a pair of identical snowflakes exist in the collection? (Note: Two snowflakes are identical if each element is exactly equal a translation to the left or right (wrapping around to the beginning) is the same as another snowflake).

Method: After defining a function the compares the snowflakes exactly as stated, a hash table is created, with the hash function associating the sum of each snowflake mod 100,000 with the table. This allows for a suitably fast comparison of elements.