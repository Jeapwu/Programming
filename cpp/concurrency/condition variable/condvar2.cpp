/*
* 生产者与消费者使用案例
*/

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

//生产者
void provider(int var){
    for(int i=0;i<6;i++){
        {
            std::lock_guard<std::mutex> lg(queueMutex);
            queue.push(var+i);
        }
        /**
         * 每次quque中加入新元素都会唤醒一个线程输出该元素.还有注意上面这条并不在保护区内,
         * 也不需要在保护区内.虽然std::queue是的读写操作不能同时进行,
         * 但是当保护区结束的时候push()操作已经完成了,
         * 而对std::queue执行读操作在另外线程的时候也是被上锁的因此不可能会产生data race.
         */
        queueCondvar.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(var));
    }  
}

//消费者
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

