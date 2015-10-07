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
#include <thread>
#include <chrono>
#include <string>

#include "Parser.h"
#include "BaseParsingStrategy.h"

using namespace std::chrono;
using namespace std;


string fileName = "D:\\file.txt";


void threads();
void singleThread();




/*
 * 
 */
int main(int argc, char** argv)
{

//    LineParsingStrategy lineStrategy;
//    std::cout << &lineStrategy << std::endl;
    //Parser p(lineStrategy);
    Parser p("D:\\file.txt", "operator");

    return 0;
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    threads();
    //singleThread();
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    double d = duration / 1000000.0;
    cout << "Duration: " << std::showpoint << std::setprecision(10) << d << endl;

    return 0;
}

string p()
{
    return "asdasd";
}

streampos getFileLength(const string fileName)
{
    ifstream myfile;
    //cout << "Trying to open " << fileName << " file..." << endl;
    myfile.open(fileName, ios::in);
    if (myfile.is_open()) {

        myfile.seekg(0, ios::end);
        streampos length = myfile.tellg();
        myfile.close();

        cout << "[" << std::this_thread::get_id() << "] File length is " << length << " bytes" << endl;

        return length;
    }

    return 0;
}

int fileParser(const string fileName, const string lookingFor, streampos from, streampos to)
{

    ifstream* const myfile = new ifstream();
    cout << "[" << std::this_thread::get_id() << "] Trying to open " << fileName << " file..." << endl;
    myfile->open(fileName, ios::in);

    if (myfile->is_open()) {

//        myfile->seekg(0, ios::end);
//        int length = myfile->tellg();

        myfile->seekg(from, ios::beg);

        cout << "[" << std::this_thread::get_id() << "] Looking for \"" << lookingFor << "\"" << " from " << from << endl;

        string s;
        streampos sPos = from;
        int found = 0;

        while (getline(*myfile, s)) {
            sPos = myfile->tellg();
            if (sPos <= to) {
                size_t pos = s.find(lookingFor, 0);
                while (pos != string::npos && pos < s.length()) {
                    ++found;
                    //cout << pos << ":" << s.length() << " ... " << s << endl;
                    pos = s.find(lookingFor, pos + 1);
                }
            }
            else {
                break;
            }
        }
        cout << "[" << std::this_thread::get_id() << "] Stopped at " << sPos << ", boundary is " << to << " found " << found << " matches." << endl;
        myfile->close();
    }

    delete myfile;

    return 0;
}


void singleThread()
{

    streampos end = getFileLength(fileName);
    //streampos middle = getFileMiddlePosition(fileName);
    fileParser( fileName, "operator", 0, end );
    
}

void threads()
{
 
    //parseThread t1("D:\\qwe.txt", 0, 0, "operator");
    
    streampos end = getFileLength(fileName);        
    streampos middle = end / 2;//getFileMiddlePosition(fileName);    
    streampos quater1 = middle / 2;
    streampos quater2 = middle + quater1;

    std::thread th1(fileParser, fileName, "operator", 0, middle);
    std::thread th2(fileParser, fileName, "operator", middle, end);
    th2.join();
    th1.join();


/*
    std::thread th1(fileParser, fileName, "operator", 0, quater1);
    std::thread th2(fileParser, fileName, "operator", quater1, middle);
    std::thread th3(fileParser, fileName, "operator", middle, quater2);
    std::thread th4(fileParser, fileName, "operator", quater2, end);
    th4.join();
    th3.join();
    th2.join();
    th1.join();
  */  
}