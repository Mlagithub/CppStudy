
#include <vector>
#include <functional>

using std::vector;

using std::invoke;

template <typename Func>
auto Project(Func function) {
    return [function](auto const &inputs) {
        using value_type = decltype(inputs.front());
        using function_return_type = std::result_of_t<Func(value_type)>;
        auto results = std::vector<std::decay_t<function_return_type>>{};
        results.reserve(inputs.size());
        for (auto const &input : inputs) {
            results.push_back(invoke(function, input));
        }
        return results;
    };
};