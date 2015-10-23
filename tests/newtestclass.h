/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass.h
 * Author: yrid
 *
 * Created on Oct 20, 2015, Oct 20, 2015 1:49:47 PM
 */

#ifndef NEWTESTCLASS_H
#define NEWTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(newtestclass);

    CPPUNIT_TEST(testHashMethod);
    //CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass();
    virtual ~newtestclass();
    void setUp();
    void tearDown();

private:
    void testHashMethod();
    void testFailedMethod();
};


class TestHash : public ParsingStrategy
{
    
    public:
	TestHash();
	virtual ~TestHash(){}
	void parse(std::ifstream * const fileStream, const std::string lookingFor, const std::streampos fromPos = std::ios::beg, const std::streampos toPos = std::ios::end) const {}
	long int hash(std::string s)
	{ 
	    return ParsingStrategy::hash(s); 
	    //return 999509;
	}
        
};

#endif /* NEWTESTCLASS_H */

