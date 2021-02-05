

# `std::variant` 知识点总结


c++17 标准在 utility 下引入了 std::variant。类似于 `union`  
用来储存多种类型。比如：`std::variant<int, double> v;`   
可以用来储存 `int` 或者 `double` 类型的值。
<br/>
<br/>

## 基本使用
```cpp
std::variant<int, double, std::string> x, y;

// assign value
x = 1;
y = "1.0";

// output: 
// x - 0
// y - 2
std::cout << "x - " << x.index() << std::endl;
std::cout << "y - " << y.index() << std::endl;


// overwrite value
x = 2.0;

// output: 
// x - 1, here x change from 0 to 1 
// y - 2
std::cout << "x - " << x.index() << std::endl;
std::cout << "y - " << y.index() << std::endl;


// read value
// d = 2.0
// s = "1.0"
double d = std::get<double>(x);
std::string s = std::get<2>(y);


// get error type 
// now x is double, so get<int> 
// throw std::bad_variant_access 
try
{
	int i = std::get<int>(x);
}
catch (std::bad_variant_access e)
{
	std::cerr << e.what() << std::endl;
}


// use get_if
int *i = std::get_if<int>(&x);
if (i == nullptr) {
    std::cout << "wrong type" << std::endl;
} else {
    std::cout << "value is " << *i << std::endl;
}


    // use visit(func, variant) to process type of variant element. 
    // func is a template function process all type of variant

    // call with class member func
    std::visit(Func(), y);

    // call with lambda func
    // need c++14 generic lambda feature
    std::visit(
        [](const auto &v) {
            std::cout << "call from Lambda, value is " << v << '\n';
        },
        x);

    // different type need different process
    // class member func
    x = "string";
    std::visit(Func1(), x);
    x = 2.3;
    std::visit(Func1(), x);

    // different type need different process
    // lambda func
    std::visit([](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;
        if
            constexpr(std::is_same_v<T, int>) {
                std::cout << "int with value " << arg << '\n';
            }
        else if
            constexpr(std::is_same_v<T, double>) {
                std::cout << "double with value " << arg << '\n';
            }
        else if
            constexpr(std::is_same_v<T, std::string>) {
                std::cout << "std::string with value " << std::quoted(arg)
                          << '\n';
            }
        else {
            static_assert(always_false<T>::value, "non-exhaustive visitor!");
        }
    }, x);

    x = "now value is 234";
    std::visit([](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;
        if
            constexpr(std::is_same_v<T, int>) {
                std::cout << "int with value " << arg << '\n';
            }
        else if
            constexpr(std::is_same_v<T, double>) {
                std::cout << "double with value " << arg << '\n';
            }
        else if
            constexpr(std::is_same_v<T, std::string>) {
                std::cout << "std::string with value " << std::quoted(arg)
                          << '\n';
            }
        else {
            static_assert(always_false<T>::value, "non-exhaustive visitor!");
        }
    }, x);

```

<br/>
<br/>


## 多态

```cpp
// define base and derived classes
class Base {
public:
    void PrintName() const { std::cout << "calling Base!\n"; }
};

class Derived1 {
public:
    void PrintName() const { std::cout << "calling Derived1!\n"; }
};

class Derived2{
public:
    void PrintName() const { std::cout << "calling Derived2!\n"; }
};
class Derived3 {
public:
    void PrintName() const { std::cout << "calling Derived3!\n"; }
};

// define 3 variant contains different number of class.
// check the size of var1 var2 and var3
// result is : var1 = var2 = var3 = 2
std::variant<Base, Derived1> var1;
std::variant<Base, Derived1, Derived2> var2;
std::variant<Base, Derived1, Derived2, Derived3> var3;
std::cout << "size of variant<Base, Derived1> is " << sizeof(var1) << '\n';
std::cout << "size of variant<Base, Derived1, Derived2> is " << sizeof(var2) << '\n';
std::cout << "size of variant<Base, Derived1, Derived2, Derived3> is " << sizeof(var3) << '\n';

// polymorphism use variant and visit
struct CallPrintName{
    void operator()(const Base &b) { b.PrintName(); }
    void operator()(const Derived1 &d1) { d1.PrintName(); }
    void operator()(const Derived2 &d2) { d2.PrintName(); }
    void operator()(const Derived3 &d3) { d3.PrintName(); }
};

std::variant<Base, Derived1, Derived2, Derived3> var;

var = Base{};
std::visit(CallPrintName{}, var);

var = Derived1{};
std::visit(CallPrintName{}, var);
```

> 优点
> > 值语义，没有动态内存分配  
> > 没有 v-table，类之间可以没有关系。  
> > Duck typing : 调用接口可以不同，更加灵活。  
> > 选择类型时的时间复杂度是 O(1)  


> 缺点
> > 改变 variant（接口） 和 visit（实现） 的代价比较大。  
> > 可能会浪费内存， variant 的大小是其所有元素大小的最大值。  
> > 每一个接口，都需要一个 visit。  

<br/>
<br/>



## 应用场景
1. 同一个函数，可能返回不同类型的返回值
2. 多态。std::visit获取到std::variant实际存储的类型的时间复杂度为O(1)，性能不会随着std::varant中类型的增多而降低。
3. 目前来看其适用性并不如传统的虚函数表多态。


## 参考文章
1. [cppreference-utility-variant](https://en.cppreference.com/w/cpp/utility/variant)
2. [cppreference-iomainip-quoted](https://en.cppreference.com/w/cpp/io/manip/quoted)
3. [C++17 更通用的 union：variant](https://kheresy.wordpress.com/2017/10/16/cpp17-variant/)
4. [知乎: 使用std::variant](https://zhuanlan.zhihu.com/p/57530780)
5. [Everything You Need to Know About std::variant from C++17](https://www.bfilipek.com/2018/06/variant.html)
6. [用c++11打造好用的variant](https://www.cnblogs.com/qicosmos/p/3559424.html)
7. [Runtime Polymorphism with std::variant and std::visit](https://www.bfilipek.com/2020/04/variant-virtual-polymorphism.html)