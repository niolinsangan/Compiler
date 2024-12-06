#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 100

// Function to check if a character is a delimiter
bool isDelimiter(char ch) {
    return (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == ',' || ch == ';' || ch == '>' || ch == '<' || ch == '=' ||
            ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}');
}

// Function to check if a character is an operator
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=');
}

// Function to check if a string is a valid identifier
bool validIdentifier(char *str) {
    if (!isalpha(str[0])) return false; // Identifier must start with a letter
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != '_') return false; // Only letters, digits, and underscores are allowed
    }
    return true;
}

// Function to check if a string is a keyword
bool isKeyword(char *str) {
    const char *keywords[] = {"if", "else", "while", "do", "break", "continue", "int", "double", "float", "return", "char", "case", "sizeof", "long", "short", "typedef", "switch", "unsigned", "void", "static", "struct", "goto", NULL};
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Function to check if a string is an integer
bool isInteger(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

// Function to check if a string is a real number
bool isRealNumber(char *str) {
    bool hasDecimal = false;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            if (hasDecimal) return false; // More than one decimal point
            hasDecimal = true;
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    return hasDecimal; // Must have at least one decimal point
}

// Function to extract and analyze tokens from the input string
void parse(char *str) {
    int left = 0, right = 0;
    int len = strlen(str);

    while (right <= len && left <= right) {
        if (!isDelimiter(str[right])) {
            right++;
        }
        if (isDelimiter(str[right]) && left == right) {
            if (isOperator(str[right])) {
                printf("'%c' IS AN OPERATOR\n", str[right]);
                right++;
                left = right;
            }
        } else if (isDelimiter(str[right]) && left != right || (right == len && left != right)) {
            char *subStr = (char *)malloc(sizeof(char) * (right - left + 1));
            strncpy(subStr, str + left, right - left);
            subStr[right - left] = '\0'; // Null-terminate the substring

            if (isKeyword(subStr)) {
                printf("'%s' IS A KEYWORD\n", subStr);
            } else if (isInteger(subStr)) {
                printf("'%s' IS AN INTEGER\n", subStr);
            } else if (isRealNumber(subStr)) {
                printf("'%s' IS A REAL NUMBER\n", subStr);
            } else if (validIdentifier(subStr)) {
                printf("'%s' IS A VALID IDENTIFIER\n", subStr);
            } else {
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
            }
            free(subStr);
            left = right;
        }
    }
}

// Driver function
int main() {
    char str[MAX_LENGTH] = "int a = b + 1.5;"; // Example input
    parse(str); // Call the parse function
    return 0;
}