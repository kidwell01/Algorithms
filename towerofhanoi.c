#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prev, *next;
};

void initLinkList(struct Node **head)
{
    (*head) = NULL;
}

void addToHead(struct Node **head, int data)
{
    if ((*head) == NULL)
    {
        (*head) = (struct Node *)malloc(sizeof(struct Node));
        (*head)->prev = NULL;
        (*head)->next = NULL;
        (*head)->data = data;
    }
    else
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->data = data;

        (*head)->prev = newNode;
        newNode->next = (*head);
        (*head) = (*head)->prev;
    }
}

void addToTail(struct Node **head, int data)
{
    if ((*head) == NULL)
    {
        (*head) = (struct Node *)malloc(sizeof(struct Node));
        (*head)->prev = NULL;
        (*head)->next = NULL;
        (*head)->data = data;
    }
    else
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->data = data;

        struct Node *cur = (*head);
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = newNode;
        newNode->prev = cur;
    }
}

void deleteData(struct Node **head, int data)
{

    struct Node *cur = (*head);
    while (cur != NULL)
    {
        if (cur->data == data)
        {
            if (cur->next == NULL && cur->prev == NULL)
            {
                (*head) = NULL;
                return;
            }
            if (cur->prev != NULL)
                cur->prev->next = cur->next;
            else
            {
                (*head) = cur->next;
                cur->next->prev = NULL;
            }
            if (cur->next != NULL)
                cur->next->prev = cur->prev;
            else
            {
                cur = cur->prev;
                cur->next = NULL;
            }
            break;
        }
        cur = cur->next;
    }
}

void deleteDatas(struct Node **head, int data, int n)
{
    if (n != 0)
    {
        deleteData(head, data);
        deleteDatas(head, data, n - 1);
    }
}

void display(struct Node *head)
{
    struct Node *cur = head;
    printf("(");
    printf("%d", cur->data);
    cur = cur->next;
    while (cur != NULL)
    {
        printf(", %d", cur->data);
        cur = cur->next;
    }
    printf(")\n");
}

void push(struct Node **stack, int data)
{
    addToHead(stack, data);
}

int pop(struct Node **stack)
{
    int n = (*stack)->data;
    deleteData(stack, n);
    return n;
}

int top(struct Node *stack)
{
    return stack->data;
}

int isEmpty(struct Node *stack)
{
    if (stack == NULL)
        return 1;
    return 0;
}

int size(struct Node *stack)
{
    int cnt = 0;
    struct Node *cur = stack;
    while (cur != NULL)
    {
        cnt++;
        cur = cur->next;
    }
    return cnt;
}

void transfer_disk(struct Node **a, struct Node **b)
{
    if (isEmpty((*b)))
        push(b, pop(a));
    else if (isEmpty((*a)))
        push(a, pop(b));
    else if (top((*a)) > top((*b)))
        push(a, pop(b));
    else
        push(b, pop(a));
}

int main()
{
    int height, step;
    while (scanf("%d", &height) != EOF)
    {
        struct Node *A = NULL, *B = NULL, *C = NULL;
        step = 1;
        for (int i = height; i > 0; i--)
            push(&A, i);

        if (height % 2 == 1)
        {
            while (!isEmpty(A) || !isEmpty(B))
            {
                if (step % 3 == 1)
                    transfer_disk(&A, &C);
                else if (step % 3 == 2)
                    transfer_disk(&A, &B);
                else
                    transfer_disk(&B, &C);
                step++;
            }
        }
        else
        {
            while (!isEmpty(A) || !isEmpty(B))
            {
                if (step % 3 == 1)
                    transfer_disk(&A, &B);
                else if (step % 3 == 2)
                    transfer_disk(&A, &C);
                else
                    transfer_disk(&B, &C);
                step++;
            }
        }
        step--;
        printf("%d\n", step);
    }
}