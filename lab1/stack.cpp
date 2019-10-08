#include "stack.h"
#include<stdlib.h>
#include<stdio.h>




void initSTACK(STACK *const p, int m)
{
	if( m < 0 ){
	        exit(RANGE_ERR);
	}else if( p == NULL ){
		exit( NULL_PTR_ERR );
	}
	else{
		if ( p->elems )
			free( p->elems );
		p->elems = (int *)malloc( sizeof(int) * m );
		p->pos = 0;
		p->max = m;
	}
}



//用栈s初始化p指向的栈
void initSTACK( STACK *const p, const STACK &s)
{
	if( p == NULL )
		exit( NULL_PTR_ERR );
	else{
		p->pos = s.pos;
		p->max = s.max;

		p->elems = (int *)malloc( sizeof(int) * s.max );

		for( int i =0;  i < s.pos;  i++ ){
			p->elems[i] = s.elems[i];
		}
	}
}



//返回p指向的栈的最大元素个数max
int size( const STACK *const p)
{
	if( p == NULL ){
		return NULL_PTR_ERR;
	}else{
		return p->max;
	}
}
		

//返回p指向的栈的实际元素个数pos
int howMany( const STACK *const p )
{
	if( p == NULL ){
		return NULL_PTR_ERR;
	}else{
		return p->pos;
	}
}


//取下标x处的栈元素
int getelem( const STACK *const p, int x)
{
	if( p == NULL ){
		return NULL_PTR_ERR;
	}else{
		if( x < 0 || x >= p->max ){
			exit(RANGE_ERR);
		}else{
			return p->elems[x];
		}
	}
}


//将e入栈，返回p
STACK *const push(STACK *const p, int e)
{
	if( p == NULL ){
		exit(NULL_PTR_ERR);
	}else if( p->pos == p->max ){
		exit( OVERFLOW );
	}else{
		p->elems[ (p->pos)++ ] = e;
		return p;
	}
}



//出栈到e，返回p
STACK *const pop(STACK *const p, int &e)
{
	if( p == NULL ){
		exit( NULL_PTR_ERR);
	}else if( p->pos == 0 ){
		exit( EMPTY_ERR );
	}else{
		e = p->elems[ --(p->pos) ];
		return p;
	}
}


//赋s给p指向的栈，并返回p
STACK *const assign(STACK *const p, const STACK &s)
{
	if( p == NULL ){
		exit(NULL_PTR_ERR);
	}else{
		if( p->max < s.pos ){
			free( p->elems );
			p->elems = (int *)malloc( sizeof(int) * s.pos );
		}

		p->pos = s.pos;
		for(int i = 0; i < s.pos; i++){
			p->elems[i] = s.elems[i];
		}

		return p;
	}
}
	


//打印p指向的栈
void print( const STACK *const p)
{
	if( p == NULL ){
		exit( NULL_PTR_ERR );
	}else{
		for( int i = 0; i < p->pos; i++ ){
			printf( "%d ", p->elems[i] );
		}
		printf("\n");
	}
}


//销毁p指向的栈
void destroySTACK( STACK *const p )
{
	if( p == NULL )
		return;
	else{
		free( p->elems );
		free( p );
	}
}
