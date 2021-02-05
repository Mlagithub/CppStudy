
# C++ Lambda 知识点总结

<br/>
C++11的一大亮点就是引入了Lambda表达式。利用Lambda表达式，可以方便的定义和创建匿名函数。对于C++这门语言来说来说，“Lambda表达式”或“匿名函数”这些概念听起来好像很深奥，但很多高级语言在很早以前就已经提供了Lambda表达式的功能，如C#，Python等。
<br/>

## 基本概念

C++11的一大亮点就是引入了Lambda表达式。利用Lambda表达式，可以方便的定义和创建匿名函数。对于C++这门语言来说来说，“Lambda表达式”或“匿名函数”这些概念听起来好像很深奥，但很多高级语言在很早以前就已经提供了Lambda表达式的功能，如C#，Python等。

### 通过 lambda 来理解 c++
```cpp
constexpr auto l = [](auto ... k) -> int {
    return (k + ...);
}
```
上式中涉及到的、可以使用的c++语法包括：
> classes  
objects 
member functions  
operator overloading  
const  
mutable  
constexpr  
noexcept  
rturn type deduction  
trailing return types  
templates  
auto   
template deduction rules  
optimizer  
variadic template  
fold expressions 
RVO  
NRVO  
IFFE IILE  
ODR used 
compile-time context  
constructablity  


### lambda 表达式的多种形式
```cpp
[t=title](){ decltype(title) ... use(t);}
[title](){ decltype(title) ... use(title);}
[&t=title]() {use(t);}
[&title]() {use(title);}
[=]() {use(title);}
[&]() {use(title);} // the most useful
```

### mutable 关键字
```cpp
[i=0]() {return ++i;} // this will compile error 
[i=0]() mutable {return ++i;}
```

### 引用容悬
> 函数 hasTitle 返回的 has_title_t 
被向上传递到上层栈后，
捕获 title 当前栈就会被销毁，title 被空悬。

* 向下（入栈）传递不会导致空悬。
* 向上（出栈）、多线程交叉传递可能导致空悬。

#### "by ref" 捕获
```cpp
auto has_little_t = [&t=title](const Book& b){
    return b.title() == t;
}
return has_title_t;

```
#### "by move" 捕获
```cpp
auto has_little_t = [t=std::move(title)](const Book& b){
    return b.title() == t;
}
return has_title_t;
```

### 引用捕获与拷贝捕获
kitten 的捕获发生在生调用时，此时 g=20，
cat 的捕获发生在声明时，此时 g=10。

```cpp
#include <stdio.h>

int g = 10;
auto kitten = [=](){return g+1;};
auto cat = [g=g](){return g+1;};

int main(){
    g = 20;
    printf("21 11\n", kitten(), cat());
}
```

### 转换为函数指针(if captureless)
```cpp
int (*fp)(int) = [](int x) {return x+1;};

template<class T> void fn(T t);
// calls fn<int(*)(int)>
fn(+[](int x){return x+1;}); 
```

### 默认构造(if captureless)
```cpp
auto lam=[](int x) {return x+1;};
// new in c++20
decltype(lam) copy; 
```

### 默认 constexpr, 但默认 no noexcept
```cpp
static_assert(lam(32)==33);
// new in c++17
static_assert(not noexcept(lam(32))); 
```


### 局部静态变量
局部静态变量的行为相比于类的静态变量来理解
```cpp
auto counter = [](){static int i; return ++i;};
auto c1 = counter;
auto c2 = counter;

std::cout << c1() << c1() << c1(); // 1 2 3
std::cout << c2() << c2() << c2(); // 4 5 6
```

### const 初始化 
```cpp 
const auto size = [&](){
    if(longlong_) return sizeof(int64_t)*8;
    else if(long_) return sizeof(long)*8;
    else return sizeof(int)*8;
}()
```

## 高阶使用

### return type deduction 
```cpp
auto s = [](){
    if(true) return 1;
    else return 2;
}();
```

```cpp
struct MyType{
    MyType() {std::cout << "MyType()\n";}
    MyType(const MyType&) {std::cout << "MyType(const MyType&)\n";}
    ~MyType() {std::cout << "~MyType()\n";}
    MyType(MyType &&) {std::cout << "MyType(MyType &&)\n";}
}
int main(){
    MyType o;
    const auto &v = [&](){
        return o;
    }();
}
```

### 捕获 this
```cpp
class Widget{
public:
    void work(int);
    // this == Widget
    void synchronous_foo(int x){
        this->work(x);
    }

    // this == Widget
    void asynchronous_foo(int x){
        fire_and_forget([=](){
            this->work(x);  
        })
    }
};
```

### 捕获变参
```cpp
auto plus = [value=1](auto ...x) {return sum(x..., value);};

// what's the T in std::forward<T>?
auto times = [](auto&& ... args){
    return product(std::forward<???>(args)...);
};
```

