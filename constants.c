#define TKId 1
#define TKVoid 2
#define TKInt 3
#define TKFloat 4
#define TKVirgula 5
#define TKDoisPontos 6
#define TKAbreParenteses 7
#define TKFechaParenteses 8
#define TKAtrib 9
#define TKPontoEVirgula 10
#define TKAbreChaves 11
#define TKFechaChaves 12
#define TKSoma 13
#define TKDuploMais 14
#define TKProd 15
#define TKChar 16
#define TKSub 17
#define TKFimArquivo 18
#define TKLong 19
#define TKShort 20
#define TKIf 21
#define TKFor 22
#define TKWhile 23
#define TKAbreColchete 24
#define TKFechaColchete 25
#define TKReturn 26
#define TKMaior 27
#define TKMenor 28
#define TKCteInt 29
#define TKMulAtri 30
#define TKTokenInvalido 163625245
#define false 0
#define true 1
#define TKElse 123
#define TKError 999
#define TK2dots 1234
#define TKAspas 90909

#define TK_FILE_END -1
#define TK_ERROR -2

#define TK_STRING 236923
#define TK_INTEGER 236924
#define TK_NEWLINE 2134234
#define TK_INDENT 12354
#define TK_DEDENT 12354

// Tokens for keywords
#define TK_AND 0
#define TK_DEL 0
#define TK_FROM 0
#define TK_NOT 0
#define TK_WHILE 0
#define TK_AS 0
#define TK_ELIF 0
#define TK_GLOBAL 0
#define TK_OR 0
#define TK_WITH 0
#define TK_ASSERT 0
#define TK_ELSE 0
#define TK_IF 0
#define TK_PASS 0
#define TK_YIELD 0
#define TK_BREAK 0
#define TK_EXCEPT 0
#define TK_IMPORT 0
#define TK_PRINT 0
#define TK_CLASS 0
#define TK_EXEC 0
#define TK_IN 0
#define TK_RAISE 0
#define TK_CONTINUE 0
#define TK_FINALLY 0
#define TK_IS 0
#define TK_RETURN 0
#define TK_DEF 0
#define TK_FOR 0
#define TK_LAMBDA 0
#define TK_TRY 0

// Tokens for operators
#define TK_SUM 0
#define TK_SUB 0
#define TK_MUL 0
#define TK_DIV 0
#define TK_PERC 0
#define TK_MM 0
#define TK_LL 0
#define TK_E 0
#define TK_L 0
#define TK_Z 0
#define TK_IGUAL 0
#define TK_DIFF 0
#define TK_DIFF 0

// Tokens for delemiters
#define TK_DELM 0

struct tokenList {
    char word[20];
    int token;
};

struct tokenList listKeywords[] = {
    { "and", TK_AND },
    { "del", TK_DEL },
    { "from", TK_FROM },
    { "not", TK_NOT },
    { "while", TK_WHILE },
    { "as", TK_AS },
    { "elif", TK_ELIF },
    { "global", TK_GLOBAL },
    { "or", TK_OR },
    { "with", TK_WITH },
    { "assert", TK_ASSERT },
    { "else", TK_ELSE },
    { "if", TK_IF },
    { "pass", TK_PASS },
    { "yield", TK_YIELD },
    { "break", TK_BREAK },
    { "except", TK_EXCEPT },
    { "import", TK_IMPORT },
    { "print", TK_PRINT },
    { "class", TK_CLASS },
    { "exec", TK_EXEC },
    { "in", TK_IN },
    { "raise", TK_RAISE },
    { "continue", TK_CONTINUE },
    { "finally", TK_FINALLY },
    { "is", TK_IS },
    { "return", TK_RETURN },
    { "def", TK_DEF },
    { "for", TK_FOR },
    { "lambda", TK_LAMBDA },
    { "try", TK_TRY },
};

struct tokenList listOperators[] = {
    { "+", TK_SUM },
    { "-", TK_SUB },
    { "*", TK_MUL },
    { "**", TK_Z },
    { "/", TK_DIV },
    { "//", TK_Z },
    { "%", TK_PERC },
    { "<<", TK_MM },
    { ">>", TK_LL },
    { "&", TK_E },
    { "|", TK_L },
    { "^", TK_Z },
    { "~", TK_Z },
    { "<", TK_Z },
    { ">", TK_Z },
    { "<=", TK_Z },
    { ">=", TK_Z },
    { "==", TK_IGUAL },
    { "!=", TK_DIFF },
    { "<>", TK_DIFF },
};

struct tokenList listDelimiters[] = {
    { "(", TK_DELM },
    { ")", TK_DELM },
    { "[", TK_DELM },
    { "]", TK_DELM },
    { "{", TK_DELM },
    { "}", TK_DELM },
    { "@", TK_DELM },
    { ",", TK_DELM },
    { ":", TK_DELM },
    { ".", TK_DELM },
    { "`", TK_DELM },
    { "=", TK_DELM },
    { ";", TK_DELM },
    { "+=", TK_DELM },
    { "-=", TK_DELM },
    { "*=", TK_DELM },
    { "/=", TK_DELM },
    { "//=", TK_DELM },
    { "%=", TK_DELM },
    { "&=", TK_DELM },
    { "|=", TK_DELM },
    { "^=", TK_DELM },
    { ">>=", TK_DELM },
    { "<<=", TK_DELM },
    { "**=", TK_DELM },
};

void getToken();
void nextChar();

void scanIndentation();
int scanIdentifier();
int scanKeyword();
int scanLiteral();
int scanOperator();
int scanDelimiter();
