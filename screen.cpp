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
int userInputInt(std::string prompt_i, int greaterThan_i, int lessThan_i) {
    std::string number;
    std::string prompt = prompt_i;
    int greaterThan = greaterThan_i;
    int lessThan = lessThan_i;
    bool error;
    int num;
    do {
        error = 0;
        std::cin.clear();
        std::cout << prompt;
        std::cin >> number;
        try {
            num = stoi(number);
        }
        catch (...) {
            error = 1;
            std::cout << "nope, try again:" << std::endl;
        }
    } while (num > lessThan || num < greaterThan || error == 1);
    return num;
}

double calcaRatio(int resH, int resV) {
    double aRatio = (double)resV / (double)resH;
    return aRatio;
}

int calcMaxFOV(double aRatio_in) {
    double aRatio = aRatio_in;
    double maxFOV = 99 / 2;
    maxFOV = tan(maxFOV * PI / 180.0);
    maxFOV = maxFOV / aRatio;
    maxFOV = atan(maxFOV);
    maxFOV = maxFOV * 180 / PI;
    maxFOV = maxFOV * 2;
    return maxFOV;
}

int calcVFOV(double HFOV_in, double aRatio_in) {
    double HFOV = HFOV_in;
    double aRatio = aRatio_in;
    double VFOV;
    VFOV = HFOV / 2;
    VFOV = tan(VFOV * PI / 180.0);
    VFOV = aRatio * VFOV;
    VFOV = atan(VFOV);
    VFOV = VFOV * 180 / PI;
    VFOV = 2 * VFOV;
    VFOV = round(VFOV);
    VFOV = (int)VFOV;
    return VFOV;
}

void srchRplceFile(std::string filePath_i, std::string destPath_i, std::string srch_i, std::string rplce_i) {
    std::ifstream inFile;
    std::ofstream outTempFile;
    std::string txtLine;
    inFile.open(filePath_i);
    outTempFile.open(destPath_i);
    if (inFile.fail()){
        std::cout << std::endl << "File not found! Here be dragons. Press any key to exit" << std::endl;
        char bye = _getch();
        exit(0);
    }
    else {
        while (!inFile.eof()) {
            std::getline(inFile, txtLine);
            if (txtLine.find(srch_i) != std::string::npos) {
                std::cout << "Found:\n" << txtLine << std::endl;
                txtLine.replace(srch_i.length(), 2, rplce_i);
                std::cout << "Line edited to:\n" << txtLine << std::endl << "\nMission accomplished! \nA new file has been saved" << std::endl;
            }
            outTempFile << txtLine << std::endl;
        }
        inFile.close();
        outTempFile.close();
    }
}

std::string readFile(std::string filePath_i) {
    std::ifstream inFile;
    std::ofstream outTempFile;
    std::string txtLine;
    std::string text;
    inFile.open(filePath_i);
    outTempFile.open("temp.txt");
    if (inFile.fail()) {
        std::cout << std::endl << "File not found! Here be dragons. Press any key to exit" << std::endl;
        //std::string bye;
        char bye = _getch();
        exit(0);
    }
    else {
        while (!inFile.eof()) {
            std::getline(inFile, txtLine);
            outTempFile << txtLine << std::endl;
            text = text + txtLine + "\n";
        }
        inFile.close();
        outTempFile.close();
    }
    return text;
}

void cpyFile(std::string filePathFrom_i, std::string filePathTo_i) {
    std::ifstream inTempFile;
    std::ofstream outFile;
    std::string filePathFrom = filePathFrom_i;
    std::string filePathTo = filePathTo_i;
    std::string inLine;
    inTempFile.open(filePathFrom);
    outFile.open(filePathTo);
    if (inTempFile.fail()) {
        std::cout << std::endl << "File not found! Here be dragons. Press any key to exit" << std::endl;
  
        char bye = _getch();
        exit(0);
    }
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