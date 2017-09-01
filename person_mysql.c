//
//  person_mysql.c
//  xcode_person_info
//
//  Created by 凡路 on 2017/8/27.
//  Copyright © 2017年 凡路. All rights reserved.
//

#include "person_mysql.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define CONFIG 100

void mysql_operate(User *user_info, const char *key_database, const char *key_table);

void
read_mysqlconfig(User *user_info) {

	FILE *pf;
	char fline[MAX_LINE] = "";
	char *result;
	char *delims = "=";
	int n = 0;
	char database[CONFIG] = "";
	char table[CONFIG] = "";
	char *p = NULL;
	char *q = NULL;
	char *m = NULL;
	int fsize = 0;

	pf = fopen("mysql_config", "r");
	if(pf == NULL) {
		fprintf(stderr, "read config failed!\n");
		return;
	}

	fseek(pf, 0, SEEK_END);
	fsize = ftell(pf);
	printf("mysql_config file size is %d\n", fsize);
	if(!fsize) {
		fprintf(stderr, "this mysql_config file is NULL\n");
		return;
	}
	else {
		fseek(pf, 0, SEEK_SET);
		while(fgets(fline, MAX_LINE, pf) != NULL) {
			m = fline;
			if(*m == '#' || *m == '\n' || *m == '[') {
				continue;
			}
			result = strtok(fline, delims);
			while(result != NULL) {
				if(n == 1) {
					strncpy(database, result, CONFIG);
					p = database;
					while(*p != '\n' && *p != ' ') {
						p++;
					}
					*p = '\0';
				}
				if(n == 3) {
					strncpy(table, result, CONFIG);
					q = table;
					while(*q != '\n' && *q != ' ') {
						q++;
					}
					*q = '\0';
				}
				result = strtok(NULL, delims);
				n += 1;
			}
		}
	}

	fclose(pf);
	mysql_operate(user_info, database, table);
	return;
}


void
mysql_operate(User *user_info, const char *key_database, const char *key_table) {

    MYSQL m_conn;
    int ret;
    //int id = 1;
    char sql_insert[300];
    
    sprintf(sql_insert, "insert into %s (id, name, sex, age, password, address) values('%d', '%s', '%s', '%d', '%s', '%s')", key_table, user_info->user_id, user_info->user_name, user_info->user_sex, user_info->user_age, user_info->user_password, user_info->user_address);
    mysql_init(&m_conn);
    if(mysql_real_connect(&m_conn, "localhost", "root", "fl1328", key_database, 0, NULL, 0)) {
        printf("mysql connect success!\n");
        ret = mysql_query(&m_conn, sql_insert);
		if(!ret) {
			printf("mysql insert date success!\n");	
		}
		else {
			fprintf(stderr, "mysql insert failed!\n");
			mysql_close(&m_conn);
		}
    }
    else {
        fprintf(stderr, "mysql connect failed!\n");
    }
	mysql_close(&m_conn);
    

    return;
}

