#include <iostream>

using namespace std;

template <class T>
class Node
{
public:
    Node() : data(), prev(NULL), next(prev) {}
    Node(T d) : data(d), prev(NULL), next(NULL) {}
    Node(T d, Node<T> *p, Node<T> *n) : data(d), prev(p), next(n) {}

    bool setPrev(Node<T> *p)
    {
        this->prev = p;
        return true;
    }

    bool setNext(Node<T> *n)
    {
        this->next = n;
        return true;
    }

    T getData()
    {
        return this->data;
    }

    Node<T> *getNext()
    {
        return this->next;
    }

    Node<T> *getPrev()
    {
        return this->prev;
    }

private:
    Node<T> *prev;
    Node<T> *next;
    T data;
};

template <class T>
class LinkedList
{
public:
    LinkedList() : head(NULL), tail(NULL) {}

    void addToTail(T data)
    {
        if (this->head != NULL)
        {
            Node<T> *newTail = new Node<T>(data, this->tail, NULL);
            this->tail->setNext(newTail);
            this->tail = newTail;
        }
        else
        {
            this->head = this->tail = new Node<T>(data, NULL, NULL);
        }
    }

    void addToHead(T data)
    {
        if (this->head == NULL)
            this->tail = this->head = new Node<T>(data);
        else
        {
            Node<T> *newHead = new Node<T>(data, NULL, this->head);
            this->head->setPrev(newHead);
            this->head = newHead;
        }
    }

    void deleteData(T data)
    {

        if (head == NULL)
        {
        }

        else if (this->head == this->tail)
        {
            if (this->head->getData() == data)
            {
                this->head = this->tail = NULL;
            }
        }

        else
        {
            Node<T> *temp = head;
            while (temp != NULL)
            {

                if (temp->getData() != data)
                    temp = temp->getNext();

                else
                {
                    if (temp == this->head)
                    {
                        this->head->getNext()->setPrev(NULL);
                        head = this->head->getNext();
                    }
                    else if (temp == this->tail)
                    {
                        this->tail->getPrev()->setNext(NULL);
                        tail = this->tail->getPrev();
                    }
                    else
                    {
                        temp->getPrev()->setNext(temp->getNext());
                        temp->getNext()->setPrev(temp->getPrev());
                    }

                    break;
                }
            }
        }
    }

    void deleteData(T data, int n)
    {
        for (int i = 0; i < n; i++)
            this->deleteData(data);
    }

    friend std::ostream &operator<<(std::ostream &out, LinkedList<T> *n)
    {
        Node<T> *tempNode = n->getHead();

        cout << "(";

        if (tempNode != NULL)
        {
            while (tempNode != NULL)
            {
                cout << tempNode->getData();
                if (tempNode != n->getTail())
                    cout << ", ";
                tempNode = tempNode->getNext();
            }
        }
        cout << ")\n";
        return out;
    }

    Node<T> *getHead()
    {
        return this->head;
    }

    Node<T> *getTail()
    {
        return this->tail;
    }

private:
    Node<T> *head;
    Node<T> *tail;
};

template <class T>
class Stack
{
public:
    Stack()
    {
        list = new LinkedList<T>();
    }

    void push(T data)
    {
        this->list->addToHead(data);
    }

    T pop()
    {
        T defaultReturnValue{};
        if (this->list->getHead() != NULL)
        {
            T rmvedData = this->list->getHead()->getData();
            this->list->deleteData(rmvedData);
            return rmvedData;
        }

        return defaultReturnValue;
    }

    T top()
    {
        T defaultReturnValue{};
        if (this->list->getHead() != NULL)
        {
            return this->list->getHead()->getData();
        }

        return defaultReturnValue;
    }

    bool isEmpty()
    {
        if (this->list->getTail() != NULL)
            return false;

        return true;
    }

    int size()
    {
        int i = 0;

        Node<T> *curNode = this->list->getHead();

        while (curNode != NULL)
        {
            i++;
            curNode = curNode->getNext();
        }

        return i;
    }

private:
    LinkedList<T> *list;
};


void moveDisksBetweenTwoPoles(Stack<int> *src, Stack<int> *dest)
{
    if (src->size() == 0)
    {
        src->push(dest->pop());
      
    }
    else if (dest->size() == 0)
    {
        dest->push(src->pop());
        
    }
    else if (src->top() > dest->top())
    {
        src->push(dest->pop());
        
    }
    else
    {
        dest->push(src->pop());
        
    }
}

void solveTheGame(int num_of_disks, Stack<int> *src, Stack<int> *aux, Stack<int> *dest)
{
    int i;
    Stack<int> *destReference = dest;
    bool flagSwaped = false;
    //depending on whether disks are odd or even, we will start differentluy
    //so we swap aux and dest if disks are even so that in our code the first move is always moving to destination.
    //the sequence of events is always the same, only the starting pole changes
    if (num_of_disks % 2 == 0)
    {
        flagSwaped = true;

        Stack<int> *t = dest;
        dest = aux;
        aux = t;
    }

    for (i = num_of_disks; i > 0; i--)
    {
        src->push(i);
    }

    //int q;

    for (i = 1; destReference->size() != num_of_disks; i++)
    {
        if (i % 3 == 1)
            moveDisksBetweenTwoPoles(src, dest);

        else if (i % 3 == 2)
            moveDisksBetweenTwoPoles(src, aux);

        else if (i % 3 == 0)
            moveDisksBetweenTwoPoles(dest, aux);
    }

    cout << i - 1 << endl;
}

// Driver Program
int main()
{

    int num_of_disks;
    while (cin >> num_of_disks)
    {
        // Input: number of disks
        Stack<int> *src, *dest, *aux;

        // allocating memory for the three pegs
        src = new Stack<int>;
        aux = new Stack<int>;
        dest = new Stack<int>;

        // calling iterative function to solve the game
        solveTheGame(num_of_disks, src, aux, dest);
    }

    return 0;
}
