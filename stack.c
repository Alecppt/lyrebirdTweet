/*
(1) student's name:     Alec Chen
(2) student ID:         301187669
(3) SFU user name:      cca169
(4) lecture section:    CMPT 300 D1 (Fall 2015)
(5) instructor's name:  Brian Booth
(6) TA's name:          Scott Kristjansonnclude
*/

#include "stack.h"


void init(struct node* head)
{
    head = NULL;
}

struct node* push(struct node* head,int data)
{
    struct node* tmp = (struct node*)malloc(sizeof(struct node));
    if(tmp == NULL)
    {
        exit(0);
    }
    tmp->data = data;
    tmp->next = head;
    head = tmp;
    return head;
}

struct node* pop(struct node *head,int *element)
{
    struct node* tmp = head;
    *element = head->data;
    head = head->next;
    free(tmp);
    return head;
}

int empty(struct node* head)
{
    return head == NULL ? 1 : 0;
}
