#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "stack.h"


#define TRUE    1
#define SUCCESS 2
#define FAIL	2
#define DEFAULT_OPT -1

typedef struct Node{
	char name[100];
	STACK *stack;
	Node *prior;
	Node *next;
}Node;


int freeStacks( Node *&ptr );
int testInitSTACKByCap(  Node *&ptr);
int testSize( Node *ptr );
int testInitSTACKkBySta( Node *&ptr, Node *head);
int testGetElem( Node *ptr);
int testPop( Node *ptr );
int testPush( Node *ptr);
int testDestroySTACK( Node *&ptr, Node *head );
int testHowMany( Node *ptr );
int testAssign( Node *ptr, Node *head );
int testPrint( Node *ptr );
int chooseStack( Node *&ptr, Node *head);



int main()
{
	int opt = DEFAULT_OPT;
	char input[100];
	
	Node *head = (Node *)malloc( sizeof(Node) );
	head->prior = 0;
	head->next = 0;
	head->stack = 0;
	
	Node *ptr = head;

	if( head->stack ){
		printf("hh\n");
	}

	while( TRUE ){
		printf(" ------------   menu    ----------------\n");
		printf(" 1.初始化p指向的栈：最多m个元素   2.用栈s初始化p指向的栈 \n");
		printf(" 3.销毁p指向的栈                  4.打印p指向的栈\n");
		printf(" 5.赋s给p指向的栈，并返回p        6.出栈到e，返回p\n" );
		printf(" 7.将e入栈，返回p                 8.返回p指向的栈的实际元素个数pos\n");
		printf(" 9.返回p指向的栈的最大元素个数max 10.取下标x处的栈元素\n");
		printf(" 0.exit                           11.选择当前栈\n");
		printf(" --------------------------------------\n");

		do{
			printf("please input your option: [0-11] ");
			scanf("%d", &opt);
		}while( opt > 11  ||  opt < 0);
		

		//system("clear");
		
		switch( opt ){
			case 0:
				freeStacks( head );
				return 0;

			case 1:
				if (testInitSTACKByCap( ptr)  ==  SUCCESS ){
					printf("初始化成功\n");
				}else{
					printf("初始化失败\n");
				}
				break;

			case 2:
				if (testInitSTACKkBySta( ptr, head)  ==  SUCCESS ){
					printf("初始化成功\n");
				}else{
					printf("初始化失败\n");
				}
				break;

			case 3:
				if( testDestroySTACK( ptr, head )  ==  SUCCESS ){
					printf("销毁栈成功\n");
				}else{
					printf("请先创建栈。\n");
				}
				break;

			case 4:
				testPrint( ptr );
				break;

			case 5:
				if( testAssign( ptr, head ) ==  SUCCESS){
					printf( "赋值成功。\n");
				}else{
					printf("赋值失败。\n");
				}
				break;

			case 6:
				testPop( ptr );
				break;

			case 7:
				testPush( ptr );
				break;

			case 8:
				testHowMany( ptr );
				break;

			case 9:
				int size;
				size = testSize( ptr );

				if( size == NULL_PTR_ERR ){
					printf("pointer error.\n");
				}else{
					printf("the capacity of the %s is %d\n",ptr->name, size);
				}
				break;

			case 10:
				testGetElem( ptr );
				break;

			case 11:
				if( head->next )
					chooseStack( ptr, head);
				else{
					printf("no stack.\n");
				}
				break;

			default:
				printf("option err\n");
				break;

		}

		opt = DEFAULT_OPT;

	}
}


int testInitSTACKByCap(  Node *&ptr )
{
	STACK *stack = (STACK *)malloc( sizeof(STACK) );
	stack->elems = NULL;

	Node *node = NULL;
	int m;

	printf("input the max capacity of the satck: ");
	scanf("%d", &m);
	
	if( m < 0 ){
		printf("the capacity error.\n");
	}

	initSTACK( stack, m );


	node = (Node *)malloc( sizeof(Node) );

	printf("input the name of the satck: ");
	scanf("%s", node->name);

	node->stack = stack;
	node->prior = ptr;
	node->next  = ptr->next;
	ptr->next   = node;

	ptr = node;
	return SUCCESS;
}



