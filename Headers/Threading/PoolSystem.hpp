#pragma once


#include <vector>
#include <iostream>
#include "Thread.hpp"
#include <queue>
#include <condition_variable>
#include "Resource/IResource.hpp"
#include "Threading/AtomicMutex.hpp"

namespace Threading 
{

	struct ResourceTask
	{
		std::function<void(void*)> task;
		void* arg;
	};

	class Pool
	{
	public:
		Pool() {};
		~Pool();

		std::queue<ResourceTask> GetTasks(){
			return tasks;
		}

		std::vector<Thread*> getPool() {
			return pool;
		}

		void registerThread(Thread* t) {
			pool.push_back(t);
		}

		void unregisterThread(Thread& t);

		void stopPool() {
			shouldThreadsStops = true;
		}

		void startPool() {
			shouldThreadsStops = false;
		}

		bool shouldStopPool() {
			return shouldThreadsStops;
		}

		void registerTask(ResourceTask task);

		ResourceTask queryResourceTask(std::string pName);

		bool isRegistering = true;
		AtomicMutex queryMtx;
		std::queue<ResourceTask> tasks;
	private:
		AtomicMutex taskMtx;

		std::atomic_bool shouldThreadsStops{ false };
		std::vector<Thread*> pool;

		std::condition_variable tasks_cond;
	};
}


