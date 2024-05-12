#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>




void Beginning(char* str, int* pos) {
    while(((*pos)!=0)&&((*pos)!=strlen(str))){
        if ((str[*pos-1]!=';')&&(str[*pos-1]!='}')&&(str[*pos-1]!='>')&&(str[*pos-1]!='"')){
            (*pos)--;
        }else{
            break;
        }
    }
}

void cdivider(char* str,FILE* output,FILE* database,int *words_count) {


    regex_t regex;
    int reti;
    char msgbuf[100];
    regmatch_t match;  // Array to store match information based on average function length

    // Compile regular expression
    reti = regcomp(&regex,"[a-zA-Z0-9_]+[ \t\n]*[*]?[ \t\n]+[a-zA-z0-9_*]+[ \t\n]*[\\(][^{}(]*[\\)][\t\n ]*[{]", REG_EXTENDED);



    int nmatches = 0; // Number of matches found
    int *matches=malloc(sizeof(int));
    char *copy = strdup(str); // Copy input string to avoid modifying the original
    
    int counter=0;
    while ((reti = regexec(&regex, copy, 1, &match, 0)) == 0) {
        char matched_str[match.rm_eo - match.rm_so + 1];
        strncpy(matched_str, &copy[match.rm_so], match.rm_eo - match.rm_so);
        matched_str[match.rm_eo - match.rm_so] = '\0';
        if (strstr(matched_str, "else ")==NULL&&strstr(matched_str, "else\n")==NULL&&strstr(matched_str, "else\t")==NULL &&
        strstr(matched_str, "for ")==NULL&&strstr(matched_str, "for\n")==NULL&&strstr(matched_str, "for\t")==NULL  &&
        strstr(matched_str, "if ")==NULL&&strstr(matched_str, "if\n")==NULL&&strstr(matched_str, "if\t")==NULL ){
            nmatches++;
            matches=realloc(matches,nmatches*sizeof(int));
            matches[nmatches-1]=counter+match.rm_so;
            }
    
        // Move the string pointer forward
        copy += match.rm_eo;
        counter+=match.rm_eo;
    }


    if (nmatches > 0) {
        // Print the matched substring
        char *function=malloc(sizeof(char));
        for (int j=0;j<nmatches;j++){
            
            int start=matches[j];
            
            Beginning(str,&start);
            int end;
            if (j+1<nmatches){
                end=matches[j+1];
                Beginning(str,&end);

            }else{
                end=strlen(str)+1;
            }
            function=realloc(function,(end-start+1)*sizeof(char));
            int k=0;
            for (k=0;k<=end-start-1;k++){
                function[k]=str[start+k];
            }
            function[end-start]='\0';

            // printf("\n\n\n\n\n\n");
            // printf("%s",function);
          
            parse(function,output,database,words_count);
            
        }

    }else {
        parse(str,output,database,words_count);
        
    }

    // Free compiled regular expression
    regfree(&regex);

}

