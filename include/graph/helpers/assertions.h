//
// Created by zeyad-osama on 13/01/2020.
//

#ifndef LIB_GRAPH_DAG_ASSERTIONS_H
#define LIB_GRAPH_DAG_ASSERTIONS_H

#include <iostream>
#include <type_traits>

/**
 * Based on this proposal:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3911.pdf
 */
namespace detail {
    template<class... TN>
    struct void_t {
        typedef void type;
    };
}
template<class... TN>
struct void_t {
    typedef typename detail::void_t<TN...>::type type;
};

/**
 * @brief Extensible whitelist for std::hash<>
 */
template<class T, typename = void>
struct filtered_hash;
template<class T>
struct filtered_hash<T,
        typename std::enable_if<std::is_enum<T>::value>::type>
        : std::hash<T> {
};

template<class T>
struct filtered_hash<T,
        typename std::enable_if<std::is_integral<T>::value>::type>
        : std::hash<T> {
};

template<class T>
struct filtered_hash<T,
        typename std::enable_if<std::is_pointer<T>::value>::type>
        : std::hash<T> {
};

template<typename, typename = void>
struct is_hashable
        : std::false_type {
};

template<typename T>
struct is_hashable<T,
        typename void_t<
                typename filtered_hash<T>::result_type,
                typename filtered_hash<T>::argument_type,
                typename std::result_of<filtered_hash<T>(T)>::type>::type>
        : std::true_type {
};

#define TEMPLATE_T_ASSERT(T) static_assert(std::is_base_of<std::string, T>::value || \
                                    std::is_pod<T>::value ||                         \
                                    is_hashable<T>::value,                           \
                                    "T type ia not compatible")


#define TEMPLATE_T_K_SAME_ASSERT(T, K) static_assert(std::is_same<T, K>::value,            \
                                    "Using AddNode(T aName) with no K aData as parameter " \
                                    "requires that T and K have same base class")

#endif //LIB_GRAPH_DAG_ASSERTIONS_H
