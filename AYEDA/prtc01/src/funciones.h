#pragma once
#include <iostream>
#include <fstream>
#include "ant.h"
#include "tape.h"
#include "simulator.h"

bool ManageHelp(int, char* const*);
void HandleSave(const std::string&, const Simulator&);
void PrintUsage();
