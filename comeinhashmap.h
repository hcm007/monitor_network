//
//  comeinhashmap.h
//  hashmap
//
//  Created by Hongchao Ma on 2016-04-20.
//  Copyright © 2016 Hongchao Ma. All rights reserved.
//

#include "port.h"
node* comeinfirstnode;
node* comeinlastnode;
int comeinnumber = 1;
void comeinsert(node* newone)
{
	//printf("insert is called\n");
    comeinlastnode->next = newone;
    comeinlastnode = newone;
};
void comeinhashmapfunction(char* ip, int paylaod, int port)
{
// printf("comein is called \n");
    node* newone_1 = initialize();
    strcpy(newone_1->ipaddress, ip);
    newone_1->count = paylaod;
    newone_1->portnumber = port;
    int position_1 = search(comeinfirstnode, newone_1);
    if (position_1>0) {
	additioncount(comeinfirstnode, position_1, newone_1);
    }
    if (position_1 == 0) {
	comeinsert(newone_1);
	comeinnumber++;
    }

};





