#ifndef JS_H
#define JS_H
#include<chrono>
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
class jser
{
    public:

    chrono::high_resolution_clock::time_point begin_t;
    chrono::high_resolution_clock::time_point end_t;
    void begin()
    {
        begin_t=chrono::high_resolution_clock::now();
    }
    double end_s()
    {
        end_t=chrono::high_resolution_clock::now();
        auto time_span_ns=end_t-begin_t;
        chrono::duration<double> time_span=chrono::duration_cast<chrono::duration<double>>(end_t-begin_t);
        return time_span_ns.count();
    }
    long long int end_ns()
    {
        end_t=chrono::high_resolution_clock::now();
        auto time_span_ns=end_t-begin_t;
        return time_span_ns.count();
    }
} timer;

#endif // JS_H
/**
int main()
{
    timer.begin();
    int a;
    for(int i=0;i<100000;i++)
    {
        a++;
    }
    cout<<timer.end();
}
**/