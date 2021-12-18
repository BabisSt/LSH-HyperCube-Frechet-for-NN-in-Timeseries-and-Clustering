#pragma once

#include <vector>
#include <cmath>
#include <functional>
#include <tuple>
#include <list>

using namespace std;

class hashTable
{
    private:
        int d;
        uint32_t w,M;
        vector<float> t;
    public:
        vector<vector<double>> v;

        void calculate_v(vector<vector<double>> &v, float k, float d);
        void calculate_t(uint32_t w,float k);
        
        vector<vector<tuple<float, int, reference_wrapper<vector<float>>>>> table;

        hashTable(int indexSize, float k, float d, float w,float M);
        ~hashTable();
        
        uint32_t calculate_h(vector<float> &point,vector<double> &v,float k);

        uint32_t calculate_grid();

        void Insert_Item(uint32_t g, int index, vector<float> &point);

        vector<pair<int, reference_wrapper<vector<float>>>>Get_Items(const uint32_t &g);
};