


#include <iostream>
#include <string>

using namespace std;


template<typename T>
class ACCT;



template<>
class ACCT<int>
{
    public:
        typedef int AccT;
        static AccT zero(void){
            return 0;
        };
        static AccT init(void){
            return 1;
        };
};


template<>
class ACCT<char>
{
    public:
        typedef int AccT;
        static AccT zero(void){
            return 0;
        };
};


template<typename T>
inline
typename ACCT<T>::AccT accumulate(T* beg, T* end)
{
    //typedef typename ACCT<T>::AccT AccT;
    typename ACCT<T>::AccT sum = ACCT<T>::zero();

    while(beg != end)
    {
        sum += *beg;
        ++beg;
    }
    return sum;
};


template<typename T1, typename T2>
class SumPolicy
{
    public:
        static void accumulate(T1& total, T2 const& value){
            total += value;
        };
};

template<typename T1, typename T2>
class MultPolicy
{
    public:
        static void accumulate(T1& total, T2 const& value){
            total *= value;
        }
};

template<typename T, 
    template<typename , typename > class Policy = SumPolicy>
class Accum
{
    public:
        typedef typename ACCT<T>::AccT AccT;
        static AccT accum(T const* beg, T const* end, T const& init = 0)
        {
            AccT sum = init;
            while(beg != end)
            {
                Policy<AccT, T>::accumulate(sum, *beg);
                ++beg;
            }
            return sum;
        }

};




int main(void)
{


    int num[] = {1, 4, 5, 5};
    //cout << " Avage of num is : " << accumulate(&num[0], &num[4])/4 << '\n';
    cout << " Avage of num is : " << Accum<int>::accum(&num[0], &num[4])/4 << '\n';
    cout << " Avage of num is : " << Accum<int, MultPolicy>::accum(&num[0], &num[4], 1)/4 << '\n';


    char name[] = "templates";
    size_t len = sizeof(name)-1;
    cout << " Avage of name is : " << accumulate(&name[0], &name[len])/len << '\n';


    return 0;
}
