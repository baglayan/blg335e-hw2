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

#include <chrono> // for measuring runtime
#include <iostream>
#include <fstream> // for reading csv files
#include <sstream> // for reading csv files
#include <vector>  // for creating vectors
#include <string.h>
#include <time.h>
#include <climits> // for sentinel
#include <cmath>

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

/**
 * @brief Class that represents a heap.
 *
 * @attention NOT NECESSARILY A MAX-HEAP!
 */
class Heap
// no clue what i'm doing
{
private:
    vector<City> array;
    int size;
    int d;

public:
    int size()
    {
        return size;
    }
    int size(int i)
    {
        size = i;
    }
    int incrementSize()
    {
        size++;
    }
    int incrementSizeBy(int i)
    {
        size += i;
    }

    /**
     * @brief Construct a new binary Heap object.
     *
     * @param array The array that will be used to create the heap.
     * @param size The size of the array.
     *
     */
    Heap(vector<City> &a, int n)
    {
        array = a;
        size = n;
        d = 2;
    }
    /**
     * @brief Construct a new d-ary Heap object.
     *
     * @param a The array that will be used to create the heap.
     * @param n The size of the array.
     * @param k The number of children of non-leaf nodes.
     */
    Heap(vector<City> &a, int n, int k)
    {
        array = a;
        size = n;
        d = k;
    }
    /**
     * @brief Overloaded [] operator to access the elements of the heap.
     *        The index starts from 1.
     *
     * @param i The index of the element to be accessed.
     * @return The element at index i.
     * @throw `out_of_range` if i is out of range of the heap.
     *
     */
    City &operator[](int i)
    {
        if (i >= 1 && i <= size)
        {
            return array[i - 1];
        }
        else
        {
            throw out_of_range("Index out of range of heap");
        }
    }

    /**
     * @brief Function that maintains the max-heap property.
     *
     * @param heap The heap object to be transformed into a max heap.
     * @param i An index of the heap.
     *          The function assumes that the subtrees rooted at left(i) and right(i) are max heaps,
     *          but heap[i] might be smaller than its children, thus violating the max-heap property.
     */
    void max_heapify(Heap &heap, int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;

        // array.size() looks sketchy,
        // class implementation might work better
        if (l < heap.size && heap[l].population > heap[i].population)
        {
            largest = l;
        }
        else
        {
            largest = i;
        }
        if (r < heap.size && heap[r].population > heap[largest].population)
        {
            largest = r;
        }
        if (largest != i)
        {
            swap_elements(heap[i], heap[largest]);
            max_heapify(heap, largest);
        }
    }

    /**
     * @brief Function that builds a max heap from a Heap object.
     *
     * @param heap The Heap object to be transformed into a max heap.
     */
    void build_max_heap(Heap &heap)
    {
        for (int i = heap.size >> 1; i >= 1; i--)
        {
            heap.max_heapify(heap, i);
        }
    }

    /**
     * @brief Function that sorts a Heap object using heapsort.
     *
     * @param heap The Heap object to be sorted.
     */
    void heapsort(Heap &heap)
    {
        build_max_heap(heap);
        for (int i = heap.size; i >= 1; i--)
        {
            swap_elements(heap[0], heap[i]);
            heap.max_heapify(heap, 0);
        }
    }

    /**
     * @brief Function that inserts a node into a Heap object.
     *
     * @param heap The Heap object which the node will be inserted into.
     * @param node The node to be inserted.
     *
     * @return EXIT_FAILURE if heap overflow, EXIT_SUCCESS otherwise.
     */
    int max_heap_insert(Heap &heap, City &node)
    {
    }

    /**
     * @brief Function that removes and returns the maximum element of a Heap object.
     *
     * @param heap The Heap object which the maximum element will be extracted from.
     * @return The maximum element of the Heap object.
     */
    City heap_extract_max(Heap &heap)
    {
    }

    /**
     * @brief Function that increases the key of a node in a Heap object.
     *
     * @param heap The Heap object which the node is in.
     * @param node The node whose key will be increased.
     * @param newKey The new key value.
     */
    void heap_increase_key(Heap &heap, City &node, int newKey)
    {
    }

    /**
     * @brief Function that returns the maximum element of a Heap object.
     *
     * @param heap The Heap object which the maximum element will be returned from.
     * @return The maximum element of the Heap object.
     */
    City heap_maximum(Heap &heap)
    {
    }

    /**
     * @brief Function that calculates the height of a d-ary Heap object.
     *
     * @param heap The Heap object which the height will be calculated from.
     * @param d The number of children of non-leaf nodes.
     *
     * @return The height of the d-ary Heap object.
     */
    int dary_calculate_height(Heap &heap, int d)
    {
    }

    /**
     * @brief Function that removes and returns the maximum element of a d-ary Heap object.
     *
     * @param heap The Heap object which the maximum element will be extracted from.
     */
    City dary_extract_max(Heap &heap)
    {
    }

    /**
     * @brief Function that inserts a node into a d-ary Heap object.
     *
     * @param heap The Heap object which the node will be inserted into.
     * @param node The node to be inserted.
     * @param d The number of children of non-leaf nodes.
     */
    void dary_insert_element(Heap &heap, City &node, int d)
    {
    }

    /**
     * @brief Function that increases the key of a node in a d-ary Heap object.
     *
     * @param heap The Heap object which the node is in.
     * @param node The node whose key will be increased.
     * @param newKey The new key value.
     * @param d The number of children of non-leaf nodes.
     */
    void dary_increase_key(Heap &heap, City &node, int newKey, int d)
    {
    }
};

#pragma region Function declarations

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

#pragma region Sorting helper functions
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
    cout << "Usage: ./Heapsort <DATASET-FILE-NAME>.csv <FUNCTION-NAME> <OUTPUT-FILE-NAME>.csv ([d<#>] | [i<#>] [k<#>])\n"
         << "Options:\n"
         << "  <DATASET-FILE-NAME>.csv:  The name of the dataset file. Must be a .csv file with semicolon as the delimiter.\n"
         << "  <FUNCTION-NAME>:  The name of the function to be used. Must be one of the following:\n"
         << "    - max_heapify\n"
         << "    - build_max_heap\n"
         << "    - heapsort\n"
         << "    - max_heap_insert\n"
         << "    - heap_extract_max\n"
         << "    - heap_increase_key\n"
         << "    - heap_maximum\n"
         << "    - dary_calculate_height\n"
         << "    - dary_extract_max\n"
         << "    - dary_insert_element\n"
         << "    - dary_increase_key\n"
         << "  <OUTPUT-FILE-NAME>.csv:  The name of the output file. Must be a .csv file with semicolon as the delimiter.\n"
         << "  [d<#>]:  Optional parameter to specify the number of children of non-leaf nodes. Example use: d5.\n"
         << "  [i<#>]:  Optional parameter to specify the index of a node.\n"
         << "  [k<#>]:  Optional parameter to specify the key value to update an element. Must be used with i\n"
         << "  i and k together are available only for the following functions:\n"
         << "    - heap_increase_key\n"
         << "    - dary_increase_key" << endl;
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