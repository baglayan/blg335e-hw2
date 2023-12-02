/**
 * Heapsort.cpp
 * BLG 335E Analysis of Algorithms Project 2
 *
 * Name: Meriç Bağlayan
 * Id  : 150190056
 * Date: 2023-12-02
 * 
 * Non-functional messy code as it is in development.
 */

#include <chrono>   // for measuring runtime
#include <iostream> 
#include <fstream>  // for reading csv files
#include <sstream>  // for reading csv files
#include <vector>   // for creating vectors
#include <string.h> // for handling arguments
#include <time.h>  
#include <climits>  // for sentinel

using namespace std;

enum Args
{
    EXECUTABLE = 0,
    DATASET = 1,
    FUNCTION = 2,
    OUTPUT = 3,
};

struct City
{
    string name;
    int population;
};

//maybe i should create a heap class? investigate
//the class should enforce the size strictly
class Heap
{
private:
    vector<City> array;
    int size;
    int d;

public:
    //getters, setters, functions
    Heap(vector<City> &array, int size, int d)
    {
        this->array = array;
        this->size = size;
        this->d = d;
    }
};

#pragma region Function declarations

/**
 * @brief Function that maintains the max-heap property.
 *
 * @param array The vector to be transformed into a max heap.
 * @param i An index of the vector.
 *          The function assumes that the subtrees rooted at left(i) and right(i) are max heaps,
 *          but array[i] might be smaller than its children, thus violating the max-heap property.
 */
void max_heapify(vector<City> &array, int i);

/**
 * @brief Function that builds a max heap from a vector.
 *
 * @param array The vector to be transformed into a max heap.
 * @param length The length of the vector.
 */
void build_max_heap(vector<City> &array, int length);

/**
 * @brief Function that sorts a vector using heapsort.
 *
 * @param array The vector to be sorted.
 * @param length The length of the vector.
 */
void heapsort(vector<City> &array, int length);

/**
 * @brief Function that inserts a node into a max heap.
 *
 * @param array The vector which the node will be inserted into.
 * @param node The node to be inserted.
 * @param size The size of the vector.
 * 
 * @return EXIT_FAILURE if heap overflow, EXIT_SUCCESS otherwise.
 */
int max_heap_insert(vector<City> &array, City &node, int size);

/**
 * @brief Function that removes and returns the maximum element of a max heap.
 *
 * @param array The vector which the maximum element will be extracted from.
 * @return The maximum element of the max heap.
 */
City heap_extract_max(vector<City> &array);

/**
 * @brief Function that increases the key of a node.
 *
 * @param array The vector which the node is in.
 * @param node The node whose key will be increased.
 * @param newKey The new key value.
 */
void heap_increase_key(vector<City> &array, City &node, int newKey);

/**
 * @brief Function that returns the maximum element of a max heap.
 *
 * @param array The vector which the maximum element will be returned from.
 * @return The maximum element of the max heap.
 */
City heap_maximum(vector<City> &array);

void dary_array_representation(); // not sure what this is supposed to do

void dary_calculate_height(vector<City> &array, int size, int d); // takes log base d of n

/**
 * @brief Function that removes and returns the maximum element of a d-ary max heap.
 *
 * @param array The vector which the maximum element will be extracted from.
 */
City dary_extract_max(vector<City> &array);

/**
 * @brief Function that inserts a node into a d-ary max heap.
 *
 * @param array The vector which the node will be inserted into.
 * @param node The node to be inserted.
 * @param size The size of the vector.
 * @param d The number of children of non-leaf nodes.
 */
void dary_insert_element(vector<City> &array, City &node, int size, int d);

/**
 * @brief Function that increases the key of a node in a d-ary max heap.
 *
 * @param array The vector which the node is in.
 * @param node The node whose key will be increased.
 * @param newKey The new key value.
 * @param d The number of children of non-leaf nodes.
 */
void dary_increase_key(vector<City> &array, City &node, int newKey, int d);

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
 * @brief Function to display the wrong file extension message.
 */
