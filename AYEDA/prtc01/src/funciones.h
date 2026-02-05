#pragma once
#include <iostream>

bool ManageHelp(int, char* const*);
void ManageSave(int, char* const*, bool&);
bool ManageOutFile(int, char* const*, std::string&);
void PrintUsage();