#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>

#include "../include/hashTable.h"

using namespace std;

hashTable::hashTable(int indexSize, float k, float d, float w, float M) // thelei init oi metablites
    : d(d), w(w), M(M)
{
    this->table.resize(indexSize);
    this->calculate_v(this->v, k, d);
}

hashTable::~hashTable() {}

void hashTable::calculate_v(vector<vector<double>> &v, float k, float d)
{
    default_random_engine re(chrono::steady_clock::now().time_since_epoch().count());
    normal_distribution<double> distribution(0, 1);

    v.resize(k, vector<double>(d));

    for (float i = 0; i < k; i++)
    {
        for (float j = 0; j < d; j++)
        {

            this->v[i][j] = distribution(re);
        }
    }
}

void hashTable::calculate_t(uint32_t w, float k)
{
    srand((unsigned)time(NULL));

    for (float i = 0; i < k; i++)
    {
        this->t.push_back(((rand() % w) + 1));
    }
}

uint32_t hashTable::calculate_h(const vector<float> &point, const vector<double> &v, float k)
{
    float x = 0;
    uint32_t result = 0;

    for (float i = 0; i < point.size(); i++)
    {
        calculate_t(this->w, k);
        if (this->t[i] != 0)
        {
            x += point[i] * abs(v[i]);
            // x= 10000;
            result = floor(double(x + this->t[i]) / double(this->w));
        }
    }

    return result % this->M;
}

// uint32_t hashTable::calculate_grid()
// {

// }

void hashTable::Insert_Item(uint32_t g, int index, vector<float> &point)
{

    this->table[g % this->table.size()].emplace_back(g, index, ref(point));
}

vector<pair<int, reference_wrapper<vector<float>>>> hashTable::Get_Items(const uint32_t &g)
{
    vector<pair<int, reference_wrapper<vector<float>>>> result;

    for (auto &bucket : this->table[g % this->table.size()])
    {
        result.emplace_back(get<1>(bucket), get<2>(bucket));
    }

    return result;
}
