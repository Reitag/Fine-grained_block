#include "FineGrainedQueue.h"

FineGrainedQueue::Node::Node(int valueFromOutside)
{
    value = valueFromOutside;
    next = nullptr;
}

FineGrainedQueue::FineGrainedQueue()
{
    head = nullptr;
}

void FineGrainedQueue::addValue(int value)
{
    Node* newNode = new Node(value);
    
    if (head == nullptr)
    {
        head = newNode;
        return;
    }
    Node* last = head;
    while (last->next != nullptr)
    {
        last = last->next;
    }
    last->next = newNode;
    return;
}

FineGrainedQueue::Node* FineGrainedQueue::find(Node* node, int pos, int curPos)
{
    if (pos == curPos || node->next == nullptr)
    {
        return node;
    }
    else if ((pos > curPos) && (node->next != nullptr))
    {
        ++curPos;
        find(node->next, pos, curPos);
    }
    else
    {
        return nullptr;
    }
}

void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    Node* prev;
    Node* newNode;

    queue_mutex.lock();
    prev = find(head, pos - 1, 1);
    newNode = new Node(value);
    queue_mutex.unlock();

    prev->node_mutex.lock();
    newNode->node_mutex.lock();
    newNode->next = prev->next;
    prev->next = newNode;
    prev->node_mutex.unlock();
    newNode->node_mutex.unlock();
}

void FineGrainedQueue::remove(int value)
{
    Node* prev;
    Node* cur;

    queue_mutex.lock();
    
    prev = this->head;
    cur = this->head->next;

    prev->node_mutex.lock();
    queue_mutex.unlock();

    if (cur)
    {
        cur->node_mutex.lock();
    }   
    while (cur)
    {
        if (cur->value == value)
        {
            prev->next = cur->next;
            prev->node_mutex.unlock();
            cur->node_mutex.unlock();
            delete cur;
            return;
        }
        Node* old_prev = prev;
        prev = cur;
        cur = cur->next;
        old_prev->node_mutex.unlock();
        if (cur)
        {
            cur->node_mutex.lock();
        }     
    }
    prev->node_mutex.unlock();
}

void FineGrainedQueue::show()
{
    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) 
    {
        std::cout << ptr->value << " ";
    }
    std::cout << std::endl;
}