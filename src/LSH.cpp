#include <iostream>
#include <chrono>
#include <unordered_set>

#include "../include/LSH.h"
#include "../include/hashTable.h"

using namespace std;

LSH::LSH(int k, int L, Data &data, float w, int r,float delta,string algorithm)
    : k(k), L(L), data(data), w(w), r(r), delta(delta), algorithm(algorithm)
{
    this->M = pow(2, 32 / k);
    this->r = r;
    this->tables.resize(this->L);
    this->delta = delta;
    data.delta = this->delta;
    this->algorithm = algorithm;
    this->k = k;
   // cout << this->data.d << endl;
    
    for (int i = 0; i < L; i++)
    {
        this->tables[i] = new hashTable(this->data.n, this->k, this->data.d, this->w, this->M);         //data.n/32
    }

    

    hashData();
}

LSH::~LSH()
{
    for (int i = 0; i < L; i++)
    {
        delete this->tables[i];
    }
}

int LSH::Run(vector<pair<string, vector<float>>> &queries, ofstream &outputFile, int &N)
{
    for (int i = 0; i < int(queries.size()); i++)
    {
        auto lshStart = chrono::high_resolution_clock::now();
        vector<pair<int, int>> lshResult = this->exec_query(queries[i].second, N);
        auto lshStop = chrono::high_resolution_clock::now();

        auto tLSH = chrono::duration_cast<chrono::milliseconds>(lshStop - lshStart);

        auto tStart = chrono::high_resolution_clock::now();
        vector<pair<int, int>> trueResult = this->data.Brute_Force_Neighbors(queries[i].second, N);
        auto tStop = chrono::high_resolution_clock::now();

        auto tTrue = chrono::duration_cast<chrono::milliseconds>(tStop - tStart);

        this->print(outputFile, lshResult, trueResult, tLSH.count(), tTrue.count(),data.data,queries);
    }

    return 0;
};

void LSH::hashData()
{
    
    for (int i = 0; i < this->L; i++)
    {
        for (int j = 0; j < this->data.n; j++)
        {
            float g = this->calculate_g(this->data.data[j].second, this->tables[i]);
            

            this->tables[i]->Insert_Item(g, j, this->data.data[j].second);
        }
        
    }
    

}

uint32_t LSH::calculate_g(vector<float> &points, hashTable *ht) 
{
    uint32_t g = 0, result;

    for (int i = 0; i < this->k; i++)
    {
        g = g + (this->r * ht->calculate_h(points, ht->v[i], this->k));
    }

    result = g % this->data.n; // this->Data.n == tableSize
    return result;
}

vector<pair<int, int>> LSH::exec_query(vector<float> &query, int &N)
{
    unordered_set<int> pickedPoints;
    vector<pair<int, vector<float>>> possible_neighbors;

    for (auto &table : this->tables)
    {
        float g = this->calculate_g(query, table);

        for (auto &point : table->Get_Items(g))
        {
            if (pickedPoints.find(point.first) == pickedPoints.end()) // for duplicates , phgaine mesa sta picked points kai an den uparxnoun balta
            {
                pickedPoints.insert(point.first);
                possible_neighbors.emplace_back(point.first, point.second);
            }
        }
    }

    return this->data.Get_Closest_Neighbors(query, possible_neighbors, N);
}

void LSH::print(ofstream &outputFile, vector<pair<int, int>> lshResult, vector<pair<int, int>> trueResult, const double &tLSH, const double &tTRUE, vector<pair<string,vector<float>>> &data,vector<pair<string,vector<float>>> &query)
{
    

    for (float j = 0; j < query.size(); j++)
    {
        outputFile << "Query: " << query[j].first << endl;
        outputFile << "Algorithm: " << this->algorithm <<endl;
        for (int i = 0; i < int(lshResult.size()); i++)
        {

            outputFile << "Approximate Nearest neighbor: " << data[j].first << ": " << lshResult[i].second << endl;
            outputFile << "True Nearest neighbor: " << data[j].first << ": " << trueResult[i].second << endl;
            outputFile << "distanceLSH: " << lshResult[i].first << endl;
            outputFile << "distanceTrue: " << trueResult[i].first << endl
                    << endl;
        }

        outputFile << "tLSH: " << tLSH << endl;
        outputFile << "tTRUE: " << tTRUE << endl;
        outputFile << endl;
    }
}