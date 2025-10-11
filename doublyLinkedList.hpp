#ifndef LinkedList
#define LinkedList

#include <cstdlib>
#include <stdio.h>

class Node
{
public:
    struct Node *prev;
    int data;
    struct Node *next;
};

class DoublyLinkedList
{
public:
    Node *head = NULL;

    ~DoublyLinkedList()
    {
        Node *h = head->next, *tmp = h;
        do {
            h = h->next;
            delete tmp;
            if(h) {
                tmp = h;
            }
        } while (h != head);
        delete head;
    }

    void display()
    {
        Node *h = head;
        do {
            printf("%d ", h->data);
            h = h->next;
        }while (h != head);
        printf("\n");
    }

    int length()
    {
        Node *p = head;
        int count = 0;
        if(!p)
            return 0;

        do
        {
            count++;
            p = p->next;
        } while(p != head);

        return count;
    }

    void insert(int index, int x)
    {
        struct Node *t, *p = head;

        if(index<0 || index>length())
            return;

        t = (struct Node *) malloc(sizeof(struct Node));
        t->data = x;

        if(index==0)
        {
            if(head)
            {
                t->next = head;
                t->prev = head->prev;

                head->prev->next = t;
                head->prev = t;
            }
            else
            {
                t->prev = t;
                t->next = t;
            } 
            head = t;
        }
        else
        {
            for(int i=0; i<index-1; i++)
                p=p->next;

            t->next = p->next;
            t->prev = p;
            if(p->next)
                p->next->prev = t;
            p->next = t;
        }
    }

    int remove(int index)
    {
        Node *p = head;
        int x = -1;

        if(index<1 || index>length())
            return x;

        if(index==1)
        {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            head=head->next;

            x = p->data;
            free(p);
        }
        else
        {
            for(int i=0; i<index-1; i++)
                p=p->next;

            p->prev->next = p->next;
            p->next->prev = p->prev;
            free(p);
        }

        return x;
    }

    bool empty() 
    {
        if(head) {
            return false;
        } else {
            return true;
        }
    }
};

#endif