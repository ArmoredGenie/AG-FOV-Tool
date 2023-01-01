// AG FOV Picker.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include "screen.h"
#include <fstream>
#include <conio.h>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

string srchFOV = " <Attr name=\"FOV\" value=\"";

int main()
{
    int minFOV = 0;
    cout << "\n------------------------------------- Star Citizen FOV Tool -------------------------------------" << endl;
    cout << "--------------------------------------- By ArmoredGenie -----------------------------------------" << endl;

    cout << "\nStar Citizen uses vertical FOV values in it's config. This Tool will use your desired horizontal" << endl;
    cout <<   "FOV and screen resolution to calculate a vertical FOV.\n" << endl;
    cout <<   "It will then read the current Star Citizen config and make a local copy with the new FOV value." << endl;
    cout <<   "You will have the option to copy this new file into the game directory to overrite the old one." << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cout << "\nReading from settings.txt:" << endl;
    vector<string> settings = readSettings("settings.txt"); //get settings from settings.txt
    string scPath = settings[1];
    int HresIn = 0;
    int VresIn = 0;
    int HfovIn = 0;
    try {
        HresIn = stoi(settings[2]);
        VresIn = stoi(settings[3]);
        HfovIn = stoi(settings[4]);
    }
    catch (...) {
        std::cout << "\nError in settings.txt! If you delete the file, the program will create a new one for you" << std::endl;
        cout << "\npress any key to exit" << endl;
        char bye = _getch();
        exit(0);
    }
cout <<   "  Path to SC.............. \"" << scPath << "\"" <<
        "\n  Horizontal resolution... \"" << HresIn << "\"" <<
        "\n  Vertical resolution..... \"" << VresIn << "\"" <<
        "\n  FOV..................... \"" << HfovIn << "\"" << endl;
    if (promptYesNo("\nJust do it? \n - Will skip all user prompts, use settings from settings.txt and write new xml to game directory \n - make sure settings above are good!\n")) {
        string attPath = scPath + "\\USER\\Client\\0\\Profiles\\default\\attributes.xml";
        double aRatio = calcaRatio(HresIn, VresIn);
        int VFOV = calcVFOV(HfovIn, aRatio);
        string VfovStr = to_string(VFOV); //convert FOV to string
        srchRplceFile(attPath, "attributes.xml", srchFOV, VfovStr);
        cpyFile("attributes.xml", attPath);
        cout << "Copied to game directory" << "-\n" << attPath << endl;
        cout << "press any key to exit" << endl;
        char bye = _getch();
        printLogo();
        this_thread::sleep_for(chrono::seconds(2));
        exit(0);
    }
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
            cout << "\nYou got it. Keeping aspect ratio of "<< aRatio << " and resolution of " << HresIn << "x" << VresIn << endl;
    }
    cout << "Enter desired horizontal FOV in degrees (180 max):\n";
    HfovIn = userInputInt(" ", 0, 180);
    int VFOV = calcVFOV(HfovIn, aRatio);
    string VfovStr = to_string(VFOV); //convert FOV to string
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    cout << "\nBig brain math results:" << endl;
    cout << "   Aspect ratio is " << aRatio << endl;
    cout << "   Desired horizontal FOV is " << HfovIn << endl;
    cout << "   Calculated vertical FOV is " << VfovStr << endl;
    cout << "\nsearching in:\n" << attPath << endl << endl;
    srchRplceFile(attPath, "attributes.xml", srchFOV, VfovStr);
    settings[1] = scPath;
    settings[2] = to_string(HresIn);
    settings[3] = to_string(VresIn);
    settings[4] = to_string(HfovIn);
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
    if (promptYesNo("\nSave the values you entered to settings.txt?")) {
        writeSettings("settings.txt", settings);
        cout << "Settings saved\n" << endl;
    }
    else {
        cout << "\nOK, not saving\n";
    }
    cout << "Bye!\n" << endl;
    cout << "press any key to exit" << endl;
    char bye = _getch();
return (0);
} 
