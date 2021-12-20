#include <iostream>
#include <queue>
#include <cmath>
#include <functional>
#include <string>
#include <sstream>
#include <random>
#include <chrono>
#include <bits/stdc++.h>

#include "../include/data.h"

using namespace std;

Data::Data()
{
    this->d = 0;
    this->n = 0;
    this->dq = 0;
    this->nq = 0;
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
        data.push_back(pair<string,vector<float>>());
        this->n++;
        this->d = 0;
        while (iss >> curr)
        {
            if (this->d == 0)
            {
                data[i].first = curr.c_str();
            }
            if (this->d > 0)
            {
                data[i].second.push_back(atof(curr.c_str()));
                
            }
            this->d++;
        }
        i++;
    }
    return 0;
}


int Data::Init_Data_Grid_curve(vector<pair<string, vector<float>>> &data)
{
    this->distanceFunction = &(this->FrechetDistance);


    srand((unsigned)time(NULL));

    for (float r = 0; r < data.size(); r++)
    {
        this->t.push_back(float(rand()) / float((RAND_MAX)) * this->delta);

        data_grid_curve.push_back(pair<string, vector<float>>());
        data_curve.push_back(pair<string, vector<float>>());
        for (float j = 0; j < data[r].second.size(); j++)
        {
            float temp_y = 0;

            temp_y = floor((((data[r].second[j]) - this->t[r]) / this->delta) + 0.5) * this->delta + this->t[r];    //snapping formula

            data_grid_curve[r].second.push_back(temp_y);    // for Aiii
            data_curve[r].second.push_back(temp_y);         // for Aii
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
        queries.emplace_back(pair<string, vector<float>>());
        this->nq++;
        this->dq = 0;

        while (iss >> curr)
        {
            if (this->dq == 0)
                queries[i].first = curr.c_str();
            if (this->dq > 0)
                queries[i].second.emplace_back(atof(curr.c_str()));
            this->dq++;
        }
        i++;
    }
    return 0;
}


int Data::Init_Query_Grid_curve(vector<pair<string, vector<float>>> &query)     //  Same for Queries
{

    for (float r = 0; r < query.size(); r++)
    {
        query_grid_curve.push_back(pair<string, vector<float>>());
        query_curve.push_back(pair<string, vector<float>>());
        for (float j = 0; j < query[r].second.size(); j++)
        {
            float temp_y = 0;

            temp_y = floor((((query[r].second[j]) - this->t[r]) / this->delta) + 0.5) * this->delta + this->t[r];

            query_grid_curve[r].second.push_back(temp_y);
            query_curve[r].second.push_back(temp_y);

        }
    }
    return 0;
}

int Data::Filtering(vector<pair<string, vector<float>>> &curve, float epsilon)
{

    for (float r = 0; r < curve.size(); r++)
    {
        for (float j = 0; j < curve[r].second.size(); j++)
        {
            if (j + 2 > curve[r].second.size() )
            {
                break;
            }
            else
            {
                // if a-b <= epsilon and b-c <= espsilon then del b
                if ((abs(curve[r].second[j] - curve[r].second[j + 1]) <= epsilon) && (abs(curve[r].second[j + 1] - curve[r].second[j + 2]) <= epsilon)) 
                {
                    curve[r].second.erase(curve[r].second.begin() + j);
                }
            }
        }
       
    }
    return 0;
}

int Data::Padding(vector<pair<string, vector<float>>> &data, vector<pair<string, vector<float>>> &query) // check how has bigger size and then pad the other
{
    for (float j = 0; j < query.size(); j++)
    {
        for (float i = 0; i < data.size(); i++)
        {
            //cout << "prin d " << data[i].second.size()<<" prin q " << query[j].second.size() << endl;
            if (data[i].second.size() > query[j].second.size())
            {
                while (data[i].second.size() != query[j].second.size())
                {
                    query[j].second.push_back(INT_MAX);
                }
            }
            else if (data[i].second.size() < query[j].second.size())
            {
                while (data[i].second.size() != query[j].second.size())
                {
                    data[i].second.push_back(INT_MAX);
                }
            }
            else    // if same size
            {
                continue;
            }
            //cout << "data " <<data[i].second.size() << " query " << query[j].second.size() << endl << endl;
        }
    }
    return 0;
}


int Data::Min_max_filter(vector<pair<string, vector<float>>> &curve)    // same as filtering but for Aii, removing dups
{
    for (float r = 0; r < curve.size(); r++)
    {
        for (float j = 0; j < curve[r].second.size(); j++)
        {
            if (j + 1 > curve[r].second.size())
            {
                break;
            }
            else if (j - 1 < 0)
            {
                continue;
            }
            else
            {
                // if j-1 < j < j+1 or j= j+1 = j-1 remove j
                if (((curve[r].second[j] > curve[r].second[j - 1]) && (curve[r].second[j] < curve[r].second[j + 1]) )|| ((curve[r].second[j] == curve[r].second[j - 1]) && (curve[r].second[j] == curve[r].second[j + 1])) )
                {
                    curve[r].second.erase(curve[r].second.begin() + j);
                }
            }
        }
    }
    return 0;
    
}


double Data::EuclideanDistance(vector<float> &p1, vector<float> &p2,int i, int j)
{
    unsigned int d = 0;

    if(i==j){} //getting rid of warning

    for (size_t i = 0; i < p1.size(); i++)
    {
        d += pow(p2[i] - p1[i], 2);
    }

    return sqrt(d);
}

double Data::FrechetDistance(vector<float> &curve_1, vector<float> &curve_2,int i, int j)
{
    
    if(i==0 && j==0)        //base case
    {
        return sqrt(pow(curve_2[0] - curve_1[0],2) * 1.0 );
    }
    if (i==0 && j> 0 )      //base case
    {
        return max(FrechetDistance(curve_1,curve_2,0,j-1),sqrt(pow(curve_2[j] - curve_1[0],2) * 1.0 ));
    }
    if( i> 0 && j==0)   //base case
    {
        return max(FrechetDistance(curve_1,curve_2,i-1,0),sqrt(pow(curve_2[0] - curve_1[i],2) * 1.0 ));
    }
        
    //max ( min ( c(i-1,j) , c(i-1,j-1) , c(i,j-1) ), ||p_i-q_j|| )
    return max( {min( {FrechetDistance(curve_1,curve_2,i-1,j) ,FrechetDistance(curve_1,curve_2,i-1,j-1),FrechetDistance(curve_1,curve_2,i,j-1)} ), sqrt(pow(curve_2[j] - curve_1[i],2) * 1.0 )});
    
}


vector<pair<int, int>> Data::Range_Search(vector<float> query, float R)
{
    vector<pair<int, int>> result;

    for (int i = 0; i < this->n; i++)
    {
        int d = this->distanceFunction(this->data[i].second, query,0,0);
        if (d < R)
        {
            result.emplace_back(d, i);
        }
    }
    return result;
}

vector<pair<int, int>> Data::Get_Closest_Neighbors( vector<float> &query, vector<pair<int, vector<float>>> &data, const int &N)
{
    vector<pair<int, int>> result;

    auto cmp = [](pair<int, int> left, pair<int, int> right)
    {
        return left.first > right.first;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);

    for (int i = 0; i < int(data.size()); i++)
    {
        q.push(make_pair(this->distanceFunction(data[i].second, query,0,0), data[i].first));
    }

    int min = (N < int(q.size())) ? N : q.size();

    for (int i = 0; i < min; i++)
    {
        result.push_back(q.top());
        q.pop();
    }

    return result;
}

vector<pair<int, int>> Data::Brute_Force_Neighbors(vector<float> &query, const int &N)
{
    vector<pair<int, int>> result;

    auto cmp = [](pair<int, int> left, pair<int, int> right)
    {
        return left.first > right.first;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);

    for (int i = 0; i < int(this->data.size()); i++)
    {
        q.push(make_pair(this->distanceFunction(this->data[i].second, query,0,0), i));
    }

    int min = (N < int(q.size())) ? N : q.size();

    for (int i = 0; i < min; i++)
    {
        result.push_back(q.top());
        q.pop();
    }

    return result;
}
