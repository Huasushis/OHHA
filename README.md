# OHHA
Outrageous Hereditary Hash Algorithm
## Process
- Append 1 and then append 0 until the length of the data $\equiv 192 (\mod 256)$
- Append the length of the original data (64 bit)
- Convert every 256 bits of binary number to 162 bits of ternary number
- etc.