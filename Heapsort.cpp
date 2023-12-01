/**
 * Heapsort.cpp
 * BLG 335E Analysis of Algorithms Project 2
 *
 * Name: Meriç Bağlayan
 * Id  : 150190056
 * Date: 2023-12-02
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

struct City
{
    string name;
    int population;
};

#pragma region Function declarations

// I would prefer camelCase

void max_heapify(vector<City> &array, int i);
void build_max_heap(vector<City> &array, int length);
void heapsort(vector<City> &array, int length);
void max_heap_insert(vector<City> &array, City node, int size);
City heap_extract_max(vector<City> &array);
void heap_increase_key(vector<City> &array, City &node, int newKey);
City heap_maximum(vector<City> &array);
void dary_array_representation();
void dary_calculate_height();
City dary_extract_max();
void dary_insert_element();
void dary_increase_key();

inline void swap_elements(City &c1, City &c2);
inline int parent(int i);
inline int left(int i);
inline int right(int i);

void display_time_elapsed(char strategy, int threshold, auto time);

/**
 * @brief Function to display the wrong usage message.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 */
void display_wrong_usage_message(int argc, const char **argv);

/**
 * @brief Function to display the help message.
 */
void cla_help();

/**
 * @brief Function to display the version message.
 */
void cla_version();
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
        cla_help();
        return EXIT_SUCCESS;
    }
    else if (argc == 2 && strcmp(argv[1], "--version") == 0)
    {
        cla_version();
        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}

#pragma region Sorting functions
inline void swap_elements(City &c1, City &c2)
{
    City temp = c1;
    c1 = c2;
    c2 = temp;
}

inline int parent(int i) {
    return i >> 1;
}

inline int left(int i) {
    return i << 1;
}

inline int right(int i) {
    return (i << 1) + 1;
}

void max_heapify(vector<City> &array, int i) {}
#pragma endregion

#pragma region Command line argument handler functions

void display_wrong_usage_message(int argc, const char **argv)
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

void display_time_elapsed(char strategy, int threshold, auto time)
{
    cout << "Time taken by Heapsort: "
         << time << " ns." << endl;
}

void cla_help()
{
    cout << "Usage: TO BE DECIDED" << endl;
}

void cla_version()
{
    cout << "==============================================" << endl;
    cout << "BLG 335E Analysis of Algorithms I Project 2" << endl;
    cout << "Heapsort" << endl;
    cout << "Development Version" << endl;
    cout << "==============================================" << endl;
}
#pragma endregion