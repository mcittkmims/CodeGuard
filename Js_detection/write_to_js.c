#include <stdio.h>
#include <stdlib.h>
#include "js_tokenizer.h"

int main(){
    FILE *database;
    char *databasename = "/Users/mcittkmims/Documents/SDA/Individual_Work/Js_detection/database.txt"; 
    database = fopen(databasename, "ab");
    FILE *code_file;
    char *code_filename = "/Users/mcittkmims/Documents/SDA/Individual_Work/Js_detection/code_for_database.txt"; 
    code_file = fopen(code_filename, "r");
    fseek(code_file, 0, SEEK_END); // Move the file pointer to the end of the file
    long size = ftell(code_file);  // Get the current position, which is the size of the file
    rewind(code_file);   
    char *str = (char *)malloc(size + 1);
    fread(str, 1, size, code_file);
    str[size] = '\0';
    printf("%s",str);
    int words;
    parse(str,database,code_file,&words);
    fclose(database);
    fclose(code_file);
    return 0;

}