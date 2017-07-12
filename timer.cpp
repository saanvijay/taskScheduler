#include "timer.h"

class Timer;

Timer::Timer() {  }

void Timer::start() {
	while(runThreads) {
		auto now = std::chrono::system_clock::now();
		for (auto &task : m_mapTaskList) {
			if(task.second.getTaskTime() <= now && task.second.getTaskState() == SCHEDULED) {
				task.second.run();
				task.second.setTaskState(RUNNING);
			}
		}
	}
}

void Timer::listAllTasks() {
	for (auto &task : m_mapTaskList) {
		std::chrono::system_clock::time_point now =  task.second.getTaskTime();
		std::time_t tsktime = std::chrono::system_clock::to_time_t(now);
		std::cout << "TaskName : "<< task.second.getTaskName() 
			<< " Scheduled at : "<< std::put_time(std::localtime(&tsktime), "%F %T") 
			<< " Status : " << task.second.getTaskState() << std::endl;
	}

}
void Timer::start(string taskName) {
	//		while(runThreads) {
	auto it = m_mapTaskList.find(taskName);
	if (it != m_mapTaskList.end()) {
		if((*it).second.getTaskState() == SCHEDULED) {	
			runMethod rMethod = (*it).second.getRunMethod();
			m_timerTask = (*it).second;
			std::chrono::system_clock::time_point tasktime=  (*it).second.getTaskTime();
			std::chrono::system_clock::time_point now =  std::chrono::system_clock::now();
			std::chrono::duration<double, std::milli> elapsed = tasktime - now;

			std::cout << "Statred " << (*it).second.getTaskName() << " ..."<<"\n";

			// handle concurrency here
			m_thread_list.push_back(std::thread([&,this]() { 
						m_mutex.lock();
						(*it).second.setTaskState(RUNNING); 
						std::this_thread::sleep_for(elapsed); 
						(*it).second.run();
						//(*rMethod)();
						(*it).second.setTaskState(FINISHED);
						m_mutex.unlock();
						}));
			m_thread_list.back().join();
		}
	}
	//	  }
}

void Timer::cancel(string taskName) {
	auto it = m_mapTaskList.find(taskName);
	if (it != m_mapTaskList.end()) {
		//if already running, ignore cancel request 
		if((*it).second.getTaskState() != RUNNING) {	
			m_mapTaskList.erase(it);
		}
	}
}

void Timer::addTask(timerTask task) {
	std::string name(task.getTaskName());
	m_mapTaskList.insert(std::pair<string, timerTask>(name, task));
}

Timer::~Timer() {
	//	for(auto &ths : m_thread_list) {
	//			ths.join();
	//	}

	runThreads = false;
}

