#ifndef LANG_UTILS_H_INCLUDED
#define LANG_UTILS_H_INCLUDED

#include <type_traits>

template<typename T, class Enable = void>
struct enum_value_type {
    using type = T;
};

template<typename T>
struct enum_value_type<T, typename std::enable_if<std::is_enum<T>::value>::type> {
    using type = typename std::underlying_type<T>::type;
};

template <typename T>
constexpr typename std::underlying_type<T>::type to_underlying(T val) noexcept {
    return static_cast<typename std::underlying_type<T>::type>(val);
}

#endif // LANG_UTILS_H_INCLUDED


