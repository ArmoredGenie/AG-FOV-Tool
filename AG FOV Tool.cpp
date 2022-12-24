// AG FOV Picker.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include "screen.h"
#include <fstream>
#include <conio.h>

using namespace std;

string srchFOV = " <Attr name=\"FOV\" value=\"";
//string scPath = "C:\\StarCitizen\\Live";
string scPath = "C:\\Program Files\\Roberts Space Industries\\StarCitizen\\LIVE";

int main()
{
    int minFOV = 60;
    int HfovIn;
    cout << "\n------------------------------------- Star Citizen FOV Tool -------------------------------------" << endl;
    cout << "--------------------------------------- By ArmoredGenie -----------------------------------------" << endl;

    cout << "\nStar Citizen uses vertical FOV values in it's config. This Tool will use your desired horizontal" << endl;
    cout <<   "FOV and screen resolution to calculate a vertical FOV.\n" << endl;
    cout <<   "It will then read the current Star Citizen config and make a local copy with the new FOV value." << endl;
    cout <<   "You will have the option to copy this new file into the game directory to overrite the old one." << endl;
    cout << "\nCurrent path to Best Damn Space Sim is:   \n" << scPath << endl; 
    if (promptYesNo("\nDo you want to change the path ? ")) {
        cout << "\nSo needy ;) Enter new path and press enter: ";
        getline(cin,scPath);
        cout << "\nNew path to Star Citizen is " << scPath << endl;
    }
    else {
        cout << "\nRoger that CMDR, using default path" << endl;
    }
    string attPath = scPath + "\\USER\\Client\\0\\Profiles\\default\\attributes.xml";
    double aRatio = calcaRatio(2560, 1440);
    cout << "\nDefault aspect ratio is 16:9 (" << aRatio <<") for \"regular\" monitors - 2560x1440, 1920x1080 etc." << endl;
        if (promptYesNo("\nDo you want to use a different aspect ratio? (utrawides,multi monitor etc)")) {
            int HresIn = userInputInt("Enter game horizontal resolution and press enter: ",0,1000000);
            int VresIn = userInputInt("\nEnter game vertical resolution and press enter: ", 0, 1000000);
            aRatio = calcaRatio(HresIn, VresIn);
            cout << "\nYour resolution is " << HresIn << "x" << VresIn << ". Aspect ratio is " << aRatio << endl;
        }
        else {
            cout << "\nYou got it. Keeping default aspect ratio of "<< aRatio << "." << endl;
        }
    int maxFOV = calcMaxFOV(aRatio);
    do {
        cout << "\nThe maximum horizontal FOV for your aspect ratio is " << maxFOV << endl;
        cout << "Enter desired horizontal FOV in degrees (" << minFOV << "-" << maxFOV << "):\n";
        HfovIn = userInputInt(" ", minFOV, maxFOV);

    } while (HfovIn > maxFOV || HfovIn < 60);
    int VFOV = calcVFOV(HfovIn, aRatio);
    string VfovStr = to_string(VFOV); //convert FOV to string
    cout << "\nBig brain math results:" << endl;
    cout << "   Aspect ratio is " << aRatio << endl;
    cout << "   Maximum horizontal FOV is " << maxFOV << endl;
    cout << "   Desired horizontal FOV is " << HfovIn << endl;
    cout << "   Calculated vertical FOV is " << VfovStr << endl;
    cout << "\nsearching in:\n" << attPath << endl << endl;
    srchRplceFile(attPath, srchFOV, VfovStr);
    if (promptYesNo("\nWould you like to copy the new file to game folder (overite)?")) {
        cpyFile("attributes.xml", attPath);
        printLogo();
        cout << "Copied!\n" << endl;
    }
    else {
        printLogo();
        cout << "\nOK, leaving attributes.xml alone\n";
    }
    cout << "Bye!\n" << endl;
    cout << "press any key to exit" << endl;
    string exit;
    exit = _getch();
return (0);
} 
