#include "stdafx.h"
#include "WorkQueue.h"


WorkQueue::WorkQueue()
{
}


WorkQueue::~WorkQueue()
{
}

void WorkQueue::AddTask(const boost::shared_ptr<HeuristicTask>& hTask)
{
	if (!finished)
	{
		boost::unique_lock<boost::mutex> lock(m_mutex);

		tasks.push(hTask);
		m_cond.notify_one();
	}
}

boost::shared_ptr<HeuristicTask> WorkQueue::getTask()
{
	boost::unique_lock<boost::mutex> lock(m_mutex);
	while (tasks.size() == 0 && !finished) m_cond.wait(lock);

	if (!finished || hasWork())
	{
		boost::shared_ptr<HeuristicTask> task = tasks.front();
		tasks.pop();

		return task;
	}
	else
	{
		return NULL;
	}
}

void WorkQueue::Finish()
{
	boost::unique_lock<boost::mutex> lock(m_mutex);
	finished = true;
	m_cond.notify_all();

}

bool WorkQueue::hasWork()
{
	return (tasks.size()>0);
}
