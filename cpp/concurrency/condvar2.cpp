#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <queue>
#include <chrono>
#include <condition_variable>

std::queue<int> queue;
std::mutex queueMutex;
std::condition_variable queueCondvar;

void provider(int var){
    for(int i=0;i<6;i++){
        {
            std::lock_guard<std::mutex> lg(queueMutex);
            queue.push(var+i);
        }
        queueCondvar.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(var));
    }  
}

void consumer(int num){
    while(true){
        int val;
        {
            std::unique_lock<std::mutex> ul(queueMutex);
            queueCondvar.wait(ul,[]{return !queue.empty();});
            val=queue.front();
            queue.pop();
        }
        std::cout<<"consumer "<<num<<":"<<val<<std::endl;
    }
}

int main(){
    auto p1=std::async(std::launch::async,provider,100);
    auto p2=std::async(std::launch::async,provider,300);
    auto p3=std::async(std::launch::async,provider,500);
    
    auto c2=std::async(std::launch::async,consumer,1);
    auto c1=std::async(std::launch::async,consumer,2);
} 

