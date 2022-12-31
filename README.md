# AG-FOV-Tool for Star Citizen

Star Citizen uses vertical FOV values in it's config. This tool will use your desired horizontal FOV and screen resolution to calculate a vertical FOV.

It will then read the current Star Citizen config and make a local copy with the new FOV value. You will be given the option to copy this new file into the game directory and overrite the old one.

User settings are saved in settings.txt. The program will create this file if it does not exist an fill it with default values so you can see the layout.

If you prefer to just edit the settings.txt, there is a "Nike mode" (just do it), where the program will skip all user prompts, use settings from settings.txt and write new xml to game directory, all in one go.
