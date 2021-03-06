#include<iostream>
using std::cout; using std::endl;

int main (){
    /*
    type &ptr --> Declaration of reference
    type *ptr --> Declaration of pointer

    &ptr (other places) --> Address
    *ptr (other places) --> Dereference
    */

    long l = 123;
    long &r_l = l;
    long *p_l = &r_l;
    /*
    -------------------------------------    
    Name  |    Type   |  Address | Value
    -------------------------------------
    l     |    long   |  0x100   |  123
    r_l   |    long&  |  0x100   |  123
    p_l   |    long*  |  0x104   |  0x100 
    */
    
    cout << p_l <<endl;                     // 0x100
    cout << *p_l <<endl;                    // 123
    
    r_l = 456;
    /*
    -------------------------------------    
    Name  |    Type   |  Address | Value
    -------------------------------------
    l     |    long   |  0x100   |  456
    r_l   |    long&  |  0x100   |  456
    p_l   |    long*  |  0x104   |  0x100 
    */
    cout << l << endl;                      // 456
    cout << (p_l == &l ? "yes\n" : "no\n"); // yes
    
    *p_l = 123;
    /*
    -------------------------------------    
    Name  |    Type   |  Address | Value
    -------------------------------------
    l     |    long   |  0x100   |  123
    r_l   |    long&  |  0x100   |  123
    p_l   |    long*  |  0x104   |  0x100 
    */
    cout << r_l << endl;                    // 123

}
