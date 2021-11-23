#include<iostream>
using std::cout;

#include<algorithm>

using std::fill_n;
using std::endl;

#include <math.h>
#include <fstream>

#include<mpi.h>

#include <vector>
using std::vector;

void saveTimestoCSV(vector<vector<double>> &ts) {
    std::ofstream out("case2.csv");

    for (auto& row : ts){
        for (auto col : row) {
            out << col << ",";
        }
    out << "\n";
    }
}

int main(int argc, char** argv){
    
    MPI_Init(&argc, &argv);
    int comm_sz, my_rank;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    
    // if(argc!=2){
    //     cout<<"Need an array size"<<endl;
    //     exit(1);
    // }
    int sz;
    double starttime, endtime;
    vector<vector<double>> time1 (100, vector<double> (24) ); 
    
    for (int i=0; i<100; ++i){
        if (my_rank == 0) {
            cout << i << endl;
            }
        for(int k=0;k<24;k++){
            sz=pow(2,k);
            int *send_ary=new int[sz];
            int *rec_ary=new int[sz];

            fill_n(send_ary,sz,3);
            fill_n(rec_ary,sz,0);
            
            starttime = MPI_Wtime();
            
            if (my_rank==0){
                MPI_Send(send_ary, sz, MPI_INT,comm_sz-1,0,MPI_COMM_WORLD);
                MPI_Recv(rec_ary, sz, MPI_INT,comm_sz-1,0,MPI_COMM_WORLD,&status);
            }
            
            else if (my_rank==comm_sz-1){
                MPI_Recv(rec_ary, sz, MPI_INT,0,0,MPI_COMM_WORLD,&status);
                MPI_Send(send_ary, sz, MPI_INT,0,0,MPI_COMM_WORLD);
                
            }
            
            endtime   = MPI_Wtime();
                    
            time1[i][k] = endtime-starttime;
            delete send_ary, rec_ary;

        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (my_rank == 0) {
        cout << "Saving to csv" << endl;
        saveTimestoCSV(time1);
    }

    MPI_Finalize();
    
}