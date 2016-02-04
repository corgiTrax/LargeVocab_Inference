'''
given a FAVE-extract output file,
1). construct triphone labels for each vowel
2). extract MFCC features of that vowel from wav file
3). use transcript file to separate sentences
'''
import sys
from features import mfcc
from features import logfbank
import scipy.io.wavfile as wav
import numpy
import math

VOWELS = ["AA","AE","AH","AO","AW","AY","EH","ER","EY","IH","IY","OW","OY","UH","UW"]
SUBVOWEL = False

# mean duration of vowels, use for resampling signals to be the same length
MEAN_DUR = 1600

class postprocess:
    def __init__(self, fave_file, wav_file, trans_file):
        self.fave_file = fave_file
        self.wav_file = wav_file
        self.trans_file = trans_file

    def process(self):
        fave_file = open(self.fave_file, 'r')
        trans_file = open(self.trans_file, 'r')
        line_count = 0
        output_file = open(self.fave_file.split('_')[0] + ".feature_seq", 'w')

        # get sentence time boundaries
        sent_bound = []
        for line_ in trans_file:
            sent_bound.append(float(line_.split()[3]))
        cur_sent = 0

        (rate, sig) = wav.read(self.wav_file)
        for line in fave_file:
            content = line.split()
            if len(content) > 0 and content[0] in VOWELS:
                # label is vowel + fm + fp + fv + ps + fc
                if not SUBVOWEL:
                   vowel = content[0]
                else:
                   vowel = content[9]
           
                label = vowel + '_' + str(content[10]) + '_' + str(content[11]) + '_'\
                        + str(content[12]) + '_' + str(content[13]) + '_'\
                        + str(content[14]) + ' '
                
                
                # rest relevant information goes to feature
                
                # use time info to extract mfcc from wav file
                # get start time and end time of current vowel
                time_start = float(content[6])
                time_end = float(content[7])
                index_start = math.floor(time_start * rate)
                index_end = math.ceil(time_end * rate)
                sub_sig = sig[index_start:index_end]
                #print(time_start, time_end, len(sub_sig))

                # resampling sub_sig to a fixed length
                resamp_sig = numpy.zeros(MEAN_DUR)
                for i in range(MEAN_DUR):
                    resamp_sig[i] = sub_sig[math.floor(i * (1.0 * len(sub_sig) / MEAN_DUR))]
                
                mfcc_feat = mfcc(resamp_sig,rate)
                
                # reshape mfcc_feat to be a row vector
                reshaped_mfcc = mfcc_feat.flatten()

                # tell if this is a new sentence
                time_stamp = float(content[5])
                if time_stamp <= sent_bound[cur_sent]:
                    # still in current sentence
                    pass
                else:
                    cur_sent += 1
                    output_file.write('\n')

                # write label, feature to file
                output_file.write(label)
                for feat in reshaped_mfcc:
                    output_file.write(str(feat) + ' ')
                output_file.write('\n')

                line_count += 1
        output_file.write('\n')
        output_file.write('\n')
        
        #print(line_count)
        #print(total_length / line_count)

        output_file.close()
        fave_file.close()

if __name__ == '__main__':
    myProc = postprocess(sys.argv[1], sys.argv[2], sys.argv[3])
    myProc.process()
