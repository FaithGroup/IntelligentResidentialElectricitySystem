#ifndef __DB__HELPER__HEADER__
#define __DB__HELPER__HEADER__

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <search.h>
#include <mysql.h>

#define MYSQL_MAX_SQL_LEN 4096 //数据库操作语句的长度

/* 记录数据库结果集的结构体*/
struct DbResult
{
char*** rows;
unsigned long nrow;
unsigned long ncol;
char**headers;//reserved for header name
void * resource;//used for holding data.
};

/*初始化MYSQL链接*/
void* InitDbCon2(const char *host, const char *user,const char *passwd, int port,const char *db);

/*释放结果集*/
void FreeDbResult(struct DbResult*dbResult);

/*创建结果集,已memset*/
struct DbResult*  CreateDbResult();


/*执行数据库查询语句*/
int db_QuerySql(void*conn,struct DbResult* dbResult,const char*sql,...);
int db_VQuerySql(void*conn,struct DbResult* dbResult,const char*sql,const va_list ap);


int HasError(void*conn);

/*执行数据库操作语句*/
int db_ExecSql(void* conn,const char*sql);

/*获取错误信息*/
const char* GetError(void*conn);

/*判断MYSQL链接*/
int ConnectedCon(void *conn);

/*关闭MYSQL链接*/
void CloseDbCon(void*conn);

#endif
