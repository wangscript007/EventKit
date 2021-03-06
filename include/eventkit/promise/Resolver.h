//
// Created by Masahiko Tsujita on 2019-08-14.
//

#ifndef EVENTKIT_RESOLVER_H
#define EVENTKIT_RESOLVER_H

#include <memory>
#include <eventkit/promise/Result.h>
#include <eventkit/common/IntrusivePtr.h>

namespace ek {
namespace promise {
namespace detail {

template <typename T, typename E>
class PromiseCore;

}
}
}

namespace ek {
namespace promise {

template <typename T, typename E>
class Fulfiller;

template <typename T, typename E>
class Rejecter;

template <typename T, typename E>
class Resolver final {
private:
    using Core = detail::PromiseCore<T, E>;

public:

    explicit Resolver(const ek::common::IntrusivePtr<Core>& pCore)
        : m_pCore(pCore) {
    }

    void fulfill(const T& value) const {
        m_pCore->onResult(Result<T, E>::succeeded(value));
    }

    void reject(const E& error) const {
        m_pCore->onResult(Result<T, E>::failed(error));
    }
    
    void operator () (const Result<T, E>& result) const {
        m_pCore->onResult(result);
    }

    explicit operator Fulfiller<T, E> () const {
        return Fulfiller<T, E>(m_pCore);
    }

    explicit operator Rejecter<T, E> () const {
        return Rejecter<T, E>(m_pCore);
    }

private:
    ek::common::IntrusivePtr<Core> m_pCore;

};

template <typename T, typename E>
class Fulfiller final {
private:
    using Core = detail::PromiseCore<T, E>;

public:

    explicit Fulfiller(const ek::common::IntrusivePtr<Core>& pCore)
        : m_pCore(pCore) {
    }

    void operator () (const T& value) const {
        m_pCore->onResult(Result<T, E>::succeeded(value));
    }

private:
    ek::common::IntrusivePtr<Core> m_pCore;

};

template <typename T, typename E>
class Rejecter final {
private:
    using Core = detail::PromiseCore<T, E>;

public:

    explicit Rejecter(const ek::common::IntrusivePtr<Core>& pCore)
        : m_pCore(pCore) {
    }

    void operator () (const E& error) const {
        m_pCore->onResult(Result<T, E>::failed(error));
    }

private:
    ek::common::IntrusivePtr<Core> m_pCore;

};

}
}

#endif //EVENTKIT_RESOLVER_H
