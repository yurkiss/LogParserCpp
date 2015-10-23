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

class FindStrategy
{
    
    protected:
	
	static constexpr int base = 33;

	unsigned long int hash(const std::string &str) const
	{
	    unsigned long int hash = 5381;
	    long int length = str.length() - 1;

	    for (int i = 0; i <= length; ++i)
	    {
		hash = hash * base + str[i];
	    }

	    return hash;
	}

	unsigned long int getNextHash(unsigned long int prevHash, char prevFirstChar, char newLastChar, long n) const
	{
	    return (prevHash - 5381 * pow(base, n) - pow(base, n - 1) * prevFirstChar) * base + 5381 * pow(base, n) + newLastChar;
	}
    
    
    public:
	FindStrategy(){}
	virtual ~FindStrategy(){}
	
	/**
	 * This find should be overrode by derived classes
         * @param str
         * @param what
         * @param from
         * @return 
         */
	virtual std::vector<std::string::size_type> find(const std::string &str, const std::string &what, std::string::size_type from = 0) = 0;

	/**
	 * Search a substring in a string using Rabin–Karp algorithm
	 * Overloaded find return single position for cases when you want to find single occurrence of what.
	 * 
	 * @param str
	 * @param what
	 * @param from
	 * @return position in string where what argument was found
	 */
	std::string::size_type find(const std::string &str, const std::string &what, std::string::size_type from = 0) const
	{
	    const long int lenWhat = what.length();
	    const long int lenStr = str.length();

	    if (lenWhat <= lenStr && from <= lenStr && from + lenWhat <= lenStr)
	    {

		unsigned long int hashWhat = hash(what);
		std::string substr = str.substr(from, lenWhat);
		unsigned long int h = hash(substr);

		if (hashWhat == h)
		{
		    return from;
		}

		for (long int i = from + 1; i + lenWhat <= lenStr; ++i)
		{
		    char prevFirstChar = str[i - 1];
		    char newLastChar = str[lenWhat + i - 1];
		    h = getNextHash(h, prevFirstChar, newLastChar, lenWhat);

		    if (hashWhat == h)
		    {
			//std::cout << what << "(" << hashWhat << ") == " << str.substr(i, lenWhat) << "(" << h << ") " << str << std::endl;
			return i;
		    }

		}
		return std::string::npos;
	    }
	    return std::string::npos;
	}

	/**
	 * Looking for all occurrences of what argument in line
	 * @param line
	 * @param what
	 * @return vector with occurrences positions
	 */
	std::vector<std::string::size_type> hashFindAllOccurrences(const std::string &line, const std::string &what)
	{
	    std::vector<std::string::size_type> result;

	    const long int lenWhat = what.length();
	    const long int lenStr = line.length();

	    std::string::size_type from = 0;

	    if (lenWhat <= lenStr && from <= lenStr && from + lenWhat <= lenStr)
	    {

		unsigned long int hashWhat = hash(what);
		std::string substr = line.substr(from, lenWhat);
		unsigned long int h = hash(substr);

		if (hashWhat == h)
		{
		    result.push_back(from);
		    from = from + lenWhat - 1;
		}

		for (auto i = from + 1; i + lenWhat <= lenStr;)
		{
		    char prevFirstChar = line[i - 1];
		    char newLastChar = line[lenWhat + i - 1];
		    h = getNextHash(h, prevFirstChar, newLastChar, lenWhat);

		    if (hashWhat == h)
		    {
			result.push_back(i);
			i += lenWhat - 1;
		    }
		    else
		    {
			++i;
		    }
		}

	    }

	    return result;
	}
};

class HashFindStrategy : public FindStrategy
{
    public:
	std::vector<std::string::size_type> find(const std::string &str, const std::string &what, std::string::size_type from = 0) override
	{
	    return hashFindAllOccurrences(str, what);
	}
    
};

class HashFindStrategyOld : public FindStrategy
{
public:

    std::vector<std::string::size_type> find(const std::string &str, const std::string &what, std::string::size_type from = 0) override
    {

	std::vector<std::string::size_type> result;

	const long int lenWhat = what.length();
	const long int lenStr = line.length();

	std::string::size_type from = 0;

	if (lenWhat <= lenStr && from <= lenStr && from + lenWhat <= lenStr)
	{

	    unsigned long int hashWhat = hash(what);
	    std::string substr = line.substr(from, lenWhat);
	    unsigned long int h = hash(substr);

	    if (hashWhat == h)
	    {
		result.push_back(from);
		from = from + lenWhat - 1;
	    }

	    for (auto i = from + 1; i + lenWhat <= lenStr;)
	    {
		char prevFirstChar = line[i - 1];
		char newLastChar = line[lenWhat + i - 1];
		h = getNextHash(h, prevFirstChar, newLastChar, lenWhat);

		if (hashWhat == h)
		{
		    result.push_back(i);
		    i += lenWhat - 1;
		}
		else
		{
		    ++i;
		}
	    }

	}
    }

};



class StandartFindStrategy : public FindStrategy
{
public:

    std::vector<std::string::size_type> find(const std::string &str, const std::string &what, std::string::size_type from = 0) override 
    {
	
	std::vector<std::string::size_type> result;
	std::string::size_type pos = str.find(what, from);
	while (pos != std::string::npos && pos < str.length())
	{
	    result.push_back(pos);
	    //std::cout << pos << ":" << s.length() << " ... " << s << std::endl;
	    pos = str.find(what, pos + what.length() - 1);
	}
	return result;
    }

};


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
	    
	    std::cout << "Line parsing strategy started" << std::endl;
	    
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
			//if(v.size() > 0)			       
			//std::cout << v.size() << std::endl;
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

/*
template <typename T_FindStrategy = StandartFindStrategy> 
class SymbolParsingStrategy : public ParsingStrategy<T_FindStrategy>
{
    public:   
	
	void parsingLoop(std::ifstream * const fileStream, const std::string lookingFor, const std::streampos fr, const std::streampos to) const override
	{
	    std::cout << "Symbol parsing strategy started" << std::endl;
	    
	    std::streampos sPos;
	    std::string s;
	    char c;	    
	    long int found = 0;
	    
	    T_FindStrategy findStrategy;

	    sPos = fr;
	    while (fileStream->get(c))
	    {
		sPos = fileStream->tellg();
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

