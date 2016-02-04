#include <iostream>
#include "Model.h"
#include "SeqFGraph.h"
#include <string>

using namespace std;

int main(){
    string model_file = "model_sub_m100";
    string temp_file = "template";

    Model myModel(temp_file.c_str(), model_file.c_str());
//    cout << myModel.K << " " << myModel.D << " " << myModel.w[0][0] << endl;

    string data_file = "data_tiny";
    SeqVec myData(&myModel,data_file.c_str());
   
//    cout << myData.data[0].features[0].size() << endl; 
//    for (int i = 0; i < myData.data[1].features[0].size(); i++){
//        if (myData.data[1].features[0][i] != 0) {
//            cout << i << " " << myData.data[1].features[0][i] << endl;
//        }
//    }

    // check myData correctly get factor_yy from model.v
//    for(int i=0;i<myModel.K;i++){  
//        for(int j=0;j<myModel.K;j++){  
//            if (myModel.v[i][j] != 0)
//                cout << i << "," << j << "," << myModel.v[i][j] << "      ";
//            if ( myData.data_fgraph[0].factor_yy[i][j]!= 0)
//                cout << i << "," << j << "," << myData.data_fgraph[0].factor_yy[i][j] << endl;
//        }
//    }

    // check myData get factor_xy from myData.data and model.w
    // print w first
//    for (int i = 0; i < myModel.K; i++) {
//        for (int j = 0; j < myModel.D+1; j++) {
//            cout << myModel.w[i][j] << endl;
//        }
//    }
//      
//   // print first seq in myData
//    for (int i = 0; i < myData.data[0].T; i++) {
//        for (int j = 0; j < myModel.D+1; j++) {
//            cout << myData.data[0].features[i][j] << endl;
//        }
//    }
//
//    // print result of factor_xy
//    for (int i = 0; i < myData.data[0].T; i++) {
//        for (int j = 0; j < myModel.K; j++) {
//            cout << myData.data_fgraph[0].factor_xy[i][j] << endl;
//        }
//    }

    // verify factor_xy = seq * transpose(w)
    
}
