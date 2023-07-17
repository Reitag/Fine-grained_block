#pragma once
#include <iostream>
#include <mutex>

class FineGrainedQueue
{
private:
    struct Node
    {
        int value;
        Node* next;
        std::mutex node_mutex;
        Node(int valueFromOutside);
    };
    Node* head;
    std::mutex queue_mutex;

public:
    FineGrainedQueue();

    void addValue(int value);
    Node* find(Node* node, int pos, int curPos);
    void insertIntoMiddle(int value, int pos);
    void remove(int value);
    void show();
};