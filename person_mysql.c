//
//  person_mysql.c
//  xcode_person_info
//
//  Created by 凡路 on 2017/8/27.
//  Copyright © 2017年 凡路. All rights reserved.
//

#include "person_mysql.h"
#include "init.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024


struct mysql_config *
read_mysqlconfig(struct mysql_config *info) {

	FILE *pf;
	char fline[MAX_LINE] = "";
	char *result;
	char *delims = "=";
	int n = 0;
	char *p = NULL;
	char *q = NULL;
	char *k = NULL;
	char *m = NULL;
	int fsize = 0;

	pf = fopen("mysql_config", "r");
	if(pf == NULL) {
		fprintf(stderr, "read config failed!\n");
		return NULL;
	}

	fseek(pf, 0, SEEK_END);
	fsize = ftell(pf);
	printf("mysql_config file size is %d\n", fsize);
	if(!fsize) {
		fprintf(stderr, "this mysql_config file is NULL\n");
		return NULL;
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
					strncpy(info->database, result, CONFIG);
					p = info->database;
					while(*p != '\n' && *p != ' ') {
						p++;
					}
					*p = '\0';
				}
				if(n == 3) {
					strncpy(info->info_table, result, CONFIG);
					q = info->info_table;
					while(*q != '\n' && *q != ' ') {
						q++;
					}
					*q = '\0';
				}
				if(n == 5) {
					strncpy(info->user_register, result, CONFIG);
					k = info->user_register;
					while(*k != '\n' && *k != ' ') {
						k++;
					}
					*k = '\0';
				}
				result = strtok(NULL, delims);
				n += 1;
			}
		}
	}
	printf("###########\n");
	printf("%s\n", info->database);
	printf("%s\n", info->info_table);
	printf("%s\n", info->user_register);
	printf("###########\n");

	fclose(pf);
	return info;
}

void
insert_mysql_register(struct user *user_info, struct mysql_config *mysql_config_info) {

    MYSQL m_conn;
    int ret;
    int id = 1;
    char sql_insert[300];

	printf("register = %s\n", mysql_config_info->user_register);
	printf("database = %s\n", mysql_config_info->database);
    
    sprintf(sql_insert, "insert into %s (id, name,password) values('%d', '%s', '%s')", mysql_config_info->user_register, id, user_info->user_name, user_info->user_password);
    mysql_init(&m_conn);
    if(mysql_real_connect(&m_conn, "localhost", "root", "fl1328", mysql_config_info->database, 0, NULL, 0)) {
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

void
insert_mysql(struct mysql_config *insert_info, User *user_info) {

    MYSQL m_conn;
    int ret;
    char sql_insert[300];

    
    sprintf(sql_insert, "insert into %s (id, name, sex, age, password, address) values('%d', '%s', '%s', '%d', '%s', '%s')", insert_info->info_table, user_info->user_id, user_info->user_name, user_info->user_sex, user_info->user_age, user_info->user_password, user_info->user_address);
    mysql_init(&m_conn);
	printf("&&&&&&&&&&&&&&\n");
    if(mysql_real_connect(&m_conn, "localhost", "root", "fl1328", insert_info->database, 0, NULL, 0)) {
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

