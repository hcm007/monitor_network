//
//  port.h
//  hashmap
//
//  Created by Hongchao Ma on 2016-04-21.
//  Copyright © 2016 Hongchao Ma. All rights reserved.
//

#include"hashmap.h"
#include <math.h>
#define length_file 60// in order to read the file

struct portserve
{
    int port;
    char serve[length];
    struct portserve* next;

};

typedef struct portserve servertable;
//return the header point to the table
servertable* firstservertablenode;
servertable* lastservertablenode;
//*********************************************************
servertable* onlinegamefirstnode;
servertable* onlinegamelastnode;

//**********************************************************



servertable* init()
{
    servertable* node=(servertable*) malloc(sizeof(servertable));
    node->port=0;
    strcpy(node->serve, "");
    node->next=NULL;
    return node;
};



void insertable(servertable* node)
{

    lastservertablenode->next=node;
    lastservertablenode=node;

};


void insertable_1(int port,char* ser)
{
    servertable* node=init();
    node->port=port;
    strcpy(node->serve, ser);
    node->next=NULL;
    insertable(node);
}




//**********************************************************


void getonlinegameportnumber()
{

    onlinegamefirstnode = init();
    onlinegamelastnode = onlinegamefirstnode;

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    FILE *onlinegame_file;
    char *filename_onlinegame = "C:\\Users\\Administrator\\Desktop\\QTproject\\TableView\\onlinegameport.txt";
    if ((onlinegame_file= fopen(filename_onlinegame, "r+")))
    {
        printf("succedd\n");
    }
    else
    {
        printf("fail\n");

    }
    char StrLine[length_file];
    while (!feof(onlinegame_file))
    {
        //++++++++read the port number++++++++++++++++++++++++++++++++++++++++++++
        fgets(StrLine, length_file, onlinegame_file);  //读取一行
        char space = ' ';
        int i = 0;
        int number = 0;
        while ((StrLine[i] != space) && (StrLine[i] != '\t'))
        {
            i++;

        }
        //printf("%d   ", i);
        for (int j = 0; j < i; j++)
        {
            int record = StrLine[j];
            record = record - 48;

            number += record*pow(10, i - j - 1);

        }


        //+++++++++++++ the port number ++++++++++++++++++++++++++++++++++++++++++
        char nextline = '\n';
        int count = i;
        while (((StrLine[count] != nextline) && ((StrLine[count] != space)))) {

            count++;

        }

        char application_file[length] = "";

        for (int k = i + 1; k<count; k++) {
            application_file[k - i - 1] = StrLine[k];

        }
        //printf("%s    ", application_file);
        //number and application_file is useful
        //printf("%s", StrLine); //输出
        servertable* node = init();


        node->port = number;
        strcpy(node->serve, application_file);
        node->next = NULL;
        onlinegamelastnode->next = node;
        onlinegamelastnode = node;



    }//respond to the while(big one)







};




//**********************************************************
//retrun 0 represent find it in onlinegameport return -1 represent didnot find it

int searchonlinegameport(int port_x)
{
    int findit=-1;
    servertable* headofonlinegameport=onlinegamefirstnode;
    while(headofonlinegameport->next!=NULL)
    {

        if(headofonlinegameport->port==port_x)
        {
            findit=0;
            break;
        }

      headofonlinegameport=headofonlinegameport->next;
    }

    return findit;


};
//**********************************************************



//******************************************************












































void getservertable()
{
    //int port_1[]={80,443,2869,843,53,68,137,138,1900,17500,5353};
   // char service[][length]={"http:www","HTTPS","SSDP","flash socket","DNS","bootp","NETbios","NETbios","SSDP","Crazy TCP","DNS"};
    firstservertablenode=init();
    lastservertablenode=firstservertablenode;

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	FILE *portnumber_file;
    char *filename= "C:\\Users\\Administrator\\Desktop\\QTproject\\TableView\\portnumber.txt";
	if ((portnumber_file = fopen(filename, "r+")))
	{
		printf("chenggongla\n");
	}
	else
	{
		printf("buxing\n");

	}
	char StrLine[length_file];
	while (!feof(portnumber_file))
	{
		//++++++++read the port number++++++++++++++++++++++++++++++++++++++++++++
		fgets(StrLine, length_file, portnumber_file);  //读取一行
		char space = ' ';
		int i = 0;
		int number = 0;
		while ((StrLine[i] != space) && (StrLine[i] != '\t'))
		{
			i++;

		}
		//printf("%d   ", i);
		for (int j = 0; j < i; j++)
		{
			int record = StrLine[j];
			record = record - 48;

			number += record*pow(10, i-j-1);
			
		}

		//printf("%d      ", number);


		//printf("     ");

		//+++++++++++++ the port number ++++++++++++++++++++++++++++++++++++++++++
		char nextline = '\n';
		int count = i;
		while (((StrLine[count] != nextline) && ((StrLine[count] != space)))) {

			count++;

		}

		char application_file[length] = "";

		for (int k = i + 1; k<count; k++) {
			application_file[k - i - 1] = StrLine[k];

		}
		//printf("%s    ", application_file);
		//number and application_file is useful
		//printf("%s", StrLine); //输出
		servertable* node = init();


		node->port=number;
		strcpy(node->serve,application_file);
		node->next = NULL;
		insertable(node);



	}//respond to the while(big one)
	 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++












	

   /*
    for (int i=0; i<11; i++) {
        
        servertable* node=init();
        //node->port=port_1[i];
       // strcpy(node->serve, service[i]);
        node->next=NULL;
        insertable(node);
    
    }
   */


};

void showservertable()
{
    servertable* head=firstservertablenode;
    do {
        printf("port:%d     servetype:%s\n",head->port,head->serve);
        if (head->next==NULL) {
            break;
        }
        head=head->next;
        
    } while (1);

}

char* searchserviceport(int port)
{

    servertable* head=firstservertablenode;
    char serveport[length]="NO";
    while (1)
    {
        if (port==head->port) {
            strcpy(serveport, head->serve);
            break;
        }
		if (head->next==NULL)
		{
			break;
		}
        head=head->next;
        
    };


    //printf("the serve port is %s\n",serveport);

	return serveport;


}


void showmap(node* first)
{
	node* head = first;

	do {

		strcpy(head->application,searchserviceport(head->portnumber));//add port cotent




		printf("ip: %s        port:%d     application:%s  transitinprotocal:%s \n", head->ipaddress, head->portnumber,head->application,head->transitionprotocal);
		int average = head->count / head->timenumber;
		//printf("average  payload:%d\n", average);
		
		if (head->next == NULL) {
			break;
		}
		head = head->next;

	} while (1);



};

