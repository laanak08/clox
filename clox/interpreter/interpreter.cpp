//
//  interpreter.cpp
//  clox
//
//  Created by Marcelle Bonterre on 3/15/20.
//  Copyright © 2020 Marcelle Bonterre. All rights reserved.
//

#include "interpreter.hpp"

using namespace clox;

void Clox::eval(const std::string& source){
    Scanner scanner{source, err_handler};
    std::vector<Token> tokens = scanner.scan();
    if ( err_handler.has_error() ) return;
    
//    Parser parser{tokens, err_handler};
//    Ast ast = parser.parse();
//    if ( err_handler.has_error() ) return;
    
//    AstPrinter pp;
//    pp.print(ast);
}

void Clox::eval_file(const std::string& path){
    std::ifstream file{path};
    std::ostringstream ss;
    ss << file.rdbuf();
    file.close();
    eval(ss.str());
}

void Clox::prompt(){
    while ( true ) {
        std::cout << ">>> ";
        std::string line;
        getline(std::cin, line);
        eval(line);
        if ( err_handler.has_error() ) {
            err_handler.report();
            err_handler.reset();
        }
    }
}
