/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Comparing.h
 * Author: yrid
 *
 * Created on October 29, 2015, 4:48 PM
 */


#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include "FindStrategy.h"
#include "BaseParsingStrategy.h"

#ifndef COMPARING_H
#define COMPARING_H

template <typename T_FindStrategy = StandartFindStrategy>
class LineParsingStrategyCompare : public ParsingStrategy<T_FindStrategy> {
public:

    void parsingLoop(std::ifstream &fileStream, const std::string lookingFor, const std::streampos fr, const std::streampos to) const override {

        std::cout << "Compare parsing strategy started" << std::endl;

        std::string s = "";
        std::streampos sPos = fr;

        std::map<std::string, std::vector <std::string::size_type> > foundMatches;

//        HashFindStrategyCarp findStrategy;
//        std::string ss = "�operator[]()must be called. Wheng()callsuse(), Vector_container�s operator[]()must be called. To";
//        std::vector<std::string::size_type> w = findStrategy.find(ss, lookingFor, 0);
//        if (!w.empty()) {}
//        return;
        
        {
            StandartFindStrategy findStrategy;
            long int lineNumber = 0;
            long int found = 0;
            while (std::getline(fileStream, s)) {
                sPos = fileStream.tellg();
                if (sPos <= to) {
                    std::vector<std::string::size_type> v = findStrategy.find(s, lookingFor, 0);
                    if (!v.empty()) {
                        foundMatches.insert(std::make_pair(s, v));
                        found += v.size();
                    }
                } else {
                    break;
                }
                ++lineNumber;
            }
            std::cout << "[" << std::this_thread::get_id() << "] Stopped at " << sPos << ", boundaries are from " << fr << " to " << to << ", found " << found << " matches." << std::endl;
        }
        
        fileStream.clear();
        fileStream.seekg(0, std::ios::beg);
        
        std::map<std::string, std::vector <std::string::size_type> > foundMatchesH;
        
        {
            HashFindStrategyCarp findStrategy;

            long int lineNumber = 0;
            long int found = 0;
            while (std::getline(fileStream, s)) {
                sPos = fileStream.tellg();
                if (sPos <= to) {
                    std::vector<std::string::size_type> v = findStrategy.find(s, lookingFor, 0);
                    if (!v.empty()) {
                        foundMatchesH.insert(std::make_pair(s, v));
                        found += v.size();
                    }
                } else {
                    break;
                }
                ++lineNumber;
            }
            std::cout << "[" << std::this_thread::get_id() << "] Stopped at " << sPos << ", boundaries are from " << fr << " to " << to << ", found " << found << " matches." << std::endl;
        }
        
        
        auto posS = foundMatches.cbegin();
        auto posH = foundMatchesH.cbegin();
        
        while ( posS != foundMatches.cend() && posH != foundMatchesH.cend()) 
        {
            if(posS->first != posH->first)
            {
                std::cout << "--- " << posS->first << " != " << posH->first;
            }
            else
            {
                std::vector<std::string::size_type> v1 = posS->second;
                std::vector<std::string::size_type> v2 = posH->second;
                
                if(v1.size() != v2.size())
                {
                    std::cout << "!!! " << posS->first << std::endl << " != " << posH->first << " " << std::endl;
                    for (auto posV = v1.cbegin(); posV != v1.cend(); ++posV) {
                        std::cout << *posV << " ";
                    }                    
                    std::cout << " != " << " ";
                    for (auto posV = v2.cbegin(); posV != v2.cend(); ++posV) {
                        std::cout << *posV << " ";
                    }                                        
                    std::cout << std::endl;
                }
            }
            
            ++posS;
            ++posH;
        }
    }


};


#endif /* COMPARING_H */

