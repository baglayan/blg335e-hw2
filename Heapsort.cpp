/**
 * Heapsort.cpp
 * BLG 335E Analysis of Algorithms Project 2
 *
 * Name: Meriç Bağlayan
 * Id  : 150190056
 * Date: 2023-12-13
 *
 */

#include <iostream>      // for input and output operations
#include <typeinfo>      // for typeid
#include <string.h>      // for strings and string operations
#include <chrono>        // for measuring runtime
#include <fstream>       // for reading csv files
#include <sstream>       // for reading csv files
#include <vector>        // for creating vectors
#include <unordered_map> // for handling optional command line arguments
#include <functional>    // for handling optional command line arguments
#include <climits>       // for sentinel
#include <cmath>         // for math operations

using namespace std;

enum Args
{
    EXECUTABLE = 0,
    DATASET = 1,
    FUNCTION = 2,
    OUTPUT = 3,
    OPTIONAL1 = 4,
    OPTIONAL2 = 5, // unused in current implementation
    OPTIONAL3 = 6  // ditto
};

/**
 * @brief Struct that represents a city with
 * a name and a population.
 *
 */
struct City
{
    string name;
    long long int population;
};

// Function declarations

/**
 * @brief Function to swap two elements.
 *
 * @param c1 The first element.
 * @param c2 The second element.
 */
inline void swap_elements(City &c1, City &c2);

/**
 * @brief Returns the index of the parent of an index in a d-ary heap.
 *
 * @param i The index whose parent index will be calculated.
 * @param d Number of children of non-leaf nodes.
 * @return The parent index of i.
 */
inline size_t dary_parent(size_t i, unsigned int d);

/**
 * @brief Returns the index of k-th child of an index in a d-ary heap.
 *
 * @param i The index whose child index will be calculated.
 * @param d Number of children of non-leaf nodes.
 * @param k The k-th child of i.
 *
 * @return The index of k-th child of i.
 */
inline size_t dary_child(size_t i, unsigned int d, unsigned int k);

/**
 * @brief Function to calculate the hypothetical parent index of an index.
 *
 * @param i The index whose parent index will be calculated.
 * @return int The hypothetical parent index of i.
 */
inline size_t parent(size_t i);

/**
 * @brief Function to calculate the hypothetical left child index of an index.
 *
 * @param i The index whose left child index will be calculated.
 * @return int The hypothetical left child index of i.
 */
inline size_t left(size_t i);

/**
 * @brief Function to calculate the hypothetical right child index of an index.
 *
 * @param i The index whose right child index will be calculated.
 * @return int The hypothetical right child index of i.
 */
inline size_t right(size_t i);

/**
 * @brief Extracts the number from the optional arguments such as "d3".
 *
 * @param arg The optional argument from which the number will be extracted.
 * @return size_t The number extracted from the optional argument.
 */
long long int extract_number_from_arg(const char *arg);

/**
 * @brief Extracts the city from the optional arguments such as "k_Tekirdag_204000".
 *
 * @param arg The optional argument from which the number will be extracted.
 * @return The city extracted from the optional argument.
 */
City extract_city_info_from_arg(const char *arg);

/**
 * @brief Function to display the time elapsed.
 *
 * @param time The time elapsed.
 * @param function The name of the function that was executed.
 */
void display_time_elapsed(chrono::_V2::high_resolution_clock::rep time, const string function);

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

/**
 * @brief Class that represents a heap.
 *
 * @attention NOT NECESSARILY A MAX-HEAP!
 */
class Heap
{
private:
    vector<City> array;
    size_t size;
    unsigned int d;

public:
    /**
     * @brief Overloaded [] operator to access the elements of the heap.
     *        The index starts from 1.
     *
     * @param i The index of the element to be accessed.
     * @return The element at index i.
     * @throw `out_of_range` if i is out of range of the heap.
     *
     */
    City &operator[](size_t i)
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
     * @brief Construct a new binary Heap object.
     *
     * @param array The array that will be used to create the heap.
     * @param size The size of the array.
     *
     */
    Heap(vector<City> &a, size_t n)
    {
        array = a;
        size = n;
        d = 2; // construct a binary heap if d is not specified. not actually used in this project
    }

    /**
     * @brief Construct a new d-ary Heap object.
     *
     * @param a The array that will be used to create the heap.
     * @param n The size of the array.
     * @param k The number of children of non-leaf nodes.
     */
    Heap(vector<City> &a, size_t n, unsigned int k)
    {
        array = a;
        size = n;
        d = k;
    }

