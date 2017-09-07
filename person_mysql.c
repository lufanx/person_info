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

char *
return_id(struct mysql_config *return_id) {
	MYSQL m_conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int ret;
	int i;
	char *id = NULL;
	char sql_return_id[100];

	sprintf(sql_return_id, "select id from %s order by id desc limit 1", return_id->info_table);
	mysql_init(&m_conn);
	if(mysql_real_connect(&m_conn, "localhost", "root", "fl1328", return_id->database, 0, NULL, 0)) {
		printf("mysql connect success!\n");
		ret = mysql_query(&m_conn, sql_return_id);
		if(!ret) {
			printf("mysql return id success!\n");
			res = mysql_store_result(&m_conn);
			while((row = mysql_fetch_row(res))) {
				for(i = 0; i < res->field_count; i++) {
					printf("$$$$$$$$$\n");
					printf("%s\n", row[i]);
					id = row[i];
					printf("$$$$$$$$$\n");
				}
			}
		}
		else {
			fprintf(stderr, "mysql return i failed!\n");
			mysql_close(&m_conn);
			return NULL;
		}
	}
	else{
		fprintf(stderr, "mysql connect failed!\n");
	}

	mysql_close(&m_conn);
	
	return id;
	
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

    
    sprintf(sql_insert, "insert into %s (id, name, sex, age, password, address, time) values('%d', '%s', '%s', '%d', '%s', '%s', '%s')", insert_info->info_table, user_info->user_id, user_info->user_name, user_info->user_sex, user_info->user_age, user_info->user_password, user_info->user_address, user_info->user_date);
    mysql_init(&m_conn);
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

/*
void
mysql_connect(struct mysql_config *alter_connect) {

	MYSQL m_conn;

	mysql_init(&m_conn);
	if(mysql_real_connect(&m_conn, "localhost", "root", "fl1328", alter_connect->database, 0, NULL, 0)) {
		printf("mysql connect!\n");
	}
	else {
		fprintf(stderr, "mysql connect failed!\n");
		mysql_close(&m_conn);
		return;
	}

	mysql_
	return;
}
*/


void
select_mysql_sign_in(struct mysql_config *sign_in, const char *user_name, const char *user_password) {

	MYSQL m_conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int ret;
	int i = 0;
	char sql_select[100];
	int status = 0;

	sprintf(sql_select, "select name from %s where password = %s", sign_in->user_register, user_password);
	mysql_init(&m_conn);
	if(mysql_real_connect(&m_conn, "localhost", "root", "fl1328", sign_in->database, 0, NULL, 0)) {
		printf("mysql connect success!\n");
		ret = mysql_query(&m_conn, sql_select);
		if(!ret) {
			printf("select data success!\n");
			res = mysql_store_result(&m_conn);
			while((row = mysql_fetch_row(res))) {
				for(i = 0; i < res->field_count; i++) {
					printf("$$$$$$$$$\n");
					printf("%s\n", row[i]);
					printf("len = %ld\n", strlen(row[i]));
					printf("$$$$$$$$$\n");
					if(!strcmp(user_name, row[i])) {
						printf("_________\n");
						status = 1;
					}
				}
			}
			if(status == 1) {
				printf("########\n");
				printf("your user_name and user_password is ok!\n");
				printf("########\n");
			}
			else {
				fprintf(stderr, "your user_name or your user_password is error!\n");
			
			}
			mysql_free_result(res);
		}
		else {
			fprintf(stderr, "select data failed!\n");
		}
	}
	else {
		fprintf(stderr, "mysql connect failed!\n");
		mysql_close(&m_conn);
	}
	
	mysql_close(&m_conn);
	return;
}

void
alter_table(struct mysql_config *alter, char *queue_name, char *queue_type) {
	
	char alter_table_queue[100];
	int ret;
	MYSQL m_conn;

	//mysql_init(&m_conn);

	printf("8888888888888\n");
	printf("%s\n", queue_name);
	printf("%s\n", queue_type);
	sprintf(alter_table_queue, "alter table %s add column %s %s", alter->info_table, queue_name, queue_type);
	printf("===========\n");
	mysql_init(&m_conn);
	if(mysql_real_connect(&m_conn, "localhost", "root", "fl1328", alter->database, 0, NULL, 0)) {
		printf("mysql connect!\n");
		ret = mysql_query(&m_conn, alter_table_queue);
		if(!ret) {
			printf("alter table success!\n");
		}
		else {
			fprintf(stderr, "alter table failed!\n");
			mysql_close(&m_conn);
			return;
		}
	}
	//printf("------------\n");
	else {
		fprintf(stderr, "mysql connect failed!\n");
		mysql_close(&m_conn);
		return;
	}
	mysql_close(&m_conn);

	return;
}

