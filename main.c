//
//  main.c
//  test_xcode
//
//  Created by 凡路 on 2017/8/21.
//  Copyright © 2017年 凡路. All rights reserved.
//


#include "init.h"
#include "person_mysql.h"

struct par{
    char *name;
    char *sex;
    int age;
};

void
user_register() {
    User user_info;
    
    memset(&user_info, 0, sizeof(user_info));
    
    printf("New user register function:\n");
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
    
    printf("This your user info:\n");
    printf("user_name: %s\n", user_info.user_name);
    printf("user_address: %s\n", user_info.user_address);
    printf("user_age: %d\n", user_info.user_age);
    
    mysql_operate(&user_info);
    
    return;
}

int
select_menu() {
    
    int number = 0;
    printf("Select menu:\n");
    
    printf("1: new user register.\n");
    printf("2: sign in.\n");
    
    printf("#########\n");
    printf("Please select: ");
    scanf("%d", &number);
    
    switch(number) {
        case 1:
            user_register();
            break;
        default:
            fprintf(stderr, "Please select true number:\n");
            return -1;
    }
    
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

}

int
parse_argc(int argc, char *argv[], struct par *get_person_info) {

    int op;
    
    memset(get_person_info, 0, sizeof(*get_person_info));
    
    while((op = getopt(argc, argv, "n:s:a:")) != -1) {
        switch(op) {
        case 'n':
            get_person_info->name = optarg;
                printf("name = %s\n", get_person_info->name);
            break;
        case 's':
            get_person_info->sex = optarg;
                printf("sex = %s\n", get_person_info->sex);
            break;
        case 'a':
             get_person_info->age = atoi(optarg);
                //get_person_info->age = age;
                printf("age = %d\n", get_person_info->age);
            break;
        default:
            fprintf(stderr, "invalid parse!\n");
            usage(argv[0]);
            return -1;
        }
    }
    return 0;
}

int
main(int argc, char *argv[]) {

    int rc;
    int menu_status;
    struct par person_info;
    
    memset(&person_info, 0, sizeof(person_info));
    
    menu_status = select_menu();
    if(menu_status) {
        return -1;
    }
    
    rc = parse_argc(argc, argv, &person_info);
    if(rc != 0) {
        return rc;
    }
    
    printf("%s is info:\n", person_info.name);
    printf("    name:%s\n", person_info.name);
    printf("    sex:%s\n", person_info.sex);
    printf("    age:%d\n", person_info.age);
    printf("\n");
    
    return 0;
    
}
