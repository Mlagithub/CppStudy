
#include <string>
#include <iostream>
#include <type_traits>

template<typename TFirst, typename... TRemaining>
class FunctionSequence : public TFirst, FunctionSequence<TRemaining...>{
public:
    FunctionSequence(TFirst first, TRemaining... remaining)
        : TFirst(first), FunctionSequence<TRemaining...>(remaining...)
    {}

    // template<typename... Args>
    // decltype(auto) operator () (Args&&... args){
    //     return FunctionSequence<TRemaining...>::operator()
    //         (TFirst::operator()(std::forward<Args>(args)...));
    // }
    template<typename... Args>
    auto operator () (Args&&... args) -> decltype(FunctionSequence<TRemaining...>::operator()
            (TFirst::operator()(std::forward<Args>(args)...)))
    {
        return FunctionSequence<TRemaining...>::operator()
            (TFirst::operator()(std::forward<Args>(args)...));
    }
};

template<typename T>
class FunctionSequence<T> : public T{
    public:
    FunctionSequence(T t) : T(t) {}
    using T::operator();
};

template<typename... T>
auto make_functionSequence(T... t) ->decltype(FunctionSequence<T...>(t...)) {
    return FunctionSequence<T...>(t...);
}


int main(){
    //note: these lambda functions are bug ridden. Its just for simplicity here.
    //For correct version, see the one on coliru, read on.
    auto trimLeft = [](std::string& str) -> std::string& { 
            str.erase(0, str.find_first_not_of(' ')); 
            return str; 
    };
    auto trimRight = [](std::string& str) -> std::string& { 
        str.erase(str.find_last_not_of(' ')+1); 
        return str; 
    };
    auto capitalize = [](std::string& str) -> std::string& { 
        for(auto& x : str) x = std::toupper(x); 
        return str; }
    ;

    auto trimAndCapitalize = make_functionSequence(trimLeft, trimRight, capitalize);
    std::string str = " what a Hullabaloo     ";

    std::cout << "Before TrimAndCapitalize: str = \"" << str << "\"\n";
    trimAndCapitalize(str);
    std::cout << "After TrimAndCapitalize:  str = \"" << str << "\"\n";

    return 0;
}