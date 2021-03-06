#include "./header.cpp"

// variável de controle para rodar o analisar Sintático.
// setar como true para usar.
bool enableSintatico = false;

int main() {
    currentState = initialState;
    tokenType = 0;

    ifstream file;
    file.open("file.py");

    if (!file) {
        printf("Error on open file.\n");
        return 1;
    }

    readFile(file);

    file.close();

    dumpTokenList();

    if (enableSintatico) {
        executeSintatico();
    }

    return 0;
}

void readFile(istream& file) {
    while (std::getline(file, lineText)) {
        line++;

        if (lineText.length() == 0) {
            continue;
        }

        column = 0;

        scanIndentation();

        getNextChar();
        getToken();

        while (lastChar != '\n') {
            getNextChar();
            getToken();
        }

        tokenList.push_back(Token(TK_NEWLINE, "NEWLINE", line, column));
    }
}

void getNextChar() {
    if (column < lineText.length()) {
        lastChar = lineText[column++];
        return;
    }

    lastChar = '\n';
}

void backChar(int n = 1) {
    column -= n;
}

void getToken() {
    string lex;

    switch (currentState) {
        case initialState:
            if (lastChar >= '0' && lastChar <= '9') {
                currentState = numberState;
                getToken();
                return;
                break;
            }

            if (lastChar == '.') {
                getNextChar();
                backChar(2);

                if (lastChar >= '0' && lastChar <= '9') {
                    getNextChar();
                    currentState = numberState;
                    getToken();
                    return;
                    break;
                }

                getNextChar();
            }

            if ((lastChar >= 'a' && lastChar <= 'z') || (lastChar >= 'A' && lastChar <= 'Z') || lastChar == '_') {
                currentState = keywordState;
                getToken();
                return;
                break;
            }

            if (lastChar == '"' || lastChar == '\'') {
                currentState = stringState;
                getToken();
                return;
                break;
            }

            if (lastChar == '#') {
                currentState = commentState;
                getToken();
                return;
                break;
            }

            currentState = operatorDelimiterState;
            getToken();
            return;
            break;

        case numberState:
            while (lastChar >= '0' && lastChar <= '9') {
                lex.push_back(lastChar);
                getNextChar();
            }

            if (lastChar == '.') {
                lex.push_back(lastChar);
                getNextChar();

                while (lastChar >= '0' && lastChar <= '9') {
                    lex.push_back(lastChar);
                    getNextChar();
                }
            }

            if (lastChar != ' ' && lastChar != '\n') {
                backChar();
            }

            tokenList.push_back(Token(TK_NUMBER, lex, line, column));
            currentState = initialState;

            break;

        case keywordState:
            while ((lastChar >= 'a' && lastChar <= 'z') || (lastChar >= 'A' && lastChar <= 'Z') || lastChar == '_' || (lastChar >= '0' && lastChar <= '9')) {
                lex.push_back(lastChar);
                getNextChar();
            }

            if (lastChar != ' ' && lastChar != '\n') {
                backChar();
            }

            tokenType = scanKeyword(lex);
            tokenList.push_back(Token(tokenType, lex, line, column));
            currentState = initialState;

            break;

        case stringState:
            getNextChar();

            while (lastChar != '"' && lastChar != '\'') {
                lex.push_back(lastChar);
                getNextChar();
            }

            tokenList.push_back(Token(TK_COMMENT, lex, line, column));
            currentState = initialState;

            break;

        case commentState:
            getNextChar();

            while (lastChar != '\n') {
                lex.push_back(lastChar);
                getNextChar();
            }

            tokenList.push_back(Token(TK_NUMBER, lex, line, column));
            currentState = initialState;

            break;

        case operatorDelimiterState:
            lex.push_back(lastChar);

            while (scanOperator(lex) > -1 || scanDelimiter(lex) > -1) {
                getNextChar();
                lex.push_back(lastChar);
            }

            if (lastChar != ' ' && lastChar != '\n') {
                backChar();
            }
            lex.pop_back();

            tokenType = scanOperator(lex);
            if (tokenType >= 0) {
                tokenList.push_back(Token(tokenType, lex, line, column));
                currentState = initialState;
                break;
            }

            tokenType = scanDelimiter(lex);
            if (tokenType >= 0) {
                tokenList.push_back(Token(tokenType, lex, line, column));
                currentState = initialState;
                break;
            }

            if (lastChar != ' ' && lastChar != '\n') {
                printf("Lexical Error (Line:%d, Column:%d): unknown \"%c\" caracter!\n", line, column, lastChar);
            }

            currentState = initialState;
            break;

        default:
            break;
    }
}

void dumpTokenList() {
    for (vector<Token>::iterator i = tokenList.begin(); i != tokenList.end(); ++i) {
        i->dump();
    }
}

void scanIndentation() {
    int n = 0;
    getNextChar();
    while (lastChar == ' ' || lastChar == '\t') {
        getNextChar();
        n++;
    }

    backChar();

    if (n > 0 && (indentStack.empty() || n >= indentStack.top())) {
        indentStack.push(n);
        tokenList.push_back(Token(TK_INDENT, "INDENT", line, column));
    } else if (!indentStack.empty()) {
        indentStack.pop();
        tokenList.push_back(Token(TK_DEDENT, "DEDENT", line, column));
    }
}

int scanKeyword(string lex) {
    for (int i = 0; i < (sizeof(listKeywords)/sizeof(TokenList)); i++) {
        if (lex.compare(listKeywords[i].word) == 0) {
            return listKeywords[i].token;
        }
    }

    return TK_IDENTIFIER;
}

int scanOperator(string lex) {
    for (int l = 0; l < (sizeof(listOperators)/sizeof(TokenList)); l++) {
        if (lex.compare(listOperators[l].word) == 0) {
            return listOperators[l].token;
        }
    }

    return -1;
}

int scanDelimiter(string lex) {
    for (int i = 0; i < (sizeof(listDelimiters)/sizeof(TokenList)); i++) {
        if (lex.compare(listDelimiters[i].word) == 0) {
            return listDelimiters[i].token;
        }
    }

    return -1;
}

void getTokenSintatico() {
    Token nextT = tokenListSintatico.front();
    tokenListSintatico.erase(tokenListSintatico.begin());
    tkSintatico = nextT.getType();
}

int checkSintatico(int tokenType) {
    switch (tokenType) {
        case TK_DEF:
            return S();
            break;

        case TK_IDENTIFIER:
            return Attr();
            break;

        default:
            return 1;
            break;
    }
}

void executeSintatico() {
    tokenListSintatico = tokenList;
    while (tokenListSintatico.empty() == false) {
        getTokenSintatico();
        if (checkSintatico(tkSintatico) == 0) {
            printf("\nSintático Inválido!\n");
            exit(0);
        }
    }

    printf("\nSintático Válido!\n");
}
