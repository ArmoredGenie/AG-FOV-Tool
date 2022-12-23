#include "screen.h"
#include <cmath>
#include <iostream>
#include <conio.h>
#define PI 3.14159265

promptYesNo::promptYesNo(std::string text_i) {
    YesNo = false;
    text = text_i;
}

bool promptYesNo::get_YesNo(){
    do {
        std::cout << promptYesNo::text << std::endl;
        std::cout << "Enter Y for yes or N for no" << std::endl;
        value = _getch();
        // Convert to Lowercase
        for (int i = 0; i < value.length(); i++) value[i] = tolower(value[i]);
        //check for values
        if (value == "yes") value = "y";
        if (value == "no") value = "n";
        if (value == "y") YesNo = true;
        if (value == "n") YesNo = false;

    } while (value != "y" && value != "n");
    return YesNo;
}


 screen::screen(int Hres_i, int Vres_i) {
    Hres = Hres_i;
    Vres = Vres_i;
    aRatio = (double)Vres / (double)Hres;
    screen::HFOV = 90;
}
int screen::get_Hres() {
    return Hres;
}
int screen::get_Vres() {
    return Vres;
}
double screen::get_aRatio() {
    return aRatio;
}
double screen::get_HFOV() {
    return HFOV;
}
double screen::get_VFOV() {
    VFOV = HFOV / 2;
    VFOV = tan(VFOV * PI / 180.0);
    VFOV = screen::aRatio * VFOV;
    VFOV = atan(VFOV);
    VFOV = VFOV * 180 / PI;
    VFOV = 2 * VFOV;
    return VFOV;
}
double screen::get_maxFOV() {
    maxFOV = 99 / 2;
    maxFOV = tan(maxFOV * PI / 180.0);
    maxFOV = maxFOV / aRatio;
    maxFOV = atan(maxFOV);
    maxFOV = maxFOV * 180 / PI;
    maxFOV = maxFOV * 2;
    return maxFOV;
}
void screen::set_HFOV(int new_HFOV) {
    HFOV = new_HFOV;
}
