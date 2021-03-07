/*************************************************************************
  > File Name: Threadpool.cpp
  > Author: MK_ser
  > Mail: zzx65706780@gmail.com 
  > Created Time: Fri 05 Mar 2021 06:23:30 PM CST
*************************************************************************/

#include"Threadpool.h"


Threadpool* Threadpool::m_threadpool = new Threadpool(8);

Threadpool::Threadpool(int thread_num) : m_mutex(), m_cond_v(), m_thread_num(thread_num), m_started(false){
    std::cout << std::this_thread::get_id()  << " :thread created" << std::endl;    
}


Threadpool::~Threadpool(){
    m_started = false;
    for(int i = 0; i < m_thread_num; ++i){
        m_threads[i]->join();
    }
    std::cout << "thread end" << std::endl; 
}

Threadpool* Threadpool::get_instence(){
    // if(!m_thread_pool ){
    //     m_thread_pool = new Threadpool(5);
    // }
    return m_threadpool;
}

void Threadpool::start(){
    m_started = true;
    m_threads.reserve( m_thread_num);
    for(int i = 0; i < m_thread_num; ++i){
        m_threads.push_back( new std::thread(std::bind(&Threadpool::mainLoop, this)));
    } 
}

void Threadpool:: addTask( Task t, PRIORITY p){
    std::unique_lock<std::mutex> lock(m_mutex);
    PriorityTask pt(p, t);
    m_task_queue.push(pt);
    m_cond_v.notify_one();

}

void Threadpool::mainLoop(){
    std::cout << std::this_thread::get_id() << std::endl;
    while(m_started){
        
        Task t;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            if(m_task_queue.empty()){
                m_cond_v.wait( lock);
            }
            t = m_task_queue.top().second;
            m_task_queue.pop();
        }
        if(t) t();
    
    }
}

