#pragma once

#include <cmath>
#include <vector>

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

        vector<hashTable *> tables;

        void hashData();

        uint32_t calculate_g(const vector<float> &points, hashTable *ht );

        void print(
                ofstream &outputFile,
                const int &query,
                vector<pair<int,int>> lshResult,
                vector<pair<int,int>> trueResult,
                const double &tLSH, const double &tTRUE,
                vector<pair<int,int>> rangeSearch
        ); 
    
    public:
        LSH(int , int L, Data &data, float w = 10000, int r= 10000);
        ~LSH();

        int Run(const vector<vector<float>> &queries, ofstream &outputFile, const int &N, const int &R);

        vector<pair<int,int>>
        exec_query(const vector<float> &query,const int &N);
};