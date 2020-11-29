#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <queue>
#include <condition_variable>

std::queue<int> queue;
std::mutex queueMutex;
std::condition_variable queueCondvar;



