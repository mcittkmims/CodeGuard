#include <stdio.h>
#include <stdlib.h>
#include <string.h>






void read_write_file(int *words_count){
    printf("1111111111");
    FILE *input;
    char *inputname = "/Users/mcittkmims/Documents/SDA/Individual_Work/Py_detection/temp.txt"; 
    FILE *output;
    char *outputname = "/Users/mcittkmims/Documents/SDA/Individual_Work/Py_detection/output.txt"; 
    // Open the file in read mode
    input = fopen(inputname, "rb");
    output = fopen(outputname, "wb");
    FILE *database;
    // Open the file in write binary mode
    int length=0;
    char *input_str=NULL;
    while (fread(&length, sizeof(int), 1, input) == 1){
        input_str=malloc(length*sizeof(char*));
        fread(input_str,sizeof(char),length,input);
        printf("%s/n",input_str);
        parse(input_str,output,database,words_count);
        
        free(input_str);
    }
    
    fclose(input);
    fclose(output);
    //fclose(database);
    //read from the database for checking
    //database=fopen("/Users/mcittkmims/Documents/SDA/Individual_Work/database.txt","rb");
    //int temp=5;
    //fwrite(&temp, sizeof(int), 1, database) == 1;
    //output=fopen("/Users/mcittkmims/Documents/SDA/Individual_Work/output.txt","rb");
    
    
    // char ** arr_str=NULL;
    // int length;
    // while (fread(&length, sizeof(int), 1, database) == 1){
    // arr_str=malloc(length*sizeof(char*));
    // // for (int i=0;i<size1;i++){
    // //     arr_str[i] = malloc(256*sizeof(char));}
    // for (int i=0;i<length;i++){
    //     int str_len;
    //     fread(&str_len,sizeof(int), 1, database);
    //     arr_str[i] = malloc(str_len*sizeof(char));
    //     fread(arr_str[i],sizeof(char),str_len,database);
    // }
    // for (int i=0;i<length;i++){
	// 	printf("%s ",arr_str[i]);
    //     free(arr_str[i]);
	// }
    // printf("\n\n\n\n");
    // }
    // free(arr_str);
}


