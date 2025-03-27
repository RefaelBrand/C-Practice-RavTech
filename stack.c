#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

struct Node {
	int val;
	struct Node* next;
};
typedef struct Node Node;
typedef struct Node* NodePtr;

struct Stack {
	NodePtr head;
};
typedef struct Stack Stack;
typedef struct Stack* StackPtr;

void clearStack(StackPtr stack) {
	if(!stack)
		return;
	
	NodePtr node = stack->head;
	while (node) {
		NodePtr toFree = node;
		node = node->next;
		free(toFree);
	}
	free(stack);
}

void init(StackPtr *stack) {
	if (*stack) {
		clearStack(*stack);
	}
	
	*stack = (StackPtr)malloc(sizeof(Stack));
	(*stack)->head = NULL;
}

bool isEmpty(const StackPtr stack) {
	if (!stack || !stack->head)
		return true;
	
	return false;
}

NodePtr addToTop(NodePtr head, const int val) {
	NodePtr newNode = (NodePtr)malloc(sizeof(Node));
	if (!newNode) {
		printf("ERROR, int function 'addToTop',couldn't allocate memory for a new Node\n");
		return NULL;
	}
	
	newNode->val = val;
	newNode->next = NULL;
	
	if (head)
		newNode->next = head;
	head = newNode;
	return head;
}

void push(StackPtr stack, const int val) {
	if (!stack) {
		printf("ERROR, in function 'push', stack is NULL\n");
		return;
	}
	
	stack->head = addToTop(stack->head, val);
}

int pop(StackPtr stack) {
	if (!stack || !stack->head) {
		printf("ERROR, in function 'pop', stack or head is NULL\n");
		exit(1);
	}
	
	int val = stack->head->val;
	NodePtr toFree = stack->head;
	stack->head = stack->head->next;
	free(toFree);
	return val;
}

int peek(StackPtr stack) {
	if (!stack || !stack->head) {
		printf("ERROR, in function 'peek', stack or head is NULL\n");
		exit(1);
	}
	
	return stack->head->val;
}

unsigned int stackSize(const StackPtr const stack) {
	unsigned int count = 0;
	if (!stack)
		return count;
	
	NodePtr node = stack->head;
	while (node) {
		count++;
		node = node->next;
	}
	return count;
}

void printStack(const StackPtr const stack) {
	printf("Stack: (%d values)\n", stackSize(stack));
	if (!stack) {
		printf("stack is empty, use 'init' to allocate one\n");
		return;
	}
	
	NodePtr node = stack->head;
	while (node) {
		printf("%d", node->val);
		if (node->next)
			printf(", ");
		node = node->next;
	}
	printf("\n");
}

void runCommand(char* input, StackPtr stack, const int* const val) {
	if (strcmp(input, "push") == 0) {
		if (!val) {
			printf("ERROR, in function 'runCommand', val is NULL\n");
			exit(1);
		}
		push(stack, *val);
		printf("PUSH: %d\n", *val);
		return;
	}
	
	if (strcmp(input, "pop") == 0) {
		if (isEmpty(stack)) {
			printf("POP: (stack empty)\n");
			return;
		}
		int val = pop(stack);
		printf("POP: %d\n", val);
		return;
	}
	if (strcmp(input, "peek") == 0) {
		if (isEmpty(stack)) {
			printf("PEEK: (stack empty)\n");
			return;
		}
		int val = peek(stack);
		printf("PEEK: %d\n", val);
		return;
	}
}

void randomPushPop(StackPtr stack, const int steps, const int pushRatio) {
	srand(time(NULL));
	for (int i = 1; i <= steps; i++) {
		sleep(1);
		if (rand() % 101 <= pushRatio) {
			int val = rand() % 100;
			runCommand("push", stack ,&val);
		}
		else {
			runCommand("pop", stack, NULL);
		}
	}
}

void runRandomStackLoop(StackPtr stack) {
	while (1) {
		randomPushPop(stack, 1, 50);
		printf("Stack size: %d\n", stackSize(stack));
	}
}

int main() {
	StackPtr stack = NULL;
	init(&stack);
	runRandomStackLoop(stack);
	clearStack(stack);
	return 0;
}