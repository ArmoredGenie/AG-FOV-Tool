#pragma once
#include <string>

class screen {
private:
    int Hres;
    int Vres;
    double aRatio;
    double HFOV;
    double VFOV;
    double maxFOV;
public:
    screen(int Hres_i, int Vres_i);
    int get_Hres();
    int get_Vres();
    double get_aRatio();
    double get_HFOV();
    double get_VFOV();
    double get_maxFOV();
    void set_HFOV(int new_HFOV);
};

bool promptYesNo(std::string);

void srchRplceFile(std::string, std::string, std::string);

void cpyFile(std::string, std::string);

void printLogo();