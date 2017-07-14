//
//  goouthashmap.h
//  hashmap
//
//  Created by Hongchao Ma on 2016-04-20.
//  Copyright © 2016 Hongchao Ma. All rights reserved.
//

#include "comeinhashmap.h"
node* gooutfirstnode;
node* gooutlastnode;
int gooutnumber = 1;

void gooutinsert(node* newone)
{
// printf("insert is called\n");
    gooutlastnode->next = newone;
    gooutlastnode = newone;
}


void goouthashmapfunction(char* ip, int paylaod, int port,int protocalnumber)
{
    node* newone_2 = initialize();
    //++++++++++++++++++++++++++++++++++++++++++++++
    if (protocalnumber==6)
    {
        strcpy(newone_2->transitionprotocal, "TCP");
    }
    if (protocalnumber==17)
    {
        strcpy(newone_2->transitionprotocal, "UDP");
    }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++
    strcpy(newone_2->ipaddress, ip);
    newone_2->count = paylaod;
    newone_2->portnumber = port;
    int position_2 = search(gooutfirstnode, newone_2);
    if (position_2>0) {
	additioncount(gooutfirstnode, position_2, newone_2);
    }
    if (position_2 == 0) {
        gooutinsert(newone_2);
	gooutnumber++;
    }
}
//#endif /* goouthashmap_h */
