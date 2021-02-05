


#include "matrix.h"

#include <iostream>
#include <ctime>

using namespace std;


int main(void){


    Matrix<double, 1, 3> em;
    Matrix<double, 3, 1> fm;
    Matrix<double, 1, 3> gm;
    Matrix<double, 3, 1> km;

    float count = 1;
    for(auto it=em.begin(), jt=fm.begin(), kt=gm.begin(), pt=km.begin();
            it != em.end(); 
            ++it, ++jt, ++kt, ++pt){
        *it = count++;
        *jt = count++;
        *kt = count++;
        *pt = count++;
    }


    auto start = time(0);

    //cout << ar.eval(0,0) << '\n';

    //auto br = (2.0*am*4.0*cm) + (2.1*dm+am*3.4)*(4.5*cm+am*5.8)*12.3 + (2.8*bm+am*2.7)*(4.2*am+dm*5.1) ;

    auto ar = (2.0*em*4.0*~gm) + (2.1*em+gm*3.4)*(4.5*fm+km*5.8)*12.3 - (2.8*em+gm*2.7)*(4.2*fm-km*5.1) ;

    for(size_t i = 0; i<1000; ++i){
        em(0, 1) = double(i%40);
        gm(0, 0) = double(i%40);
        fm(1, 0) = double(i%40);
        km(1, 0) = double(i%40);
        cout << ar.eval(0,0) << '\n';
        //cout << i << '\t' << ar.eval(0,0) << '\n';
        //cout << br << '\n';
    }
    auto end = time(0);
    cout << "Elasped time : " << end - start << '\n';
    cin.get();

    return 0;
};
