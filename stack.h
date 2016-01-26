/*
(1) student's name:     Alec Chen
(2) student ID:         301187669
(3) SFU user name:      cca169
(4) lecture section:    CMPT 300 D1 (Fall 2015)
(5) instructor's name:  Brian Booth
(6) TA's name:          Scott Kristjansonnclude
*/
#include <stdio.h>
#include <stdlib.h>
#pragma once

struct node
{
    int data;
    struct node* next;
};

int empty(struct node *s);
struct node* push(struct node *s,int data);
struct node* pop(struct node *s,int *data);
void init(struct node* s);

