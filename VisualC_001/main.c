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

void testMysqlConnect(); // test connect to mysql server and do command
void testByteSwapInt32(int x);     // test swap all bytes of int number (reverse its bytes)
void testThread();  
void thread1();
void thread2();

int main(int argc, char* argv[]) {
   
    //testMysqlConnect();
    //testByteSwapInt32(0x12345678);
    testThread();



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

void testByteSwapInt32(int x)
{
    printf("\ndata before swapping : %08X", x);
    x = ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8)
        | (((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24));
    printf("\ndata after swapping  : %08X", x);
}

void testThread()
{

    HANDLE myhandle[2];

    myhandle[0] = (HANDLE)_beginthread(thread1, 0, NULL);
    myhandle[1] = (HANDLE)_beginthread(thread2, 0, NULL);

    WaitForSingleObject(myhandle[0], INFINITE);
    WaitForSingleObject(myhandle[1], INFINITE); 
    //CloseHandle(myhandle[0]);
    //FindClose(myhandle[1]); 

}

void thread1()
{
    for (size_t i = 0; i < 1000; i++)
    {
        printf("\nthread111: %d", i);
    }
}

void thread2()
{
    for (size_t i = 0; i < 1000; i++)
    {
        printf("\nthread222 %d", i);
    }
}
