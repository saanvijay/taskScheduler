#pragma once
#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>
#include <ctime>
#include <string>
#include <thread>
#include <queue>
#include <utility>
#include <map>
#include <future>
#include <mutex>
using namespace std;

class timerTask;

struct compareSchedule{
    bool operator () (timerTask& task1, timerTask& task2) {
        return task1.getTaskTime() < task2.getTaskTime();
    }
};

class Timer {
	timerTask m_timerTask;
	vector<std::thread> m_thread_list;
	mutex m_mutex;
	std::map<std::string, timerTask> m_mapTaskList;
	bool runThreads = true;
public:
	Timer() {  }
	void start() {
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

	void listAllTasks() {
			for (auto &task : m_mapTaskList) {
				std::chrono::system_clock::time_point now =  task.second.getTaskTime();
				std::time_t tsktime = std::chrono::system_clock::to_time_t(now);
				std::cout << "TaskName : "<< task.second.getTaskName() 
					  << " Scheduled at : "<< std::put_time(std::localtime(&tsktime), "%F %T") 
					  << " Status : " << task.second.getTaskState() << std::endl;
			}

	}
	void start(string taskName) {
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

	void cancel(string taskName) {
		auto it = m_mapTaskList.find(taskName);
		if (it != m_mapTaskList.end()) {
			//if already running, ignore cancel request 
			if((*it).second.getTaskState() != RUNNING) {	
				m_mapTaskList.erase(it);
			}
		}
	}

	void addTask(timerTask task) {
		std::string name(task.getTaskName());
		m_mapTaskList.insert(std::pair<string, timerTask>(name, task));
	}

      ~Timer() {
	//	for(auto &ths : m_thread_list) {
	//			ths.join();
	//	}

		runThreads = false;
	}

};
