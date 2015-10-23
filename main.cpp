/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: yrid
 *
 * Created on 29 вересня 2015, 16:49
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <string>


#include "ParsingManager.h"

using namespace std::chrono;



enum class UseCases
{
    SINGLE_THREAD, THREADS, SINGLE_THREAD_OOP, THREADS_OOP
};


/**
 * Program entry point
 * 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv)
{

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    
    ParsingManager prsManager;
    
    UseCases useCase = UseCases::THREADS_OOP;    
    switch(useCase)
    {
        case UseCases::THREADS_OOP:
            
            prsManager.threadsOOP();    
            break;
            
        case UseCases::SINGLE_THREAD_OOP:
            
            prsManager.singleThreadOOP();
            break;
            
        case UseCases::THREADS:
            
            prsManager.threads();
            break;
            
        case UseCases::SINGLE_THREAD:
            
            prsManager.singleThread();
            break;        
            
        default:
            break;
    }
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    double d = duration / 1000000.0;
    std::cout << "Duration: " << std::showpoint << std::setprecision(10) << d << std::endl;

    return 0;
}

/* THE END */

