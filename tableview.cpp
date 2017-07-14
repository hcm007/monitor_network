#include "tableview.h"
#include "ui_tableview.h"
#include<QTime>
#include <pcap.h>
#include <conio.h>
#include"goouthashmap.h"
#include <Packet32.h>
#include <remote-ext.h>
#include <Win32-Extensions.h>
//*******
//******************
bool judge=false;
int tablelength=0;
#define numberofqueue 1048576//******************

//********************************

//***********************************

TableView::TableView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TableView)
{
    ui->setupUi(this);
}

TableView::~TableView()
{
    delete ui;
}
void TableView::initializetablewidget()
{
    ui->tableWidget->setColumnCount(4);
    QStringList m_Header;
    m_Header<<QString("IP")<<QString("Port")<<QString("Application")<<QString("T/UDP");
    ui->tableWidget->setHorizontalHeaderLabels(m_Header);
    ui->tableWidget->setWindowTitle("network analyze");
    connect(ui->closeButton,SIGNAL(clicked(bool)),this,SLOT(changejudge()));
    connect(ui->closeButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->okButton,SIGNAL(clicked(bool)),this,SLOT(touchOkButton()));
    ui->online->setText(tr("Correct"));
    ui->normal->setText(tr("Correct"));
    comeinfirstnode = initialize();
    comeinlastnode = comeinfirstnode;
    gooutfirstnode = initialize();
    gooutlastnode = gooutfirstnode;
    getservertable();
for(int i=0;i<1000;i++){
     ui->tableWidget->insertRow(i);
     ui->tableWidget->setItem(i,0,new QTableWidgetItem("0"));
     ui->tableWidget->setItem(i,1,new QTableWidgetItem("no"));
     ui->tableWidget->setItem(i,2,new QTableWidgetItem("no"));
     ui->tableWidget->setItem(i,3,new QTableWidgetItem("no"));
     ui->tableWidget->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
}
}
void TableView::changejudge()
{
    judge=true;
}
 void TableView::touchOkButton()
 {
//*****************************************************
    pcap_send_queue* onlinegamequeue=pcap_sendqueue_alloc(numberofqueue);
    pcap_send_queue* nomalqueue=pcap_sendqueue_alloc(numberofqueue);

//************************************************
    pcap_if_t *alldevs;
    pcap_if_t *d;
    int inum;
    int i = 0;
    pcap_t *adhandle;
    int res;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct tm *ltime;
    char timestr[16];
    struct pcap_pkthdr *header;
    const u_char *pkt_data;
    time_t local_tv_sec;
    u_int netmask;
    struct bpf_program fcode;
    char packet_filter[] = "ip";// "ip and tcp";
     //+++++++++++++++initialize the hash map (two)++++++++++++++++++
/*
         comeinfirstnode = initialize();
         comeinlastnode = comeinfirstnode;
         gooutfirstnode = initialize();
         gooutlastnode = gooutfirstnode;*/
         //getservertable();
//******************************
    getonlinegameportnumber();
//***************************
//+++++++++++++++++++++++++++++++++++++++++++++++++++++
 /* 获取本机设备列表 */
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
    {
        fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
        exit(1);
    }
         /* 打印列表 */
    for (d = alldevs; d; d = d->next)
    {
        i++;
    }
     inum = 1;
     if (inum < 1 || inum > i)
     {
          printf("\nInterface number out of range.\n");
             /* 释放设备列表 */
          pcap_freealldevs(alldevs);
             //return -1;
      }
         /* 跳转到已选中的适配器 */
      for (d = alldevs, i = 0; i< inum - 1; d = d->next, i++);
         /* 打开设备 */
         if ((adhandle = pcap_open(d->name,          // 设备名
             65536,            // 要捕捉的数据包的部分
                              // 65535保证能捕获到不同数据链路层上的每个数据包的全部内容
             PCAP_OPENFLAG_PROMISCUOUS,    // 混杂模式
             1000,             // 读取超时时间
             NULL,             // 远程机器验证
             errbuf            // 错误缓冲池
         )) == NULL)
         {
             //fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
             /* 释放设列表 */
             pcap_freealldevs(alldevs);
             //return -1;
         }


         //this is set filter
     //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

         if (pcap_datalink(adhandle) != DLT_EN10MB)
         {
             pcap_freealldevs(alldevs);
         }

         if (d->addresses != NULL)
             /* 获得接口第一个地址的掩码 */
             netmask = ((struct sockaddr_in *)(d->addresses->netmask))->sin_addr.S_un.S_addr;
         else
             /* 如果接口没有地址，那么我们假设一个C类的掩码 */
             netmask = 0xffffff;
         //编译过滤器
         if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) <0)
         {
            /* 释放设备列表 */
             pcap_freealldevs(alldevs);
         }

         //设置过滤器
         if (pcap_setfilter(adhandle, &fcode)<0)
         {
             //fprintf(stderr, "\nError setting the filter.\n");
             /* 释放设备列表 */
             pcap_freealldevs(alldevs);
         }

     //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

         //printf("\nlistening on %s...\n", d->description);
         /* 释放设备列表 */
         pcap_freealldevs(alldevs);
         /* 获取数据包 */
         int gengxin=0;
         //pcap_setmode(adhandle, MODE_STAT);//*******************************************
       //bool panduan=true;//******************************************************
         while ((res = pcap_next_ex(adhandle, &header, &pkt_data)) >= 0) {
             //++++
             if(judge)
             {break;
             }
             if (res == 0)
                 /* 超时时间到 */
                 continue;
     //*******************************************************************************************
             //**************************************************************************************
             //to calculate the bandwith
             static DWORD m_packetslen=0;
             static DWORD m_tickcount=0;
             static double m_speed=0.0;
             m_packetslen+=header->len;
             //if(panduan){
             if(GetTickCount()-m_tickcount>1000)
             {
                 m_speed=m_packetslen/1024.0;
                m_tickcount=GetTickCount();
                 m_packetslen=0;

                char buf[length_file];
                char* zifuchuan=gcvt(m_speed,5,buf);
                ui->bandwidth->setText(tr(zifuchuan));
               // printf("%f\n",m_speed);
           //pcap_setmode(adhandle, MODE_CAPT);
          // panduan=false;

             //}
}
          //********************************************************************************************
             //*******************************************************************************************
             /* 将时间戳转换成可识别的格式 */
             local_tv_sec = header->ts.tv_sec;
             ltime = localtime(&local_tv_sec);
             strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);
             //printf("%s,%.6d len:%d\n", timestr, header->ts.tv_usec, header->len);
             //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
              char originalmac[length] = "";//added in task 3
             for (int i = 6; i < 12; i++)
             {
                 int quzhi = pkt_data[i];
                   char shoulu[20] = "";

                   itoa(quzhi, shoulu, 16);
                   if (strlen(shoulu)==1)
                   {
                        char a[3] = "0";
                       strcpy(shoulu, strcat(a, shoulu));
                   }
                 if (i==11)
                 {
                     strcat(originalmac, shoulu);
                 }
                 else
                 {
                     strcat(originalmac, shoulu);
                     strcat(originalmac, ":");
                 }
             }
         //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
             int payload = pcap_snapshot(adhandle);
             char sourceip[length] = "";
             for (int i = 26; i < 30; i++)
             {
                 char shoulu[20] = "";
                 int a =pkt_data[i];
                 itoa(a, shoulu, 10);
                 if (i == 29)
                 {
                 }
                 else
                 {
                     strcat(shoulu, ".");
                 }
                 strcat(sourceip, shoulu);
             }
             //printf("souce ip : %s\n", sourceip);
              int sourceport_1 = pkt_data[34];
              int sourceport_2 = pkt_data[35];
              int sourceport = 256 * sourceport_1 + sourceport_2;
     //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

             char destinationip[length] = "";
             for (int i = 30; i < 34; i++)
             {
                 char shoulu[20] = "";
                 int a = pkt_data[i];
                 itoa(a, shoulu, 10);
                 if (i == 29)
                 {
                 }
                 else
                 {
                     strcat(shoulu, ".");
                 }
                 strcat(destinationip, shoulu);
             }
             //printf("destination ip : %s\n", destinationip);
              int destinationport_1 = pkt_data[36];
              int destinationport_2 = pkt_data[37];
              int destinationport = destinationport_1 * 256 + destinationport_2;

     //++++++++++++++++++++++++++++++++++++++++++++++

             //printf("orinal mac %s\n", originalmac);
             if (strcmp(thecomputer,originalmac)!=0)
             {
                 //printf("lai zi wai bian\n");
                 //hashmapfunction(sourceip, payload, originalmac, sourceport);
                 comeinhashmapfunction(sourceip, payload, sourceport);
             }
             if (strcmp(thecomputer,originalmac)==0)
             {
                 int transitprotocal = pkt_data[23];//new added

                 goouthashmapfunction(destinationip, payload, destinationport,transitprotocal);

                 //**************************************************************
                 if(searchonlinegameport(destinationport)==0)
                 {
                     if(pcap_sendqueue_queue(onlinegamequeue,header,pkt_data)==-1)
                         ui->online->setText(tr("buffer small"));
                 }

                 if(searchonlinegameport(destinationport)==-1)
                 {
                    if(pcap_sendqueue_queue(nomalqueue,header,pkt_data)==-1)
                         ui->normal->setText(tr("buffer small"));
                 }

                 //******************************************************
             }
     //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            // showmap(gooutfirstnode);
             node* head=gooutfirstnode;
             int countnumber=0;

while(head->next!=NULL){
       strcpy(head->application,searchserviceport(head->portnumber));
           ui->tableWidget->item(countnumber,0)->setText(tr(head->ipaddress));
           char pn[length];
           itoa(head->portnumber,pn,10);
           ui->tableWidget->item(countnumber,1)->setText(tr(pn));
           ui->tableWidget->item(countnumber,2)->setText(tr(head->application));
           ui->tableWidget->item(countnumber,3)->setText(tr(head->transitionprotocal));
           head=head->next;
           countnumber++;
}

QTime t;
t.start();
while (t.elapsed()<30) {
    QCoreApplication::processEvents();
}
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
         }//dui ying qian mian de while
         //return 0;
 }

//**********************************************


















