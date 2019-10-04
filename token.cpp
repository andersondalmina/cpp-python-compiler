#include <string>

using namespace std;

class Token {
    int type;
    string value;
    int line;
    int column;

    public:
        Token(int, string, int, int);
        void dump();
};

Token::Token(int type, string value, int line, int column) {
    this->type = type;
    this->value = value;
    this->line = line;
    this->column = column;
}

void Token::dump() {
    printf("Token (Type: %d, Char: '%s', Line: %d, Column: %d)\n", this->type, this->value.c_str(), this->line, this->column);
}
