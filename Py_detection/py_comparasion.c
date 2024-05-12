#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "py_tokenizer.h"
#include "transfer_to_pyfile.h"


// Function to find the union of two arrays
void getUnion_Intersection(char **a, int n, char **b, int m,int *union_len,int *intersection_len)
{
    // Defining set container union_arr
    char **union_arr = malloc(sizeof(char*) * (n + m));
    int union_size = 0;
    int intersection_size=0;
 
    // Inserting array elements in s
    for (int i = 0; i < n; i++) {
        union_arr[union_size]=malloc((strlen(a[i])+1)*sizeof(char));
        strcpy(union_arr[union_size],a[i]);
        union_size++;
        
    }
 
    for (int i = 0; i < m; i++) {
        if (!isStringPresent(b[i], union_arr,union_size)) {
            union_arr[union_size]=malloc((strlen(b[i])+1)*sizeof(char));
            strcpy(union_arr[union_size],b[i]);
            union_size++;
        }
    }
 
    for (int i = 0; i < union_size; i++) {
        if (isStringPresent(union_arr[i],a,n)&&isStringPresent(union_arr[i],b,m)){
            intersection_size++;
        }
        free(union_arr[i]);
    }
    *union_len=union_size;
    *intersection_len=intersection_size;
    free(union_arr);
}
 
float py_checker(){
    int num_of_words=0;

    read_write_file(&num_of_words);
    //printf("The number of elements %d",num_of_words);
    FILE *database;
    char *databasename = "/Users/mcittkmims/Documents/SDA/Individual_Work/Py_detection/database.txt"; 
    FILE *output;
    char *outputname = "/Users/mcittkmims/Documents/SDA/Individual_Work/Py_detection/output.txt"; 
    // Open the file in read binary mode
    database = fopen(databasename, "rb");
    // Open the file in read binary mode
    output=fopen(outputname,"rb");
    char ** output_str=NULL;

    int length;
    float similarity_score=0;
    while (fread(&length, sizeof(int), 1, output) == 1){
        output_str=malloc(length*sizeof(char*));
        for (int i=0;i<length;i++){
            int str_len;
            fread(&str_len,sizeof(int), 1, output);
            output_str[i] = malloc(str_len*sizeof(char));
            fread(output_str[i],sizeof(char),str_len,output);
        }
        char ** database_str=NULL;
        int size;
        float max_similarity=0;
        database = fopen(databasename, "rb");
        while(fread(&size,sizeof(int),1,database)==1){
            database_str=malloc(size*sizeof(char*));
            for (int i=0;i<size;i++){
                int len;
                fread(&len,sizeof(int), 1, database);
                database_str[i] = malloc(len*sizeof(char));
                fread(database_str[i],sizeof(char),len,database);
            }
            int union_size, intersection_size;
            getUnion_Intersection(output_str,length,database_str,size,&union_size,&intersection_size);
            float max_temp =(float)intersection_size/union_size;
            //printf("\n%f",max_temp);
            if (max_temp>max_similarity){
                max_similarity=max_temp;
            } 
            for (int i=0;i<size;i++){
                free(database_str[i]);
	        }
            free(database_str);
        }
        fclose(database);
        //printf("\nThe number of elements per set %d",length);
        //printf("\nThe similarity per set %f",max_similarity);
        float average_raport=(float)length/num_of_words;
        similarity_score=similarity_score+(average_raport*max_similarity);
        //printf("\nThe similarity increasing %f",similarity_score);
        for (int i=0;i<length;i++){
            free(output_str[i]);
	    }
        free(output_str);

    }
    return similarity_score;
}

int main(){
    float score_code=py_checker();
    //printf("\nThe code is %f similar",score_code);
    FILE *score;
    char *scorename = "/Users/mcittkmims/Documents/SDA/Individual_Work/website/score.txt";
    score = fopen(scorename, "w"); 
    fprintf(score, "%f", score_code);
    fclose(score);



    return 0;
}