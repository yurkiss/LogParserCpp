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

#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <cmath>
#include <vector>
#include "FindStrategy.h"


template <typename T_FindStrategy = StandartFindStrategy>
class ParsingStrategy
{        
    
    public:
	ParsingStrategy(){}    
	virtual ~ParsingStrategy(){}	
	
	virtual void parsingLoop(std::ifstream &fileStream, const std::string lookingFor, const std::streampos fr, const std::streampos to) const = 0;
	
	void parse(std::ifstream &fileStream, const std::string lookingFor, const std::streampos fromPos = std::ios::beg, const std::streampos toPos = std::ios::end) const 
	{
	    
	    if (fileStream.is_open())
	    {
		std::streampos fr = fromPos;
		if (fr == std::ios::beg)
		{
		    fr = 0;
		}

		std::streampos to = toPos;
		if (to == std::ios::end)
		{
		    fileStream.seekg(0, std::ios::end);
		    to = fileStream.tellg();
		}

		fileStream.seekg(fr, std::ios::beg);

		parsingLoop(fileStream, lookingFor, fr, to);

	    }

	}
	
};

template <typename T_FindStrategy = StandartFindStrategy> 
class LineParsingStrategy : public ParsingStrategy<T_FindStrategy>
{
    public:
	
	void parsingLoop(std::ifstream &fileStream, const std::string lookingFor, const std::streampos fr, const std::streampos to) const override
	{
	    
	    std::cout << "Line parsing strategy started";
	    
	    std::string s = "";
	    std::streampos sPos = fr;

	    T_FindStrategy findStrategy;

	    long int found = 0;
	    while (std::getline(fileStream, s))
	    {
		sPos = fileStream.tellg();
		if (sPos <= to)
		{
		    std::vector<std::string::size_type> v = findStrategy.find(s, lookingFor, 0);                    
		    if (!v.empty())
		    {                        
			found += v.size();
		    }
		}
		else
		{
		    break;
		}
	    }
	    
	    std::cout << "[" << std::this_thread::get_id() << "] Stopped at " << sPos << ", boundaries are from " << fr << " to " << to << ", found " << found << " matches." << std::endl;
            
	}
	

};


template <typename T_FindStrategy = StandartFindStrategy> 
class SymbolParsingStrategy : public ParsingStrategy<T_FindStrategy>
{
    public:   
	
        void parsingLoop(std::ifstream &fileStream, const std::string lookingFor, const std::streampos fr, const std::streampos to) const override
	{
	    std::cout << "Symbol parsing strategy started";
	    
	    std::streampos sPos;
	    std::string s;
	    char c;	    
	    long int found = 0;
	    
	    T_FindStrategy findStrategy;

	    sPos = fr;
	    while (fileStream.get(c))
	    {
		sPos = fileStream.tellg();
		if (sPos <= to)
		{
		    s.push_back(c);
		    if (c == '\n' || sPos == to)
		    {

			std::vector<std::string::size_type> v = findStrategy.find(s, lookingFor, 0);
			if (!v.empty())
			{
			    found = v.size();
			    //if(v.size() > 0)			       
			    //std::cout << found << std::endl;
			}

			s.clear();
		    }
		}
		else
		{
		    break;
		}

	    }
	    std::cout << "[" << std::this_thread::get_id() << "] Stopped at " << sPos << ", boundaries are from " << fr << " to " << to << ", found " << found << " matches." << std::endl;

	}
	
};

/**/

#endif /* BASEPARSINGSTRATEGY_H */

