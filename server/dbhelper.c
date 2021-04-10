#include "dbhelper.h"

void* InitDbCon2(const char *host, const char *user,const char *passwd, int port, const char *db)
{
	MYSQL *con = malloc(sizeof(MYSQL));
 	mysql_init(con);  
	my_bool reconnect =1;
	mysql_options(con,MYSQL_OPT_RECONNECT,&reconnect);
 	if( mysql_real_connect(con,host,user,passwd,db, port, NULL, CLIENT_MULTI_STATEMENTS))
	{
            mysql_query(con,"set names utf8");
            return con;
	}
	free(con);
	return NULL;
}

void CloseDbCon(void*conn)
{
	if(conn)
	{
		mysql_close(conn);
		free(conn);
		conn = NULL;
	}
}

int ConnectedCon(void *conn)
{
    return mysql_ping(conn);
}

int db_ExecSql(void* conn,const char*sql)
{
	mysql_query(conn,"set names utf8");    
	if( mysql_query(conn, sql))
		return -1;
	return mysql_affected_rows(conn);
	
}


int HasError( void*conn)
{
//refer to:http://dev.mysql.com/doc/refman/5.1/zh/apis.html#mysql-error
	if(conn)
	{
		if(mysql_error(conn)[0] != '\0')
			return 1;

	}
	return 0;

}
const char* GetError(void*conn)
{
	if(conn)
		return mysql_error(conn);
	return "";
}


void FreeDbResult(struct DbResult*dbResult)
{
	if(dbResult)
	{
		if(dbResult->rows)
			free(dbResult->rows);
  		if(dbResult->resource)
			mysql_free_result(dbResult->resource);   
		if(dbResult->headers)
			free(dbResult->headers);
		free(dbResult);
	}
}

struct DbResult* CreateDbResult()
{
	struct DbResult *tmp = NULL;

	tmp = (struct DbResult *)malloc(sizeof(struct DbResult));
	
	if (NULL != tmp)
	{
		memset(tmp, 0, sizeof(struct DbResult));
	}
	
	return tmp;
}


int db_VQuerySql(void*conn,struct DbResult* dbResult,const char*sqlfmt,const va_list ap)
{
	char sql[MYSQL_MAX_SQL_LEN];
	vsprintf(sql,sqlfmt,ap);

	mysql_query(conn,"set names utf8");    
	int rt = mysql_query(conn,sql);
	if(rt)
	{
		return 0;
	}

	if(dbResult->rows != NULL) {
		free(dbResult->rows);
	}
	if(dbResult->headers != NULL) {
		free(dbResult->headers);
	}
	if(dbResult->resource != NULL) {
		mysql_free_result(dbResult->resource);
	}
	memset(dbResult, 0, sizeof(struct DbResult));
	
	MYSQL_RES*result = mysql_store_result(conn);
	if(!result)
		return 0;
	dbResult->nrow = mysql_num_rows(result);
	dbResult->ncol = mysql_num_fields(result);
	dbResult->rows = calloc(dbResult->nrow,sizeof(char**));
	dbResult->headers = calloc(dbResult->ncol,sizeof(char*));

	MYSQL_FIELD *fields  = mysql_fetch_fields(result);
	int i;
	for(i = 0; i < dbResult->ncol; i++)
	{
		dbResult->headers[i] = fields[i].name;
	}
	MYSQL_ROW row;	
	i = 0;
	while((row = mysql_fetch_row(result)))
	{
		dbResult->rows[i++] = row;
	}
	dbResult->resource = result;
	return 1;
}

int db_QuerySql(void*conn,struct DbResult* dbResult,const char*sqlfmt,...)
{
	va_list ap;
	va_start(ap,sqlfmt);
	int rt = db_VQuerySql(conn,dbResult,sqlfmt,ap);
	va_end(ap);
	return rt;
}


