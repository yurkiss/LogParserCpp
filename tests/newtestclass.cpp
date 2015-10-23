/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass.cpp
 * Author: yrid
 *
 * Created on Oct 20, 2015, Oct 20, 2015 1:49:47 PM
 */

#include "newtestclass.h"
#include "../BaseParsingStrategy.h"
#include <string> 

CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);


newtestclass::newtestclass()
{
}

newtestclass::~newtestclass()
{
}

void newtestclass::setUp()
{
}

void newtestclass::tearDown()
{
}


void newtestclass::testHashMethod()
{
    
    TestHash testClass;
    long int h = testClass.hash("abr");
    //std::cout << h << std::endl;
    long int v = 999509;
    //CPPUNIT_ASSERT_MESSAGE("abr" + std::to_string(h), h);
    CPPUNIT_ASSERT_EQUAL(v, h);
    //CPPUNIT_ASSERT(true);
        
}

void newtestclass::testFailedMethod()
{
    CPPUNIT_ASSERT(false);
}

TestHash::TestHash()
{
    
}
