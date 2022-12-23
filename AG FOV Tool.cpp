// AG FOV Picker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "screen.h"
#include <fstream>
#include <conio.h>

using namespace std;

string txtLine;
string srch = " <Attr name=\"FOV\" value=\"";
int number;
char letter; 
size_t pos;
int HresIn = 2560;
int VresIn = 1440;
int HfovIn;
int maxFOV;
string VfovStr;
//string scPath = "C:\\StarCitizen\\Live";
string scPath = "C:\\Program Files\\Roberts Space Industries\\StarCitizen\\LIVE";
string attPath;
string newAttPath;
ifstream inFile;
ifstream inTempFile;
ofstream outTempFile;
ofstream outFile;

int main()
{
    cout << "------------------------- Star Citizen FOV Tool ----------------------------" << endl;
    cout << "---------------------------- By ArmoredGenie -------------------------------" << endl;
    cout << "\nStar Citizen uses vertical FOV values in it's config. This Tool will use your" << endl;
    cout <<   "desired horizontal FOV and screen resolution to calculate a vertical FOV.\n" << endl;
    cout <<   "It will then read the current Star Citizen config and make a local copy with " << endl;
    cout <<   "the new FOV value. You will be given the option to copy this new file into \nthe game directory and overrite the old one." << endl;
    cout << "\nCurrent path to Best Damn Space Sim is:   \n" << scPath << endl;
    promptYesNo Q1("\nDo you want to change it?"); 
    if (Q1.get_YesNo()) {
        cout << "\nNeedy. Enter new path and press enter: ";
        getline(cin,scPath);
        cout << "\nNew path to Star Citizen is " << scPath << endl;
    }
    else {
        cout << "\nRoger that CMDR, using default path" << endl;
    }
    attPath = scPath + "\\USER\\Client\\0\\Profiles\\default\\attributes.xml";
    cout << "\nDefault resolution for aspect ratio calculation is " << HresIn << "x" << VresIn << ".";
    promptYesNo Q2(" Change it? ");
        if (Q2.get_YesNo()) {
            cout << "\nEnter horizontal resolution and press enter:";
            cin >> HresIn;
            cout << "\nEnter vertical resolution and press enter:";
            cin >> VresIn;
            cout << "\nAspect ratio will be calculated using a resolution of " << HresIn << "x" << VresIn << "." << endl;
        }
        else {
            cout << "\no7. Keeping default resolution of " << HresIn << "x" << VresIn << "." << endl;
        }
    screen my_screen(HresIn, VresIn);
    do {
        maxFOV = floor(my_screen.get_maxFOV());
        cout << "\nThe maximum horizontal FOV for your aspect ratio is " << maxFOV << endl;
        cout << "Enter desired horizontal FOV in degrees (60-" << maxFOV << "),then press enter:";
        cin >> HfovIn;
    } while (HfovIn > maxFOV || HfovIn < 60);
    my_screen.set_HFOV(HfovIn);
    VfovStr = to_string((int)round(my_screen.get_VFOV())); //round Vertical FOV and convert to string
    cout << "\nBig brain math results:" << endl;
    cout << "   Screen resolution is " << my_screen.get_Hres() << "x" << my_screen.get_Vres() << endl;
    cout << "   Aspect ratio is " << my_screen.get_aRatio() << endl;
    cout << "   Maximum horizontal FOV is " << maxFOV << endl;
    cout << "   Desired horizontal FOV is " << HfovIn << endl;
    cout << "   Calculated vertical FOV is " << VfovStr << endl;
    cout << "\nsearching in:\n" << attPath << endl << endl;
    inFile.open(attPath);
    outTempFile.open("attributes.xml");
    if (inFile.fail())
        cout << endl << "File not found! Here be dragons." << endl;
    else {
        while (!inFile.eof()) {
            getline(inFile, txtLine);
            if (txtLine.find(srch) != std::string::npos) {
                cout << "Found:\n" << txtLine << endl;
                txtLine.replace(srch.length(), 2, VfovStr);
                cout << "Line edited to:\n" << txtLine << endl << "\nMission accomplished! \nA new attributes.xml file has been saved wherever this .exe is stored" << endl;
            }
        outTempFile << txtLine << endl;
        }
        inFile.close();
        outTempFile.close();
    }
    promptYesNo Q3("\nWould you like to copy the new file to game folder (overite)?");
    if (Q3.get_YesNo()) {
        inTempFile.open("attributes.xml");
        outFile.open(attPath);
        if (inTempFile.fail())
            cout << endl << "File not found! Here be dragons" << endl;
        else {
            while (!inTempFile.eof()) {
                getline(inTempFile, txtLine);
                outFile << txtLine << endl;
            }
            inTempFile.close();
            outFile.close();
        }
    }
    else {
        cout << "\nRoger, will leave attributes.xml alone\n";
    }
    cout << "\nBye!\n\n";
    
//    VFOVline.replace(25, 2, VfovStr);
//    cout << "now line is :\n" << VFOVline << endl;
return (0);
} 
