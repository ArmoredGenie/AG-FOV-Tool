#include "screen.h"
#include <cmath>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
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
        std::cout << std::endl << filePath_i << "\n - File to search not found! Here be dragons. Press any key to exit" << std::endl;
        char bye = _getch();
        exit(0);
    }
    else {
        while (!inFile.eof()) {
            std::getline(inFile, txtLine);
            if (txtLine.find(srch_i) != std::string::npos) {
                std::cout << "Found:\n" << txtLine << std::endl;
                // txtLine.replace(srch_i.length(), 2, rplce_i);
                txtLine = srch_i + rplce_i + "\"/>";
                std::cout << "Line edited to:\n" << txtLine << std::endl << "\nMission accomplished! \nA new XML file has been saved locally" << std::endl;
            }
            outTempFile << txtLine << std::endl;
        }
    }
        inFile.close();
        outTempFile.close();
}

std::string readFile(std::string filePath_i) {
    std::ifstream inFile;
    std::ofstream outTempFile;
    std::string txtLine;
    std::string text;
    inFile.open(filePath_i);
    outTempFile.open("temp.txt");
    if (inFile.fail()) {
        std::cout << std::endl << filePath_i << "\n - File not found! Here be dragons. Press any key to exit" << std::endl;
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
    std::string inLine;
    inTempFile.open(filePathFrom_i);
    outFile.open(filePathTo_i);
    if (inTempFile.fail()) {
        std::cout << std::endl << filePathFrom_i <<"\n - File to copy not found! Here be dragons. Press any key to exit" << std::endl;
  
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

std::vector<std::string> readSettings(std::string filePath_i) {
    std::ifstream inFile;
    std::string txtLine;
    std::vector<std::string> text;
    inFile.open(filePath_i);
    if (inFile.fail()) {
        std::cout << std::endl << "Settings file not found! Creating one with default values" << std::endl;
        //std::string bye;
        text.push_back("Settings below, each on a new line (Path to SC / horizontal res / vertical res / desired horizontal FOV):");
        text.push_back("C:\\Program Files\\Roberts Space Industries\\StarCitizen\\LIVE");
        text.push_back("2560");
        text.push_back("1440");
        text.push_back("100");
        writeSettings("settings.txt", text);
    }
    else {
        while (!inFile.eof()) {
            std::getline(inFile, txtLine);
            text.push_back(txtLine);
        }
        inFile.close();
    }
    return text;
}

void writeSettings(std::string filePath_i, std::vector<std::string> settings_i) {
    std::ofstream outFile;
    std::string txtLine;
    outFile.open(filePath_i);
    for (size_t i = 0; i != settings_i.size(); ++i) {
        outFile << settings_i[i] << std::endl;
    }
    outFile.close();
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