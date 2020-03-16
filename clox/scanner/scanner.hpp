//
//  scanner.hpp
//  clox
//
//  Created by Marcelle Bonterre on 3/15/20.
//  Copyright © 2020 Marcelle Bonterre. All rights reserved.
//

#ifndef scanner_hpp
#define scanner_hpp
#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "token.hpp"
#include "../error_handler/error_handler.hpp"

namespace clox {

class Scanner {
public:
    Scanner(const std::string& source, ErrorHandler& err_handler) : source{source},
        tokens{},
        err_handler{err_handler},
        keywords{
            {"class", CLASS},
            {"super", SUPER},
            {"this", THIS},
            {"true", TRUE},
            {"false", FALSE},
            {"if", IF},
            {"else", ELSE},
            {"and", AND},
            {"or", OR},
            {"for", FOR},
            {"while", WHILE},
            {"var", VAR},
            {"nil", NIL},
            {"fun", FUN},
            {"return", RETURN},
            {"print", PRINT}
        } {};
    std::vector<Token> scan();
private:
    std::string source;
    std::vector<Token> tokens;
    ErrorHandler err_handler;

private:
    void scan_token();
    bool match(const char c);
    std::string get_number_val();
    std::string get_string_val();
    std::string get_identifier_val();
    TokenType identifer_token_type(const std::string& s);
    void ignore_line();
    
    bool is_alphanumeric(const char c) const { return is_alpha(c) || is_digit(c); }
    bool is_alpha(const char c) const { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'; }
    void consume_token(TokenType type, std::string value);
    bool end_of_file(int inc = 0){ return current + inc >= source.length(); }
    char next_char(){ ++current; return source[current - 1]; }
    bool is_digit(const char c) const { return c >= '0' && c <= '9'; }
    std::string current_lexeme() { return source.substr(start, current - start); }
    char peek(int inc = 0){ return !end_of_file(inc) ? source[current+inc] : '\0'; }
    char peek_next(){ return peek(1); }
    
private:
    size_t start{0};
    size_t current{0};
    size_t line{1};
    std::unordered_map<std::string, TokenType> keywords;
}; // class Scanner

} // namespace clox

#endif /* scanner_hpp */
