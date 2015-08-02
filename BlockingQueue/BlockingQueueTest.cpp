/*
 * BlockingQueueTest.cpp
 *
 *  Created on: Sep 28, 2014
 *      Author: RWHTT
 */

#include "BlockingQueue.h"

mutex cout_mutex;

void produce(shared_ptr<BlockingQueue<int>> &q, int id, int cntOfPushes)
{
    unique_lock<mutex> coutLock(cout_mutex, defer_lock);
    static int pushedValue = 0;

    for (int i = 0; i < cntOfPushes; i++)
    {
        coutLock.lock();
        cout << "Producer " << id << " Pushing " << pushedValue << "." << endl;
        coutLock.unlock();

        q->push(pushedValue);

        coutLock.lock();
        cout << "Producer " << id << " Pushed " << pushedValue << "." << endl;
        pushedValue++;
        coutLock.unlock();
    }
}

void consume(shared_ptr<BlockingQueue<int>> &q, int id, int cntOfPops)
{
    unique_lock<mutex> coutLock(cout_mutex, defer_lock);

    for (int i = 0; i < cntOfPops; i++)
    {
        coutLock.lock();
        cout << "Consumer " << id << " Popping item " << i << "." << endl;
        coutLock.unlock();

        auto value = q->pop();

        coutLock.lock();
        cout << "Consumer " << id << " Popped " << value << "." << endl;
        coutLock.unlock();
    }
}

int main()
{
    shared_ptr<BlockingQueue<int>> q(new BlockingQueue<int>());

    using namespace std::placeholders;

    cout << "The main thread starts!!" << endl;

    thread prod0(produce, ref(q), 0, 3);
    thread prod1(produce, ref(q), 1, 6);

    thread consumer0(consume, ref(q), 0, 4);
    thread consumer1(consume, ref(q), 1, 3);

    prod0.join();
    consumer0.join();
    consumer1.join();
    prod1.join();

    cout << "The main thread is done!!" << endl;

    return 0;
}