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
#include "timerTask.h"
using namespace std;

class timerTask;

struct compareSchedule{
    bool operator () (timerTask& task1, timerTask& task2) {
        return task1.getTaskTime() < task2.getTaskTime();
    }
};

class Timer {
	static Timer* m_timerInstance;
	timerTask m_timerTask;
	vector<std::thread> m_thread_list;
	mutex m_mutex;
	std::map<std::string, timerTask> m_mapTaskList;
	bool runThreads = true;
	Timer(){}
public:
	static Timer* getTimerInstance();
	void start();
	void listAllTasks(); 
	void start(string taskName); 
	void cancel(string taskName);
	void addTask(timerTask task);
       ~Timer(); 

};
