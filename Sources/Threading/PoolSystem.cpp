// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Threading/PoolSystem.hpp"

namespace Threading
{

	Pool::~Pool()
	{
		for (auto t : pool)
			delete t;
	}

	void Pool::unregisterThread(Thread& t)
	{
		for (int i = 0; i < pool.size(); i++) 
		{
			if (t.getName() == pool.at(i)->getName())
			{
				pool.erase(pool.begin() + i);
				break;
			}
		}
	}

	void Pool::registerTask(ResourceTask task)
	{
		if (task.task == nullptr)
		{
			return;
		}

		taskMtx.lock();
		tasks.push(task);
		//std::cout << tasks.size() << std::endl;
		taskMtx.unlock();

		tasks_cond.notify_one();
	}

	ResourceTask Pool::queryResourceTask(std::string pName)
	{
		ResourceTask task = tasks.front();
		tasks.pop();
		return task;
	}
}
