#include <list>
#include <unordered_set>
#include <vector>
#include <string>
#include <chrono>
#include <random>

#include "hashTable.h"
#include "data.h"

using namespace std;

class f
{
    private:
        unordered_set<string> setofZeros;
        unordered_set<string> setofOnes;

    public:
        f();
        ~f();

        int calculate_f(string key);
    
};

class HyperCube
{
    private:
        int k, M, probes;
        Data &data;
        hashTable *ht;
        vector<f *> fTable;

        string to_Binary(int n, int size);

        int hamming(string str1, string str2);

        list<string> Hamming_Distance(string s, int probes);

        void print(
            ofstream &outputfile,
            vector<pair<int, int>> cubeResult,
            vector<pair<int, int>> trueResult,
            const int64_t &tCube, const int64_t &tTrue,
            vector<pair<string,vector<float>>> &data,
            vector<pair<string,vector<float>>> &query
            );
        
        void hashData();
        void HyperCube_Insert(string &s, int index, vector<float> &point);
    
    public:
        HyperCube(int k, int M, int probes, Data &data, float w = 10000);
        ~HyperCube();

        int Run(vector<pair<string,vector<float>>> &queries, ofstream &outputFileint, int &N);
        vector<pair<int, int>> exec_query(vector<float> &query, int &N);
};