    /**
     * @brief Destroy the Heap object
     *
     */
    ~Heap()
    {
        array.clear();
    }

    /**
     * @brief Function that maintains the max-heap property.
     *
     * @param i An index of the heap.
     *          The function assumes that the subtrees rooted at left(i) and right(i) are max heaps,
     *          but heap[i] might be smaller than its children, thus violating the max-heap property.
     */
    void max_heapify(size_t i)
    {
        size_t l = left(i);  // left child index
        size_t r = right(i); // right child index
        size_t largest;      // index of the largest element during comparisons among heap[i], heap[l] and heap[r]

        if (l <= this->size && (*this)[l].population > (*this)[i].population) // check for left child
        {
            largest = l;
        }
        else
        {
            largest = i; // if left child is not larger than heap[i], heap[i] is the largest
        }
        if (r <= this->size && (*this)[r].population > (*this)[largest].population) // check for right child
        {
            largest = r;
        }

        if (largest != i) // if heap[i] is not the largest, swap it with the largest and call max_heapify on the largest
        {
            swap_elements((*this)[i], (*this)[largest]);
            this->max_heapify(largest);
        }
    }

    /**
     * @brief Function that builds a max heap from the heap.
     *
     */
    void build_max_heap()
    {
        for (int i = size >> 1; i >= 1; i--) // iteratively max heapify starting from the last pre-leaf node
        {
            max_heapify(i);
        }
    }

    /**
     * @brief Function that inserts a node into a Heap object.
     *
     * @param node The node to be inserted.
     *
     * @return EXIT_FAILURE if heap overflow, EXIT_SUCCESS otherwise.
     */
    void max_heap_insert(City &newCity)
    {
        if (size == array.max_size()) // check for heap overflow
        {
            throw overflow_error("Heap overflow");
        }
        size++;                          // increase heap size to accomodate new node
        City newCityPreChange = newCity; // save node before modifying it
        newCity.population = INT_MIN;    // set population to negative sentinel
        array.push_back(newCity);        // add node to the end of the array

        this->heap_increase_key(size, newCityPreChange); // increase key of the node to its actual value
    }

    /**
     * @brief Function that returns the maximum element of a Heap object.
     *
     * @return The maximum element of the Heap object.
     */
    City heap_maximum()
    {
        if (this->size < 1) // check for heap underflow
        {
            throw underflow_error("Heap underflow");
        }
        return (*this)[1]; // return the first element of the max heap
    }

    /**
     * @brief Function that removes and returns the maximum element of a Heap object.
     *
     * @return The maximum element of the Heap object.
     */
    City heap_extract_max()
    {
        City max = this->heap_maximum();  // save the maximum element in a variable
        (*this)[1] = (*this)[this->size]; // replace the maximum element with the last element of the heap
        this->size--;                     // decrease the size of the heap
        this->max_heapify(1);             // max heapify starting from the root
        return max;                       // return the maximum element
    }

    /**
     * @brief Function that increases the key of a node in a Heap object.
     *
     * @param index The index of the node whose key will be increased.
     * @param newKey The new key value.
     */
    void heap_increase_key(unsigned int index, City newKey)
    {
        if (newKey.population < (*this)[index].population) // check for new key being smaller than current key
        {
            throw invalid_argument("New key is smaller than current key");
        }

        (*this)[index].population = newKey.population; // set the new key value

        while (index > 1 && (*this)[parent(index)].population < (*this)[index].population) // swap elements until the max-heap property is restored
        {
            swap_elements((*this)[index], (*this)[parent(index)]);
            index = parent(index);
        }
    }

    /**
     * @brief Function that maintains the max-heap property for a d-ary heap.
     *
     * @param i An index of the heap.
     */
    void dary_max_heapify(size_t i)
    {
        // Index of the largest element during comparisons among heap[i] and its children
        size_t largest = i;

        for (size_t child = d * (i - 1) + 2;
             child <= d * (i - 1) + d + 1;
             child++) // iterate over children
        {
            if (child <= this->size && (*this)[child].population > (*this)[largest].population) // if child is larger than largest, set largest to child
            {
                largest = child;
            }
        }

        if (largest != i) // if heap[i] is not the largest, swap it with the largest and call max_heapify on the largest
        {
            swap_elements((*this)[i], (*this)[largest]);
            this->dary_max_heapify(largest);
        }
    }

