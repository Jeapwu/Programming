
/**
* 条件变量使用案例
*/

#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
using namespace std;

bool readyFlag;
std::mutex readyMutex;
std::condition_variable readyCondvar;

void thread1(){
    std::cout<<"<return>"<<std::endl;
    std::cin.get();
    //共享数据加锁
    {
        std::lock_guard<std::mutex> lg(readyMutex);
        readyFlag=true;
    } //释放mutex
    //通知另一线程处理数据
    readyCondvar.notify_one();
}

void thread2(){
    {
        std::unique_lock<std::mutex> ul(readyMutex);
        readyCondvar.wait(ul,[]{return readyFlag;});
    }
    std::cout<<"done"<<std::endl;
}

int main(){
    auto f1=std::async(std::launch::async,thread1);
    auto f2=std::async(std::launch::async,thread2);
}