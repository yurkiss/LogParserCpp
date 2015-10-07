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
	//Parser();
	Parser(const std::string fileName, const std::string lookingFor, ParsingStrategy& strategy = *new LineParsingStrategy);	
	//Parser(ParsingStrategy& strategy);
	Parser(const Parser& orig);
	virtual ~Parser();
	void setParsingStrategy(ParsingStrategy& strategy) { this->strategy = strategy; }
	void parse(std::streampos from = std::ios::beg, std::streampos to = std::ios::end){ this->strategy.parse(fileStream, from, to); }
    private:
	ParsingStrategy& strategy;
	const std::string fileName;
	const std::string lookingFor;
	std::streampos from;
	std::streampos to;
	std::ifstream* fileStream;
	
};

#endif /* PARSER_H */

