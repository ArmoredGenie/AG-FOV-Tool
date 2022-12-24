#include "screen.h"
#include <cmath>
#include <iostream>
#include <conio.h>
#include <fstream>
#define PI 3.14159265

bool promptYesNo(std::string text_i){
    bool YesNo = false;
    std::string text = text_i;
    std::string value;
    do {
        std::cout << text << std::endl;
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

void srchRplceFile(std::string filePath_i, std::string srch_i, std::string rplce_i) {
    std::ifstream inFile;
    std::ofstream outTempFile;
    std::string txtLine;
    std::string filePath = filePath_i;
    std::string srch = srch_i;
    std::string rplce = rplce_i;
    inFile.open(filePath);
    outTempFile.open("attributes.xml");
    if (inFile.fail())
        std::cout << std::endl << "File not found! Here be dragons." << std::endl;
    else {
        while (!inFile.eof()) {
            std::getline(inFile, txtLine);
            if (txtLine.find(srch) != std::string::npos) {
                std::cout << "Found:\n" << txtLine << std::endl;
                txtLine.replace(srch.length(), 2, rplce);
                std::cout << "Line edited to:\n" << txtLine << std::endl << "\nMission accomplished! \nA new attributes.xml file has been saved wherever this .exe is stored" << std::endl;
            }
            outTempFile << txtLine << std::endl;
        }
        inFile.close();
        outTempFile.close();
    }
}

void cpyFile(std::string filePathFrom_i, std::string filePathTo_i) {
    std::ifstream inTempFile;
    std::ofstream outFile;
    std::string filePathFrom = filePathFrom_i;
    std::string filePathTo = filePathTo_i;
    std::string inLine;
    inTempFile.open(filePathFrom);
    outFile.open(filePathTo);
    if (inTempFile.fail())
        std::cout << std::endl << "File not found! Here be dragons" << std::endl;
    else {
        while (!inTempFile.eof()) {
            std::getline(inTempFile, inLine);
            outFile << inLine << std::endl;
        }
        inTempFile.close();
        outFile.close();
    }
}

void printLogo() {
    std::cout << "                                                                                                    \n";
    std::cout << "                                                                                                    \n";
    std::cout << "                                                ';;'                                                \n";
    std::cout << "                                               ';'';'                                               \n";
    std::cout << "                                              .;.  .;.                                              \n";
    std::cout << "                                             .;.    .;.                                             \n";
    std::cout << "                                            .;.      .;.                                            \n";
    std::cout << "                                           .;.        .;.                                           \n";
    std::cout << "                                          .;.          .;.                                          \n";
    std::cout << "                                         .;.     .,.    ';.                                         \n";
    std::cout << "                                        .;'     .; ;.    ';.                                        \n";
    std::cout << "                                       .;'     .;. .:.    ';.                                       \n";
    std::cout << "                                      .;'     .;.   ';.    ,;.                                      \n";
    std::cout << "                                      ;,     .;.     ,;     ,;                                      \n";
    std::cout << "                                     ;,     .;.       ;,     ,;                                     \n";
    std::cout << "                                    ,,     .;'        .;'     ,,                                    \n";
    std::cout << "                                   ,;      ;'          .;.     ;,                                   \n";
    std::cout << "                                  ,;      ,,            .;.     ;,                                  \n";
    std::cout << "                                 ';.     ,,              ';.    .;'                                 \n";
    std::cout << "                                ';.     ';                ';.    .;'                                \n";
    std::cout << "                               ';.     ';.                 ,;     .;'                               \n";
    std::cout << "                              .;.     .;.                   ;,     .;.                              \n";
    std::cout << "                             .;.     .;.                    .;'     .;.                             \n";
    std::cout << "                            .;.     .;.                      .;.     .;.                            \n";
    std::cout << "                           .;.     .;.                        .;.     .;.                           \n";
    std::cout << "                          .;.     .;.                          ';.     .;.                          \n";
    std::cout << "                         .;.     .;'                            ,;.     .;.                         \n";
    std::cout << "                        .;'      ;,                              ,,      ';.                        \n";
    std::cout << "                       .;'      ,,   .,;;;;;;;;;;;;;;;;;;;;;;',.  ;,      ';.                       \n";
    std::cout << "                      .;'      ,,    ;,                      .;.  .;'      ';.                      \n";
    std::cout << "                     .;,      ';     ;,                      .;.   .:.      ,;.                     \n";
    std::cout << "                     ;,      ';.     ;,                       ;'    .;.      ,;                     \n";
    std::cout << "                    ,,      .;.      ;:                       ;'     ';.      ,,                    \n";
    std::cout << "                   ,,      .;.       ;;;;;;;;;;;;;;;;,:.      ;'      ,;       ,,                   \n";
    std::cout << "                  ,;      .;.                        .;.      ,'       ,,       ;,                  \n";
    std::cout << "                 ,;      .;.                         .;.      ,,        ;,       ;,                 \n";
    std::cout << "                ';.     .;'                          .;.      ,,        .;'      .;'                \n";
    std::cout << "               ';.     .;'                           .;.      ',         .;.      .;'               \n";
    std::cout << "              ';.     .;,                            .;.      ';          .;.      .;'              \n";
    std::cout << "             .;.      .,';;;;;;;;;;;;;;;;;;;;;;;;;;;;''.      ';           ';.      .;.             \n";
    std::cout << "            .;.                                               ';            ,;       .;.            \n";
    std::cout << "           .;.                                                ';.            ;,       .;.           \n";
    std::cout << "          .;.                                                 .;.            .;'       .;.          \n";
    std::cout << "         .;.       .'';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;,,              .;'       .;.         \n";
    std::cout << "        .;.       .;,                                                          .:.       .;.        \n";
    std::cout << "       .;'       .;,                                                            .:.       ';.       \n";
    std::cout << "       ':........;'                                                               ;.......':'       \n";

}