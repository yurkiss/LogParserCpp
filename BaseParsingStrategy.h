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
#include <thread>
#include <string>


class ParsingStrategy
{        
    public:
	ParsingStrategy(){};    
	virtual ~ParsingStrategy(){};
	virtual void parse(std::ifstream *const fileStream, const std::string lookingFor, const std::streampos fromPos = std::ios::beg, const std::streampos toPos = std::ios::end) const =0;
	
};

class LineParsingStrategy : public ParsingStrategy
{
    public:
	virtual void parse(std::ifstream *const fileStream, const std::string lookingFor, const std::streampos fromPos = std::ios::beg, const std::streampos toPos = std::ios::end) const override 
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

		fileStream->seekg(fr, std::ios::beg);

		std::string s = "";
		std::streampos sPos = fr;

		long int found = 0;
		while (std::getline(*fileStream, s))
		{
		    sPos = fileStream->tellg();
		    if (sPos <= to)
		    {
			std::string::size_type pos = s.find(lookingFor, 0);
			while (pos != std::string::npos && pos < s.length())
			{
			    ++found;
			    //std::cout << pos << ":" << s.length() << " ... " << s << std::endl;
			    pos = s.find(lookingFor, pos + 1);
			}
		    }
		    else
		    {
			break;
		    }
		}
		std::cout << "[" << std::this_thread::get_id() << "] Stopped at " << sPos << ", boundaries are from " << fr << " to " << to << ", found " << found << " matches." << std::endl;

	    }

	}
};

class SymbolParsingStrategy : public ParsingStrategy
{
    public:    
	virtual void parse(std::ifstream * const fileStream, const std::string lookingFor, const std::streampos fromPos = std::ios::beg, const std::streampos toPos = std::ios::end) const override
	{

	    std::cout << "Symbol parsing strategy started" << std::endl;

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

		fileStream->seekg(fr, std::ios::beg);


		std::streampos sPos;	    
		char c;
		long int found = 0;

		//std::string* ss = new std::string;
		std::string s;

		sPos = fr;
		while(fileStream->get(c))
		{
		    sPos = fileStream->tellg();
		    //++sPos;		
		    if(sPos <= to)
		    {       		    		   
			s.push_back(c);
			if (c == '\n' || sPos == to)
			{ 
			    std::string::size_type pos = s.find(lookingFor, 0);
			    while (pos != std::string::npos && pos < s.length())
			    {
				++found;
				//std::cout << pos << ":" << s.length() << " ... " << s << std::endl;
				pos = s.find(lookingFor, pos + 1);
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

	}
};



#endif /* BASEPARSINGSTRATEGY_H */

