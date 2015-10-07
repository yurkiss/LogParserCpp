/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */




/* 
 * File:   Parser.cpp
 * Author: yrid
 * 
 * Created on October 6, 2015, 12:14 PM
 */

#include "Parser.h"
#include <thread>


Parser::Parser(const Parser& orig) : strategy (orig.strategy)
{
    std::cout << "Copy constructor" << std::endl;
}

//Parser::Parser(ParsingStrategy& strategy) : strategy(strategy)
Parser::Parser(const std::string fileName, const std::string lookingFor, ParsingStrategy& strategy) 
    : strategy(strategy), fileName(fileName), lookingFor(lookingFor)
{

    this->fileStream = new std::ifstream;
    std::cout << "[" << std::this_thread::get_id() << "] Trying to open " << fileName << " file..." << std::endl;
    this->fileStream->open(fileName, std::ios::in);
    if(fileStream->is_open())
    {
        std::cout << "file is opened" << std::endl;
    }
    std::cout << &strategy << std::endl;
}

//Parser::Parser() : strategy(*new LineParsingStrategy)
//{
//  std::cout << "Default constructor" << std::endl;  
//  std::cout << &strategy << std::endl;
//}

Parser::~Parser()
{
}

