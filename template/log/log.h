
#include <iostream>

using namespace std;

//bool isLog = true;



#define LOG(msg) \
    if(isLog) { \
        cout << __FILE__ << "(" << __LINE__ << ")" << msg << endl; }



