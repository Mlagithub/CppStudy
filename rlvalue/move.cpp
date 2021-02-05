
#include <iostream>

using namespace std;

class Person
{
    public:
        Person(){
            cout << " default \n";
        }
        Person & operator=(const Person& val){
            id = val.id;
            cout << " = \n";
        }
        Person(const Person& val){
            id = val.id;
            cout << " Cref \n";
        }
        ~Person() {
            cout << " de con \n";
        }
        //Person(const Person& val) {
        //    id = val.id;
        //    cout << " 复制构造 \n";
        //}
        //Person& operator = (const Person& val){
        //    cout << " 赋值运算 \n";
        //}
        //Person(Person&& val){
        //    id = val.id;
        //    cout << " 移动构造 \n";
        //}
        //Person& operator = (Person&& val){
        //    id = val.id;
        //    cout << " 移动赋值 \n";
        //}
    public:
        int id = 0;

};


Person v1(Person val){

    Person tmp = val;

    return tmp;
}

Person v2(Person val){

    return val;
}

Person v3(Person&& val){

    return val;
}

Person v4(Person& val){

    return val;
}

Person& v5(Person& val){
    return val;
}

int main(void)
{

    cout << "\n -------------------- p1 : -----------------------\n";
    Person p1;
    p1.id = 1;

    cout << "\n -------------------- p2 : -----------------------\n";
    Person p2 = p1;
    p2.id = 2;

    cout << "\n -------------------- p3 : -----------------------\n";
    Person p3 = v2(p1);
    p3.id = 3;

    cout << "\n -------------------- p4 : -----------------------\n";
    //Person p4 = v3(std::move(p1));
    //Person p4 = v4(p1);
    Person p4 = v5(p1);
    //Person p4 = v2(std::move(p1));
    //Person p4 = v2(p1);
    
    cout << "\n -------------------- p5 : -----------------------\n";
    Person p5 = std::move(p4);


    return 0;
}
