// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------


#include "Threading/Thread.hpp"
#include "Threading/PoolSystem.hpp"
#include <iostream>

namespace Threading
{
	Thread::Thread(Pool& pPool, const std::string& pName)
	{
		name = pName + " - Thread";

		thread = std::thread([&]()
		{
			while (!pPool.shouldStopPool())
			{
				pPool.queryMtx.lock();

				while (pPool.tasks.empty())
				{
					if (pPool.shouldStopPool())
					{
						pPool.queryMtx.unlock();
						return;
					}
				}

				ResourceTask rt = pPool.queryResourceTask(name);
				pPool.queryMtx.unlock();

				try
				{
					rt.task(rt.arg);
				}
				catch (const std::exception&)
				{
					continue;
				}

			}
		});
	}


	Thread::~Thread()
	{
		thread.join();
	}
}
