#include "cJSON.h"
#include "deal_api.h"
#include "write_log.h"
#include "fixed_value.h"
#include "dbhelper.h"
/*******************************************************************************
*  func desc:   init_mysql_conn
*  input param: void
*  out   param: g_mysql_conn
*  retun value: void
********************************************************************************/
void init_mysql_conn(void** g_mysql_conn)
{
    if (NULL == g_mysql_conn)
    {
        return;
    }   
    if (NULL == *g_mysql_conn)
    {
        *g_mysql_conn = InitDbCon2(MYSQL_LOCAL, MYSQL_USER, MYSQL_PASSWD, 
            MYSQL_PORT, MYSQL_DATABASE);    
    }
    return ;
}



int get_device_list_from_mysql(char* packet)
{
    if (NULL == packet)
    {
        return -1;
    }
    char sql_str[MAX_LEN_SQL_STR]={0};
    struct DbResult *dbResult = NULL;
    int ret = 0;
    cJSON* device_list = NULL;
    device_list = cJSON_CreateObject();
    cJSON_AddNumberToObject(device_list,STR_TYPE,TYPE_DEVICE_LIST_RSP);
    /*查询pwd*/
    void *g_mysql_conn = NULL;
    init_mysql_conn(&g_mysql_conn);
    if(NULL == g_mysql_conn)
    {
        write_log(LOG_ERROR,"connect mysql error");
        return -1;
    }    
    snprintf(sql_str, sizeof(sql_str),SQL_SELECT_DEVICE_LIST);
    write_log(LOG_DEBUG,"%s",sql_str);
    if (NULL != g_mysql_conn)
    {
        //查pwd
        dbResult = CreateDbResult();
        ret = db_QuerySql(g_mysql_conn, dbResult, sql_str);//querys
        write_log(LOG_DEBUG,"g not null %d dbresult %p",ret,dbResult);
        if (1 != ret)
        {
            if (dbResult)
            {
                FreeDbResult(dbResult);
                dbResult = NULL;
            }
            CloseDbCon(g_mysql_conn);
            g_mysql_conn = NULL;
            return -1;
        }
        if (NULL != dbResult && dbResult->nrow > 0)
        {
            int row = 0;
            for (row = 0; row < dbResult->nrow; row++)
            {
                cJSON* list = NULL;
                char tempname[LISTENQ] = {0};
                snprintf(tempname,sizeof(tempname),"%d",row);
                list = cJSON_AddObjectToObject(device_list,tempname);
                //循环遍历select结果每一行
                if (NULL != dbResult->rows[row][0])
                {
                    //friend_id
                    cJSON_AddNumberToObject(list,STR_ID,atoi(dbResult->rows[row][0]));
                }
                if (NULL != dbResult->rows[row][1])
                {
                    //friend_name
                    cJSON_AddStringToObject(list,STR_NAME,dbResult->rows[row][1]);  
                }
                if (NULL != dbResult->rows[row][2])
                {
                    //remark
                    cJSON_AddNumberToObject(list,STR_VALTAGE,atoi(dbResult->rows[row][2]));
                }
                if (NULL != dbResult->rows[row][3])
                {
                    cJSON_AddNumberToObject(list,STR_POWER,atoi(dbResult->rows[row][3]));
                }   
                if (NULL != dbResult->rows[row][4])
                {
                    cJSON_AddNumberToObject(list,STR_STATE,atoi(dbResult->rows[row][4]));
                }
                cJSON_AddNumberToObject(list,STR_ELECTRICITY,atoi(dbResult->rows[row][3]) / atoi(dbResult->rows[row][2]));
            }
            cJSON_AddNumberToObject(device_list,STR_NUM,dbResult->nrow);
            strncpy(packet,cJSON_Print(device_list),MAXLINE); //get string from json
            FreeDbResult(dbResult);
            dbResult = NULL; 
        }
        else
        {
            CloseDbCon(g_mysql_conn);
            g_mysql_conn = NULL;
            return -1;
        }
        if (dbResult)
        {
            FreeDbResult(dbResult);
            dbResult = NULL; 
        }
        CloseDbCon(g_mysql_conn);
        g_mysql_conn = NULL;
    }//mysqlconn

}


/*
*name:write_data_to_socket_fd(void* data,int data_len)
*inputparam:data,data_len
*return: -1:deal error other:send bit nums 
*describe:write to fd,if write success return bit nums.else return -1
*/
int write_data_to_socket_fd(int fd,void* data,int data_len)
{
    if (NULL == data || 0 == data_len)
    {
        return -1;
    }
    return write(fd,data,data_len);
    return 0;
}


int client_request_deal(int fd,char* data,int data_len)
{
    if (NULL == data || 0 == data_len)
    {
        return 0;
    }
    //从data中解析json结构
    cJSON *json = cJSON_Parse(data);
    cJSON *node = NULL;
    //cJSON_GetObjectItem 根据key来查找json节点，如果有返回非空
    node = cJSON_GetObjectItem(json,STR_TYPE);
    int type = -1;
    if (NULL == node)
    {
        //get message type failed;
        write_log(LOG_ERROR,"json node type is null");
    }
    else
    {
        if (node->type == cJSON_Number)
        {
            //get message type success
            type = node->valueint;
            write_log(LOG_INFO,"type:%d",node->valueint);
        }
    }
    char buf[MAXLINE] = {0};
    switch (type)
    {
    case TYPE_DEVICE_LIST_REQ: 
        get_device_list_from_mysql(buf);
        write_data_to_socket_fd(fd,buf,strlen(buf));
        break;
    default:
        break;
    }
    return 0;

}


