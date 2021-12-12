#include <iostream>
#include <queue>
#include <cmath>
#include <functional>
#include <string>
#include <sstream>
#include <random>
#include <chrono>

#include "../include/data.h"

using namespace std;

Data::Data()
{
    this->d = 0;
    this->n = 0;
    this->x = 1;
    this->delta = 0.5;
    this->distanceFunction = &(this->EuclideanDistance);
}

int Data::Init_DataSet(ifstream &inputFile)
{
    string line;
    string curr;
    int i = 0;

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        data.push_back(vector<float>());
        this->n++;

        while (iss >> curr)
        {
            data[i].push_back((float)atof(curr.c_str()));
            this->d++;
            
        }
        i++;
    }

    return 0;
}

int Data::Init_Data_curve(const vector<vector<float>> &data)
{

    for (float r = 0; r < data.size(); r++)
    {
        data_curve.push_back(vector<pair<float,float>>());
        for (float j = 0; j < data[r].size(); j++)
        {
            float temp_x = j * this->x;
            data_curve[r].push_back(make_pair(temp_x,data[r][j]));
            //cout << " " << data_curve[r][j].first << " " << data_curve[r][j].second << endl;
            
        
        }
    }
    //Init_Query_Grid_curve(query_curve);
    return 0;
}

int Data::Init_Data_Grid_curve(const vector<vector<pair<float,float>>> &data_curve)
{
    srand( (unsigned)time( NULL ) );

    for (float r = 0; r < data_curve.size(); r++)
    {
        this->t.push_back( float(rand())/float((RAND_MAX)) * this->delta );
        data_grid_curve.push_back(vector<pair<float,float>>());
        for (float j = 0; j < data_curve[r].size(); j++)
        {
            float temp_x=0;
            float temp_y=0;

            temp_x = floor((((data_curve[r][j].first) - this->t[r])/this->delta)+0.5)*this->delta + this->t[r];
            temp_y = floor((((data_curve[r][j].second) - this->t[r])/this->delta)+0.5)*this->delta + this->t[r];
            
            data_grid_curve[r].push_back(make_pair(temp_x,temp_y));


            //cout << " " << grid_curve[r][j].first << " " << grid_curve[r][j].second << endl;

        }
    }
    return 0;
}


int Data::ReadQueryFile(ifstream &queryFile)
{
    string line;
    string curr;
    int i = 0;

    while (getline(queryFile, line))
    {
        istringstream iss(line);
        queries.push_back(vector<float>());

        while (iss >> curr)
        {
            queries[i].push_back((float)atof(curr.c_str()));
        }
        i++;
    }
    return 0;
}


int Data::Init_Query_curve(const vector<vector<float>> &query)
{

    for (float r = 0; r < query.size(); r++)
    {
        query_curve.push_back(vector<pair<float,float>>());
        for (float j = 0; j < query[r].size(); j++)
        {
            float temp_x = j * this->x;
            query_curve[r].push_back(make_pair(temp_x,query[r][j]));
            
        } 
    }

    return 0;
}

int Data::Init_Query_Grid_curve(const vector<vector<pair<float,float>>> &query_curve)
{

    for (float r = 0; r < query_curve.size(); r++)
    {
        query_grid_curve.push_back(vector<pair<float,float>>());
        for (float j = 0; j < query_curve[r].size(); j++)
        {
            float temp_x=0;
            float temp_y=0;

            temp_x = floor((((query_curve[r][j].first) - this->t[r])/this->delta)+0.5)*this->delta + this->t[r];
            temp_y = floor((((query_curve[r][j].second) - this->t[r])/this->delta)+0.5)*this->delta + this->t[r];
            
            query_grid_curve[r].push_back(make_pair(temp_x,temp_y));


            //cout << " " << query_grid_curve[r][j].first << " " << query_grid_curve[r][j].second << endl;

        }
    }
    return 0;
}

double Data::EuclideanDistance(const vector<float> &p1, const vector<float> &p2)
{
    unsigned int d = 0;

    for (size_t i = 0; i < p1.size(); i++)
    {
        d += pow(p2[i] - p1[i], 2);
    }
    
    return sqrt(d);
}

double Data::FrechetDistance(const vector<vector<pair<float,float>>> &curve_1, const vector<vector<pair<float,float>>> &curve_2)
{
    
}



vector<pair<int, int>> Data::Range_Search(vector<float> query, float R)
{
    vector<pair<int, int>> result;

    for (int i = 0; i < this->n; i++)
    {
        int d = this->distanceFunction(this->data[i], query);
        if (d < R)
        {
            result.emplace_back(d, i);
        }
    }
    return result;
}

vector<pair<int, int>> Data::Get_Closest_Neighbors(const vector<float> &query, const vector<pair<int, vector<float>>> &data, const int &N)
{
    vector<pair<int, int>> result;

    auto cmp = [](pair<int, int> left, pair<int, int> right){    
        return left.first > right.first;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
    
    for (int i = 0; i < int(data.size()); i++)
    {
        q.push(make_pair(this->distanceFunction(data[i].second, query), data[i].first));
    
    }

    int min = (N < int(q.size())) ? N : q.size();

    for (int i = 0; i < min; i++)
    {
        result.push_back(q.top()); 
        q.pop();
    }
    
    return result;
}

vector<pair<int, int>> Data::Brute_Force_Neighbors(const vector<float> &query, const int &N)
{
    vector<pair<int, int>> result;

    auto cmp = [](pair<int, int> left, pair<int, int> right)
    {
        return left.first > right.first;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);

    for (int i = 0; i < int(this->data.size()); i++)
    {
        q.push(make_pair(this->distanceFunction(this->data[i], query), i));
    }

    int min = (N < int(q.size())) ? N : q.size();

    for (int i = 0; i < min; i++)
    {
        result.push_back(q.top());
        q.pop();
    }

    return result;
}