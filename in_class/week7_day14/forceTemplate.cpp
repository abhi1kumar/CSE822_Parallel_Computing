#include<iostream>
using std::cout; using std::endl; using std::cin; using std::fixed;
#include<iomanip>
using std::setprecision;

/*
  wfp 1/28/15
  force function template matching
*/

template <typename fn_type> 
fn_type my_function(fn_type first, fn_type second){
  fn_type result;
  result = first * second;
  return result;
}
    

int main () {
  cout << setprecision(4) << fixed;  
  int int_result;
  double dbl_result;

  int_result = my_function(20, 123);
  cout << "Int result:"<<int_result<<endl;
  dbl_result = my_function<double>(20,123);
  cout << "Double result:"<<dbl_result<<endl;
}
