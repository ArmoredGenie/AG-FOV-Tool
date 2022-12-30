#pragma once
#include <string>
#include<vector>

double calcaRatio(int, int);

int calcMaxFOV(double);

bool promptYesNo(std::string);

void srchRplceFile(std::string, std::string, std::string, std::string);

void cpyFile(std::string, std::string);

void printLogo();

int calcVFOV(double, double);

int userInputInt(std::string, int, int);

std::vector<std::string> readSettings(std::string filePath_i);

void writeSettings(std::string filePath_i, std::vector<std::string> settings_i);