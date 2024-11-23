#ifndef Data_Structure_H
#define Data_Structure_H

#include <string>
#include <stdexcept>

class Node
{
public:
    int value;  // value of the node
    Node *next; // Pointer that points to next node

    Node(int value)
    {
        this->value = value;
        this->next = nullptr;
    }
};

class Queue
{
private:
    Node *head;
    Node *tail;
    int length;

public:
    Queue()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
        head = nullptr;
        tail = nullptr;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    void enqueue(int value)
    {
        Node *newNode = new Node(value);
        if (isEmpty())
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    int dequeue()
    {
        if (isEmpty())
        {
            throw std::underflow_error("Que is empty!");
        }
        Node *temp = head;
        head = head->next;
        length--;
        return temp->value;
    }

    int peek()
    {
        if (isEmpty())
        {
            throw std::underflow_error("Queue is empty!");
        }

        return head->value;
    }

    std::string print()
    {
        if (isEmpty())
        {
            return "[]";
        }
        std::string data = "[";
        Node *temp = head;
        while (temp->next)
        {
            data += std::to_string(temp->value) + ", ";
            temp = temp->next;
        }
        data += std::to_string(temp->value) + "]";

        return data;
    }

    int size() { return length; }
};

class Stack
{
private:
    Node *head;
    int length;

public:
    Stack()
    {
        head = nullptr;
        length = 0;
    }

    ~Stack()
    {
        while (!isEmpty())
        {
            pop(); // remove the data one by one
        }
        head = nullptr;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    void push(int value)
    {
        Node *newNode = new Node(value);
        newNode->next = head;
        head = newNode;

        length++; // increase the length of the stack
    }

    int pop()
    {
        if (isEmpty())
        {
            throw std::underflow_error("Stack is empty!");
        }

        Node *temp = head;
        head = head->next;

        length--;
        return temp->value;
    }

    int peek()
    { // return top value without removing
        if (isEmpty())
        {
            throw std::underflow_error("Stack is empty!");
        }
        return head->value;
    }

    int size()
    {
        return this->length;
    }

    std::string print()
    {
        if (isEmpty())
        {
            return "[]";
        }
        std::string data = "[";
        Node *temp = head;
        while (temp->next)
        {
            data += std::to_string(temp->value) + ", ";
            temp = temp->next;
        }
        data += std::to_string(temp->value) + "]";

        return data;
    }
};

#endif