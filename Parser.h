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
	Parser(const std::string fileName, const std::string lookingFor, ParsingStrategy *const strategy);	
	Parser(const Parser& orig); //copy constructor
	virtual ~Parser();
	//void setParsingStrategy(const ParsingStrategy *const i_strategy) { m_strategy = i_strategy; }
	void parse(std::streampos from = std::ios::beg, std::streampos to = std::ios::end){ m_strategy->parse(m_fileStream, m_lookingFor, from, to); }	
	void parse(const ParsingStrategy *const strategy, std::streampos from = std::ios::beg, std::streampos to = std::ios::end){};
	
    private:
	ParsingStrategy *m_strategy;
	const std::string m_fileName;
	const std::string m_lookingFor;
	std::ifstream *m_fileStream;
	
};

#endif /* PARSER_H */

