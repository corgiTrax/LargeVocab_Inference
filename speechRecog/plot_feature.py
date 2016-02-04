import copy as py_copy
from collections import Counter
import matplotlib.pyplot as plt
import sys

data_file = open(sys.argv[1],'r')
labels = []

lines = data_file.readlines()

line_one_index = int(sys.argv[2])
line_two_index = int(sys.argv[3])

one_line = lines[line_one_index].split()
another_line = lines[line_two_index].split()

print("The first label is: ", one_line[0])
print("The second label is: ", another_line[0])

plt.plot(one_line[1:-1], 'b',another_line[1:-1],'r')
plt.show()


#for line in data_file:
##    print(len(line.split()))
#    label = line.split()[0]
#    labels.append(label)
#
#print(len(labels))
#print(len(set(py_copy.deepcopy(labels))))
#print(Counter(labels))
#print(len(Counter(labels)))




