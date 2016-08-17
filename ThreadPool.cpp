#include "stdafx.h"
#include "ThreadPool.h"


ThreadPool::ThreadPool(int n) : numThread(n)
{
	tgroup = boost::shared_ptr<boost::thread_group>(new boost::thread_group());
	tasks = boost::shared_ptr<WorkQueue>(new WorkQueue());

	for (int i = 0; i < n; ++i) {
		tgroup->create_thread(boost::bind(&ThreadPool::RunTask, this));
	}

}


ThreadPool::~ThreadPool() 
{
	tasks->Finish();
	WaitForCompletion();

	tgroup->join_all();
}

void ThreadPool::AddTask(const boost::shared_ptr<HeuristicTask>& task)
{
	tasks->AddTask(task);
}

void ThreadPool::RunTask()
{
	boost::shared_ptr<HeuristicTask> task;
	while ((task = tasks->getTask()) != NULL) {
		task->Run();
		task.reset();
	}
}

void ThreadPool::Finish()
{
	tasks->Finish();
}

void ThreadPool::WaitForCompletion()
{
	while (tasks->hasWork()) {}
	tgroup->join_all();
}
