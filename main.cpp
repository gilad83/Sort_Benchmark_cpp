#include <iostream>
#include <chrono>
#include "SortAlgos.h"
#include <iterator>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>



typedef std::chrono::high_resolution_clock::time_point timeMili;
typedef std::chrono::duration<double,std::milli> timeInDouble;

void sort(std::vector<int> &bubbleVect, std::vector<int> &mergeVect, std::vector<int> &quickRandVect,
          std::vector<int> &quickDeterVect);
bool getFileContent(const std::string& fileName, std::vector<int> &bubbleVect, std::vector<int> &mergeVect,
                    std::vector<int> &quickRandVect, std::vector<int> &quickDeterVect);
bool writeToFile(const std::string& fileName,std::vector<int> &numberSorted);
void runSort(std::vector<int> &sortVect, SortAlgos &sortAlgos, std::vector<std::pair<timeInDouble, std::string>> &times
             , const std::string& sortName);

int main()
{
    // Init vector for each method.
    std::vector<int> bubbleVect,mergeVect,quickRandVect,quickDeterVect;

    // Get the contents of file in a vector
    bool result = getFileContent("input.txt", bubbleVect,mergeVect,quickRandVect,quickDeterVect);
    if(!result) {
        return -1;
    }
    // Sort and print the times.
    sort(bubbleVect, mergeVect, quickRandVect, quickDeterVect);
    if(!writeToFile("output_bubbleSort.txt",bubbleVect)) return -1;
    if(!writeToFile("output_mergeSort.txt",mergeVect)) return -1;
    if(!writeToFile("output_quickSortRandom.txt",quickRandVect)) return -1;
    if(!writeToFile("output_quickSortDeterminisitc.txt",quickDeterVect)) return -1;
    return 0;
}
/**
 * sort : Run the sorting algos.
 *        creates a time stamp before and after sorting with each method,
 *        than prints the fastest method.
 */
void sort(std::vector<int> &bubbleVect, std::vector<int> &mergeVect, std::vector<int> &quickRandVect,
          std::vector<int> &quickDeterVect)
{
    BubbleSort bubbleSort;
    MergeSort mergeSort;
    QuickSort quickSortRandom;
    QuickSort quickSortDeterministic;
    quickSortDeterministic.chooseMethod(1);
    std::vector<std::pair <timeInDouble,std::string>> times;

    timeMili start_time;
    timeMili end_time;
    std::cout << "starting to sort" << "\n";
    runSort(bubbleVect, bubbleSort, times,"Bubble Sort ");
    runSort(mergeVect, mergeSort, times,"Merge Sort ");
    runSort(quickRandVect, quickSortRandom, times,"Quick Sort Random ");
    runSort(quickDeterVect, quickSortDeterministic, times,"Quick Sort Deterministic ");
    // Using simple sort() function to sort
    std::sort(times.begin(), times.end());
    // Printing the sorted vector(after using sort())
    std::cout << "The fastest sort is : "<< times[0].second << "\n"  ;
}

void runSort(std::vector<int> &sortVect, SortAlgos &sortAlgos,
        std::vector<std::pair<timeInDouble, std::string>> &times, const std::string& sortName) {
    std::cout << sortName << ": ";
    timeMili start_time = std::chrono::high_resolution_clock::now();
    sortAlgos.sort(sortVect);
    timeMili end_time = std::chrono::high_resolution_clock::now();
    timeInDouble time_Sort = end_time - start_time;
    times.emplace_back(time_Sort, sortName);
    std::cout <<time_Sort / std::chrono::milliseconds(1) << "ms to run.\n";
}


/**
 * It will iterate through all the lines in file and
 * put them in given vector
 */
bool getFileContent(const std::string& fileName, std::vector<int> &bubbleVect, std::vector<int> &mergeVect,
                    std::vector<int> &quickRandVect, std::vector<int> &quickDeterVect) {
    // Open the File
    std::ifstream in(fileName.c_str());
    std::string::size_type sz;   // alias of size_t

    // Check if object is valid
    if (!in) {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return false;
    }
    std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str)) {
        // Line contains string of length > 0 then save it in vector
        if (str.size() > 0) {
            bubbleVect.push_back(std::stoi(str, &sz));
            mergeVect.push_back(std::stoi(str, &sz));
            quickRandVect.push_back(std::stoi(str, &sz));
            quickDeterVect.push_back(std::stoi(str, &sz));
        }
    }
    //Close The File
    in.close();
    return true;
}

bool writeToFile(const std::string& fileName,std::vector<int> &numberSorted){
    std::ofstream outputFile;
    outputFile.open(fileName);
    if (outputFile.fail()){
        return false;
    }
    std::copy(numberSorted.begin(), numberSorted.end(), std::ostream_iterator<int>(outputFile, "\n"));
    return true;

}