#pragma once

#include <iostream>
#include <vector>

#include "./LSH.h"
#include "./hyperCube.h"

using namespace std;

enum Method
{
    _Classic,
    _LSH,
    _HyperCube,
    _LSH_Fr,
    _Classic_Fr
};

class kmeansplusplus
{
private:
    int nClusters;
    bool complete;
    int lsh_k, L;          // for lsh
    int cube_k, M, probes; // for hypercube
    int minChange = 0;
    int maxIterations = 90;
    Method method;
    Data &data;
    LSH *lsh = nullptr;
    HyperCube *cube = nullptr;
    vector<pair<string, vector<float>>> centroids;

    void initCentroids();
    float minDinstance_from_Centroids(vector<float> &point);
    int findNextCentroid(vector<double> &P, const double x); // used for initialization
    int median(vector<float> &v);
    int minCentroid(vector<float> &point, const int flag);
    int nextCentroid(vector<float> &point);
    void print(vector<vector<int>> &clusters, ofstream &outputFile, int64_t time, vector<double> silouette);

    vector<vector<int>> LloydsClustering(const int flag);
    vector<vector<int>> LSHClustering(const int flag);
    vector<vector<int>> HyperCubeClustering();

    vector<double> Silouette(vector<vector<int>> clusters);

public:
    kmeansplusplus(const int &clusters, const bool &complete, Data &data, const int frechet);
    kmeansplusplus(const int &clusters, const bool &complete, const int &lsh_k, const int &L, Data &data, const int frechet);
    kmeansplusplus(const int &clusters, const bool &complete, const int &cube_k, const int &M, const int &probes, Data &data);
    ~kmeansplusplus();

    int Run(ofstream &outputFile);
};