''' a simple script to verify my c++ code produces correct factor_xy'''
import numpy

file_in = open("output.txt", 'r')
numpy.set_printoptions(threshold=numpy.nan)
numpy.set_printoptions(precision=3)

#w: 3039*901
w = numpy.zeros((3039, 901))
for i in range(3039):
    for j in range(901):
        w[i][j] = float(file_in.readline())

#w transpose
w_t = numpy.matrix(w).getT()

#seq: 16*901
seq = numpy.zeros((16, 901))
for i in range(16):
    for j in range(901):
        seq[i][j] = float(file_in.readline())

seq_m = numpy.matrix(seq)

#factor_xy: 16*3039
factor_xy = numpy.zeros((16, 3039))
for i in range(16):
    for j in range(3039):
        factor_xy[i][j] = float(file_in.readline())
factor_xy_m = numpy.matrix(factor_xy)

test_m = seq_m * w_t

print(numpy.allclose(factor_xy_m.getA(),test_m.getA()))
#print(factor_xy_m)
#print(test_m)

file_in.close()

