/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseParsingStrategy.h
 * Author: yrid
 *
 * Created on October 6, 2015, 12:16 PM
 */

#ifndef BASEPARSINGSTRATEGY_H
#define BASEPARSINGSTRATEGY_H

#include <fstream>

class ParsingStrategy
{    
    public:
	ParsingStrategy(){};    
	virtual ~ParsingStrategy(){};
	virtual void parse(std::ifstream* fileStream, const std::streampos fromPos = std::ios::beg, const std::streampos toPos = std::ios::end) =0;
	
};

class LineParsingStrategy : public ParsingStrategy
{
    virtual void parse(std::ifstream* fileStream, const std::streampos fromPos = std::ios::beg, const std::streampos toPos = std::ios::end) 
    override 
    {		
	if(fileStream->is_open())
	{	
	    std::streampos fr = fromPos;	
	    if( fr == std::ios::beg )
	    {
		fr = 0;
	    }

	    std::streampos to = toPos;
	    if (to == std::ios::end)
	    {
		fileStream->seekg(0, std::ios::end);
		to = fileStream->tellg();
	    }    
	    
	}
	
    }
};

class SymbolParsingStrategy : public ParsingStrategy
{

    virtual void parse(std::ifstream* fileStream, const std::streampos fromPos = std::ios::beg, const std::streampos toPos = std::ios::end)
    override
    {
	if (fileStream->is_open())
	{
	    std::streampos fr = fromPos;
	    if (fr == std::ios::beg)
	    {
		fr = 0;
	    }

	    std::streampos to = toPos;
	    if (to == std::ios::end)
	    {
		fileStream->seekg(0, std::ios::end);
		to = fileStream->tellg();
	    }

	}

    }
};



#endif /* BASEPARSINGSTRATEGY_H */

