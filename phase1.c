#include <stdio.h>
#include <string.h>

char whitespace[] = " \n\t";
char digits[] = "0123456789";
char letter_[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
char * reserved[] = {"", "int", "float", "main", "return", "if", "else", "while"};
char * special[] = {"", ".", ",", "(", ")", "{", "}", "\"", "\'", ";"};
char * operators[] = {"", "+", "-", "*", "/", "%"};

int belongs(char a, char string[])
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (a == string[i])
        {
            return 1;
        }
    }
    return 0;
}

int isState(int s, int states[])
{
    int n = 1;
    for (int i = 0; i < 1; i++)
    {
        if (s == states[i])
        {
            return 1;
        }
    }
    return 0;
}

int belongs2(char needle[], char * haystack[])
{
    int i = 0;
    while(haystack[i])
    {
        if (strcmp(needle, haystack[i]) == 0)
            return i;
        i++;
    }
    return 0;
}

int move(int state, char input)
{

    int transition_table[][19] = {
        {3, 1, 0, 3, 5, 5, 0, 0, 10, 0, 0, 13, 0, 0, 16, 0, 0, -1, 0}, // digits
        {1, 1, 0, 7, -1, 6, 0, 0, 10, 0, 0, 13, 0, 0, 16, 0, 0, -1, 0}, // letter_
        {0, 2, 0, 4, -1, 6, 0, 0, 10, 0, 0, 13, 0, 0, 16, 0, 0, -1, 0}, // \.
        {8, 2, 0, 7, -1, 6, 0, 0, 10, 0, 0, 13, 0, 0, 16, 0, 0, -1, 0}, // >
        {11, 2, 0, 7, -1, 6, 0, 0, 10, 0, 0, 13, 0, 0, 16, 0, 0, -1, 0}, // <
        {14, 2, 0, 7, -1, 6, 0, 0, 9, 0, 0, 12, 0, 0, 15, 0, 0, 18, 0}, // =
        {17, 2, 0, 7, -1, 6, 0, 0, 10, 0, 0, 13, 0, 0, 16, 0, 0, -1, 0}, // !
        {0, 2, 0, 7, -1, 6, 0, 0, 10, 0, 0, 13, 0, 0, 16, 0, 0, -1, 0}, // whitespace
        {0, 2, 0, 7, -1, 6, 0, 0, 10, 0, 0, 13, 0, 0, 16, 0, 0, -1, 0}  // other
    };

    if (state == 0)
    {
        if (belongs(input, digits))
            state = 5;
        else if (belongs(input, letter_))
            state = 2;
        else
            state = 0;
    }
    else if (state == 2)
    {
        if (belongs(input, letter_) || belongs(input, digits))
            state = 2;
        else
            state = 3;
    }
    else if (state == 5)
    {
        if (belongs(input, digits))
            state = 5;
        else if (input == '.')
            state = 6;
        else
            state = 9;
    }
    else if (state == 6)
    {
        if (belongs(input, digits))
            state = 7;
        else
            state = -1;
    }
    else if (state == 7)
    {
        if (belongs(input, digits))
            state = 7;
        else
            state = 8;
    }
    return state;
}

char * FA(char * file_name)
{
    FILE * fp = fopen(file_name, "r");

    int line_number = 1;
    char yytext[100];
    int yylen;

    int int_states[] = {9};
    int float_states[] = {8};
    int id_states[] = {3};

    char c = fgetc(fp);
    while(c > 0)
    {
        char state = 0;
        yylen = 0;
        while(c > 0)
        {
            yytext[yylen] = '\0';
            yytext[yylen+1] = '\0';
            state = move(state, c);
            int tkNum;
            // printf("State:%d c=%c yytext(%d)=%s\n", state, c, yylen, yytext);
            // printf("belongs2(yytext, operators) = %d\n", belongs2(yytext, operators));

            // Check for operators
            if (tkNum = belongs2(yytext, operators))
            {
                yytext[yylen] = '\0';
                printf("Operator[%d] %s at line %d\n", tkNum, yytext, line_number);
                c = fgetc(fp);
                break;
            }

            // Check for special symbols
            if (tkNum = belongs2(yytext, special))
            {
                yytext[yylen] = '\0';
                printf("Symbol[%d] %s at line %d\n", tkNum, yytext, line_number);
                c = fgetc(fp);
                break;
            }

            // Check for reserved words
            if (tkNum = belongs2(yytext, reserved))
            {
                printf("Reseved word[%d] %s at line %d\n", tkNum, yytext, line_number);
                break;
            }

            if (isState(state, int_states))
            {
                printf("Int %s at line %d\n", yytext, line_number);
                break;
            }
            if (isState(state, float_states))
            {
                printf("Float %s at line %d\n", yytext, line_number);
                break;
            }
            else if(isState(state, id_states))
            {
                printf("ID %s at line %d\n", yytext, line_number);
                break;
            }
            else if (state == -1) // invalid
            {
                printf("Unidentified token: %s at line %d\n", yytext, line_number);
                break;
            }

            yytext[yylen++] = c;
            c = fgetc(fp);

            if (c == '\n')
                line_number++;
        }
        if (belongs(c, whitespace))
        {
            c = fgetc(fp);
            continue;
        }
    }
    fclose(fp);
}

int main()
{
    // id = [a-zA-Z_][a-zA-Z_0-9]*
    // float = int.int
    // whitespace = [ \n\t]
    // special = . // Anything else

    char * result = FA("input.c");


    return 0;
}
