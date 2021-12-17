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
        data.emplace_back(pair<string, vector<float>>());
        this->n++;
        this->d = 0;

        while (iss >> curr)
        {
            if (d == 0)
                data[i].first = curr.c_str();
            if (d > 0)
                data[i].second.emplace_back(atof(curr.c_str()));
            this->d++;
        }
        i++;
    }

    /*    cout << "n:" << n << "  d:" << d << endl;     TYPOMA TOU DATASET

        for (int k = 0; k < 10; k++)
        {
            cout << "id:" << data[k].first;
            cout << endl;
            for (int z = 0; z < 120; z++)
            {
                cout << data[k].second[z] << " ";
            }
            cout << endl;
        }
    */
    return 0;
}

int Data::Init_Data_curve(vector<pair<string,vector<float>>> &data) // erwthma 2
{
    //this->distanceFunction = &(this->vector<float> &p1, vector<float> &p2);
    for (float r = 0; r < data.size(); r++)
    {
        data_curve.push_back(pair<string,vector<pair<float, float>>>());
        for (float j = 0; j < data[r].second.size(); j++)
        {
            float temp_x = j * this->x;
            data_curve[r].second.push_back(make_pair(temp_x, data[r].second[j]));
            // cout << " " << data_curve[r][j].first << " " << data_curve[r][j].second << endl;
        }
    }

    
    // Init_Data_Grid_curve(data);
    return 0;
}

int Data::Init_Data_Grid_curve(vector<pair<string, vector<float>>> &data) // erwthma 3, kanei snap thn y
{
    srand((unsigned)time(NULL));

    for (float r = 0; r < data.size(); r++)
    {
        this->t.push_back(float(rand()) / float((RAND_MAX)) * this->delta);
        data_grid_curve.push_back(pair<string, vector<float>>());
        for (float j = 0; j < data[r].second.size(); j++)
        {
            float temp_y = 0;

            temp_y = floor((((data[r].second[j]) - this->t[r]) / this->delta) + 0.5) * this->delta + this->t[r];

            data_grid_curve[r].second.push_back(temp_y);

            // cout << data_grid_curve[r][j] << endl;
        }
        // cout << data[r].size() << endl;
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
        this->n++;
        this->d = 0;

        while (iss >> curr)
        {
            if (d == 0)
                queries[i].first = curr.c_str();
            if (d > 0)
                queries[i].second.emplace_back(atof(curr.c_str()));
            this->d++;
        }
        i++;
    }
    return 0;
}

int Data::Init_Query_curve(vector<pair<string,vector<float>>> &query) // erwthma 2
{
    vector<double> results;
    for (float r = 0; r < query.size(); r++)
    {
        query_curve.push_back(pair<string,vector<pair<float, float>>>());
        for (float j = 0; j < query[r].second.size(); j++)
        {
            float temp_x = j * this->x;
            query_curve[r].second.push_back(make_pair(temp_x, query[r].second[j]));
        }
    }
    //double x =FrechetDistance(data_curve[0].second,query_curve[0].second,0,0);
    //cout << "x" << x <<endl;
    return 0;
}



int Data::Init_Query_Grid_curve(vector<pair<string, vector<float>>> &query) // erwthma 3, pairnw thn mia metablhth y kai thn kanw snap
{

    for (float r = 0; r < query.size(); r++)
    {
        query_grid_curve.push_back(pair<string, vector<float>>());
        for (float j = 0; j < query[r].second.size(); j++)
        {
            float temp_y = 0;

            temp_y = floor((((query[r].second[j]) - this->t[r]) / this->delta) + 0.5) * this->delta + this->t[r];

            query_grid_curve[r].second.push_back(temp_y);
            

            // cout << query_grid_curve[r][j] << endl;
        }
        // cout << data[r].size() << endl;
    }
    return 0;
}

int Data::Filtering(vector<pair<string, vector<float>>> &curve)
{
    float epsilon = 0.1;    //

    for (float r = 0; r < curve.size(); r++)
    {
        for (float j = 0; j < curve[r].second.size(); j++)
        {
            if (curve[r].second[j + 2] == NULL)
            {
                break;
            }
            else
            {
                if ((abs(curve[r].second[j] - curve[r].second[j + 1]) <= epsilon) && (abs(curve[r].second[j + 1] - curve[r].second[j + 2]) <= epsilon))
                {
                    curve[r].second.erase(curve[r].second.begin() + j);
                }
            }
        }
        // cout << "curve " << curve[r].size()<< endl;
    }
    return 0;
}