    /**
     * @brief Function that builds a max d-ary heap from the d-ary heap.
     *
     * @param n Size of the heap.
     *
     */
    void dary_build_max_heap() // iteratively max heapify starting from the last pre-leaf node
    {
        for (int i = floor((size - 2) / d + 1); i >= 1; i--)
        {
            dary_max_heapify(i);
        }
    }

    /**
     * @brief Function that calculates the height of a d-ary Heap object.
     *
     * @return The height of the d-ary Heap object.
     */
    int dary_calculate_height()
    {
        return ceil(log(size * d - size + 1) / log(d)); // calculate the height of the heap using logarithms
    }

    /**
     * @brief Function that removes and returns the maximum element of a d-ary Heap object.
     *
     */
    City dary_extract_max()
    {
        City max = this->heap_maximum();  // save the maximum element in a variable
        (*this)[1] = (*this)[this->size]; // replace the maximum element with the last element of the heap
        this->size--;                     // decrease the size of the heap
        this->dary_max_heapify(1);        // max heapify starting from the root
        return max;                       // return the maximum element
    }

    /**
     * @brief Function that inserts a node into a d-ary Heap object.
     *
     * @param node The node to be inserted.
     */
    void dary_insert_element(City &node)
    {
        if (size == array.max_size())
        {
            throw overflow_error("Heap overflow");
        }
        size++;                       // increase heap size to accomodate new node
        City newCityPreChange = node; // save node before modifying it
        node.population = INT_MIN;    // set population to negative sentinel
        array.push_back(node);        // add node to the end of the array

        this->dary_increase_key(size, newCityPreChange); // increase key of the node to its actual value
    }

    /**
     * @brief Function that increases the key of a node in a d-ary Heap object.
     *
     * @param index The index of the node whose key will be increased.
     * @param newKey The new key value.
     */
    void dary_increase_key(unsigned int index, City newKey)
    {
        if (newKey.population < (*this)[index].population) // check for new key being smaller than current key
        {
            throw invalid_argument("New key is smaller than current key");
        }

        (*this)[index].population = newKey.population; // set the new key value

        while (index > 1 && (*this)[dary_parent(index, d)].population < (*this)[index].population) // swap elements until the max-heap property is restored
        {
            swap_elements((*this)[index], (*this)[dary_parent(index, d)]);
            index = dary_parent(index, d);
        }
    }

    /**
     * @brief Function that sorts a Heap object using heapsort.
     *
     */
    void heapsort()
    {
        this->build_max_heap();            // build a max heap
        for (size_t i = size; i >= 2; i--) // iteratively swap the first element with the ith element and max heapify the heap
        {
            swap_elements((*this)[1], (*this)[i]);
            size--;
            this->max_heapify(1);
        }
    };

    /**
     * @brief Function that sorts a d-ary Heap object using heapsort.
     *
     */
    void dary_heapsort()
    {
        this->dary_build_max_heap(); // build a max heap
        for (size_t i = size; i >= 2; i--) // iteratively swap the first element with the ith element and max heapify the heap
        {
            swap_elements((*this)[1], (*this)[i]);
            size--;
            this->dary_max_heapify(1);
        }
    }

    /**
     * @brief Function that prints the heap to an output file.
     *
     * @param outputFile The output file to which the heap will be printed.
     * @param n Size of the heap.
     */
    void print_to_output_file(ofstream &outputFile, size_t n)
    {
        size = n;
        for (size_t i = 1; i <= size; i++)
        {
            outputFile << (*this)[i].name << ";" << (*this)[i].population << endl;
        }
    }
};

/**
 * @brief Function to execute a function and measure its runtime.
 *
 * @param heap The heap object on which the function will be executed.
 * @param func The function to be executed.
 * @param functionName The name of the function to be executed.
 * @param args The arguments of the function to be executed.
 */
template <typename Func, typename... Args>
void execute_and_measure(Heap &heap, Func func, const string &functionName, Args... args);

