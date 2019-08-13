//
// Created by Masahiko Tsujita on 2019-08-12.
//

#ifndef EVENTKIT_DISPATCHQUEUE_H
#define EVENTKIT_DISPATCHQUEUE_H

#include <mutex>
#include <list>
#include <queue>
#include <RunLoop.h>

namespace ek {

class DispatchItem {
public:
    virtual ~DispatchItem() = default;

    virtual void run() = 0;

};

template <typename Function>
class DispatchFunctionItem : public DispatchItem {
public:

    template <typename F>
    explicit DispatchFunctionItem(F&& function);

    ~DispatchFunctionItem() override = default;

    void run() override;

private:
    Function m_function;

};

class DispatchQueue {
public:

    friend class RunLoop;

    template <typename F>
    void dispatchAsync(F&& function);

private:

    void dispatchItemAsync(const std::shared_ptr<DispatchItem>& pTask);

    void fire();

    void setRunLoop(RunLoop* pRunLoop);

private:
    std::mutex m_mutex;
    std::queue<std::shared_ptr<DispatchItem>, std::list<std::shared_ptr<DispatchItem>>> m_queue;
    RunLoop* m_pRunLoop;

};

}

#include <detail/DispatchQueue-inl.h>

#endif //EVENTKIT_DISPATCHQUEUE_H
