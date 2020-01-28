#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

enum{
    LenLine = 1024*500,
    MaxNums = 1024*500,
    LenCasesStr = 4, // Including '\n' and the null terminated
    LenBytesStr = 8, // Including '\n' and the null terminated 
};

struct Num_List{
    int num[MaxNums];
    int len;
};
typedef struct Num_List Num_List;

void save_code (Num_List* code, char* line){
    char* token;
    int i = 0;
    
    token = strtok(line, " ");
    while (token != NULL) {
        code->num[i] = atoi(token);
        i++;
        token = strtok(NULL, " ");
    }
}

Num_List encrypt (Num_List msg, Num_List key){
    Num_List code;
    int i;
    
    code.len = msg.len;
    for(i = 0; i < msg.len; i++){
        code.num[i] = msg.num[i] ^ key.num[i];
    }
    return code;
}

void print_msg (Num_List msg){
    int i;
    
    for(i = 0; i < msg.len; i++){
        printf("%c", msg.num[i]);
    }
    printf("\n");
}

void take_case(){
    char* bytes_str = malloc(LenBytesStr);
    char* line;
    int bytes;
    int i;
    Num_List code[3];
    Num_List key_a;
    Num_List msg;
   
    fgets(bytes_str, LenBytesStr, stdin);
    bytes = atoi(bytes_str);
    free(bytes_str);
    
    line = malloc(LenLine);
    for(i = 0; i < 3; i++){
        code[i].len = bytes;
        fgets(line, LenLine, stdin);
        save_code(&code[i], line);
    }
    free(line);
    
    key_a = encrypt(code[1], code[2]);
    msg = encrypt(code[0], key_a);
    print_msg(msg);
}

int main() {
    char* cases_str = malloc(LenCasesStr);
    int cases;
    int i;
    
    fgets(cases_str, LenCasesStr, stdin);
    cases = atoi(cases_str);
    free(cases_str);
    
    for(i = 0; i < cases; i++){
        take_case();
    }
}
