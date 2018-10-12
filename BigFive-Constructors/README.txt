This program was written by Tushar Malakar as the first project of Software Analysis and
 Design III (CSCI33500) at Hunter College. Portions of this assignment were supplied in
 whole or partially by Professor Ioannis Stamos.

The purpose of this assignment is to demonstrate the importance of “The Big Five” by
 creating a Chain that uses a dynamic array as an underlying data structure.

All functions that were defaulted defined by Professor Ioannis Stamos were altered and
 defined to fit the specifications the Professor stated.

One function that was added, however, was an additional + overloading friend function to
 accommodate for line 44 (cout << d + "hi_there”;) of TestPart2 as the first overload
 function only took into account of two chains that were being concatenated and not the
 scenario of one chain and an object such as the “hi there” scenario.

With that function being added, all tests were passed and can be demonstrated on the Linux
 Terminals at Hunter College by manually typing in a chain under the format of:[4: 1 2 3 4] 0r [1: 22] or [2: 33333 444] or [3: 444 555 222]
