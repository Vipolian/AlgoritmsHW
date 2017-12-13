#include <iostream>
#include "AVLTree.h"

#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include <ctime>
#include <chrono>
#include "SkipList.h"


int FindValue(const std::string &str) {
    std::istringstream iss(str);
    std::string tmp;
    iss >> tmp;
    tmp.clear();
    iss >> tmp;
    int value = atoi(tmp.c_str());
    return value;
}

bool FileIsEqual(const std::string &firstFileName, const std::string &secondFileName) {
    std::ifstream firstFile(firstFileName), secondFile(secondFileName);
    assert(firstFile);
    assert(secondFile);

    std::string buffer1((std::istreambuf_iterator<char>(firstFile)), std::istreambuf_iterator<char>());
    std::string buffer2((std::istreambuf_iterator<char>(secondFile)), std::istreambuf_iterator<char>());
    firstFile.close();
    secondFile.close();

    return (buffer1 == buffer2);
}

int main() {

    std::string line;
    std::ifstream fileIn("/Users/Vipolion/Documents/ALG/AVL_Skip/in.txt");
    assert(fileIn);
    std::ofstream fileOut("/Users/Vipolion/Documents/ALG/AVL_Skip/out.txt");
    assert(fileOut);
    std::ifstream filecorrect("/Users/Vipolion/Documents/ALG/AVL_Skip/true.txt");
    assert(fileIn);


    
    CAVLTree avlTree;


    fileIn.clear();
    fileIn.seekg(0);


    std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
    start = std::chrono::high_resolution_clock::now();

    while (getline(fileIn, line)) {
        if (line.find("delete") == 0) {
            if (!avlTree.Remove(FindValue(line))) {
                fileOut << "error1" << std::endl;
            }

        }
        if (line.find("print") == 0) {
            avlTree.Print(fileOut);
            fileOut << std::endl;
        }
        if (line.find("add") == 0) {
//
            avlTree.Add(FindValue(line));
//
        }
        if (line.find("search") == 0) {

            if (!avlTree.Has(FindValue(line))) {
                fileOut << "false" << std::endl;
            }

//
        }
        if (line == "min") {
            fileOut << avlTree.Min() << std::endl;
        }
        if (line == "max") {
            fileOut << avlTree.Max() << std::endl;
        }
        if (line == " ") {
            fileOut << "error" << std::endl;
        }
    }
    stop = std::chrono::high_resolution_clock::now();
    std::cout << "runtime = " << std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() << std::endl;

    fileIn.close();
    fileOut.close();

    if (FileIsEqual("/Users/Vipolion/Documents/ALG/AVL_Skip/out.txt", "/Users/Vipolion/Documents/ALG/AVL_Skip/true.txt")) {
        std::cout << "Correct" << std::endl;
    } else {
        std::cout << "Not correct" << std::endl;
    }
 }}
