/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParsingManager.h
 * Author: yrid
 *
 * Created on October 23, 2015, 12:35 PM
 */

#ifndef PARSINGMANAGER_H
#define PARSINGMANAGER_H

#include <iostream>
#include <fstream>
#include <thread>
#include <string>

#include "Parser.h"
#include "BaseParsingStrategy.h"

const std::string fileName = "D:\\file.txt";
//const string fileName = "D:\\qwe.txt";
const std::string lookingFor = "operator";

class ParsingManager
{
    private:

	std::streampos getFileLength(const std::string fileName)
	{
	    std::ifstream myfile;
	    myfile.open(fileName, std::ios::in);
	    if (myfile.is_open())
	    {

		myfile.seekg(0, std::ios::end);
		std::streampos length = myfile.tellg();
		myfile.close();

		std::cout << "[" << std::this_thread::get_id() << "] File length is " << length << " bytes" << std::endl;

		return length;
	    }

	    return 0;
	}

	static int fileParser(const std::string fileName, const std::string lookingFor, std::streampos from, std::streampos to)
	{

	    std::ifstream * const myfile = new std::ifstream();
	    std::cout << "[" << std::this_thread::get_id() << "] Trying to open " << fileName << " file..." << std::endl;
	    myfile->open(fileName, std::ios::in);

	    if (myfile->is_open())
	    {

		myfile->seekg(from, std::ios::beg);

		std::cout << "[" << std::this_thread::get_id() << "] Looking for \"" << lookingFor << "\"" << " from " << from << std::endl;

		std::string s;
		std::streampos sPos = from;
		int found = 0;

		while (getline(*myfile, s))
		{
		    sPos = myfile->tellg();
		    if (sPos <= to)
		    {
			size_t pos = s.find(lookingFor, 0);
			while (pos != std::string::npos && pos < s.length())
			{
			    ++found;
			    pos = s.find(lookingFor, pos + 1);
			}
		    }
		    else
		    {
			break;
		    }
		}
		std::cout << "[" << std::this_thread::get_id() << "] Stopped at " << sPos << ", boundary is " << to << " found " << found << " matches." << std::endl;
		myfile->close();
	    }

	    delete myfile;

	    return 0;
	}
	
	
    public:

	/***/
	void singleThread()
	{

	    std::streampos end = getFileLength(fileName);
	    fileParser(fileName, lookingFor, 0, end);

	}

	/***/
	void threads()
	{

	    std::streampos end = getFileLength(fileName);
	    std::streampos middle = end / 2;
	    std::streampos quater1 = middle / 2;
	    std::streampos quater2 = middle + quater1;
	    	    
	    std::thread th1(ParsingManager::fileParser, fileName, lookingFor, 0, quater1);
	    std::thread th2(ParsingManager::fileParser, fileName, lookingFor, quater1, middle);
	    std::thread th3(ParsingManager::fileParser, fileName, lookingFor, middle, quater2);
	    std::thread th4(ParsingManager::fileParser, fileName, lookingFor, quater2, end);

	    th4.join();
	    th3.join();
	    th2.join();
	    th1.join();

	}

	/***/
	void singleThreadOOP()
	{
	    std::streampos end = getFileLength(fileName);
	    std::streampos middle = end / 2;
	    std::streampos quater1 = middle / 2;
	    std::streampos quater2 = middle + quater1;

	    LineParsingStrategy<StandartFindStrategy> lineParsingStrategy;

	    Parser p1(fileName, lookingFor);
	    p1.parse(0, end);

	}

	/***/
	void threadsOOP()
	{

	    std::streampos end = getFileLength(fileName);
	    std::streampos middle = end / 2;
	    std::streampos quater1 = middle / 2;
	    std::streampos quater2 = middle + quater1;

	    Parser p1(fileName, lookingFor);
	    Parser p2(fileName, lookingFor);
	    Parser p3(fileName, lookingFor);
	    Parser p4(fileName, lookingFor);

	    void (Parser::* ptrParse)(std::streampos, std::streampos) = &Parser::parse<LineParsingStrategy, StandartFindStrategy>;
	    //void (Parser::* ptrParse)(std::streampos, std::streampos) = &Parser::parse<LineParsingStrategy, HashFindStrategy>;

	    std::thread th1(ptrParse, &p1, 0, quater1);
	    std::thread th2(ptrParse, &p2, quater1, middle);
	    std::thread th3(ptrParse, &p3, middle, quater2);
	    std::thread th4(ptrParse, &p4, quater2, end);

	    th4.join();
	    th3.join();
	    th2.join();
	    th1.join();

	}

};

#endif /* PARSINGMANAGER_H */

