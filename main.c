#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./constants.c"
#include "./stack.c"

// line and columns read
int line = 1;
int column = 1;

// token is the current token value
int token;

// file is a pointer to file read
FILE *file;

// lastChar is the last char read from file
char lastChar;

// indentStack is the stack to control indentation
struct Stack* indentStack;

// states of analisis
enum states {start, string, number, keyword, operatorDelimiter} currentState;

// nextChar read next charactere from file
void nextChar() {
    if (feof(file)) {
        token = TK_FILE_END;
        fclose(file);
        return;
    }

    fread(&lastChar, 1, 1, file);
    column++;
    // printf("Leu caracter %c\n", lastChar);

    if (lastChar == '\n') {
        printf("Reconhecido (%d, %d): Nova Linha - Token: %d\n", line, column, TK_NEWLINE);
        column = 0;
        line++;
        scanIndentation();
    }
}

void getToken() {
    if (lastChar == '\n') {
        return;
    }

    if (lastChar == '#') {
        while (lastChar != '\n') {
            nextChar();
        }
        return;
    }

    int posl = 0;
    char lex[20];

    while (true) {
        lex[posl++] = lastChar;

        if (lastChar >= '0' && lastChar <= '9') {
            while (lastChar >= '0' && lastChar <= '9') {
                nextChar();
                lex[posl++] = lastChar;
            }
            fseek(file, -1, SEEK_CUR);
            lex[--posl] = '\0';
            token = TK_INTEGER;
            break;
        }

        if ((lastChar >= 'a' && lastChar <= 'z') || (lastChar >= 'A' && lastChar <= 'Z') || lastChar == '_') {
            while ((lastChar >= 'a' && lastChar <= 'z') || (lastChar >= 'A' && lastChar <= 'Z') || lastChar == '_' || (lastChar >= '0' && lastChar <= '9')) {
                nextChar();
                lex[posl++] = lastChar;
            }
            fseek(file, -1, SEEK_CUR);
            lex[--posl] = '\0';
            token = scanKeyword(lex);
            break;
        }

        if (lastChar == '"' || lastChar == '\'') {
            nextChar();
            lex[--posl] = lastChar;
            posl++;
            while (lastChar != '"' && lastChar != '\'') {
                nextChar();
                lex[posl++] = lastChar;
            }
            lex[--posl] = '\0';
            token = TK_STRING;
            break;
        }

        // while (lastChar != ' ' && lastChar != '\n') {
        while (scanOperator(lex) > -1 || scanDelimiter(lex) > -1) {
            nextChar();
            lex[posl++] = lastChar;
        }
        // fseek(file, -1, SEEK_CUR);
        lex[--posl] = '\0';

        token = scanOperator(lex);
        if (token >= 0) {
            break;
        }

        token = scanDelimiter(lex);
        if (token >= 0) {
            break;
        }

        if (lastChar == ' ') {
            token = TKTokenInvalido;
            break;
        }

        printf("Erro léxico (%d,%d): caractere \"%c\" desconhecido!\n", line, column, lastChar);
        token = TK_ERROR;
        break;
    }

    if (token != TK_FILE_END && token != TKTokenInvalido) {
        printf("Reconhecido (%d, %d): %s - Token: %d\n", line, column, lex, token);
    }
}

int main() {
    currentState = start;
    indentStack = newStack(50);

    file = fopen("file.py", "rb");
    if (!file) {
        printf("Erro na abertura do fonte.\n");
        return 0;
    }

    while (token != TK_FILE_END && token != TK_ERROR) {
        nextChar();
        getToken();
    }

    if (token == TK_ERROR) {
        return 1;
    }

    printf("Chegou no fim de arquivo fonte!\n");
    return 0;
}

void scanIndentation() {
    int n = 0;
    nextChar();
    while (lastChar == ' ') {
        nextChar();
        n++;
    }

    // fseek(file, -1, SEEK_CUR);

    if (n >= peek(indentStack)) {
        push(indentStack, n);
        printf("Reconhecido (%d): Indentação - Token: %d\n", line, TK_INDENT);
    } else {
        pop(indentStack);
        printf("Reconhecido (%d): Edentaçāo - Token: %d\n", line, TK_DEDENT);
    }
}

int scanKeyword(char lex[]) {
    for (int i = 0; i < sizeof(listKeywords); i++) {
        if (strcmp(lex, listKeywords[i].word) == 0) {
            return listKeywords[i].token;
        }
    }

    return TKId;
}

int scanOperator(char lex[]) {
    for (int i = 0; i < sizeof(listOperators); i++) {
        if (strcmp(lex, listOperators[i].word) == 0) {
            return listOperators[i].token;
        }
    }

    return -1;
}

int scanDelimiter(char lex[]) {
    for (int i = 0; i < sizeof(listDelimiters); i++) {
        if (strcmp(lex, listDelimiters[i].word) == 0) {
            return listDelimiters[i].token;
        }
    }

    return -1;
}
