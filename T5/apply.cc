#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <map>
#include <initializer_list>

using namespace std;

template <typename T_Entry, typename T_Func>
auto apply(const T_Entry& collection, T_Func f) { // reference to collection is better because it doesn't copy it.

    using T_Return = decltype( f( *begin(collection ) ) ); // begin(collection) works for other iterables. collection.begin() works only for vectors.
    vector<T_Return> v;

    for (const auto& item : collection) { // Again, this way we don't make a copy of each element.
        T_Return transformed_item = f(item);
        v.push_back(transformed_item);
    }

    return v;
}

// Specific template to deal with initializer_list
template <typename T, typename T_Func> 
auto apply (initializer_list<T> list, T_Func f) {

    vector<T> entry_vector(list); // That is how a initializer_list is passed to build a similar vector.

    return ::apply(entry_vector, f); // This way, std::apply is ignored and my version of apply is used when an initializer_list is passed.

}

