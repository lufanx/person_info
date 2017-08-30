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


void
mysql_operate(User *user_info) {

    MYSQL m_conn;
    int ret;
    //int id = 1;
    
    char sql_insert[300];
    
    sprintf(sql_insert, "insert into person_info (id, name, sex, age, password, address) values('%d', '%s', '%s', '%d', '%s', '%s')", user_info->user_id, user_info->user_name, user_info->user_sex, user_info->user_age, user_info->user_password, user_info->user_address);
    
    mysql_init(&m_conn);
    if(mysql_real_connect(&m_conn, "localhost", "root", "fl1328", "person_bank", 0, NULL, 0)) {
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

