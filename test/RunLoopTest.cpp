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
            auto pThread = std::make_shared<std::thread>([&]{
                pRunLoop->run();
            });

            THEN("the thread will terminate immediately") {
                REQUIRE_RETURN_WITH_TIMEOUT(pThread->join(), 5s);
            }
        }

        WHEN("a event source added to the run loop") {
            auto pDispatchQueue = std::make_shared<ek::dispatch::DispatchQueue>();
            pRunLoop->addDispatchQueue(pDispatchQueue);

            WHEN("the run loop starts running on a thread") {
                auto pThread = std::make_shared<std::thread>([&]{
                    pRunLoop->run();
                });

                THEN("the thread will keep running") {
                    REQUIRE_NOT_RETURN_WITH_TIMEOUT(pThread->join(), 5s);
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
