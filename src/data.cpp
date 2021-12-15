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

int Data::Init_Data_curve(vector<vector<float>> &data) // erwthma 2
{

    for (float r = 0; r < data.size(); r++)
    {
        data_curve.push_back(vector<pair<float, float>>());
        for (float j = 0; j < data[r].size(); j++)
        {
            float temp_x = j * this->x;
            data_curve[r].push_back(make_pair(temp_x, data[r][j]));
            // cout << " " << data_curve[r][j].first << " " << data_curve[r][j].second << endl;
        }
    }
    //Init_Data_Grid_curve(data);
    return 0;
}

int Data::Init_Data_Grid_curve(vector<pair<string,vector<float>>> &data) // erwthma 3, kanei snap thn y
{
    srand((unsigned)time(NULL));

    for (float r = 0; r < data.size(); r++)
    {
        this->t.push_back(float(rand()) / float((RAND_MAX)) * this->delta);
        data_grid_curve.push_back(pair<string,vector<float>>());
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
        data.emplace_back(pair<string, vector<float>>());
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

int Data::Init_Query_curve(vector<vector<float>> &query) // erwthma 2
{

    for (float r = 0; r < query.size(); r++)
    {
        query_curve.push_back(vector<pair<float, float>>());
        for (float j = 0; j < query[r].size(); j++)
        {
            float temp_x = j * this->x;
            query_curve[r].push_back(make_pair(temp_x, query[r][j]));
        }
    }

    return 0;
}

int Data::Init_Query_Grid_curve(vector<pair<string,vector<float>>> &query) // erwthma 3, pairnw thn mia metablhth y kai thn kanw snap
{

    for (float r = 0; r < query.size(); r++)
    {
        query_grid_curve.push_back(pair<string,vector<float>>());
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

int Data::Filtering(vector<pair<string,vector<float>>> &curve)
{
    float epsilon = 0.1;

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

int Data::Padding(vector<pair<string,vector<float>>> &data, vector<pair<string,vector<float>>> &query)
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

double Data::EuclideanDistance(const vector<float> &p1, const vector<float> &p2)
{
    unsigned int d = 0;

    for (size_t i = 0; i < p1.size(); i++)
    {
        d += pow(p2[i] - p1[i], 2);
    }

    return sqrt(d);
}

// double Data::FrechetDistance(const vector<vector<pair<float,float>>> &curve_1, const vector<vector<pair<float,float>>> &curve_2)
// {

// }

// float Data::find_dist(vector<pair<float,float>> &p, vector<pair<float,float>> &q)
// {

//     find_dist(p[0].second-1,p[0].second-1)
// }

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

vector<pair<int, int>> Data::Get_Closest_Neighbors(const vector<float> &query, const vector<pair<int, vector<float>>> &data, const int &N)
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

    for (int i = 0; i < n; i++)
    {
        while (query[k][0] != NULL)
        {
            for (int j = 0; j < d; j++)
            {
                result[][] += abs(data[i][j] - query[k][j]);
            }
            k++;
        }
        k = 0;
    }
}