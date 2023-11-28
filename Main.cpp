/**
 * Main.cpp
 * BLG 335E Analysis of Algorithms Project 2
 *
 * Name: Meriç Bağlayan
 * Id  : 150190056
 * Date: 2023-11-28
 */

#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <time.h>

using namespace std;

enum Args
{
    EXECUTABLE = 0,
    INPUT = 1
};

#pragma region Function declarations
void displayTimeElapsed(char strategy, int threshold, auto time);

/**
 * @brief Function to display the wrong usage message.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 */
void displayWrongUsageMessage(int argc, const char **argv);

/**
 * @brief Function to display the help message.
 */
void claHelp();

/**
 * @brief Function to display the version message.
 */
void claVersion();
#pragma endregion

/**
 * @brief Main driver function.
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return EXIT_SUCCESS (0) if the program runs successfully, EXIT_FAILURE (1) otherwise.
 */
int main(int argc, const char **argv)
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        claHelp();
        return EXIT_SUCCESS;
    }
    else if (argc == 2 && strcmp(argv[1], "--version") == 0)
    {
        claVersion();
        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}

#pragma region Sorting functions

#pragma endregion

#pragma region Command line argument handler functions

void displayWrongUsageMessage(int argc, const char **argv)
{
    switch (argc)
    {
    case 1:
        cerr << "Error: You need to specify commands before moving on. Use '--help' to view the available commands." << endl;
        break;
    case 2:
        cerr << "Error: Unknown argument: " << argv[1] << ". Use '--help' to view the available commands." << endl;
        break;
    default:
        cerr << "Error: Unknown arguments: ";
        for (int i = 1; i <= argc; i++)
        {
            cerr << argv[i];
            if (i < argc - 1)
            {
                cerr << ", ";
            }
            else
            {
                cerr << ". Use '--help' to view the available commands." << endl;
            }
        }
    }
}

void displayTimeElapsed(char strategy, int threshold, auto time)
{
    cout << "Time taken by program: "
         << time << " ns." << endl;
}

void claHelp()
{
    cout << "Usage: TO BE DECIDED" << endl;
}

void claVersion()
{
    cout << "==============================================" << endl;
    cout << "BLG 335E Analysis of Algorithms I Project 2" << endl;
    cout << "Name TBA" << endl;
    cout << "Development Version" << endl;
    cout << "==============================================" << endl;
}
#pragma endregion