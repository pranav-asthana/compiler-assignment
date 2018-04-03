#include <stdio.h>
#include <string.h>

char whitespace[] = " \n\t";
char digits[] = "0123456789";
char letter_[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
char * reserved[] = {"", "int", "float", "main", "return", "if", "else", "while"};
char * special[] = {"", ".", ",", "(", ")", "{", "}", "\"", "\'", ";"};
char * operators[] = {"", "+", "-", "*", "/", "%"};
char * rel_ops[] = {"GTE", "GT", "LTE", "LT", "EQEQ", "EQ", "NEQ"};

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

int isState(int s, int states[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (s == states[i])
        {
            return i+1;
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
        {3, 1, -1, 3, 5, 5, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1}, // digits
        {1, 1, -1, 7, -1, 6, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1}, // letter_
        {-1, 2, -1, 4, -1, 6, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1}, // \.
        {8, 2, -1, 7, -1, 6, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1}, // >
        {11, 2, -1, 7, -1, 6, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1}, // <
        {14, 2, -1, 7, -1, 6, -1, -1, 9, -1, -1, 12, -1, -1, 15, -1, -1, 18, -1}, // =
        {17, 2, -1, 7, -1, 6, -1, -1, 10, -1, -1, 13, -1, -1, 16, -1, -1, -1, -1}, // !
        {0, 2, 0, 7, 0, 6, 0, 0, 10, 0, 0, 13, 0, 0, 16, 0, 0, 0, 0}, // whitespace
        {0, 2, 0, 7, 0, 6, 0, 0, 10, 0, 0, 13, 0, 0, 16, 0, 0, 0, 0}  // other
    };

    if (belongs(input, digits))
        state = transition_table[0][state];
    else if (belongs(input, letter_))
        state = transition_table[1][state];
    else if (belongs(input, whitespace))
        state = transition_table[7][state];
    else
    {
        switch (input)
        {
            case '.':
            {
                state = transition_table[2][state];
                break;
            }
            case '>':
            {
                state = transition_table[3][state];
                break;
            }
            case '<':
            {
                state = transition_table[4][state];
                break;
            }
            case '=':
            {
                state = transition_table[5][state];
                break;
            }
            case '!':
            {
                state = transition_table[6][state];
                break;
            }
            default:
            {
                state = transition_table[8][state];
                break;
            }
        }
    }
    return state;
}

char * FA(char * file_name)
{
    FILE * fp = fopen(file_name, "r");

    int line_number = 1;
    char yytext[100];
    int yylen;

    int int_states[] = {7};
    int float_states[] = {6};
    int id_states[] = {2};
    int rel_op_states[] = {9, 10, 12, 13, 15, 16, 18};

    char c = fgetc(fp);
    while(c > 0)
    {
        char state = 0;
        yylen = 0;
        while(c > 0)
        {
            yytext[yylen] = '\0';
            yytext[yylen+1] = '\0';
            int tkNum;

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
                // c = fgetc(fp);
                break;
            }
            // Check for reserved words
            if (tkNum = belongs2(yytext, reserved))
            {
                printf("Reseved word[%d] %s at line %d\n", tkNum, yytext, line_number);
                break;
            }


            // printf("State:%d c='%c' yytext(%d)=%s\n", state, c, yylen, yytext);
            state = move(state, c);
            // printf("State:%d c='%c' yytext(%d)=%s\n----\n", state, c, yylen, yytext);
            int op_id;
            if (op_id = isState(state, rel_op_states, 7))
            {
                char * operator = rel_ops[op_id-1];
                printf("Relational operator[] %s at line %d\n", operator, line_number);
                if (strlen(operator) > 2)
                    c = fgetc(fp);
                break;
            }
            if (isState(state, int_states, 1))
            {
                printf("Int %s at line %d\n", yytext, line_number);
                break;
            }
            else if (isState(state, float_states, 1))
            {
                printf("Float %s at line %d\n", yytext, line_number);
                break;
            }
            else if(isState(state, id_states, 1))
            {
                printf("ID %s at line %d\n", yytext, line_number);
                break;
            }
            else if (state == -1) // invalid
            {
                printf("Unidentified token: %s at line %d\n", yytext, line_number);
                printf("Lexical error\n");
                return 0;
            }

            if (belongs(c, whitespace) == 0)
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

    // char * result = FA("mini.c");
    char * result = FA("input.c");



    return 0;
}
