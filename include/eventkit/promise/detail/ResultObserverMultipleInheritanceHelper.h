//
// Created by Masahiko Tsujita on 2019-08-25.
//

#ifndef EVENTKIT_RESULTOBSERVERMULTIPLEINHERITANCEHELPER_H
#define EVENTKIT_RESULTOBSERVERMULTIPLEINHERITANCEHELPER_H

#include <eventkit/promise/ResultObserver.h>

namespace ek {
namespace promise {
namespace detail {

struct result_observer_multiple_inheritance_helper_tag_t { explicit result_observer_multiple_inheritance_helper_tag_t() = default; };

constexpr result_observer_multiple_inheritance_helper_tag_t
    result_observer_multiple_inheritance_helper_tag = result_observer_multiple_inheritance_helper_tag_t();

/**
 * @class       ResultObserverMultipleInheritanceHelper
 * @brief       A helper class to inherit multiple `ResultObserver`s without conflict.
 */
template <typename T, typename E>
class ResultObserverMultipleInheritanceHelper : public ResultObserver<T, E> {
public:
    virtual ~ResultObserverMultipleInheritanceHelper() override = default;
    
    virtual void onResult(const Result<T, E>& result) override final {
        onResult(result_observer_multiple_inheritance_helper_tag, result);
    }
    
    virtual void ref() const override {
        ref(result_observer_multiple_inheritance_helper_tag);
    }
    
    virtual void unref() const override {
        unref(result_observer_multiple_inheritance_helper_tag);
    }
    
    virtual void onResult(result_observer_multiple_inheritance_helper_tag_t, const Result<T, E>& result) = 0;
    
    virtual void ref(result_observer_multiple_inheritance_helper_tag_t) const = 0;
    
    virtual void unref(result_observer_multiple_inheritance_helper_tag_t) const = 0;
    
};

}
}
}

#endif //EVENTKIT_RESULTOBSERVERMULTIPLEINHERITANCEHELPER_H
