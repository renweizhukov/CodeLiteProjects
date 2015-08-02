/*
 * BlockingQueue.h
 *
 *  Created on: Sep 28, 2014
 *      Author: RWHTT
 */

#ifndef BLOCKINGQUEUE_H_
#define BLOCKINGQUEUE_H_

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

using namespace std;

const int MAX_QUEUE_SIZE = 10;

template <typename T>
class BlockingQueue
{
public:
    T pop()
    {
        unique_lock<mutex> mlock(m_mutex);
        while (m_queue.empty())
        {
            //cout << "Queue size = " << m_queue.size() << ": waiting for the queue to become not empty." << endl;
            m_queueNotEmpty.wait(mlock);
            //cout << "Queue size = " << m_queue.size() << ": the queue is not empty now." << endl;
        }

        T value = m_queue.front();
        m_queue.pop();

        mlock.unlock();
        m_queueNotFull.notify_one();
        return value;
    }

    void push(T& value)
    {
        unique_lock<mutex> mlock(m_mutex);
        while (m_queue.size() == MAX_QUEUE_SIZE)
        {
            //cout << "Max queue size = " << MAX_QUEUE_SIZE << "." << endl;
            //cout << "Queue size = " << m_queue.size() << ": waiting for the queue to become not full." << endl;
            m_queueNotFull.wait(mlock);
            //cout << "Queue size = " << m_queue.size() << ": the queue is not full now." << endl;
        }

        m_queue.push(value);
        mlock.unlock();
        m_queueNotEmpty.notify_one();
    }

private:
    queue<T> m_queue;
    mutex m_mutex;
    condition_variable m_queueNotEmpty;
    condition_variable m_queueNotFull;
};

#endif /* BLOCKINGQUEUE_H_ */