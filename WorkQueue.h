#pragma once
#include <queue>
#include "boost\thread.hpp"
#include "HeuristicTask.h"


class WorkQueue
{
public:
	WorkQueue();
	~WorkQueue();

	void AddTask(const boost::shared_ptr<HeuristicTask>& hTask);
	boost::shared_ptr<HeuristicTask> getTask();
	void Finish();
	bool hasWork();


private:
	std::queue<boost::shared_ptr<HeuristicTask>> tasks;
	boost::mutex m_mutex;
	boost::condition_variable m_cond;

	bool finished = false;
};

