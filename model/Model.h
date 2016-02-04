#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <vector>
#include "util.h"
using namespace std;

const int MAX_LINE = 10000000;  // max char in a line in a file
const int FNAME_LENGTH = 10000; // max length of a file name

class Model{

    public:
    int K; 
    int D;

    double** v; // K by K
	double** w; // K by D + 1

    Model (const char* templ_file, const char* model_file);
};

Model::Model(const char* templ_file, const char* model_file) {

    char* _line = new char[MAX_LINE];    
    vector<string> tokens; 
    vector<string> iv_pair;    

    // get K from template file
	ifstream fin_templ(templ_file);
	if (fin_templ.fail()){
		cerr << "can't open template file." << endl;
		exit(0);
	}
	fin_templ.getline(_line, MAX_LINE); 
    fin_templ.getline(_line, MAX_LINE); // actual labels are on the 2nd line of template file
	string line = string(_line);
	split(line, " ", tokens);
    K = tokens.size();        
    fin_templ.close();
   
	// get D from model file
	ifstream fin_model(model_file);
	if (fin_model.fail()){
		cerr << "can't open model file." << endl;
		exit(0);
	}
	fin_model.getline(_line, MAX_LINE);
	line = string(_line);
	split(line, ":", tokens);
	D = atoi(tokens[1].c_str());
    
    // declare w and v
    w = new double*[K];//  K by D+1
	for(int k = 0; k < K; k++)
		w[k] = new double[D+1];
    v = new double*[K];//  K by K
	for(int k = 0;k < K; k++)
        v[k] = new double[K];
    // initialize all entries to 0
	for(int i = 0; i < K; i++)
        for (int j = 0; j < D + 1; j++)
            w[i][j] = 0;
	for(int i = 0; i < K; i++)
        for (int j = 0; j < K; j++)
            v[i][j] = 0;

    // fill in w and v using second line in model file
	fin_model.getline(_line, MAX_LINE);
	line = string(_line);
	split(line, " ", tokens);
    int w_end_index =  K * (D + 1) - 1;    

	for(int i = 0; i < tokens.size(); i++){
        split(tokens[i], ":", iv_pair);
        int index = atoi(iv_pair[0].c_str());
		double val = atof(iv_pair[1].c_str());
	    
        int row, col;
        if (index <= w_end_index) { // index = 0 to K*(D+1) - 1: fill in w as col vectors
            row = index % K; 
            col = index / K; 
            w[row][col] = val;    
            // cout << index << " w: " << row << " " << col << " " << w[row][col] << endl;
        }
        else { // index = K*(D+1) to end: fill in v as row vectors
            row = (index - K * (D + 1)) / K;
            col = (index - K * (D + 1)) % K; 
            v[row][col] = val;
            // cout << index << " v: " << row << " " << col << " " << v[row][col] << endl;
        }
	}

    fin_model.close();
    delete[] _line;
}

#endif
