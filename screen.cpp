#include "screen.h"
#include <cmath>
#define PI 3.14159265

 screen::screen(int Hres_i, int Vres_i) {
    Hres = Hres_i;
    Vres = Vres_i;
    aRatio = (double)Vres / (double)Hres;
    maxFOV = 99 / 2;
    maxFOV = tan(maxFOV * PI / 180.0);
    maxFOV = maxFOV / aRatio;
    maxFOV = atan(maxFOV);
    maxFOV = maxFOV * 180 / PI;
    maxFOV = maxFOV * 2;
    //maxFOV = floor(maxFOV);
    
    //VFOV = round(VFOV);
    
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
    return VFOV;
}
double screen::get_maxFOV() {
    return maxFOV;
}
void screen::set_HFOV(int new_HFOV) {
    HFOV = new_HFOV;
    VFOV = HFOV / 2;
    VFOV = tan(VFOV * PI / 180.0);
    VFOV = aRatio * VFOV;
    VFOV = atan(VFOV);
    VFOV = VFOV * 180 / PI;
    VFOV = 2 * VFOV;
}
