/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParsingActions.h
 * Author: yrid
 *
 * Created on October 7, 2015, 4:16 PM
 */

#ifndef PARSINGACTIONS_H
#define PARSINGACTIONS_H

#include <string>

class ParsingAction
{
    public:
//TODO:asdasd
//	ParsingAction();
//	virtual ~ParsingAction();
	virtual void perform() =0;    
};

class LookForAWord : public ParsingAction
{
    private:
	const std::string str;
	const std::string word;
    public:
	LookForAWord(const std::string whereToLook, const std::string whatWord) : str(whereToLook), word(whatWord){}
	virtual ~LookForAWord();
	virtual void perform()
	{

	}
};


#endif /* PARSINGACTIONS_H */

