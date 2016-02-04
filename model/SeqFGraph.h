#ifndef SEQFGRAPH_H
#define SEQFGRAPH_H

#include <iostream>
#include "util.h"
#include "Model.h"
using namespace std;

// feature starts index wtih 1

// a single sequence
// warning: there should not be an empty line at end of data file, ow it will be seen as a seq with length 0
class Seq {
	public:
    Seq() { T = 0; }
	int T; // seq length
	vector<int> labels; // 1*T
	vector< vector<int> > features; // 1*T, each feature is of size D + 1
};

// graph for a single sequence
class SeqFGraph {
	public:
	double** factor_xy; // T by K
	double** factor_yy; // K by K
	SeqFGraph(Model* model, Seq* seq);
};

SeqFGraph::SeqFGraph(Model* model, Seq* seq){
    // factor_yy is just model->v (same for every <y, y+1>), K by K
    factor_yy = model->v;     
    // factor_xy is model->w * feature vec, T by K
    int T = seq->features.size();
    int D = model->D;
    int K = model->K;
    
    // initialize factor_xy: T by K
    factor_xy = new double*[T];
    for (int t = 0; t < T; t++)
        factor_xy[t] = new double[K];
    for (int t = 0; t < T; t++) 
        for (int k = 0; k < K; k++) 
            factor_xy[t][k] = 0;
 
//    cout << T << " " << D << " " << K << endl;
    // compute w * features
    for (int t = 0; t < T; t++) {
        for (int k = 0; k < K; k++) {
            double temp = 0; // = (kth row of W) * seq->features[t]
            for (int d = 0; d < D + 1; d++) {
                temp += model->w[k][d] * seq->features[t][d];
            }
            factor_xy[t][k] = temp;
        }
    }
}

// a collection of sequences
class SeqVec {
    public:
    vector<Seq> data; // a vector of sequences
    vector<SeqFGraph> data_fgraph; // a vector of factor graph correspond to data
    SeqVec(Model* model, const char* data_file);
};

SeqVec::SeqVec(Model* model, const char* data_file){
    // 1.0 get data
	char* _line = new char[MAX_LINE];
	string line;
	vector<string> tokens;
	vector<string> iv_pair;
	
    // get D from model
	int D = model->D;

	// get sequences from data file
	ifstream fin_data(data_file);
	if (fin_data.fail()){
		cerr << "can't open data file." << endl;
		exit(0);
	}
	data.push_back(Seq());
	Seq* seq = &(data.back());
	
	while( !fin_data.eof() ){
		fin_data.getline(_line,MAX_LINE);
		string line(_line);
		if( line.size() <= 1 && !fin_data.eof() ){
			data.push_back(Seq());
			seq = &(data.back());
			continue;
		}else if( line.size() <= 1 ){
			break;
		}

		split(line," ", tokens);

		// get Label
		seq->labels.push_back(atoi(tokens[0].c_str()));
		// get feature, size D+1
		vector<int> fea;
        for (int i = 0; i < D + 1; i++){
            fea.push_back(0);
        }
		for(int j = 1;j < tokens.size(); j++){
			split(tokens[j], ":", iv_pair);
			int index = atoi(iv_pair[0].c_str());
			int value =  atof(iv_pair[1].c_str());
            fea[index] = value;
		}
		seq->features.push_back(fea);
        seq->T++;
	}
	fin_data.close();

    // 2.0 construct factor graphs
    for (int i = 0; i < data.size(); i++) {
        SeqFGraph fgraph(model, &data[i]);  
        data_fgraph.push_back(fgraph);
    }    

}

#endif
