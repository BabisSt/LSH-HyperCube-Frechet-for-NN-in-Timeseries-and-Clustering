/*
Auto to arxeio eiani gia na diabazei ta dataset kai na ta kanei parse

*/

#pragma once

#include <fstream>
#include <vector>

using namespace std;

class Data
{
private:
    static double EuclideanDistance(const vector<float> &p1, const vector<float> &p2);
    static double FrechetDistance(const vector<vector<pair<float, float>>> &curve_1, const vector<vector<pair<float, float>>> &curve_2);

public:
    int n; // number of data
    int d; // dimension
    int x;
    float delta;
    vector<float> t;
    vector<string> id;
    vector<pair<string, vector<float>>> data;
    vector<pair<string, vector<float>>> queries;

    vector<vector<pair<float, float>>> data_curve;  // erwthma 2
    vector<vector<pair<float, float>>> query_curve; // erwthma 2

    vector<pair<string,vector<float>>> data_grid_curve;          // erwthma 3 thn exw sthn euteia , prepei filtering
    vector<pair<string,vector<float>>> query_grid_curve;

    Data();

    vector<float> compare(vector<vector<float>> data, vector<vector<float>> query);

    int Init_DataSet(ifstream &inputFile); // dhmiourgia tou dataset
    int Init_Data_curve(vector<vector<float>> &data);
    int Init_Data_Grid_curve(vector<pair<string,vector<float>>> &data);

    int ReadQueryFile(ifstream &queryFile); // dhmourgia tou queryset
    int Init_Query_curve(vector<vector<float>> &query);
    int Init_Query_Grid_curve(vector<pair<string,vector<float>>> &query);

    int Filtering(vector<pair<string,vector<float>>> &curve);
    int Padding(vector<pair<string,vector<float>>> &data, vector<pair<string,vector<float>>> &query);

    // float find_dist(vector<pair<float,float>> &p, vector<pair<float,float>> &q);
    double (*distanceFunction)(const vector<float> &p1, const vector<float> &p2);

    vector<pair<int, int>> Range_Search(vector<float> query, float R);

    vector<pair<int, int>> Get_Closest_Neighbors(const vector<float> &query, const vector<pair<int, vector<float>>> &data, const int &N);
    vector<pair<int, int>> Brute_Force_Neighbors(const vector<float> &query, const int &N);
};