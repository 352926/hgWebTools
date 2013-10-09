#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define VERSION "v1.0"
#define AUTHOR "Change"
#define EMAIL "352926@qq.com"

char *l_opt_arg;
char* const short_options = "hur:v";
struct option long_options[] = {
    {"help",0,NULL,'h'},
    {"update",0,NULL,'u'},
    {"log",2,NULL,'l'},
    {"rev",1,NULL,'r'},
    {"version",0,NULL,'v'},
    {0,0,0,0},
};
void *pullNew();
void *help();

int main(int argc, char *argv[]){
    int c,j;
    while((c = getopt_long (argc, argv, short_options, long_options, NULL)) != -1){
        switch(c){
            case 'h':
                help();
                return 1;
                break;
            case 'u':
                pullNew();
                return 1;
                break;
            case 'r':
                l_opt_arg = optarg;
                printf("还在开发,%s!\n",l_opt_arg);
                return 1;
                break;
            case 'l':
                system("/usr/bin/hg log | head");
                return 1;
                break;
            case 'v':
                printf("Version:%s\n",VERSION);
                printf("Author:%c[%d;1m%s%c[0m<%s>\n",27,31,AUTHOR,27,EMAIL);
                return 1;
                break;
            default:
                help();
                return 1;
                break;
        }
    }
    help();
    return 0;
}

void *pullNew(){
    system("/usr/bin/hg update -r`hg pull > /dev/null && hg log --template '{rev} |{branches}|\n' | grep \"线上\" | head -1 | awk '{print $1}'` -C");
    system("/usr/bin/hg log --template '当前版本：{rev} 分支：{branches} 版本说明：{desc}\n' | grep \"线上\" | head -1");
    printf("谢谢使用!\n");
}

void *help(){
    printf("Hg网站发布小工具- Change\n\n");
    printf("  -v, --version                当前版本\n");
    printf("  -h, --help                   查看帮助\n");
    printf("  -u, --update                 发布至最新“线上”分支\n");
    printf("  -l, --log 123                查看123分支的文件变化\n");
    printf("  -r, --rev 123                更新至指定版本\n");
    printf("谢谢使用!\n");
}

