#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;

#include<cstdlib>

#include<thread>
using std::thread;

#include<future>
using std::future; using std::async;

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

int t_function(int id)
{
    return id * id;
}


int main (int argc, char *argv[])
{
    if (argc != 2)
        cout << "Need thread count argument" << endl;
    else
    {
        int t_cnt = atoi(argv[1]);

        vector<future<int> > f;
        
        for(int id=0; id< t_cnt; ++id)
        {
            f.push_back(async(std::launch::async, t_function, id));
            cout << "Started= "<< id << endl;
        }

        long res = 0;    
        int id = 0;
        for(auto &fut : f)
        {
            res += fut.get();    
        	cout << "Joined = "<< id++ << endl;
        }
        cout << "Result = "<< res << endl;

    }

    return 0;
}
