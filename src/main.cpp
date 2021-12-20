#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <math.h>

#include "../include/input.h"
// #include "../include/data.h"
// #include "../include/LSH.h"
// #include "../include/hyperCube.h"
#include "../include/kmeansplusplus.h"



using namespace std;

int main(int argc, char *argv[])
{
    int flag = true;

    Input input;

    srand(time(NULL));
    char* str = strdup("discrete");


    if (input.Parse_Input_Options(argc, argv) == -1) // pairnoume to input pou mas dinei o xrhsths
    {
        cerr << "input::ParseCmdOptions() failed" << endl;
    }

    while (flag)
    {
        string file;
        Data data;

        while (!input.inputFile.is_open())
        {
            cout << "Please provide a path to an input file" << endl; // dinoume path gia to dataset
            cin >> file;
            input.Open_Input_File(file); // anoigei to arxeio
        }

        if (data.Init_DataSet(input.inputFile) == -1) // diabazei ta dedomena tou arxeio kai ta ftiaxnei
        {
            cerr << "Data::InitDataset() failed" << endl;
            return -1;
        }

        if (input.mode == _cluster) // me cluster
        {
            kmeansplusplus *kmeans;
            if (!strcmp(input.method, "Classic") || !strcmp(input.method, "Classic_Fr")) // Classic periptwsh gia kmeans++ (Lloyd's)
            {
                if (strcmp(input.method, "Classic"))
                    kmeans = new kmeansplusplus(input.nClusters, input.complete, data, 0);
                else if (strcmp(input.method, "Classic_Fr"))
                    kmeans = new kmeansplusplus(input.nClusters, input.complete, data, 0);
            }
            else if (!strcmp(input.method, "LSH") || !strcmp(input.method, "LSH_Fr")) // gia LSH
            {
                if (strcmp(input.method, "LSH"))
                    kmeans = new kmeansplusplus(input.nClusters, input.complete, input.lsh_k, input.L, data, 0);
                else if (strcmp(input.method, "LSH_Fr"))
                    kmeans = new kmeansplusplus(input.nClusters, input.complete, input.lsh_k, input.L, data, 1);
            }
            else if (!strcmp(input.method, "Hypercube")) // gia hypercube
            {
                kmeans = new kmeansplusplus(input.nClusters, input.complete, input.cube_k, input.M, input.probes, data);
            }
            else
            {
                cout << "Method: " << input.method << " not recognized " << endl;
                return -1;
            }

            kmeans->Run(input.outputFile);

            delete kmeans;
        }
        else // xwris cluster gia queries
        {
            while (!input.queryFile.is_open()) // pairnoume to arxeio queries
            {
                cout << "Please provide a path to a query file" << endl;
                cin >> file;
                input.Open_Query_File(file);
            }

            if (data.ReadQueryFile(input.queryFile) == -1) // to diabazoume
            {
                cerr << "Data::ReadQueryFile() failed" << endl;
                return -1;
            }

            if (input.mode == _lsh) // an einai lsh
            {
                LSH *lsh = new LSH(input.lsh_k, input.L, data, 10000,input.R,input.delta,"lsh");
                if(lsh->Run(data.queries, input.outputFile, input.N) == -1)
                {
                    cerr << "LSH::Run() failed" << endl;
                }
                delete lsh;
            }
            else if (input.mode == _frechet)        // an einai frechet
            {
                if(strcmp(input.metric,str) == 0)     //erwthma 2
                {
                   
                    data.Init_Data_Grid_curve(data.data);           //init
                    data.Init_Query_Grid_curve(data.queries);
                    

                    data.Min_max_filter(data.data_curve);       //for duplicates
                    data.Min_max_filter(data.query_curve);


                    data.Padding(data.data_curve, data.query_curve);    //padding
                    LSH *lsh = new LSH(input.lsh_k, input.L, data, 10000,input.R,input.delta,"frechet"); //discrete
                    
                    if(lsh->Run(data.queries, input.outputFile, input.N) == -1)
                    {
                        cerr << "LSH::Run() failed" << endl;
                    }
                    delete lsh;
                }
                else                    //erwthma 3
                {
                    
                    data.Filtering(data.data,0.1);      //filttering
                    data.Filtering(data.queries,0.1);

                    data.Init_Data_Grid_curve(data.data);       //init
                    data.Init_Query_Grid_curve(data.queries);

                    data.Padding(data.data_grid_curve, data.query_grid_curve);  //padding
                
                    LSH *lsh = new LSH(input.lsh_k, input.L, data, 10000,input.R,input.delta);  //continuous

                    if(lsh->Run(data.queries, input.outputFile, input.N) == -1)
                    {
                        cerr << "LSH::Run() failed" << endl;
                    }
                    delete lsh;
                }
            }
            else                                            //an einai hypercube
            {
                
                HyperCube *hc = new HyperCube(floor(log2(data.n)), input.M, input.probes, data);

                if(hc->Run(data.queries, input.outputFile, input.N) ==  -1)
                {
                    cerr << "HyperCube::hyperCubeRun() failed" << endl;
                }

                delete hc;
            }
        }

        free(input.metric);
        free(str);
        string str;
        while (1) // epanalambanei gia diaforetikes ekteleseis tou xrhsth
        {
            cout << "Would you like to run again with different input? [Y, N]" << endl;
            cin >> str;

            if (!str.compare("Y") || !str.compare("y"))
            {
                input.inputFile.close();
                input.queryFile.close();
                break;
            }
            else if (!str.compare("N") || !str.compare("n"))
            {
                flag = false;
                break;
            }
        }
    }
    
    return 0;
}