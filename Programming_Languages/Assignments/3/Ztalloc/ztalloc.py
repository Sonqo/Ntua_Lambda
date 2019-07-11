import sys
from collections import deque

class Borders:
    """ Class of cases, containing lower border, higher border, path of numeric calculations followed to this state and number of state """
    def __init__(self, low_b, high_b, path, state):
        self.low_b = low_b; self.high_b = high_b; self.path = path; self.state = state

array = []
queue = deque()

with open(sys.argv[1]) as fileobj:
    for line in fileobj:
        array.append(line.split())

N = int(array[0][0]) # Number of total cases
    
for i in range(1, N+1):

    visited = [0] * 1000000 # Visited cases array

    x = Borders(int(array[i][0]), int(array[i][1]), "", 0) # Append one case at a time
    queue.append(x)

    visited[int(array[i][1])] = 1

    flag = 0 # Borders found flag

    temp_state = 1

    while queue and flag != 1:
        
        temp = queue.popleft() 

        if temp.low_b <= 999999 and temp.high_b <= 999999:

            if temp.state < 1000000: # Number of states which are going to be examined = 1.000.000 (M)

                if temp.low_b >= int(array[i][2]) and temp.high_b <= int(array[i][3]): # If the end borders are met, print the string path of calculations

                    flag = 1
                    if temp.path == "":
                        print("EMPTY")
                    else:
                        print(temp.path, temp.state)

                temp_1 = temp.low_b // 2 
                temp_2 = temp.high_b // 2 

                if visited[temp_1] != 1:

                    temp_state += 1

                    x = Borders(temp_1, temp_2, temp.path + "h", temp_state)
                    queue.append(x)

                    visited[temp_1] = 1

                temp_1 = temp.low_b * 3 + 1
                temp_2 = temp.high_b * 3 + 1

                if (temp_1 <= 999999 and temp_2 <= 999999): # Ztalloc can store a number up to 6-digits
                    
                    if visited[temp_1] != 1:

                        temp_state += 1

                        x = Borders(temp_1, temp_2, temp.path + "t", temp_state)
                        queue.append(x)

                        visited[temp_1] = 1 
        
            else: # In case examined cases exceed 1M
                
                flag = 1
                print("IMP0SSIBLE")
        
        if flag == 1: # Dequeue any unwanted elements, before proceeding to the next case
            while queue:
                queue.popleft()