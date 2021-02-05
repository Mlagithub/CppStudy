
#include "log.h"
#include <string>

using namespace std;


void foo(){
    string file = "blah.txt";
    int err = 124;

    bool isLog = true;

    LOG("Read failed: " << file << " (" << err << ") ");

}


int main(void){

    foo();

    return 0;
}
