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


public:
    int n,nq; // number of data
    int d,dq; // dimension
    int x;
    float delta;
    vector<float> t;
    vector<pair<string, vector<float>>> data;
    vector<pair<string, vector<float>>> queries;

    vector<pair<string,vector<float>>> data_curve;  // erwthma 2
    vector<pair<string,vector<float>>> query_curve; // erwthma 2

    vector<pair<string,vector<float>>> data_grid_curve;          // erwthma 3 thn exw sthn euteia , prepei filtering
    vector<pair<string,vector<float>>> query_grid_curve;

    vector<double> results_frechet;


    Data();

        static double EuclideanDistance(vector<float> &p1, vector<float> &p2,int i, int j);
    static double FrechetDistance(vector<float> &curve_1, vector<float> &curve_2,int i, int j); // isws ginei private, thn eixa edw gia testing

    vector<float> compare(vector<vector<float>> data, vector<vector<float>> query);

    int Init_DataSet(ifstream &inputFile); // dhmiourgia tou dataset
    int Init_Data_Grid_curve(vector<pair<string,vector<float>>> &data);

    int ReadQueryFile(ifstream &queryFile); // dhmourgia tou queryset
    int Init_Query_Grid_curve(vector<pair<string,vector<float>>> &query);

    int Filtering(vector<pair<string,vector<float>>> &curve,float epsilon);
    int Padding(vector<pair<string,vector<float>>> &data, vector<pair<string,vector<float>>> &query);

    
    double (*distanceFunction)(vector<float> &p1,vector<float> &p2,int i, int j);

    vector<pair<int, int>> Range_Search(vector<float> query, float R);
    int Min_max_filter(vector<pair<string, vector<float>>> &curve);

    int Run_Frechet(pair<string,vector<pair<float,float>>> &curve_1, pair<string,vector<pair<float,float>>> &curve_2);

    vector<pair<int, int>> Get_Closest_Neighbors(vector<float> &query, vector<pair<int, vector<float>>> &data, int &N);
    vector<pair<int, int>> Brute_Force_Neighbors(vector<float> &query,int &N);
};