```cpp
// use decltype
auto one = [](auto&& ... args){
    return product(std::forward<decltype(args)>(args)...);
};

// c++20 
auto two = []<class ... Ts>(Ts&& ... args){
    return product(std::forward<Ts>(args)...);
};

```

### lambda 作为函数参数
#### STL's  way  
```cpp
class Shelf{
public:
    template<class Func>
    void for_each_book(Func f){
        for(const Book& b : books_) f(b);
    }
}

Shelf myshelf;
myshelf.for_each_book([](auto && book){book.print();});
```

#### "Type Erasure"'s way 
to capture lambda inside a library type that exposes just the call operator
```cpp
class Shelf{
public:
    // ConcreteCBType
    void for_each_book(ConcreteCBType f){
        for(const Book& b : books_) f(b);
    }
}

Shelf myshelf;
myshelf.for_each_book([](auto && book){book.print();});
```


### 拷贝与移动
Lambda 是否可以拷贝、是否可移动取决于它的捕获对象是否可拷贝、是否可移动。
```cpp
std::uniqure_ptr<int> prop;
auto lamb = [p = std::move(prop)](){};
auto lamb2 = std::move(lamb); // ok
auto lamb3 = lamb; //error: call to implicitly-deleted copy constructor
```

### 继承 lambda 
#### 执行一系列自定义操作
```cpp
template<typename TFirst, typename... TRemaining>
class FunctionSequence : public TFirst, FunctionSequence<TRemaining...>
{
    public:
    FunctionSequence(TFirst first, TRemaining... remaining)
        : TFirst(first), FunctionSequence<TRemaining...>(remaining...)
    {}

    template<typename... Args>
    decltype(auto) operator () (Args&&... args){
        return FunctionSequence<TRemaining...>::operator()
            (    TFirst::operator()(std::forward<Arg>(args)...)     );
    }
};

template<typename T>
class FunctionSequence<T> : public T
{
    public:
    FunctionSequence(T t) : T(t) {}

    using T::operator();
};


template<typename... T>
auto make_functionSequence(T... t){
    return FunctionSequence<T...>(t...);
}

int main(){

    //note: these lambda functions are bug ridden. Its just for simplicity here.
    //For correct version, see the one on coliru, read on.
    auto trimLeft = [](std::string& str) -> std::string& { str.erase(0, str.find_first_not_of(' ')); return str; };
    auto trimRight = [](std::string& str) -> std::string& { str.erase(str.find_last_not_of(' ')+1); return str; };
    auto capitalize = [](std::string& str) -> std::string& { for(auto& x : str) x = std::toupper(x); return str; };

    auto trimAndCapitalize = make_functionSequence(trimLeft, trimRight, capitalize);
    std::string str = " what a Hullabaloo     ";

    std::cout << "Before TrimAndCapitalize: str = \"" << str << "\"\n";
    trimAndCapitalize(str);
    std::cout << "After TrimAndCapitalize:  str = \"" << str << "\"\n";

    return 0;
}

```
> output  
Before TrimAndCapitalize: str = " what a Hullabaloo     "
After TrimAndCapitalize:  str = "WHAT A HULLABALOO"


#### 重载 operator() 并提供统一的调用接口
```cpp
#include <iostream>
#include <type_traits>

template<typename Lhs, typename Rhs>
struct S : Lhs, Rhs{
    S(Lhs lhs, Rhs rhs) : Lhs(lhs), Rhs(rhs) {}
    using Lhs::operator();
    using Rhs::operator();
};

template<typename Lhs, typename Rhs>
auto make_combined(Lhs &&lhs, Rhs &&rhs){
    return S<std::decay_t<Lhs>, std::decay_t<Rhs>>(std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

int main(){
    auto l1 = [](){return 3;};
    auto l2 = [](int i){return i*10;};
    auto combined = make_combined(l1, l2);
    std::cout << combined() << std::endl;
    std::cout << combined(3) << std::endl;
    return 0;
}
```


## Lambda vs Closure
闭包是编程的一个概念，来自于函数式编程，c++中的 Lambda 表达式就是一种闭包。
```cpp
auto f = [&](int x, int y) {return x+y;};
```
* c++ Lambda是一个表达式，该表达式被编译后生成一个闭包以在运行时工作
* lambda 与闭包类似于类与类的实现，前者只存在于代码中，不存在于运行时。
* 上式中的 f 并不是闭包，而是闭包的拷贝，闭包是一个临时量。如果要保存闭包，可以使用万能引用实现，如下图所示。

```cpp 
auto f&& = [&](int x, int y) {return x+y;};
```

 
## 什么情况下不要使用 Lambda  
* when constructing an object is passed to const &
* when it appedes readability and maintainability
* when code size increase dramatically 
* when performance suffers 