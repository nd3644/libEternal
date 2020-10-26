#include "dbglog.h"
#include <iostream>

Eternal::DbgLog *Eternal::DbgLog::myInstance = nullptr;

Eternal::DbgLog *Eternal::DbgLog::GetInstance() {
    if(myInstance == nullptr) {
        myInstance = new DbgLog();
    }
    return myInstance;
}

Eternal::DbgLog::DbgLog() {
    myFile.open("dbg.txt");
}

Eternal::DbgLog::~DbgLog() {
    myFile.close();
}

void Eternal::DbgLog::operator<<(std::string str) {
    std::cout << str << std::endl;
}

void Eternal::DbgLog::Write(std::string str) {
    myFile << str;
    myFile.flush();
    std::cout << str << std::endl;
}