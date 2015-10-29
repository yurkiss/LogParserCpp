/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FindStrategy.h
 * Author: yrid
 *
 * Created on October 26, 2015, 11:18 AM
 */

#ifndef FINDSTRATEGY_H
#define FINDSTRATEGY_H

#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <cmath>
#include <vector>

/**  
 * Abstarct FindStrategy class represents basic abstraction of find().
 * Contains useful hash functions.
 */
class FindStrategy
{
    protected:

	static constexpr int base = 33;
	
	virtual unsigned long int hash(const std::string &str) const
	{
	    unsigned long int hash = 5381;
	    long int length = str.length() - 1;

	    for (int i = 0; i <= length; ++i)
	    {
		hash = hash * base + str[i];
	    }

	    return hash;
	}

	virtual unsigned long int getNextHash(unsigned long int prevHash, char prevFirstChar, char newLastChar, long n) const
	{
	    return (prevHash - 5381 * pow(base, n) - pow(base, n - 1) * prevFirstChar) * base + 5381 * pow(base, n) + newLastChar;
	}


    public:

	FindStrategy() { }
	virtual ~FindStrategy() { }

	/**
	 * Abstract function find()
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
	std::string::size_type _find(const std::string &str, const std::string &what, std::string::size_type from = 0) const
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
		    //from = from + lenWhat - 1;
		}

		for (auto i = from + 1; i + lenWhat <= lenStr;)
		{
		    char prevFirstChar = line[i - 1];
		    char newLastChar = line[lenWhat + i - 1];
		    h = getNextHash(h, prevFirstChar, newLastChar, lenWhat);

		    if (hashWhat == h)
		    {
			result.push_back(i);
			++i;// += lenWhat - 1;
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


/**
 * HashFindStrategy class
 */
class HashFindStrategy : public FindStrategy
{
    public:

        HashFindStrategy() 
        {
            std::cout << " (HashFindStrategy)" << std::endl;
        }
        
	std::vector<std::string::size_type> find(const std::string &str, const std::string &what, std::string::size_type from = 0) override
	{
	    return hashFindAllOccurrences(str, what);
	}
};


/**
 * HashFindStrategyCarp class
 * Implements search using Rabin fingerprint algorithm
 */
class HashFindStrategyCarp : public FindStrategy
{
    public:       

        bool mDebug = false;
        
	static constexpr int base = 33;
	
	/**
	 * Calculate hash using the Rabin fingerprint algorithm
         * @param str - string to be encoded
         * @return hash
         */
	unsigned long int hash(const std::string &str) const override
	{
	    unsigned long int hash = 0;
	    long int length = str.length() - 1;

            if (mDebug) std::cout << "hash()" << std::endl << "{" << std::endl;
            
	    for (int i = length; i >= 0; --i)
	    {                
		unsigned long int a = pow(base, i);                
                unsigned long int b = a * int(str[length - i]);
                unsigned long int d = hash + b;
                
                if (mDebug)
                {
                    std::cout <<"pow(" << base << "," << i << ") = " << a << std::endl;
                    std::cout << a << " * " << int(str[length - i]) << " = " << b << std::endl;                
                    std::cout << hash << " + " << b << " = " << d << std::endl;
                }
                                
                hash = d;                
            }
            
            if (mDebug) std::cout << "}" << std::endl;
            
	    return hash;
	}

	unsigned long int getNextHash(unsigned long int prevHash, char prevFirstChar, char newLastChar, long int n) const override
	{
            
            unsigned long int b = pow(base, n);             
            unsigned long int c = b * int(prevFirstChar);   
            unsigned long int d = (prevHash - c) * base;    
            unsigned long int e = d + int(newLastChar);     
            
            if (mDebug) 
            {
                std::cout << "getNextHash()" << std::endl << "{" << std::endl;
                std::cout << "pow(" << base << ", " << n << ") = " << b << std::endl;
                std::cout << b << " * " << int(prevFirstChar) << " = " << c << std::endl;
                std::cout << "(" << prevHash << " - " << c << ") * " << base << " = " << d << std::endl;
                std::cout << d << " + " << int(newLastChar) << " = " << e << std::endl;            
                std::cout << "}" << std::endl;
            }
            
            return e;
	}

    
    public:

        HashFindStrategyCarp() 
        {
            std::cout << " (HashFindStrategyCarp)" << std::endl;
        }

        
	std::vector<std::string::size_type> find(const std::string &line, const std::string &what, std::string::size_type from = 0) override
	{
            
            std::vector<std::string::size_type> result;

            const long int lenWhat = what.length();
            const long int lenStr = line.length();

            if (lenWhat <= lenStr && from <= lenStr && from + lenWhat <= lenStr)
            {

                unsigned long int hashWhat = hash(what);
                std::string substr = line.substr(from, lenWhat);
                unsigned long int h = hash(substr);

                if (hashWhat == h)
                {
                    std::cout << from << " " << what << "(" << hashWhat << ") == " << line.substr(0, lenWhat) << "(" << h << ") " << line << std::endl;
                    result.push_back(from);
                    //from = from + lenWhat - 1;                    
                }

                for (auto i = from + 1; i + lenWhat <= lenStr;)
                {                    
                    
                    char prevFirstChar = line[i - 1];
                    char newLastChar = line[lenWhat + i - 1];
                    h = getNextHash(h, prevFirstChar, newLastChar, lenWhat - 1);

                    if (hashWhat == h)
                    {
                        std::cout << i << "  " << what << "(" << hashWhat << ") == " << line.substr(i, lenWhat) << "(" << h << ") " << line << std::endl;
                        result.push_back(i);
                        ++i;//= lenWhat - 1;
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


/**
 * StandartFindStrategy class
 * Find symbols using std::string::find
 */
class StandartFindStrategy : public FindStrategy
{
    public:
        
        StandartFindStrategy()
        {
            std::cout << " (StandartFindStrategy)" << std::endl;
        }

	std::vector<std::string::size_type> find(const std::string &str, const std::string &what, std::string::size_type from = 0) override
	{                 
	    std::vector<std::string::size_type> result;
	    std::string::size_type pos = str.find(what, from);
	    while (pos != std::string::npos && pos < str.length())
	    {
		result.push_back(pos);
		pos = str.find(what, pos + what.length() - 1);
                //pos = str.find(what, pos + 1);
	    }
	    return result;
	}

};

#endif /* FINDSTRATEGY_H */

