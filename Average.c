#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

enum{
    MaxInt = 12, //Max len of a int in a string(including '\n' and '\0')
    Float_Prec = 50, //Indicate the precisión that we use to represent a float
    N_Decimals = 4,
};

long double aritMean (int num_list[], int len)
{
    long double sum;
    int i;
    
    sum = (long double)num_list[0];
    for(i=1; i<len; i++){
        sum = sum + (long double)num_list[i];
    }
    return sum/len;
}

long double geoMean (int num_list[], int len)
{
    long double prod;
    int i;
    
    prod = powl((long double)num_list[0],1/(long double)len);
    for(i=1; i<len; i++){
        prod = prod * powl((long double)num_list[i],1/(long double)len);
    }
    return prod;
}

char* to_str (long double num)
{
    char* result = malloc(Float_Prec);
    snprintf(result, Float_Prec, "%Lf", num);
    return result;
}

void delete_zeros (char* num)
{
    char* aux;
    
    aux = strchr(num, '\0');
    aux--;
    while(*aux == '0'){
        *aux = '\0';
        aux--;
    }
    if(*aux == '.'){
        *aux = '\0';
    }
}

void truncate (char* num, int n_decimals)
{
    int i;
    
    while(*num != '.'){
        num++;
    }
    for(i=0; i<n_decimals+1; i++){
        num++;
    }
    *num = '\0';
    delete_zeros(num);
}

int main() {
    int nums;
    char* line = malloc(MaxInt);
    int i;
    long double arit_mean;
    long double geo_mean;
    char* num;
    
    fgets(line, MaxInt, stdin);
    nums = atoi(line);
    
    int num_list[nums];
    for(i=0; i<nums; i++){
        fgets(line, MaxInt, stdin);
        num_list[i] = atoi(line);
    }
    free(line);
    
    arit_mean = aritMean(num_list, nums);
    geo_mean = geoMean(num_list, nums);
    num = to_str(arit_mean-geo_mean);
    truncate(num, N_Decimals);
    printf("%s\n", num);
}
