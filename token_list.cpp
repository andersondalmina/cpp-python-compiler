#define TK_IDENTIFIER 1

#define TK_STRING 2
#define TK_NUMBER 3
#define TK_NEWLINE 4
#define TK_INDENT 5
#define TK_DEDENT 6
#define TK_COMMENT 82

// Tokens for keywords
#define TK_AND 7
#define TK_DEL 8
#define TK_FROM 9
#define TK_NOT 10
#define TK_WHILE 11
#define TK_AS 12
#define TK_ELIF 13
#define TK_GLOBAL 14
#define TK_OR 15
#define TK_WITH 16
#define TK_ASSERT 17
#define TK_ELSE 18
#define TK_IF 19
#define TK_PASS 20
#define TK_YIELD 21
#define TK_BREAK 22
#define TK_EXCEPT 23
#define TK_IMPORT 24
#define TK_PRINT 25
#define TK_CLASS 26
#define TK_EXEC 27
#define TK_IN 28
#define TK_RAISE 29
#define TK_CONTINUE 30
#define TK_FINALLY 31
#define TK_IS 32
#define TK_RETURN 33
#define TK_DEF 34
#define TK_FOR 35
#define TK_LAMBDA 36
#define TK_TRY 37

// Tokens for operators
#define TK_SUM 38
#define TK_SUM_SUM 381
#define TK_SUB 39
#define TK_SUB_SUB 391
#define TK_MUL 40
#define TK_MUL_MUL 41
#define TK_DIV 42
#define TK_DIV_DIV 43
#define TK_PERC 44
#define TK_GG 45
#define TK_LL 46
#define TK_E 47
#define TK_L 48
#define TK_Z 49
#define TK_IGUAL 50
#define TK_DIFF 51
#define TK_LOWER 53
#define TK_GREATER 54
#define TK_GREATER_EQUAL 55
#define TK_LOWER_EQUAL 56

// Tokens for delemiters
#define TK_OPEN_PARENTESI 57
#define TK_CLOSE_PARENTESI 58
#define TK_OPEN_BRACKET 59
#define TK_CLOSE_BRACKET 60
#define TK_OPEN_KEY 61
#define TK_CLOSE_KEY 62
#define TK_ARROBA 63
#define TK_COMA 64
#define TK_TWO_DOTS 65
#define TK_DOT 66
#define TK_DELM 67
#define TK_ATTR 68
#define TK_SEMICON 69
#define TK_PLUS_IGUAL 70
#define TK_MINUS_IGUAL 71
#define TK_MUL_IGUAL 72
#define TK_DIV_IGUAL 73
#define TK_DIV_DIV_IGUAL 74
#define TK_PERC_IGUAL 75
#define TK_E_IGUAL 76
#define TK_L_IGUAL 77
#define TK_Z_IGUAL 78
#define TK_GG_IGUAL 79
#define TK_LL_IGUAL 80
#define TK_MM_IGUAL 81

struct TokenList {
    char word[20];
    int token;
};

struct TokenList listKeywords[] = {
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

struct TokenList listOperators[] = {
    { "+", TK_SUM },
    { "++", TK_SUM_SUM },
    { "-", TK_SUB },
    { "--", TK_SUB_SUB },
    { "*", TK_MUL },
    { "**", TK_MUL_MUL },
    { "/", TK_DIV },
    { "//", TK_DIV_DIV },
    { "%", TK_PERC },
    { "<<", TK_GG },
    { ">>", TK_LL },
    { "&", TK_E },
    { "|", TK_L },
    { "^", TK_Z },
    { "~", TK_DIFF },
    { "<", TK_LOWER },
    { ">", TK_GREATER },
    { "<=", TK_LOWER_EQUAL },
    { ">=", TK_GREATER_EQUAL },
    { "==", TK_IGUAL },
    { "!=", TK_DIFF },
    { "<>", TK_DIFF },
};

struct TokenList listDelimiters[] = {
    { "(", TK_OPEN_PARENTESI },
    { ")", TK_CLOSE_PARENTESI },
    { "[", TK_OPEN_BRACKET },
    { "]", TK_CLOSE_BRACKET },
    { "{", TK_OPEN_KEY },
    { "}", TK_CLOSE_KEY },
    { "@", TK_ARROBA },
    { ",", TK_COMA },
    { ":", TK_TWO_DOTS },
    { ".", TK_DOT },
    { "`", TK_DELM },
    { "=", TK_ATTR },
    { ";", TK_SEMICON },
    { "+=", TK_PLUS_IGUAL },
    { "-=", TK_MINUS_IGUAL },
    { "*=", TK_MUL_IGUAL },
    { "/=", TK_DIV_IGUAL },
    { "//=", TK_DIV_DIV_IGUAL },
    { "%=", TK_PERC_IGUAL },
    { "&=", TK_E_IGUAL },
    { "|=", TK_L_IGUAL },
    { "^=", TK_Z_IGUAL },
    { ">>=", TK_GG_IGUAL },
    { "<<=", TK_LL_IGUAL },
    { "**=", TK_MM_IGUAL },
};
