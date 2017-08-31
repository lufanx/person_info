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

#define MAX_LINE 100

void mysql_operate(User *user_info, const char *key_database, const char *key_table);

void
read_mysqlconfig(User *user_info) {

	FILE *pf;
	char fline[MAX_LINE];
	int fsize = 0;
	char delims[] = "=";
	char *result = NULL;
	int select_values = 0;
	char *key_database = NULL;
	char *key_table = NULL;
	int check_file = 0;

	pf = fopen("mysql_config", "r");
	if(pf == NULL) {
		fprintf(stderr, "read mysql config failed!\n");
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
		while(!feof(pf)) {
			fgets(fline, MAX_LINE, pf);
			check_file += 1;
			if(check_file == 3) {
				break;
			}
			result = strtok(fline, delims);
			while(result != NULL) {
				if(select_values == 1) {
					key_database = result;
				}
				if(select_values == 3) {
					key_table = result;
				}
				select_values += 1;
				result = strtok(NULL, delims);
			}
		}

	}
	fclose(pf);
	mysql_operate(user_info, key_database, key_table);
	return;
}


void
mysql_operate(User *user_info, const char *key_database, const char *key_table) {

    MYSQL m_conn;
    int ret;
    //int id = 1;
    
    char sql_insert[300];
    
    sprintf(sql_insert, "insert into '%s' (id, name, sex, age, password, address) values('%d', '%s', '%s', '%d', '%s', '%s')", key_table, user_info->user_id, user_info->user_name, user_info->user_sex, user_info->user_age, user_info->user_password, user_info->user_address);
    
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

