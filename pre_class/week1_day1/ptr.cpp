#include<iostream>
using std::cout; using std::endl;

int main (){
  long l = 123;
  long &r_l = l;
  long *p_l = &r_l;

  cout << p_l <<endl;                     // Line 1
  cout << *p_l <<endl;                    // Line 2
  r_l = 456;
  cout << l << endl;                      // Line 3
  cout << (p_l == &l ? "yes\n" : "no\n"); // Line 4
  *p_l = 123;
  cout << r_l << endl;                    // Line 5

}
