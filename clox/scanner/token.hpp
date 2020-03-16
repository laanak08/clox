//
//  token.hpp
//  clox
//
//  Created by Marcelle Bonterre on 3/15/20.
//  Copyright © 2020 Marcelle Bonterre. All rights reserved.
//

#ifndef token_hpp
#define token_hpp
#pragma once

#include <string>

namespace clox {
enum TokenType {
    // strictly single char
    DOT, COMMA, SEMICOLON,
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE,
    PLUS, MINUS, SLASH, STAR,
    
    // ambiguous single chars
    BANG, EQUAL, GREATER, LESS,
    
    // two char
    BANG_EQUAL,
    EQUAL_EQUAL,
    GREATER_EQUAL,
    LESS_EQUAL,
    
    // literals
    IDENTIFIER, STRING, NUMBER,
    
    // reserved keywords
    CLASS, SUPER, THIS,
    TRUE, FALSE,
    IF, ELSE, AND, OR,
    FOR, WHILE,
    VAR, NIL,
    FUN, RETURN,
    PRINT,
    
    E_O_F
    
}; // enum TokenType

class Token {
public:
    Token(TokenType type, size_t line) : type{type}, lexeme{""}, literal{""}, line{line} {}
    Token(TokenType type, const std::string& lexeme, size_t line) : type{type}, lexeme{lexeme}, literal{""}, line{line} {}
    Token(TokenType type, const std::string& lexeme, const std::string& literal, size_t line) : type{type}, lexeme{lexeme}, literal{literal}, line{line} {}
private:
    TokenType type;
    std::string lexeme;
    std::string literal;
    size_t line;
}; // class Token

} // namespace clox

#endif /* token_hpp */
