#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>

#include "./data.h"
#include "./hashTable.h"

using namespace std;

class LSH
{
    private:
        int k, L;
        Data &data;
        float w, M;

        int r;
        double delta;
        

        vector<hashTable *> tables;

        void hashData();

        uint32_t calculate_g(vector<float> &points, hashTable *ht );

        void print(
                ofstream &outputFile,
                vector<pair<int,int>> lshResult,
                vector<pair<int,int>> trueResult,
                const double &tLSH, const double &tTRUE,
                vector<pair<string,vector<float>>> &data,
                vector<pair<string,vector<float>>> &query
        ); 
    
    public:
    string algorithm;
        LSH(int , int L, Data &data, float w = 10000, int r= 10000, float delta= 0.5,string algorithm= "default");
        ~LSH();

        int Run(vector<pair<string, vector<float>>> &queries, ofstream &outputFile, int &N);

        vector<pair<int,int>>
        exec_query(vector<float> &query, int &N);
};