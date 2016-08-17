#pragma once
#include "WorkQueue.h"
#include "HeuristicTask.h"

class ThreadPool
{
public:
	ThreadPool(int n);
	~ThreadPool();

	void AddTask(const boost::shared_ptr<HeuristicTask>& task);
	void WaitForCompletion();
	void RunTask();
	void Finish();
	

private:
	int numThread;
	boost::shared_ptr<boost::thread_group> tgroup;
	boost::shared_ptr<WorkQueue> tasks;	

};

