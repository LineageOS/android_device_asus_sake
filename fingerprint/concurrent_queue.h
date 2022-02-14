/*
 * Copyright (C) 2022 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class concurrent_queue
{
  private:
    std::condition_variable c;
    mutable std::mutex m;
    std::queue<T> q;

  public:
    void push(T const& v) {
        std::unique_lock<std::mutex> lock(m);
        q.push(v);
        lock.unlock();
        c.notify_one();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return q.empty();
    }

    void pop(T& v) {
        std::unique_lock<std::mutex> lock(m);
        while (q.empty()) {
            c.wait(lock);
        }

        v = q.front();
        q.pop();
    }
};
