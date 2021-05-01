#ifndef _DEAL_API_H_
#define _DEAL_API_H_

#define LISTENQ 1024

#define MAXLINE 4096

#define MAX_LEN_SQL_STR 1024

/************************mysql macro********************************************/
#define MYSQL_LOCAL                 "127.0.0.1"
#define MYSQL_USER                   "root"
#define MYSQL_PASSWD              "Z001221z"
#define MYSQL_DATABASE           "management" 
#define MYSQL_PORT        3306

#define SQL_SELECT_DEVICE_LIST "SELECT `id`, `name`, `voltage`, `power`,`state` FROM `device_list`"




int client_request_deal(int fd,char* data,int data_len);

#endif