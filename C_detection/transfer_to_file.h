#include <stdio.h>
#include <stdlib.h>
#include <string.h>






void read_write_file(int *words_count){
    FILE *input;
    char *inputname = "/Users/mcittkmims/Documents/SDA/Individual_Work/website/input.txt"; 
    FILE *output;
    char *outputname = "/Users/mcittkmims/Documents/SDA/Individual_Work/C_detection/output.txt"; 
    // Open the file in read mode
    input = fopen(inputname, "r");
    // Open the file in write binary mode
    output=fopen(outputname,"wb");
    fseek(input, 0, SEEK_END); // Move the file pointer to the end of the file
    long size = ftell(input);  // Get the current position, which is the size of the file
    rewind(input);   
    char *str = (char *)malloc(size + 1);
    fread(str, 1, size, input);
    str[size] = '\0';
    //Writing in the database
    //FILE *database=fopen("/Users/mcittkmims/Documents/SDA/Individual_Work/database.txt","ab");
    FILE *database;
    cdivider(str,output,database,words_count);
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


