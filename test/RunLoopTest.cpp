//
// Created by Masahiko Tsujita on 2019-08-14.
//

#include <thread>
#include <catch2/catch.hpp>
#include "TestUtils.h"
#include <eventkit/dispatch/RunLoop.h>
#include <eventkit/dispatch/DispatchQueue.h>

using namespace std::chrono_literals;

SCENARIO("a run loop", "[run_loop]") {

    GIVEN("a run loop without any event sources") {
        auto pRunLoop = std::make_shared<ek::dispatch::RunLoop>();

        WHEN("the run loop starts running on a thread") {
            DECLARE_FLAG(RUNLOOP_END);
            std::thread thread([=]{
                pRunLoop->run();
                SET_FLAG(RUNLOOP_END);
            });
            thread.detach();

            THEN("the thread will terminate immediately") {
                REQUIRE_FLAG_SET(RUNLOOP_END, 5s);
            }
        }

        WHEN("a event source added to the run loop") {
            auto pDispatchQueue = ek::common::make_intrusive<ek::dispatch::DispatchQueue>();
            pRunLoop->addDispatchQueue(pDispatchQueue);

            WHEN("the run loop starts running on a thread") {
                DECLARE_FLAG(RUNLOOP_END);
                std::thread thread([=]{
                    pRunLoop->run();
                    SET_FLAG(RUNLOOP_END);
                });
                thread.detach();

                THEN("the thread will keep running") {
                    REQUIRE_NOT_FLAG_SET(RUNLOOP_END, 5s);
                }

//                WHEN("the event source is removed from the run loop") {
//                    pDispatchQueue->dispatchAsync([=]{
//                        pRunLoop->removeDispatchQueue(pDispatchQueue.get());
//                    });
//
//                    THEN("the thread will terminate immediately") {
//                        REQUIRE_RETURN_WITH_TIMEOUT(pThread->join(), 5s);
//                    }
//                }
            }
        }
    }

}
