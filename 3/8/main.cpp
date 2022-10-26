#include <iostream>
#include "miptstring.h"
#include "miptstringview.h"

using std::cout, std::endl;

int main() {
    mipt::String x = "ABCD";
    mipt::String y = "ABCE";
    mipt::StringView x_v = x;
    mipt::StringView y_v = y;
    
    cout << (x < y) << endl;
    cout << (x_v < y_v) << endl;
    
    cout << x_v.substr(1,10) << endl; 
    x_v.remove_suffix(2);
    cout << x_v << endl;
    
    mipt::String test = x_v;
    cout << "string from stringview: " << test << endl;
    cout << x_v.at(8);
    cout << x_v.at(1);
    
    return 0;
}
