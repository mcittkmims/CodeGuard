#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 256


bool isStringPresent(char *string, char **array, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(string, array[i]) == 0) {
            return true; // String found
        }
    }
    return false; // String not found
}

// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch)
{
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || 
		ch == '/' || ch == ',' || ch == ';' || ch == '>' || 
		ch == '<' || ch == '=' || ch == '(' || ch == ')' || 
		ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
		ch == '\n'|| ch == '\t'|| ch == '"' ||
		ch == '.' || ch == ':' || ch == '?' || ch == '`' || 
		ch == '\\' || ch == '%'|| ch == '!' || ch == '&' || 
		ch == '|' || ch == '^' || ch == '~')
		return (true);
	return (false);
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || 
		ch == '/' || ch == '>' || ch == '<' || 
		ch == '=' || ch == '+' || ch == '-' ||
		ch == '%' || ch == '!' || ch == '&' ||
		ch == '|')
		return (true);
	return (false);
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char* str)
{
	if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
		str[0] == '3' || str[0] == '4' || str[0] == '5' || 
		str[0] == '6' || str[0] == '7' || str[0] == '8' || 
		str[0] == '9' || isDelimiter(str[0]) == true)
		return (false);
	return (true);
}

// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char* str)
{
	if (!strcmp(str, "if") || !strcmp(str, "else") ||
		!strcmp(str, "while") || !strcmp(str, "do") || 
		!strcmp(str, "break") || 
		!strcmp(str, "continue") || !strcmp(str, "int")
		|| !strcmp(str, "double") || !strcmp(str, "float")
		|| !strcmp(str, "return") || !strcmp(str, "char")
		|| !strcmp(str, "case") || !strcmp(str, "char")
		|| !strcmp(str, "sizeof") || !strcmp(str, "long")
		|| !strcmp(str, "short") || !strcmp(str, "typedef")
		|| !strcmp(str, "switch") || !strcmp(str, "unsigned")
		|| !strcmp(str, "void") || !strcmp(str, "static")
		|| !strcmp(str, "struct") || !strcmp(str, "goto"))
		return (true);
	return (false);
}

// Returns 'true' if the string is an INTEGER.
bool isInteger(char* str)
{
	int i, len = strlen(str);

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' || (str[i] == '-' && i > 0))
			return (false);
	}
	return (true);
}

// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(char* str)
{
	int i, len = strlen(str);
	bool hasDecimal = false;

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' && str[i] != '.' || 
			(str[i] == '-' && i > 0))
			return (false);
		if (str[i] == '.')
			hasDecimal = true;
	}
	return (hasDecimal);
}

// Extracts the SUBSTRING.
char* subString(char* str, int left, int right)
{
	int i;
	char* subStr = (char*)malloc(
				sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];
	subStr[right - left + 1] = '\0';
	return (subStr);
}

// Parsing the input STRING.
void parse(char* str,FILE* output,FILE* database,int *words_count)
{	
	char **arr_str=NULL;
	int size=0;
	int left = 0, right = 0;
	int len = strlen(str);

	while (right <= len && left <= right) {
		if (isDelimiter(str[right]) == false)
			right++;

		if (isDelimiter(str[right]) == true && left == right) {
			if (isOperator(str[right]) == true){
				char operator[2];
				operator[0]=str[right];
				operator[1]='\0';
				if (!isStringPresent(operator,arr_str,size)){
					size++;
					arr_str = realloc(arr_str, (size ) * sizeof(char*));
					arr_str[size-1] = malloc(2*sizeof(char));
					arr_str[size-1][0]=str[right];
					arr_str[size-1][1]='\0';
				}
				}

			right++;
			left = right;
		} else if (isDelimiter(str[right]) == true && left != right
				|| (right == len && left != right)) {
			char* subStr = subString(str, left, right - 1);
			if (!isStringPresent(subStr,arr_str,size)){
				size++;
				arr_str = realloc(arr_str, (size) * sizeof(char*));
				arr_str[size-1] = malloc((strlen(subStr)+1)*sizeof(char));
				strcpy(arr_str[size-1],subStr);
				arr_str[size-1][strlen(subStr)]='\0';
			}
			left = right;
		}
	}
	//Writing the functions of the program in a file for further checking
	fwrite(&size,sizeof(int),1,output);
	*words_count+=size;
	for (int i=0; i<size;i++){
		int length = strlen(arr_str[i]) + 1;
		fwrite(&length,sizeof(int),1,output);
		fwrite(arr_str[i],sizeof(char),length,output);
	}
	//Writing in database
	// fwrite(&size,sizeof(int),1,database);
	// for (int i=0; i<size;i++){
	// 	int length = strlen(arr_str[i]) + 1;
	// 	fwrite(&length,sizeof(int),1,database);
	// 	fwrite(arr_str[i],sizeof(char),length,database);
	// }
	// for (int i=0;i<size;i++){
	// 	printf("%s ",arr_str[i]);
	// }

	free(arr_str);
	return;
}

// DRIVER FUNCTION
