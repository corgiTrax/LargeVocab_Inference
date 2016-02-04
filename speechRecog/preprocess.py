''' To obtain transcription file for FAVE, using CMU PAD dataset
we do
1). concantenate all wav files in target folder into a single wav file
2). use this script to read in all wav files in target folder, get their length.
3). create the output file in the format
speakerID spakerName annotation_begin_time annotation_end_time text
4). we can get text from list file
'''
from os import listdir
from os.path import isfile, join
import wave
import sys
import copy as py_copy
import os

class preprocess:
    def __init__(self, wav_folder, text_file):
        self.wav_folder = py_copy.deepcopy(wav_folder)
        self.text_file = text_file
        self.out_dir =wav_folder.split('/')[-2]
        if not os.path.exists(self.out_dir):
            os.makedirs(self.out_dir)
        self.trans_file = self.out_dir + '/' + self.out_dir + ".trans"
        print(self.trans_file)
        self.merge_file = self.out_dir + '/' + self.out_dir + ".sh"
        print(self.merge_file)
        self.speakerIDs = []
        self.times = []
        self.transcripts = []

    def process_text(self):
        ''' build a dictionary of the form <string(text ID), string(text)>, 
        so for any file name prefix(text ID), we can get its corresponding sentence'''
        self.dic = {}
        text_file = open(self.text_file, 'r')
        for line in text_file:
            sentence = line.split('(')[0]
            key = ((line.split('('))[1].split(')'))[0] 
            self.dic.update({key:sentence})
        text_file.close()

    def process_wav(self):
        files = sorted([ f for f in listdir(self.wav_folder)])
        # get speakerID and name from single file names
        for cur_file in files:
            speakerID = cur_file[0:6] # specific to PDAm name format
            self.speakerIDs.append(speakerID)
            key = cur_file[0:10]
            self.transcripts.append(self.dic[key].capitalize())

        # get wav files duration in to a list (in seconds)
        # change this list into output format (start0, end0, start1, end1...)
        start = 0.0
        self.times = []
            
        for cur_file in files:
            full_file_name = self.wav_folder + '/' + cur_file
            cur_wav = wave.open(full_file_name,'r')
            duration = float(cur_wav.getnframes()) / cur_wav.getframerate()
            end = start + duration
            self.times.append([start, end])
            start = end
            cur_wav.close() 

    
    def write_result(self):
        # write result to file using FAVE required format
        trans_file = open(self.trans_file,'w')
        for i in range(len(self.speakerIDs)):
            line = self.speakerIDs[i] + '\t' + self.speakerIDs[i] + '\t' + \
            str(round(self.times[i][0],3)) + '\t' + str(round(self.times[i][1],3)) + '\t' + self.transcripts[i] + '\n'
            trans_file.write(line)


        trans_file.close()
    
    def create_merge_script(self):
        merge_file = open(self.merge_file, 'w')
        merge_file.write("sox ")
        files = sorted([ f for f in listdir(self.wav_folder)])
        # get speakerID and name from single file names
    
        for cur_file in files:
           merge_file.write("../" + self.wav_folder + cur_file + ' ')

        merge_file.write(self.out_dir + ".wav")
        merge_file.close()

if __name__ == '__main__':
    myProc = preprocess(sys.argv[1], "transcript.sent")
    myProc.process_text()
    myProc.process_wav()
    myProc.write_result()
    myProc.create_merge_script()
    
