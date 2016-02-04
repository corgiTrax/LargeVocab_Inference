from features import mfcc
from features import logfbank
import scipy.io.wavfile as wav
import numpy

import math
numpy.set_printoptions(threshold=numpy.nan)
numpy.set_printoptions(precision=3)



(rate,sig) = wav.read("001.wav")
print(rate)
print(1.0*len(sig)/rate)
time_start = 1694.209
time_end = 1694.379
index_start = math.floor(time_start * rate)
index_end = math.ceil(time_end * rate)
print(index_start)
print(index_end)
sub_sig = sig[index_start:index_end]
#wav.write("AE.wav", rate, sub_sig)


mfcc_feat = mfcc(sub_sig,rate)
#fbank_feat = logfbank(sig,rate)
reshaped_mfcc = mfcc_feat.flatten()

#print(mfcc_feat.shape)
#print(mfcc_feat)
#print(reshaped_mfcc.shape)
print(reshaped_mfcc)
for feat in reshaped_mfcc:
    print(str(feat) + ' ')

