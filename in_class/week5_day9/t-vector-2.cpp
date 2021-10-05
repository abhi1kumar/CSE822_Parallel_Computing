#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<thread>
using std::thread;
#include<cstdlib>

/*
void t_function(int id, vector<int>& results){
  results[id] = id * id;
}

int main (int argc, char *argv[]){
  if (argc != 2)
    cout << "Need thread count argument" << endl;
  else{
    int t_cnt = atoi(argv[1]);
    vector<thread> thrds;
    vector<int>results(t_cnt);
    for(int i=0; i<t_cnt; ++i){
      thrds.emplace_back(t_function, i, std::ref(results) );
      cout << "starting: "<<i<<endl;
    }
    int id=0;
    // has to be a reference for a thread
    for(auto &t : thrds){
      if(t.joinable() ){
	t.join();
	cout << "Joined: "<< id++ << endl;
      }
    }

    long total = 0;
    for(int i=0; i<t_cnt; ++i)
      total += results[i];
    cout << "Total: "<<total << endl;
  } // of else
}
*/
int main (int argc, char *argv[])
{
    if (argc != 2)
        cout << "Need thread count argument" << endl;
    else
    {
        int t_cnt = atoi(argv[1]);

    }
    return 0;
}
