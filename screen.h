#pragma once
#include <string>

double calcaRatio(int, int);

int calcMaxFOV(double);

bool promptYesNo(std::string);

void srchRplceFile(std::string, std::string, std::string);

void cpyFile(std::string, std::string);

void printLogo();

int calcVFOV(double, double);

int userInputInt(std::string, int, int);