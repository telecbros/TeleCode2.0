#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

enum{
    MaxInt = 12, //Max len of a int in a string(including '\n' and '\0')
    LenLine = 100,
};

struct Street{
    int begin;
    int end;
    int visited;
};
typedef struct Street Street;

void ext_data (char* line, int* n_cruc, int* n_strs, int* n_hotls)
{
    char* token;
    int i;
    
    token = strtok(line, " ");
    for(i=0; i<3; i++) {
        if(i == 0){
            *n_cruc = atoi(token);
        }else if(i == 1){
            *n_strs = atoi(token);
        }else{
            *n_hotls = atoi(token);
        }
        token = strtok(NULL, " ");
    }
}

void save_hotels (char* line, int hotls[], int n_hotls)
{
    char* token;
    int i;
    
    token = strtok(line, " ");
    for(i=0; i<n_hotls; i++) {
        hotls[i] = atoi(token);
        token = strtok(NULL, " ");
    }
}

void save_str (char* line, Street* str)
{
    char* token;
    int i;
    
    token = strtok(line, " ");
    for(i=0; i<2; i++) {
        if(i == 0){
            str->begin = atoi(token);
        }else if(i == 1){
            str->end = atoi(token);
        }
        token = strtok(NULL, " ");
    }
    str->visited = 0;
}

void save_strs (Street strs[], int n_strs)
{
    char* line = malloc(LenLine);
    int i;
    
    for(i=0; i<n_strs; i++) {
        fgets(line, LenLine, stdin);
        save_str(line, &strs[i]);
    }
    free(line);
}

void print_hotels (int hotls[], int n_hotls)
{
    int i;

    for(i=0; i<n_hotls; i++) {
        printf("%d\n", hotls[i]);
    }
}

void print_strs (Street strs[], int n_strs)
{
    int i;

    for(i=0; i<n_strs; i++) {
        printf("%d ", strs[i].begin);
        printf("%d ", strs[i].end);
        printf("%d\n", strs[i].visited);
    }
}

//Search a street that have argumment begin as street.begin
Street search_str(Street strs[], int n_strs, int begin)
{
    int i;
    Street sol;
    
    for(i=0; i<n_strs; i++){
        if(strs[i].begin == begin){
            sol = strs[i];
            break;
        }
    }
    return sol;
}

int there_are_next(Street strs[], int n_strs, Street curr_str)
{
    int i;
    int found = 0;
    
    for(i=0; i<n_strs; i++){
        if(curr_str.end == strs[i].begin){
            found = 1;
            break;
        }
    }
    return found;
}

int there_are_str(Street strs[], int n_strs, int hotl)
{
    int i;
    int found = 0;
    
    for(i=0; i<n_strs; i++){
        if(strs[i].begin == hotl){
            found = 1;
            break;
        }
    }
    return found;
}

Street next_str(Street strs[], int n_strs, Street curr_str)
{
    int i;
    Street next;
    
    for(i=0; i<n_strs; i++){
        if(curr_str.end == strs[i].begin){
            next = strs[i];
            break;
        }
    }
    return next;
}

void init_strs(Street strs[], int n_strs)
{
    int i;
    
    for(i=0; i<n_strs; i++){
        strs[i].visited = 0;
    }
}

int same_str(Street str1, Street str2)
{
    return (str1.begin == str2.begin) &&
           (str1.end == str2.end) &&
           (str1.visited == str2.visited);
}

void change_visited(Street strs[], int n_strs, Street curr_str)
{
    int i;
    
    for(i=0; i<n_strs; i++){
        if(same_str(strs[i], curr_str)){
            strs[i].visited = 1;
            break;
        }
    }
}

int is_good (Street strs[], int n_strs, int hotl)
{
    Street curr_str;
    int result;
    
    if(!there_are_str(strs, n_strs, hotl)){
        return 0;
    }
    
    curr_str = search_str(strs, n_strs, hotl);
    for(;;){
        if(hotl == curr_str.end){
            result = 1;
            break;
        }else if(curr_str.visited == 1 || 
                 !there_are_next(strs, n_strs, curr_str)){
            result = 0;
            break;
        }
        change_visited(strs, n_strs, curr_str);
        curr_str = next_str(strs, n_strs, curr_str);   
    }
    init_strs(strs, n_strs);
    return result;
}

int good_htls (Street strs[], int n_strs, int hotls[], int n_hotls)
{
    int result = 0;
    int i;
    
    for(i=0; i<n_hotls; i++){
        if(is_good(strs, n_strs, hotls[i])){
            result++;
        }
    }
    return result;
}

void take_city()
{
    char* line = malloc(LenLine);
    int n_cruc;
    int n_strs;
    int n_hotls;
    int n_htls_ok = 0;
    int i;
    
    fgets(line, LenLine, stdin);
    ext_data(line, &n_cruc, &n_strs, &n_hotls);
    
    fgets(line, LenLine, stdin);
    int hotls[n_hotls];
    save_hotels(line, hotls, n_hotls);
    
    Street strs[n_strs];
    save_strs(strs, n_strs);
    
    n_htls_ok = good_htls(strs, n_strs, hotls, n_hotls);
    printf("%d\n", n_htls_ok);
    
    //print_hotels(hotls, n_hotls);
    //print_strs(strs, n_strs);
}

int main()
{
    char* n_cities_str = malloc(MaxInt);
    int n_cities;
    int i;

    fgets(n_cities_str, MaxInt, stdin);
    n_cities = atoi(n_cities_str);
    free(n_cities_str);
    
    for(i = 0; i < n_cities; i++){
        take_city();
    }
}
