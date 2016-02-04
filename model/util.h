#ifndef UTIL
#define UTIL

#include<vector>
#include<map>
#include<string>
#include<cmath>
#include <iomanip>      // std::setprecision
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

void split(string str, string pattern, vector<string>& tokens);

double maximum(double* values, int size);

double maximum(double* values, int size,int &posi);

int expOverSumExp(double *values, double *prob, int size);

double logSumExp(double* values, int size);

double normalize(double* values, int size);

void dataToFeatures( vector<vector<pair<int,double> > >& data, int dim,  //intput
		vector<vector<pair<int,double> > >& features //output
        );	

void softThd(double* w, vector<int> &act_set, double t_lambda);
void softThd(double* w, int size, double t_lambda);
double softThd(const double &x,const double  &thd);

double l1_norm(double* w, int size);

double l1_norm(vector<double>& w);

double l1_norm(double *w, vector<int> &actset);

double l2_norm(double* w,int size);
void shuffle(vector<int>& arr);

double sign(double v);

#endif
