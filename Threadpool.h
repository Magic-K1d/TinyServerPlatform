/*************************************************************************
  > File Name: Threadpool.h
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Fri 05 Mar 2021 06:22:27 PM CST
 *************************************************************************/

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>

class Threadpool{
    public:
        ~Threadpool();
        static Threadpool* GetInstance();
        enum PRIORITY{ L0 = 1, L1, L2, L3};
        using Task = std::function<void()>;
        using PriorityTask = std::pair<PRIORITY, Task>;
 
        struct PriorityCmp{
            bool operator()(const Threadpool::PriorityTask p1, const Threadpool::PriorityTask p2){
                return p1.first > p2.first;
            }
        };

       using Task_queue = std::priority_queue<PriorityTask, std::vector<PriorityTask>, PriorityCmp>;
        using Threads = std::vector<std::thread*>;

        void AddTask( Task t, PRIORITY p = L3);
        void MainLoop();
        void Start();


    private:
        static Threadpool* m_threadpool;
        Threadpool( int thread_num);
        Threadpool(const Threadpool&) = delete;
        const Threadpool& operator=(const Threadpool&) = delete;


        int m_thread_num;
        bool m_started;
        Threads m_threads;
        Task_queue m_task_queue;
        std::mutex m_mutex;
        std::condition_variable m_cond_v;

};




#endif // THREADPOOL_H
