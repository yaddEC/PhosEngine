#pragma once

#include <atomic>

namespace Threading
{
    class AtomicMutex
    {
    private: 
        std::atomic<bool> flag{ false };

    public:
        void lock()
        {
            while (flag.exchange(true, std::memory_order_relaxed));
            std::atomic_thread_fence(std::memory_order_acquire);
        }

        void unlock()
        {
            std::atomic_thread_fence(std::memory_order_release);
            flag.store(false, std::memory_order_relaxed);
        }
    };
}



