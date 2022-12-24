// AG FOV Picker.cpp : This file contains the 'main' function. Program execution begins and ends there.

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
    printLogo();
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
    attPath = scPath + "\\USER\\Client\\0\\Profiles\\default\\attributes.xml";
    cout << "\nDefault resolution for aspect ratio calculation is " << HresIn << "x" << VresIn << "." << endl;
        if (promptYesNo("\nDo you want to change the resolution from default? ")) {
            cout << "\nEnter horizontal resolution and press enter:";
            cin >> HresIn;
            cout << "\nEnter vertical resolution and press enter:";
            cin >> VresIn;
            cout << "\nAspect ratio will be calculated using a resolution of " << HresIn << "x" << VresIn << "." << endl;
        }
        else {
            cout << "\nYou got it. Keeping default resolution of " << HresIn << "x" << VresIn << "." << endl;
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
    srchRplceFile(attPath, srch, VfovStr);
    if (promptYesNo("\nWould you like to copy the new file to game folder (overite)?")) {
        cpyFile("attributes.xml", attPath);
    }
    else {
        cout << "\nRoger, will leave attributes.xml alone\n";
    }

    cout << "Bye!";
    system("pause");
return (0);
} 