template <typename Func, typename... Args>
void execute_measure_print(ofstream &outputFile, Heap &heap, Func func, const string &functionName, Args... args);

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

    // Remove UTF-8 byte order mark if it exists
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
    unsigned int argD;
    size_t argI;
    City argK;

    unordered_map<char, std::function<void(const char *)>> argMap = {
        {'d', [&](const char *arg)
         { argD = extract_number_from_arg(arg); }},
        {'i', [&](const char *arg)
         { argI = extract_number_from_arg(arg); }},
        {'k', [&](const char *arg)
         { argK = extract_city_info_from_arg(arg); }}};

    int optionalArgc = argc - 4;

    if (optionalArgc == 0)
    {
        argD = 2;
        argI = 0;
        argK = {"", 0};
    }
    else if (optionalArgc >= 1 && optionalArgc <= 3)
    {
        for (int i = 0; i < optionalArgc; ++i)
        {
            char optionLetter = argv[i + OPTIONAL1][0];

            if (argMap.find(optionLetter) != argMap.end())
            {
                argMap[optionLetter](argv[i + OPTIONAL1]);
            }
            else
            {
                display_wrong_usage_message(argc, argv);
                return EXIT_FAILURE;
            }
        }
    }
    else
    {
        display_wrong_usage_message(argc, argv);
        return EXIT_FAILURE;
    }

    ofstream outputFile(outputName, ofstream::out);
    if (!outputFile.is_open())
    {
        cerr << "Could not open the output file " << outputName << "." << endl;
        return EXIT_FAILURE;
    }

    size_t vectorSize = cities.size();
    Heap heap(cities, cities.size(), argD);

    // Using a function map turns out just as long.
    if (strcmp(function.c_str(), "max_heapify") == 0)
    {
        // size_t floor_size_over_two = vectorSize >> 1;
        execute_and_measure(heap, &Heap::max_heapify, "max_heapify", argI);
        heap.print_to_output_file(outputFile, vectorSize);
    }
    else if (strcmp(function.c_str(), "build_max_heap") == 0)
    {
        execute_and_measure(heap, &Heap::build_max_heap, "build_max_heap");
        heap.print_to_output_file(outputFile, vectorSize);
    }
    else if (strcmp(function.c_str(), "heapsort") == 0)
    {
        switch (argD)
        {
        case 2:
            execute_and_measure(heap, &Heap::heapsort, "heapsort");
            break;
        default:
            execute_and_measure(heap, &Heap::dary_heapsort, "heapsort");
            break;
        }
        heap.print_to_output_file(outputFile, vectorSize);
    }
    else if (strcmp(function.c_str(), "max_heap_insert") == 0)
    {
        execute_and_measure(heap, &Heap::build_max_heap, "build_max_heap");
        execute_and_measure(heap, &Heap::max_heap_insert, "max_heap_insert", argK);
        heap.print_to_output_file(outputFile, vectorSize);
    }
    else if (strcmp(function.c_str(), "heap_extract_max") == 0)
    {
        execute_and_measure(heap, &Heap::build_max_heap, "build_max_heap");
        execute_measure_print(outputFile, heap, &Heap::heap_extract_max, "heap_extract_max");
    }
    else if (strcmp(function.c_str(), "heap_increase_key") == 0)
    {
        execute_and_measure(heap, &Heap::build_max_heap, "build_max_heap");
        execute_and_measure(heap, &Heap::heap_increase_key, "heap_increase_key", argI, argK);
        heap.print_to_output_file(outputFile, vectorSize);
    }
    else if (strcmp(function.c_str(), "heap_maximum") == 0)
    {
        execute_and_measure(heap, &Heap::build_max_heap, "build_max_heap");
        execute_measure_print(outputFile, heap, &Heap::heap_maximum, "heap_maximum");
    }
    else if (strcmp(function.c_str(), "dary_calculate_height") == 0)
    {
        execute_and_measure(heap, &Heap::dary_build_max_heap, "dary_build_max_heap");
        execute_measure_print(outputFile, heap, &Heap::dary_calculate_height, "dary_calculate_height");
    }
    else if (strcmp(function.c_str(), "dary_extract_max") == 0)
    {
        execute_and_measure(heap, &Heap::dary_build_max_heap, "dary_build_max_heap");
        execute_measure_print(outputFile, heap, &Heap::dary_extract_max, "dary_extract_max");
    }
    else if (strcmp(function.c_str(), "dary_insert_element") == 0)
    {
        execute_and_measure(heap, &Heap::dary_build_max_heap, "dary_build_max_heap");
        execute_and_measure(heap, &Heap::dary_insert_element, "dary_insert_element", argK);
        heap.print_to_output_file(outputFile, vectorSize);
    }
    else if (strcmp(function.c_str(), "dary_increase_key") == 0)
    {
        execute_and_measure(heap, &Heap::dary_build_max_heap, "dary_build_max_heap");
        execute_and_measure(heap, &Heap::dary_increase_key, "dary_increase_key", argI, argK);
        heap.print_to_output_file(outputFile, vectorSize);
    }
    else
    {
        cerr << "Unknown function: " << function << endl;
        return EXIT_FAILURE;
    }

    outputFile.close();

    return EXIT_SUCCESS;
}

