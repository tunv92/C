#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>
#include <string.h> 
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <stdint.h>
#include <stddef.h>
#include <wchar.h>
#include <limits.h> 
#include <time.h>
#include <process.h> 
#include <mysql.h>

void testMysqlConnect();

int main(int argc, char* argv[]) {
   
    testMysqlConnect();


    return 0;
}

void testMysqlConnect()
{
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;
    char* server = "192.168.100.86";
    char* user = "mst";
    char* password = "tunguyenaz1"; /* set me first */
    char* database = "mstdb";
    conn = mysql_init(NULL);

    printf("MySQL client version: %s\n", mysql_get_client_info());

    /* Connect to database */
    if (!mysql_real_connect(conn, server,
        user, password, database, 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        //exit(1);
    }

    /* send SQL query */
    if (mysql_query(conn, "show tables")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        //exit(1);
    }
    res = mysql_use_result(conn);

    /* output table name */
    printf("MySQL Tables in mysql database:\n");
    while ((row = mysql_fetch_row(res)) != NULL)
        printf("%s \n", row[0]);


    /* close connection */
    mysql_free_result(res);
    mysql_close(conn);
}
