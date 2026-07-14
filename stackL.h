#pragma once
#include<stdio.h>
typedef int element;		// 스택 원소(element)의 자료형을 char로 정의 

typedef struct  stackNode {	// 스택의 노드를 구조체로 정의
	int status;
	struct stackNode* link;
} stackNode;

extern stackNode* top;				// 스택의 top 노드를 지정하기 위해 포인터 top 선언

int isStackEmpty();
void push(int status);
element pop();
element peek();
void printStack();