void display_wrong_file_extension_message();

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
    else if (argc < 4 || argc > 7)
    {
        display_wrong_usage_message(argc, argv);
        return EXIT_FAILURE;
    }

    const char *DATASET_ARGUMENT = argv[DATASET];
    const char *OUTPUT_ARGUMENT = argv[OUTPUT];

    const char *DATASET_EXTENSION = DATASET_ARGUMENT + strlen(DATASET_ARGUMENT) - 4;
    const char *OUTPUT_EXTENSION = OUTPUT_ARGUMENT + strlen(OUTPUT_ARGUMENT) - 4;

    bool areFileExtensionsCorrect = strcmp(DATASET_EXTENSION, ".csv") == 0 && strcmp(OUTPUT_EXTENSION, ".csv") == 0;
    if (!areFileExtensionsCorrect)
    {
        display_wrong_file_extension_message();
        return EXIT_FAILURE;
    }

    const string datasetName = argv[DATASET];
    const string outputName = argv[OUTPUT];

    ifstream datasetFile(datasetName);

    if (!datasetFile.is_open())
    {
        cerr << "Could not open the dataset file " << datasetName << "." << endl;
        return EXIT_FAILURE;
    }

    vector<City> cities;

    string firstLine;
    getline(datasetFile, firstLine);

    // Remove UTF-8 BOM if it exists
    if (!firstLine.empty() && firstLine[0] == '\xEF' && firstLine[1] == '\xBB' && firstLine[2] == '\xBF')
    {
        firstLine.erase(0, 3);
        istringstream stream(firstLine);
        City city;
        getline(stream, city.name, ';');
        stream >> city.population;
        cities.push_back(city);
    }

    string line;
    while (getline(datasetFile, line))
    {
        istringstream stream(line);
        City city;
        getline(stream, city.name, ';');
        stream >> city.population;
        cities.push_back(city);
    }

    datasetFile.close();

    const string function = argv[FUNCTION];

    return EXIT_SUCCESS;
}

#pragma region Sorting functions
inline void swap_elements(City &c1, City &c2)
{
    City temp = c1;
    c1 = c2;
    c2 = temp;
}

inline int parent(int i)
{
    return i >> 1;
}

inline int left(int i)
{
    return i << 1;
}

inline int right(int i)
{
    return (i << 1) + 1;
}

void max_heapify(vector<City> &array, int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;

    //array.size() looks sketchy,
    //class implementation might work better
    if (l < array.size() && array[l].population > array[i].population)
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
    if (r < array.size() && array[r].population > array[largest].population)
    {
        largest = r;
    }
    if (largest != i)
    {
        swap_elements(array[i], array[largest]);
        max_heapify(array, largest);
    }
}

void build_max_heap(vector<City> &array, int length)
{
    for (int i = length >> 1; i >= 0; i--)
    {
        max_heapify(array, i);
    }
}

void heapsort(vector<City> &array, int length)
{
    build_max_heap(array, length);
    for (int i = length - 1; i >= 0; i--)
    {
        swap_elements(array[0], array[i]);
        max_heapify(array, 0);
    }
}
#pragma endregion

#pragma region Command line argument handler functions
void displayWrongFileExtensionMessage()
{
    cerr << "Files for dataset and output should have the extension '.csv'." << endl;
}

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
    // not entirely sure about the optional parameters
    cout << "Usage: ./Heapsort <DATASET-FILE-NAME>.csv <FUNCTION-NAME> <OUTPUT-FILE-NAME>.csv ([d<#>] | [i<#>] [k<#>])" << endl;
    cout << "Options:" << endl;
    cout << "  <DATASET-FILE-NAME>.csv:  The name of the dataset file. Must be a .csv file with semicolon as the delimiter." << endl;
    cout << "  <FUNCTION-NAME>:  The name of the function to be used. Must be one of the following:" << endl;
    cout << "    - max_heapify" << endl;
    cout << "    - build_max_heap" << endl;
    cout << "    - heapsort" << endl;
    cout << "    - max_heap_insert" << endl;
    cout << "    - heap_extract_max" << endl;
    cout << "    - heap_increase_key" << endl;
    cout << "    - heap_maximum" << endl;
    cout << "    - dary_array_representation" << endl;
    cout << "    - dary_calculate_height" << endl;
    cout << "    - dary_extract_max" << endl;
    cout << "    - dary_insert_element" << endl;
    cout << "    - dary_increase_key" << endl;
    cout << "  <OUTPUT-FILE-NAME>.csv:  The name of the output file. Must be a .csv file with semicolon as the delimiter." << endl;
    cout << "  [d<#>]:  Optional parameter to specify the number of children of non-leaf nodes. Example use: d5." << endl;
    cout << "  [i<#>]:  Optional parameter to specify the index of a node." << endl;
    cout << "  [k<#>]:  Optional parameter to specify the key value to update an element. Must be used with i" << endl;
    cout << "  i and k together are available only for the following functions:" << endl;
    cout << "    - heap_increase_key" << endl;
    cout << "    - dary_increase_key" << endl;
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