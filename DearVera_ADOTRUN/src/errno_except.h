#ifndef ERRNO_EXCEPT_H_INCLUDED
#define ERRNO_EXCEPT_H_INCLUDED

#include <cerrno>
#include <system_error>
#include <type_traits>

inline void check_errno() {
    const auto e = errno;
    if (e) {
        errno = 0;
        throw std::system_error(e, std::system_category());
    }
}

template <typename Function, typename ... Args>
inline auto call_system(Function function, Args ... args) -> typename std::result_of<Function(Args ...)>::type {
    const auto ret = function(args ...);
    check_errno();
    return ret;
}

#endif // ERRNO_EXCEPT_H_INCLUDED


