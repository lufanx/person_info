//
//  person_mysql.h
//  xcode_person_info
//
//  Created by 凡路 on 2017/8/27.
//  Copyright © 2017年 凡路. All rights reserved.
//

#ifndef person_mysql_h
#define person_mysql_h


#include "init.h"

#define CONFIG 100

#include "/usr/local/Cellar/mysql/5.7.19/include/mysql/mysql.h"
//#include "mysql.h"

struct mysql_config{
	char database[CONFIG];
	char info_table[CONFIG];
	char user_register[CONFIG];
};

void insert_mysql_register(struct user *user_info, struct mysql_config *mysql_config_info);
void insert_mysql(struct mysql_config *insert_info, User *user_info);
struct mysql_config *read_mysqlconfig(struct mysql_config *info);
//void mysql_operate(User *user_info);

#endif /* person_mysql_h */
