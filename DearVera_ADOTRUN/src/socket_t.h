#ifndef SOCKET_T_H_INCLUDED
#define SOCKET_T_H_INCLUDED

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "lang_utils.h"
#include "errno_except.h"

#ifndef SOCK_NONBLOCK
#include <fcntl.h>
#define SOCK_NONBLOCK O_NONBLOCK
#define SOCK_CLOEXEC FD_CLOEXEC
#define MSG_NOSIGNAL 0
#endif

enum class socket_domain_t : enum_value_type<decltype(AF_UNSPEC)>::type {
    unspec = AF_UNSPEC,
    unix = AF_UNIX,
    inet = AF_INET,
    inet6 = AF_INET6
};

enum class socket_type_t : enum_value_type<decltype(SOCK_STREAM)>::type {
    stream = SOCK_STREAM,
    dgram = SOCK_DGRAM
};

enum class socket_type_flags_t : enum_value_type<decltype(SOCK_NONBLOCK)>::type {
    none = 0,
    nonblock = SOCK_NONBLOCK,
    cloexec = SOCK_CLOEXEC
};

class socket_t {
public:
    constexpr socket_t() : m_socket{-1} {}
    inline socket_t(socket_t&& other) noexcept : m_socket{other.m_socket} {
        other.m_socket = -1;
    }
    inline socket_t& operator=(socket_t&& other) noexcept {
        m_socket = other.m_socket;
        other.m_socket = -1;
        return *this;
    }

    inline socket_t(socket_domain_t domain, socket_type_t type, socket_type_flags_t flags = socket_type_flags_t::none, int protocol = 0);
    inline ~socket_t();

    inline int get() const noexcept {
        return m_socket;
    }

    inline void close();

    inline void bind(const sockaddr* addr, socklen_t addrlen);

    inline void listen(int backlog);

    inline socket_t accept(sockaddr* addr, socklen_t* addrlen);

private:
    constexpr explicit socket_t(int sock) : m_socket{sock} {}

    int m_socket = -1;
};

socket_t::socket_t(socket_domain_t domain, socket_type_t type, socket_type_flags_t flags, int protocol) :
    m_socket{call_system(::socket, to_underlying(domain), to_underlying(type) | to_underlying(flags), protocol)} {}

socket_t::~socket_t() {
    close();
}

void socket_t::bind(const sockaddr* addr, socklen_t addrlen) {
    call_system(::bind, m_socket, addr, addrlen);
}

void socket_t::listen(int backlog) {
    call_system(::listen, m_socket, backlog);
}

socket_t socket_t::accept(sockaddr* addr, socklen_t* addrlen) {
    return socket_t(call_system(::accept, m_socket, addr, addrlen));
}

void socket_t::close() {

    if (m_socket == -1) return;

    try {
        call_system(::shutdown, m_socket, SHUT_WR);
    } catch (...) {
    }

    timeval timeout {};
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    try {
        call_system(::setsockopt, m_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    } catch (...) {
    }

    char buf[8 * 1024];
    for(;;) if (::recv(m_socket, buf, sizeof(buf), MSG_NOSIGNAL) < 1) break;

    try {
        call_system(::close, m_socket);
    } catch (...) {
    }

    m_socket = -1;
}

#endif // SOCKET_T_H_INCLUDED


