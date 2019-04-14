import sys
from collections import deque

# Class of cat(A) water(W) elements
class itemSymbol:
    def __init__(self, line, column, symbol, time, position):
        self.line = line; self.column = column; self.symbol = symbol; self.time = time; self.position = position

array = []
queue = deque()

# Map padding
with open(sys.argv[1]) as fileobj:
    for line in fileobj:
        # Line reading and border of X's added to each line
        array.append(['X'] + list(line.rstrip()) + ['X'])
fileobj.close()

# Lines(N) and columns(M) calculation
N = len(array)
M = len(array[0]) - 2

# Border creation of X's added to first and last line of map
array.insert(0, ['X' for i in range (M+2)])
array.insert(N+1, ['X' for i in range (M+2)])

# Enqueing water and cat elements
for i in range (1, N+1):
    for j in range (1, M+1):
        ch = array[i][j]
        if ch is 'W' or ch is 'A':
            ch = itemSymbol(i, j, ch, 0, "")
            queue.append(ch)