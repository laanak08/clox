//
//  scanner.cpp
//  clox
//
//  Created by Marcelle Bonterre on 3/15/20.
//  Copyright © 2020 Marcelle Bonterre. All rights reserved.
//
#include <vector>
#include <string>

#include "scanner.hpp"

using namespace clox;
using clox::TokenType;


std::string Scanner::get_identifier_val(){
    while( is_alphanumeric(peek()) ) next_char();
    // TODO check keyword map for token type
    return current_lexeme();
}

std::string Scanner::get_number_val(){
    while( is_digit(peek()) ) next_char();
    if( peek() == '.' && is_digit(peek_next()) ){
        next_char();
        while( is_digit(peek()) ) next_char();
    }
    
    return current_lexeme();
}

std::string Scanner::get_string_val(){
    while( peek() != '"' && !end_of_file() ) {
        if ( peek() == '\n' ) ++line;
        next_char();
    }
    
    if ( end_of_file() ) {
        Error err{line, "Unterminated string: "};
        err_handler.record(err);
        return "";
    }
    
    next_char();
    
    std::string val_w_quotes = current_lexeme();
    std::string val = val_w_quotes.substr(1, val_w_quotes.length() - 1);
    
    return val;
}

void Scanner::ignore_line(){
    while( peek() != '\n' && !end_of_file() ) next_char();
}

bool Scanner::match(const char c){
    if ( end_of_file() || source[current] != c ) return false;
    ++current;
    return true;
}

void Scanner::consume_token(TokenType type, std::string value = ""){
    tokens.push_back(Token{type, current_lexeme(), value, line});
}

void Scanner::scan_token(){
    char c{next_char()};
    switch (c) {
        case '.': consume_token(DOT); break;
        case ',': consume_token(COMMA); break;
        case ';': consume_token(SEMICOLON); break;
        case '(': consume_token(LEFT_PAREN); break;
        case ')': consume_token(RIGHT_PAREN); break;
        case '[': consume_token(LEFT_BRACE); break;
        case ']': consume_token(RIGHT_BRACE); break;
        case '+': consume_token(PLUS); break;
        case '-': consume_token(MINUS); break;
        case '*': consume_token(STAR); break;
        
        case '!': consume_token(match('=') ? BANG_EQUAL : BANG); break;
        case '=': consume_token(match('=') ? EQUAL_EQUAL : EQUAL); break;
        case '>': consume_token(match('=') ? GREATER_EQUAL : GREATER); break;
        case '<': consume_token(match('=') ? LESS_EQUAL : LESS); break;
        
        case '"': consume_token(STRING, get_string_val()); break;
        case '/': !match('/') ? consume_token(SLASH) : ignore_line(); break;
        
        case ' ': case '\r': case '\t': break; // ignore whitespace
        
        case '\n': line++; break;
        default:
            if ( is_digit(c) ) {
                consume_token(NUMBER, get_number_val());
            } else if ( is_alpha(c) ) {
                consume_token(IDENTIFIER, get_identifier_val());
            } else {
                std::string msg{"Unexpected character: "}; msg += c;
                Error err{line, msg};
                err_handler.record(err);
            }
    }
}

std::vector<Token> Scanner::scan(){
    while ( !end_of_file() ) {
        start = current;
        scan_token();
    }
    
    tokens.push_back(Token{E_O_F, line});
    return tokens;
}
