//
//  main.cpp
//  clox
//
//  Created by Marcelle Bonterre on 3/14/20.
//  Copyright © 2020 Marcelle Bonterre. All rights reserved.
//

#include <sysexits.h>
#include <iostream>

#include "interpreter/interpreter.hpp"

using clox::Clox;

int main(int argc, const char * argv[]) {
    if ( argc > 2 ) {
        std::cout << "Usage: clox [script]" << std::endl;
        return EX_USAGE;
    }
    
    Clox clox_lang{};
    
    if ( argc == 2 ) {
        clox_lang.eval_file(argv[1]);
        if ( clox_lang.had_error() ) {
            clox_lang.err_report();
            return EX_DATAERR;
        }
    } else {
        clox_lang.prompt();
    }
    
    return EX_OK;
}
