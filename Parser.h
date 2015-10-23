/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: yrid
 *
 * Created on October 6, 2015, 12:14 PM
 */

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>

#include "BaseParsingStrategy.h"


class Parser
{    
    public:	
	Parser(const std::string fileName, const std::string lookingFor);			
	~Parser();	
	
	template<template<typename> class _PS = LineParsingStrategy, typename _FS = StandartFindStrategy>
	void parse(std::streampos from = std::ios::beg, std::streampos to = std::ios::end)
	{ 
	    _PS<_FS> _strategy;	    
	    _strategy.parse(m_fileStream, m_lookingFor, from, to);
	};
	
    private:	
	const std::string m_fileName;
	const std::string m_lookingFor;
	std::ifstream m_fileStream;
	
	Parser(const Parser& orig); //copy constructor
	
};

#endif /* PARSER_H */

