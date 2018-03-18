#include <iostream>
#include "timerTask.h"
#include "timer.h"
using namespace std;
using namespace vjp;

void configureProject() {
	cout << "configure project..." << endl;
}

void buildProject() {
	cout << "Building project..." << endl;
}

void testProject() {
	cout << "Testing Project..." << endl;
}

void sendingEmail() {

	cout << "Sending emails..." << endl;
}

int main() {
Timer *timer = Timer::getTimerInstance();
auto now = std::chrono::system_clock::now();

std::string configure("configure");
std::string build("build");
std::string test("test");
std::string emails("emails");

//timerTask configure_task(configure, &configureProject, now+ std::chrono::hours(24));
timerTask configure_task(configure, &configureProject, now+ std::chrono::seconds(24));
timerTask build_task(build, &buildProject, now + std::chrono::seconds(15));
timerTask test_task(test, &testProject, now+ std::chrono::seconds(40));
timerTask emails_task(emails, &sendingEmail, now);

timer->addTask(configure_task);
timer->addTask(build_task);
timer->addTask(test_task);
timer->addTask(emails_task);
//timer->cancel("test");

timer->listAllTasks();

timer->start_async("configure");
timer->start_async("build");
timer->start_async("test");
timer->start_async("emails");
//timer->start("configure");
//timer->start("build");
//timer->start("test");
//timer->start("emails");
//timer->start();

timer->listAllTasks();
delete(timer);
return 0;
}