int testSize( Node *ptr )
{
	if( ptr == NULL ){
		printf("pointer error.\n");
		return NULL_PTR_ERR;
	}else{
		return size( ptr->stack );
	}

}



int testInitSTACKkBySta( Node *&ptr,  Node *head )
{
	Node *tmp = head->next;
	char name[100];

	printf("input the name of dest stack: ");
	scanf("%s", name);

	for( ; tmp != NULL; tmp = tmp->next){
		if( strcmp( tmp->name, name ) == 0 ){

			STACK *stack = (STACK *)malloc( sizeof(STACK) );
			stack->elems = NULL;

			initSTACK( stack, *(tmp->stack) );

			Node *node = (Node *)malloc( sizeof(Node) );

			printf("input the name of new stack: ");
			scanf("%s", node->name);

			node->stack = stack;
			node->prior = ptr;
			node->next = ptr->next;
			ptr->next = node;

			ptr = node;
			return SUCCESS;
		}else{
			return FAIL;
		}
	}
}



int testHowMany( Node *ptr )
{
	printf( "the total number of elements in %s is %d. \n", ptr->name, howMany( ptr->stack) );
	return SUCCESS;
}


int testPush( Node *ptr)
{
	int e;

	printf("input the element: ");
	scanf("%d", &e);

	if( ptr->stack->pos == ptr->stack->max ){
		printf("the stack if full.\n");
		return FAIL;
	}else{
		push( ptr->stack, e );
		return SUCCESS;
	}
}


int testPop( Node *ptr )
{
	int e = 1;

	if( ptr->stack->pos == 0 ){
		printf("empty stack. \n");
		return FAIL;
	}else{
		pop( ptr->stack, e );
		printf("pop %d \n", e); 
		return SUCCESS;
	}
}



int testGetElem( Node *ptr)
{
	int i;

	printf("input the index: ");
	scanf("%d", &i );

	int e = getelem( ptr->stack, i );

	if( e == RANGE_ERR ){
		printf( "the index is not exist.\n");
		return FAIL;
	}else{
		printf("the element is: %d\n", e);
		return SUCCESS;
	}
}


int testAssign( Node *ptr, Node *head )
{
	char name[100];

	printf("input the name of dest stack: ");
	scanf( "%s", name );

	for(Node *tmp = head->next;  tmp != NULL;  tmp = tmp->next){
		if( strcmp( name, tmp->name )  ==  0 ){
			assign( tmp->stack, *(ptr->stack) );
			return SUCCESS;
		}
	}

	return FAIL;
}



int testPrint( Node *ptr )
{
	print( ptr->stack );
}


int testDestroySTACK( Node *&ptr, Node *head )
{
	Node *tmp = ptr;

	if( ptr == head )
		return FAIL;
	else{
		destroySTACK( tmp->stack );
		tmp->stack = NULL;
		
		ptr = ptr->next == NULL? ptr->prior : ptr->next;
		if( ptr != head ){
			if( tmp->next )
				tmp->prior->next = tmp->next->prior;
			tmp->prior->next = tmp->next;
		}else{
			ptr->next = NULL;
		}

		free( tmp );

		return SUCCESS;
	}
}

		


int freeStacks( Node *&ptr )
{
	Node *tmp = ptr;

	while( ptr != NULL ){
		tmp = ptr;
		ptr = ptr->next;

		if( tmp->stack){
			if( tmp->stack->elems )
				free( tmp->stack->elems );
			free( tmp->stack );
		}
		free( tmp );
	}

	ptr = tmp = 0;

	return SUCCESS;
}


int chooseStack( Node *&ptr, Node *head)
{
	Node *tmp = head->next;
	char name[100];

	printf("choose stacks from: ");
	for( ;tmp != NULL; tmp=tmp->next){
		printf("%s ", tmp->name);
	}
	printf("\nnow stack is: %s\n",ptr->name );

	scanf("%s", name);
	for( tmp = head->next;  tmp != NULL;  tmp=tmp->next){
		if( strcmp( name, tmp->name) == 0 ){
			ptr = tmp;
			return SUCCESS;
		}
	}

	return FAIL;
}

