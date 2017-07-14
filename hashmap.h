//
//  hashmap.h
//  hashmap
//
//  Created by Hongchao Ma on 2016-04-20.
//  Copyright © 2016 Hongchao Ma. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nowhashmaplength=0;//+++++++++++++++++++++++++++++++
int previoushashmaplength=0;//++++++++++++++++++++++++
#define length 25  //restore the ip and mac
#define TRUE 1
#define FALSE 0
const char thecomputer[length] = "00:21:70:5f:b3:62";
struct node_1
{
    char ipaddress[length];//just restore the ip address souce ip or destination ip
    int count;//restore the number of bytes of paload
    int portnumber;//restore the port number of ip
    int timenumber;//restore the how many time of ip address
    char application[length];//to restore the information
    char transitionprotocal[length];
    struct node_1* next;
};
typedef struct node_1 node;
node* initialize()
{
    node* a = (node*)malloc(sizeof(node));
    strcpy(a->ipaddress, "");
//+++++++++++++++++++
    strcpy(a->application, "");// to initialize the application
    strcpy(a->transitionprotocal, "");
//+++++++++++++++++++++++++++++
    a->count = 0;
    a->portnumber = 0;
    a->timenumber = 1;
    a->next = NULL;
//printf("initialize is called %x\n",a);
    return a;
};

//++++++++++++++++++++++insert the node in the link+++++++++++++++++++++++++++++
/*
void insert(node* last,node* newone)
{
// printf("insert is called\n");
last->next=newone;
last=newone;

};*/
//++++++++++++++++++++++insert the node in the link++++++++++++++++++++++++++++

//search every link if there is one node exist return the positin otherwise return 0
int search(node* first, node* newone)
{
// printf("search is called\n");
    int position = 0;
    node* head = first;
    int pose = 0;
    while (head->next != NULL) {
	position++;
	if ((strcmp(head->ipaddress, newone->ipaddress) == 0) && ((head->portnumber) == (newone->portnumber)))
	{
	    pose = position;
            break;
	}
	    head = head->next;
	}
	//printf("position in search %d\n",pose);
	return pose;
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//add the exist number in the node
void additioncount(node* first, int position, node* newone)
{
//printf("addition is called\n");
    node* head = first; 
    for (int i = 0; i<position - 1; i++) {
	head = head->next;
	}
    head->count = head->count + newone->count;
    head->timenumber = head->timenumber + newone->timenumber;
    free(newone);//you should be careful zheli

};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
void showmap(node* first)
{
	node* head = first;

	do {
		printf("ip: %s        port:%d    total payload: %d  timenumber:%d   \n", head->ipaddress, head->portnumber, head->count, head->timenumber);
		int average = head->count / head->timenumber;
		printf("average  payload:%d\n", average);
		//searchserviceport(head->portnumber);//add port cotent
		if (head->next == NULL) {
			break;
		}
		head = head->next;

	} while (1);



};

*/



//#endif /* hashmap_h */
