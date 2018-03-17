#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <ctime>
#include <chrono>
#include <future>
using namespace std;

enum taskState {
	SCHEDULED=0,
	RUNNING,
	CANCELLED,
	FINISHED
};

typedef void (*runMethod) (void);

class timerTask {
	string m_taskName;
	chrono::system_clock::time_point  m_taskTime;
	taskState m_taskState = SCHEDULED;
	runMethod m_runMethod;
public:
	timerTask() { m_taskName=""; }
	timerTask(string &taskName, runMethod rMethod, chrono::system_clock::time_point scheduledTime) {
		m_taskName = taskName;
		m_runMethod = rMethod;	
		m_taskTime = scheduledTime;
	} 
	taskState getTaskState() { return m_taskState; }
	void setTaskState(taskState state) { m_taskState = state;}
	string getTaskName() { return m_taskName; }
	chrono::system_clock::time_point getTaskTime() { return m_taskTime; }
	timerTask &getTimerTaskObject(string taskName) { if (taskName == m_taskName) return *this; }
	runMethod getRunMethod() { return m_runMethod; }
	void run() { (*m_runMethod)(); }
	
};
