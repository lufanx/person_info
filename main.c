//
//  main.c
//  test_xcode
//
//  Created by 凡路 on 2017/8/21.
//  Copyright © 2017年 凡路. All rights reserved.
//


#include "init.h"
#include "person_mysql.h"

//struct par{
//    char *name;
//    char *sex;
//    const char *mysql_config;
//    int age;
//};

int select_menu(struct mysql_config*);


void
user_register(struct mysql_config *mysql_config_info) {
	struct user user_info;

	memset(&user_info, 0, sizeof(user_info));

	printf("Please stdin your user_name:");
	scanf("%s", user_info.user_name);
	printf("Please stdin your user_password:");
	scanf("%s", user_info.user_password);

	printf("%s\n", user_info.user_name);
	printf("%s\n", user_info.user_password);

	insert_mysql_register(&user_info, mysql_config_info);
	
	return;
}

void
sign_in(struct mysql_config *sign_in) {

	char name[10];
	char password[7];
	
	printf("Please stdin your user_name:");
	scanf("%s", name);
	printf("Please stdin your user_password:");
	scanf("%s", password);

	select_mysql_sign_in(sign_in, name, password);
	
	return;
}

void
alter_table_queue(struct mysql_config *alter) {
	
	char queue_name[10];
	char queue_type[15];

	printf("Please stdin your queue name:");
	scanf("%s", queue_name);
	printf("Please stdin your queue type:");
	scanf("%s", queue_type);

	printf("%s\n", queue_name);
	printf("%s\n", queue_type);

	alter_table(alter, queue_name, queue_type);

	return;
}

void
insert_info(struct mysql_config *insert_info) {

    User user_info;
	char *id;
    
    memset(&user_info, 0, sizeof(user_info));

	id = return_id(insert_info);
	printf("mysql laster id = %s\n", id);
    
    printf("New user register function:\n");
    printf("Please stdin your userid must is laster id+1:");
    scanf("%d",&user_info.user_id);
    printf("Please stdin your username:");
    scanf("%s",user_info.user_name);
    printf("Please stdin your usersex:");
    scanf("%s", user_info.user_sex);
    printf("Please stdin your userpassword:");
    scanf("%s",user_info.user_password);
    printf("Please stdin your useraddress:");
    scanf("%s",user_info.user_address);
    printf("Please stdin your userage:");
    scanf("%d", &user_info.user_age);
    printf("Please stdin your date:");
    scanf("%s", user_info.user_date);
    
    printf("This your user info:\n");
    printf("user_name: %s\n", user_info.user_name);
    printf("user_address: %s\n", user_info.user_address);
    printf("user_age: %d\n", user_info.user_age);
    
    insert_mysql(insert_info, &user_info);
    
    return;
}

static int
menu(struct mysql_config *mysql_config_info) {

	int ret;

    printf("Select menu:\n");
    
    printf("1: new user register.\n");
    printf("2: sign in.\n");
	printf("3: insert your info.\n");
	printf("4: alter table queue.\n");
	printf("5: sign out.\n");

	ret = select_menu(mysql_config_info);
	if(ret == -1) {
		return -1;
	}
	return 1;
}

int
select_menu(struct mysql_config *mysql_config_info) {
    
    int number = 0;

    printf("#########\n");
    printf("Please select: ");
    scanf("%d", &number);
    
    switch(number) {
        case 1:
            user_register(mysql_config_info);
            break;
		case 2:
			sign_in(mysql_config_info);
			break;
		case 3:
			insert_info(mysql_config_info);
			break;
		case 4:
			alter_table_queue(mysql_config_info);
			break;
		case 5:
			return -1;
        default:
            fprintf(stderr, "Please select true number:\n");
            return -1;
    }
	menu(mysql_config_info);
    
    return 0;
}

static void
usage(const char *parse_name) {

    printf("%s, [options]", parse_name);
    printf("\n");
    printf("options:");
    printf("\n");
    
    printf("-n     person_info_name\n");
    printf("-s     person_info_sex\n");
    printf("-a     person_info_age\n");
    printf("-c     person_info_mysql_config\n");

}

static int
parse_argc(int argc, char *argv[], struct par *get_person_info) {

    int op;
    
    memset(get_person_info, 0, sizeof(*get_person_info));

	if(argc <= 1) {
		printf("your stdin parameter too less!\n");
		usage(argv[0]);
		return -1;
	}
    
    while((op = getopt(argc, argv, "n:s:a:")) != -1) {
        switch(op) {
        case 'n':
            get_person_info->name = optarg;
                //printf("name = %s\n", get_person_info->name);
            break;
        case 's':
            get_person_info->sex = optarg;
                //printf("sex = %s\n", get_person_info->sex);
            break;
        case 'a':
             get_person_info->age = atoi(optarg);
                //get_person_info->age = age;
                //printf("age = %d\n", get_person_info->age);
            break;
		//case 'c':
	    // 	get_person_info->mysql_config = optarg;
	    // 		printf("mysql_config = %s\n", get_person_info->mysql_config);
	    // break;
        default:
            fprintf(stderr, "invalid parse!\n");
            usage(argv[0]);
            return -1;
        }
    }
    return 0;
}

int
main(int argc, char **argv)
{

    int rc;
	int select_ret;
    struct par person_info;
	struct mysql_config *mysql_config_info;
	struct mysql_config info;
    
    memset(&person_info, 0, sizeof(person_info));

    rc = parse_argc(argc, argv, &person_info);
    if(rc != 0) {
        return rc;
    }

	mysql_config_info = read_mysqlconfig(&info);
    
    select_ret = menu(mysql_config_info);
	if(select_ret == -1) {
		return -1;
	}
    
    return 0;
    
}
