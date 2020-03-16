//
//  interpreter.hpp
//  clox
//
//  Created by Marcelle Bonterre on 3/15/20.
//  Copyright © 2020 Marcelle Bonterre. All rights reserved.
//

#ifndef interpreter_hpp
#define interpreter_hpp
#pragma once


#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../scanner/scanner.hpp"
#include "../error_handler/error_handler.hpp"

namespace clox {

class Clox {
public:
    Clox(): err_handler{} {}
    Clox(ErrorHandler& e) : err_handler{e} {}
    
    void eval(const std::string& source);
    void eval_file(const std::string& path);
    void prompt();
    bool had_error() { return err_handler.has_error(); }
    void err_report() { err_handler.report(); }
private:
    ErrorHandler err_handler;
}; // class Clox

} // namespace clox


#endif /* interpreter_hpp */
