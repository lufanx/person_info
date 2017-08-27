//
//  person_mysql.c
//  xcode_person_info
//
//  Created by 凡路 on 2017/8/27.
//  Copyright © 2017年 凡路. All rights reserved.
//

#include "person_mysql.h"



void
mysql_operate(User *user_info) {

    MYSQL m_conn;
    int ret;
    int id = 1;
    
    char sql_insert[100];
    
    sprintf(sql_insert, "insert into person_info values('%d', '%s', '%s', '%d', '%s', '%s')", id, user_info->user_name, user_info->user_sex, user_info->user_age, user_info->user_password, user_info->user_address );
    
    mysql_init(&m_conn);
    if(mysql_real_connect(&m_conn, "localhost", "root", "fl1328", "person_bank", 0, NULL, 0)) {
        printf("mysql connect success!\n");
        ret = mysql_query(&m_conn, sql_insert);
    }
    else {
        fprintf(stderr, "mysql connect failed!\n");
    }
    

    return;
}

