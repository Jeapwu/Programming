/*
* 系统时间获取案例
*/

#include <locale>
#include <chrono>
#include <ctime>
#include <iostream>
#include <cstdlib>
using namespace std;

int main(){
    auto now=std::chrono::system_clock::now();
    time_t t=std::chrono::system_clock::to_time_t(now);
    tm* nowTM=std::localtime(&t);

    locale locC;
    const time_put<char>& p=use_facet<time_put<char>>(locC);

    string format="%A %x\n";
    p.put(cout,cout,':',nowTM,format.c_str(),format.c_str()+format.size());
}