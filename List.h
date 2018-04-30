#pragma once
#include <string>
#include <iostream>
using namespace std;
template<typename T>
class List
{
private:

    class Node
    {
    public:
        T element;
        Node* next;
        Node(T element, Node* next)
        {
            this->element = element;
            this->next = next;
        }
        virtual ~Node()
        {

        }
    };

    Node* first;
    int quantity;

    void deallocate()
    {
        Node* temp = nullptr;
        for (int i = 0; i < quantity; i++)
        {
            temp = first;
            first = temp->next;
            delete temp;
            temp = nullptr;
        }
        first = nullptr;
    }

    void copy(const List& other)
    {
        quantity = 0;
        first = nullptr;
        if(other.quantity != 0)
        {
            Node* otherTraverser = other.first;
            first = new Node(otherTraverser->element, nullptr);
            quantity++;

            Node* thisTraverser = first;
            otherTraverser = otherTraverser->next;

            while(otherTraverser != nullptr)
            {
                thisTraverser->next = new Node(otherTraverser->element, nullptr);
                quantity++;
                otherTraverser = otherTraverser->next;
                thisTraverser = thisTraverser->next;
            }
        }
    }

    int getElementPos(const T& element)
    {
        int atPosition = -1;
        bool found = false;
        Node* traverser = first;
        for (int i = 0; i < quantity && !found; i++)
        {
            if(traverser->element == element)
            {
                found = true;
                atPosition = i;
            }
            traverser = traverser->next;
        }
        return atPosition;
    }

public:
    List()
    {
        first = nullptr;
        quantity = 0;
    }

    virtual ~List()
    {
        deallocate();
    }

    List(const List& other)
    {
        copy(other);
    }

    List& operator=(const List& other)
    {
        if(this != &other)
        {
            deallocate();
            copy(other);
        }
        return *this;
    }

    void insertAt(int pos, const T& element) //throw(...);
    {
        if(pos == 0)
        {
            Node* newElement = new Node(element, first);
            first = newElement;
            quantity++;
        }
        else if(pos < 0 || pos > quantity)
        {
            char error[] = "Given position is out of range";
            throw error;
        }
        else
        {
            Node* traverser = first;
            for (int i = 0; i < pos - 1; i++)
            {
                traverser = traverser->next;
            }
            Node* newElement = new Node(element, traverser->next);
            traverser->next = newElement;
            quantity++;
        }
    }

    T getAt(int pos) const //throw(...);
    {
        T element;
        Node* traverser = first;
        if(pos < 0 || pos > quantity)
        {
            char error[] = "Given position is out of range!";
            throw error;
        }
        else
        {
            for (int i = 0; i < pos; i++)
            {
                traverser = traverser->next;
            }
            element = traverser->element;
        }
        return element;
    }

    void removeAt(int pos) //throw(...);
    {
        Node* traverser = first;
        Node* temp = nullptr;
        if(pos == 0)
        {
            first = traverser->next;
            delete traverser;
            quantity--;
        }
        else if(pos < 0 || pos > quantity)
        {
            char error[] = "Given position is out of range!";
            throw error;
        }
        else
        {
            for (int i = 0; i < pos - 1; i++)
            {
                traverser = traverser->next;
            }
            temp = traverser->next;
            traverser->next = temp->next;
            delete temp;
            quantity--;
        }
    }

    bool removeElement(const T& element)
    {
        bool removed = false;
        int elementPosition = getElementPos(element);
        if(elementPosition != -1)
        {
            removeAt(elementPosition);
            removed = true;
        }
        return removed;
    }

    bool findElement(const T& toFind) const
    {
        bool found = false;
        Node* traverser = first;
        for (int i = 0; i < quantity && !found; i++)
        {
            if(traverser->element == toFind)
            {
                found = true;
            }
            traverser = traverser->next;
        }
        return found;
    }

    int length() const
    {
        return quantity;
    }

    void getAll(T arr[], int cap) //throw(...);
    {
        if(cap < quantity)
        {
            char error[] = "Given capacity is not enough!";
            throw error;
        }
        else
        {
            Node* traverser = first;
            for (int i = 0; i < quantity; i++)
            {
                arr[i] = traverser->element;
                traverser = traverser->next;
            }
        }
    }
};