[![Build Status](https://travis-ci.org/saanvijay/taskScheduler.svg?branch=master)](https://travis-ci.org/saanvijay/taskScheduler)
![Platforms](https://img.shields.io/badge/platform-linux-lightgray.svg)

# taskScheduler
Task scheduler, task should be executed at given time

Design a Timer class that manages the execution of deferred tasks. The time constructor takes as its argument an object which includes a Run method and a name field which is string. 

Timer must support 
starting a thread, identified by name, at a given time in the future. ancelling a thread, identified by name (if a thread has already started cancel request should be ignored)