int Data::Padding(vector<pair<string, vector<float>>> &data, vector<pair<string, vector<float>>> &query)
{
    for (float j = 0; j < query.size(); j++)
    {
        for (float i = 0; i < data.size(); i++)
        {
            // cout << "prin d " << data[i].size()<<" prin q " << query[j].size() << endl;

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
            else
            {
                continue;
            }
            // cout << "data " <<data[i].size() << " query " << query[j].size() << endl << endl;
        }
    }
    return 0;
}

double Data::EuclideanDistance(vector<float> &p1, vector<float> &p2)
{
    unsigned int d = 0;

    for (size_t i = 0; i < p1.size(); i++)
    {
        d += pow(p2[i] - p1[i], 2);
    }

    return sqrt(d);
}

double Data::FrechetDistance(pair<string,vector<pair<float,float>>> &curve_1, pair<string,vector<pair<float,float>>> &curve_2,int i, int j)
{
    //cout <<" i" <<i << "j" << j<< endl;
    //cout << "size 1 " << curve_1.size() << "size 2" << curve_2.size() << endl;
    if( i==0 && j==0)
    {
        return sqrt(pow(curve_2.second[0].second - curve_1.second[0].second,2) * 1.0 );
    }
    if (i==0 && j> 0 )
    {
        return max(FrechetDistance(curve_1,curve_2,0,j-1),sqrt(pow(curve_2.second[j].second - curve_1.second[0].second,2) * 1.0 ));
    }
    if( i> 0 && j==0)
    {
        return max(FrechetDistance(curve_1,curve_2,i-1,0),sqrt(pow(curve_2.second[0].second - curve_1.second[i].second,2) * 1.0 ));
    }
        //cout << "x " << curve_2[j].first << " " << curve_1[i].first << endl;
        //cout << "y " << curve_2[j].second << " " << curve_1[i].second << endl;

    return max( {min( {FrechetDistance(curve_1,curve_2,i-1,j) ,FrechetDistance(curve_1,curve_2,i-1,j-1),FrechetDistance(curve_1,curve_2,i,j-1)} ), sqrt(pow(curve_2.second[j].first - curve_1.second[i].first,2) + pow(curve_2.second[j].second - curve_1.second[i].second,2) * 1.0 )});
    //return min(FrechetDistance(curve_1,curve_2,i-1,j),double(24));
}

int Data::Run_Frechet(pair<string,vector<pair<float,float>>> &curve_1, pair<string,vector<pair<float,float>>> &curve_2)
{

    // for (float i = 0; i < curve_1.second.size(); i++)
    // {
    //     for (float j = 0; j < curve_2.second.size(); j++)
    //     {
    // cout << "mesa" << endl;
    //         results_frechet.push_back( FrechetDistance(curve_1,curve_2,i,j));
    //     }
    // }

    // return 0;
}


vector<pair<int, int>> Data::Range_Search(vector<float> query, float R)
{
    vector<pair<int, int>> result;

    for (int i = 0; i < this->n; i++)
    {
        int d = this->distanceFunction(this->data[i].second, query);
        if (d < R)
        {
            result.emplace_back(d, i);
        }
    }
    return result;
}

vector<pair<int, int>> Data::Get_Closest_Neighbors( vector<float> &query, vector<pair<int, vector<float>>> &data, int &N)
{
    vector<pair<int, int>> result;

    auto cmp = [](pair<int, int> left, pair<int, int> right)
    {
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

vector<pair<int, int>> Data::Brute_Force_Neighbors(vector<float> &query, int &N)
{
    vector<pair<int, int>> result;

    auto cmp = [](pair<int, int> left, pair<int, int> right)
    {
        return left.first > right.first;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);

    for (int i = 0; i < int(this->data.size()); i++)
    {
        q.push(make_pair(this->distanceFunction(this->data[i].second, query), i));
    }

    int min = (N < int(q.size())) ? N : q.size();

    for (int i = 0; i < min; i++)
    {
        result.push_back(q.top());
        q.pop();
    }

    return result;
}

vector<float> Data::compare(vector<vector<float>> data, vector<vector<float>> query)
{
    vector<vector<float>> result;
    vector<float> curr_max;
    int k = 0;
    float sum = 0;

    while (query[k][0] != NULL) // Loops through all the query time series
    {
        for (int i = 0; i < n; i++) // Loops through all the data time series
        {
            for (int j = 0; j < d; j++) // Loops through every point of a time series
            {
                sum += abs(query[k][j] - data[i][j]); // Sums up their difference
            }
            //**result.emplace_back(sum); // Stores it in result (k - No of query, i - No of data)
            sum = 0;
        }
        k++;
    }
}