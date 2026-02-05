#pragma once
#include <iostream>
#include <fstream>
#include "ant.h"
#include "tape.h"

bool ManageHelp(int, char* const*);
void ManageSave(int, char* const*, bool&);
bool ManageOutFile(int, char* const*, std::string&);
void PrintUsage();
