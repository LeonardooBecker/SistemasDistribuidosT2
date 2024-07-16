#ifndef _cisj_
#define _cisj_


typedef struct node_set {
	int* nodes;
	ssize_t size;
	ssize_t offset;
} node_set;

node_set* cis(int i, int s);

#endif