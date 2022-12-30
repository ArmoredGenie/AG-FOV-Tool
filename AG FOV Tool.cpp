// AG FOV Picker.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include "screen.h"
#include <fstream>
#include <conio.h>
#include <vector>

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
    cout << "\nSettings are now saved in the local file settings.txt..." << endl;
    vector<string> settings = readSettings("settings.txt");
    scPath = settings[0];
    int HresIn = stoi(settings[1]);
    int VresIn = stoi(settings[2]);
   
    cout << "\nCurrent path to Best Damn Space Sim is:   \n" << scPath << endl; 

    
    if (promptYesNo("\nDo you want to change the path ? ")) {
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << "\nSo needy ;) Enter new path and press enter: ";
        getline(cin,scPath);
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << "\nNew path to Star Citizen is " << scPath << endl;
    }
    else {
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << "\nRoger that CMDR, using current path" << endl;
    }
    string attPath = scPath + "\\USER\\Client\\0\\Profiles\\default\\attributes.xml";
    double aRatio = calcaRatio(HresIn, VresIn);
    cout << "\nCurrent aspect ratio is (" << aRatio <<") based on a " << HresIn << "x" << VresIn <<  " resolution." << endl;
    if (promptYesNo("\nDo you want to use a different aspect ratio/resolution?")) {
            HresIn = userInputInt("Enter game horizontal resolution and press enter: ",0,1000000);
            VresIn = userInputInt("Enter game vertical resolution and press enter: ", 0, 1000000);
            aRatio = calcaRatio(HresIn, VresIn);
            cout << "-------------------------------------------------------------------------------------------------" << endl;
            cout << "\nYour resolution is " << HresIn << "x" << VresIn << ". Aspect ratio is " << aRatio << endl;
    }
    else {
            cout << "-------------------------------------------------------------------------------------------------" << endl;
            cout << "\nYou got it. Keeping default aspect ratio of "<< aRatio << "." << endl;
    }
    settings[0] = scPath;
    settings[1] = to_string(HresIn);
    settings[2] = to_string(VresIn);
    if (promptYesNo("\nSave new settings?")) {
        writeSettings("settings.txt", settings);
        cout << "Settings saved to settings.txt\n" << endl;
    }
    else {
        cout << "\nOK, not saving\n";
    }
    int maxFOV = calcMaxFOV(aRatio);
    do {
        cout << "\nThe maximum horizontal FOV for your aspect ratio is " << maxFOV << endl;
        cout << "Enter desired horizontal FOV in degrees (" << minFOV << "-" << maxFOV << "):\n";
        HfovIn = userInputInt(" ", minFOV, maxFOV);

    } while (HfovIn > maxFOV || HfovIn < 60);
    int VFOV = calcVFOV(HfovIn, aRatio);
    string VfovStr = to_string(VFOV); //convert FOV to string
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cout << "\nBig brain math results:" << endl;
    cout << "   Aspect ratio is " << aRatio << endl;
    cout << "   Maximum horizontal FOV is " << maxFOV << endl;
    cout << "   Desired horizontal FOV is " << HfovIn << endl;
    cout << "   Calculated vertical FOV is " << VfovStr << endl;
    cout << "\nsearching in:\n" << attPath << endl << endl;
    srchRplceFile(attPath, "attributes.xml", srchFOV, VfovStr);
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    if (promptYesNo("\nWould you like to copy the new file to game folder (overwrite)?")) {
        cpyFile("attributes.xml", attPath);
        printLogo();
        cout << "Copied!\n" << endl;
    }
    else {
        printLogo();
        cout << "\nOK, leaving new attributes.xml in same directory as this .exe\n";
    }
    cout << "Bye!\n" << endl;
    cout << "press any key to exit" << endl;
    char bye = _getch();
return (0);
} 
