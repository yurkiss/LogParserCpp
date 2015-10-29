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
#include <functional>

#include "Parser.h"
#include "BaseParsingStrategy.h"
#include "FindStrategy.h"
#include "Comparing.h"


enum class UseCases
{
    SINGLE_THREAD, 
    THREADS, 
    SINGLE_THREAD_OOP_L_S, SINGLE_THREAD_OOP_L_C, SINGLE_THREAD_OOP_L_H,
    THREADS_OOP_L_S, THREADS_OOP_L_C, THREADS_OOP_L_H,
    THREADS_OOP_S_S, THREADS_OOP_S_C, THREADS_OOP_S_H,
    TEST_HASH, COMPARE
};

enum class HashFunction
{
    STANDART, CARP, HASHCODE
};


/**
 * ParsingManager class
 * It's factory of choices
 */
class ParsingManager
{
    private:
        
        const std::string mLookingFor;        
        const std::string mFileName;
	
    public:
        
        ParsingManager(const std::string lookingFor, const std::string fileName, UseCases useCase) : mLookingFor(lookingFor), mFileName(fileName)
        {
            
            switch(useCase)
            {
                case UseCases::THREADS_OOP_L_S:                    
                    threadsOOP<LineParsingStrategy, StandartFindStrategy>();
                    break;
                case UseCases::THREADS_OOP_L_C:
                    threadsOOP<LineParsingStrategy, HashFindStrategyCarp>();
                    break;
                case UseCases::THREADS_OOP_L_H:
                    threadsOOP<LineParsingStrategy, HashFindStrategy>();
                    break;
                case UseCases::THREADS_OOP_S_S:
                    threadsOOP<SymbolParsingStrategy, StandartFindStrategy>();
                    break;
                case UseCases::THREADS_OOP_S_C:
                    threadsOOP<SymbolParsingStrategy, HashFindStrategyCarp>();
                    break;
                case UseCases::THREADS_OOP_S_H:
                    threadsOOP<SymbolParsingStrategy, HashFindStrategy>();
                    break;
                    
                case UseCases::SINGLE_THREAD_OOP_L_S:                    
                    singleThreadOOP<LineParsingStrategy, StandartFindStrategy>();
                    break;
                case UseCases::SINGLE_THREAD_OOP_L_C:
                    singleThreadOOP<LineParsingStrategy, HashFindStrategyCarp>();
                    break;
                case UseCases::SINGLE_THREAD_OOP_L_H:
                    singleThreadOOP<LineParsingStrategy, HashFindStrategy>();
                    break;

                case UseCases::THREADS:

                    threads();
                    break;

                case UseCases::SINGLE_THREAD:

                    singleThread();
                    break;        

                case UseCases::TEST_HASH:
                    
                    testHashFunction();
                    break;        

                default:
                    break;
            }
    
        }

	/***/
	void singleThread()
	{

	    std::streampos end = getFileLength(mFileName);
	    fileParser(mFileName, mLookingFor, 0, end);

	}

	/***/
	void threads()
	{

	    std::streampos end = getFileLength(mFileName);
	    std::streampos middle = end / 2;
	    std::streampos quater1 = middle / 2;
	    std::streampos quater2 = middle + quater1;
	    	    
	    std::thread th1(ParsingManager::fileParser, mFileName, mLookingFor, 0, quater1);
	    std::thread th2(ParsingManager::fileParser, mFileName, mLookingFor, quater1, middle);
	    std::thread th3(ParsingManager::fileParser, mFileName, mLookingFor, middle, quater2);
	    std::thread th4(ParsingManager::fileParser, mFileName, mLookingFor, quater2, end);

	    th4.join();
	    th3.join();
	    th2.join();
	    th1.join();

	}

	/***/
        template<template<typename> class T_P, class T_F>
	void singleThreadOOP()
	{
	    std::streampos end = getFileLength(mFileName);
	    std::streampos middle = end / 2;
	    std::streampos quater1 = middle / 2;
	    std::streampos quater2 = middle + quater1;

	    Parser p1(mFileName, mLookingFor);
	    p1.parse<T_P, T_F>(0, end);

	}

	/***/
        template<template<typename> class T_P, class T_F>
	void threadsOOP()
	{

	    std::streampos end = getFileLength(mFileName);
	    std::streampos middle = end / 2;
	    std::streampos quater1 = middle / 2;
	    std::streampos quater2 = middle + quater1;

	    Parser p1(mFileName, mLookingFor);
	    Parser p2(mFileName, mLookingFor);
	    Parser p3(mFileName, mLookingFor);
	    Parser p4(mFileName, mLookingFor);

            std::function<void(Parser&, std::streampos, std::streampos) > parseFunc;                        
            parseFunc = &Parser::parse<T_P, T_F>;         
                                 

	    std::thread th1(parseFunc, std::ref(p1), 0, quater1);
	    std::thread th2(parseFunc, std::ref(p2), quater1, middle);
	    std::thread th3(parseFunc, std::ref(p3), middle, quater2);
	    std::thread th4(parseFunc, std::ref(p4), quater2, end);

	    th4.join();
	    th3.join();
	    th2.join();
	    th1.join();

	}
        
        void testHashFunction()
        {
            const std::string s = "Thoperator";
            HashFindStrategyCarp st;
            unsigned long int hash = st.hash(s);
            
            std::cout << "hash(" << s << "): " << hash << std::endl;
            
            unsigned long int nextHash = st.getNextHash(hash, s[0], ' ', s.length() - 1);
            unsigned long int hashNextWord = st.hash("hoperator ");
            
            std::string boolResult = (nextHash == hashNextWord) ? " (true)" : " (false)";
            std::cout << nextHash << "==" << hashNextWord << boolResult << std::endl;
            //hoperat hash:11269224158441868
        }  

        
    private:

        std::streampos getFileLength(const std::string fileName) {
            std::ifstream myfile;
            myfile.open(fileName, std::ios::in);
            if (myfile.is_open()) {

                myfile.seekg(0, std::ios::end);
                std::streampos length = myfile.tellg();
                myfile.close();

                std::cout << "[" << std::this_thread::get_id() << "] File length is " << length << " bytes" << std::endl;

                return length;
            }

            return 0;
        }

        static int fileParser(const std::string fileName, const std::string lookingFor, std::streampos from, std::streampos to) {

            std::ifstream * const myfile = new std::ifstream();
            std::cout << "[" << std::this_thread::get_id() << "] Trying to open " << fileName << " file..." << std::endl;
            myfile->open(fileName, std::ios::in);

            if (myfile->is_open()) {

                myfile->seekg(from, std::ios::beg);

                std::cout << "[" << std::this_thread::get_id() << "] Looking for \"" << lookingFor << "\"" << " from " << from << std::endl;

                std::string s;
                std::streampos sPos = from;
                int found = 0;

                while (getline(*myfile, s)) {
                    sPos = myfile->tellg();
                    if (sPos <= to) {
                        size_t pos = s.find(lookingFor, 0);
                        while (pos != std::string::npos && pos < s.length()) {
                            ++found;
                            pos = s.find(lookingFor, pos + 1);
                        }
                    } else {
                        break;
                    }
                }
                std::cout << "[" << std::this_thread::get_id() << "] Stopped at " << sPos << ", boundary is " << to << " found " << found << " matches." << std::endl;
                myfile->close();
            }

            delete myfile;

            return 0;
        }
    
        
        
};
#endif /* PARSINGMANAGER_H */