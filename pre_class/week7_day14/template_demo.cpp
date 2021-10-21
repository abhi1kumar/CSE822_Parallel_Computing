#include<iostream>
using namespace std;

//==============================================================================
// Template
//==============================================================================
template <typename my_type>
my_type add (my_type& first, my_type& second)
{
    my_type result;
    result = first + second;
    return result;
}

//==============================================================================
// Main starts here
//==============================================================================
int main (){


    //==========================================================================
    // Adding two integers
    //==========================================================================
    int a, b, res_int;

    a = 1;
    b = 2;

    // Call function template on int
    res_int = add<int>(a, b);
    cout << "Output of adding two integers " << a << " + " << b << " = " << res_int << endl;
    if (static_cast<int>(res_int) == res_int) 
    {
        // int value
        cout << "Output is an integer" << endl;
    }
    else 
    {
        // non-integer value
        cout << "Output is a float" << endl;
    }  

    //==========================================================================
    // Adding two floats
    //==========================================================================
    float x, y, res_float;

    x = 1.3;
    y = 2.3;

    // Call function template on int
    res_float = add<float>(x, y);
    cout << "Output of adding two floats   " << x << " + " << y << " = " << res_float << endl;
    if (static_cast<int>(res_float) == res_float) 
    {
        // int value
        cout << "Output is an integer" << endl;
    }
    else 
    {
        // non-integer value
        cout << "Output is a float" << endl;
    }  

}
