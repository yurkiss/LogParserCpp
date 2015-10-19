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


Parser::Parser(const Parser& orig) : m_strategy (orig.m_strategy)
{
    std::cout << "Copy constructor" << std::endl;
}

Parser::Parser(const std::string fileName, const std::string lookingFor, ParsingStrategy *const strategy) 
    : m_strategy(strategy), m_fileName(fileName), m_lookingFor(lookingFor)
{

    this->m_fileStream = new std::ifstream;
    std::cout << "[" << std::this_thread::get_id() << "] Trying to open " << fileName << " file..." << std::endl;
    this->m_fileStream->open(fileName, std::ios::in);
}

Parser::Parser(const std::string fileName, const std::string lookingFor) : m_fileName(fileName), m_lookingFor(lookingFor)
{    
    m_strategy = new LineParsingStrategy;
    
}

Parser::~Parser()
{
    
}

