#ifndef GLIM_TASK_QUEUE_HPP
#define GLIM_TASK_QUEUE_HPP

#include <atomic>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace glim {

class TaskQueue {
   public:
    explicit TaskQueue(usize numberOfThreads) {
        for (usize i = 0; i < numberOfThreads; ++i) {
            threads.emplace_back([this] { loop(); });
        }
    }
    ~TaskQueue() {
        finished_ = true;
        for (auto& thread : threads) {
            thread.join();
        }
    }

    template <typename F>
    std::future<std::invoke_result_t<F>> enqueue(F&& f) {
        using Ret = std::invoke_result_t<F>;
        auto task = std::make_unique<Task<Ret, F>>(std::promise<Ret>{},
                                                   std::forward<F>(f));
        auto future = task->p.get_future();
        {
            std::lock_guard<std::mutex> l{tasksMutex};
            tasks.push(std::move(task));
        }
        return future;
    }

    bool finished() const {
        std::lock_guard<std::mutex> l{tasksMutex};
        return tasks.empty();
    }
    void cancel() { cancel_ = true; }

   private:
    std::vector<std::thread> threads;

    struct TaskBase {
        virtual ~TaskBase() = default;
        virtual void execute() = 0;
    };
    template <typename T, typename F>
    struct Task : TaskBase {
        explicit Task(std::promise<T> p, F f)
            : p{std::move(p)}, f{std::move(f)} {}
        std::promise<T> p;
        F f;
        void execute() override { p.set_value(std::invoke(f)); }
    };
    template <typename F>
    struct Task<void, F> : TaskBase {
        explicit Task(std::promise<void> p, F f)
            : p{std::move(p)}, f{std::move(f)} {}
        std::promise<void> p;
        F f;
        void execute() override {
            std::invoke(f);
            p.set_value();
        }
    };
    std::queue<std::unique_ptr<TaskBase>> tasks;
    mutable std::mutex tasksMutex;

    std::atomic_bool finished_{false}, cancel_{false};

    void loop() {
        while (true) {
            if (cancel_) {
                break;
            }
            if (finished_ && [&] {
                    std::lock_guard<std::mutex> l{tasksMutex};
                    return tasks.empty();
                }()) {
                break;
            }
            if (auto task = [&]() -> std::unique_ptr<TaskBase> {
                    std::unique_lock<std::mutex> l{tasksMutex};
                    if (!tasks.empty()) {
                        auto task = std::move(tasks.front());
                        tasks.pop();
                        l.unlock();
                        return task;
                    }
                    l.unlock();
                    return nullptr;
                }()) {
                task->execute();
            }
        }
    }
};

}  // namespace glim

#endif