// Sorting helper functions
inline void swap_elements(City &c1, City &c2)
{
    City temp = c1; // hold c1 in a temporary variable
    c1 = c2;
    c2 = temp; // complete the swap
}

inline size_t dary_parent(size_t i, unsigned int d)
{
    return floor((i - 2) / d + 1);
}

inline size_t dary_child(size_t i, unsigned int d, unsigned int k)
{
    return d * (i - 1) + k + 1;
}

inline size_t parent(size_t i)
{
    return i >> 1;
}

inline size_t left(size_t i)
{
    return i << 1;
}

inline size_t right(size_t i)
{
    return (i << 1) + 1;
}

// Command line argument handler functions
long long int extract_number_from_arg(const char *arg)
{
    return stoll(++arg); // discard first character which is either d or i, we only care about the number
}

City extract_city_info_from_arg(const char *arg)
{
    string argString(arg);
    size_t underscoreIndex = argString.find("_");
    if (underscoreIndex != string::npos)
    {
        stringstream stream(arg);
        string cityInfo;
        vector<string> cityInfoVector;

        while (getline(stream, cityInfo, '_'))
        {
            cityInfoVector.push_back(cityInfo);
        }

        City city = {cityInfoVector[1], stoll(cityInfoVector[2])};
        return city;
    }
    else
    {
        return {"NO_CITY_NAME", stoll(arg++)};
    }
}

void display_wrong_file_extension_message()
{
    cerr << "Files for dataset and output should have the extension '.csv'." << endl;
    cla_help();
}

void display_wrong_usage_message(int argc, const char **argv)
{
    switch (argc)
    {
    case 1:
        cerr << "Error: You need to specify commands before moving on." << endl;
        break;
    case 2:
        cerr << "Error: Unknown argument: " << argv[1] << "." << endl;
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
                cerr << "." << endl;
                cla_help();
            }
        }
    }
}

template <typename Func, typename... Args>
void execute_and_measure(Heap &heap, Func func, const string &functionName, Args... args)
// change the return type and return value of this so that it matches that of the function
{
    auto start = chrono::high_resolution_clock::now();

    (heap.*func)(args...);

    auto end = chrono::high_resolution_clock::now();
    auto timeElapsed = chrono::duration_cast<chrono::nanoseconds>(end - start);

    display_time_elapsed(timeElapsed.count(), functionName); // might not stay this way
}

template <typename Func, typename... Args>
void execute_measure_print(ofstream &outputFile, Heap &heap, Func func, const string &functionName, Args... args)
// change the return type and return value of this so that it matches that of the function
{
    auto start = chrono::high_resolution_clock::now();

    auto result = (heap.*func)(args...);

    auto end = chrono::high_resolution_clock::now();
    auto timeElapsed = chrono::duration_cast<chrono::nanoseconds>(end - start);

    display_time_elapsed(timeElapsed.count(), functionName); // might not stay this way

    if (typeid(result) == typeid(City))
    {
        City &cityResult = reinterpret_cast<City &>(result);
        outputFile << cityResult.name << ";" << cityResult.population;
    }
    else if (typeid(result) == typeid(int))
    {
        int intResult = reinterpret_cast<int &>(result);
        outputFile << intResult;
    }
    else
    {
        cerr << "Unknown return type of function: " << functionName << endl;
    }
}

void display_time_elapsed(chrono::_V2::high_resolution_clock::rep time, const string function)
{
    cout << "Time taken by " << function << ": "
         << time << " ns." << endl;
}

void cla_help()
{
    cout << "Usage: ./Heapsort <DATASET-FILE-NAME>.csv <FUNCTION-NAME> <OUTPUT-FILE-NAME>.csv ([d<#>] [i<#>] [k_<cityname>_<population>])\n"
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
         << "  [k_<cityname>_<population>]:  Optional parameter to specify the key value to update an element. Must be used with i\n"
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
