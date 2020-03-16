//
//  error_handler.hpp
//  clox
//
//  Created by Marcelle Bonterre on 3/15/20.
//  Copyright © 2020 Marcelle Bonterre. All rights reserved.
//

#ifndef error_handler_hpp
#define error_handler_hpp
#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace clox {

class Error {
private:
    size_t line;
    std::string ctx;
    std::string msg;
public:
    Error(size_t line, const std::string& ctx, const std::string& msg) : line{line}, ctx{ctx}, msg{msg} {};
    Error(size_t line, const std::string& msg) : line{line}, ctx{""}, msg{msg} {};
    void print(){ std::cout << "[line " << line << "] Error" << ctx <<  ": " + msg << std::endl; }
}; // class Error

class ErrorHandler {
private:
    std::vector<Error> errors;
public:
    ErrorHandler() : errors{} {}
    ErrorHandler(Error& e) : errors{e} {}
    void report() { for (auto& e : errors ) { e.print(); } }
    bool has_error() { return !errors.empty(); }
    void record(Error& e) { errors.push_back(e); }
    void reset() { errors.clear(); }
}; // class ErrorHandler

} // namespace clox

#endif /* error_handler_hpp */
