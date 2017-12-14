#include <iostream>
#include <sstream>
#include <fstream>
#include "DoubleHT.h"
#include "LineHT.h"
#include "ChainHT.h"


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
    std::string buffer1((std::istreambuf_iterator<char>(firstFile)), std::istreambuf_iterator<char>());
    std::string buffer2((std::istreambuf_iterator<char>(secondFile)), std::istreambuf_iterator<char>());
    firstFile.close();
    secondFile.close();

    return (buffer1 == buffer2);
}


int main() {

    std::string line;
    std::ifstream fileIn("/Users/Vipolion/Documents/ALG/HashMaps/in.txt");
    std::ofstream fileOut("/Users/Vipolion/Documents/ALG/HashMaps/out.txt");
    std::ifstream fileCorrect("/Users/Vipolion/Documents/ALG/HashMaps/true.txt");


    d_hash_table DoubleH(11);
    l_hash_table LineH(11);
    c_hash_table ChainH(11);

    fileOut << std::endl << "//////////////////----Double_Hash_Table-----//////////////////" << std::endl<< std::endl;

    std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
    start = std::chrono::high_resolution_clock::now();

    while (getline(fileIn, line)) {

        if (line.find("delete") == 0) {

            if (!DoubleH.remove(FindValue(line))) {

                fileOut << "error1" << std::endl;

            }

        }

        if (line.find("print") == 0) {

            fileOut << "structure: ";
            DoubleH.print(fileOut);
            fileOut << std::endl;

        }

        if (line.find("add") == 0) {

            DoubleH.add(FindValue(line));

        }

        if (line.find("search") == 0) {

            if (!DoubleH.has(FindValue(line))) {

                fileOut << FindValue(line) << " hasn't found" << std::endl;

            } else {

                fileOut << FindValue(line) << " has found" << std::endl;

            }
        }

//        if (line == "min") {
//            fileOut << DoubleH.Min() << std::endl;
//        }
//        if (line == "max") {
//            fileOut << DoubleH.Max() << std::endl;
//        }
//        if (line == " ") {
//            fileOut << "error" << std::endl;
//        }
        }


        stop = std::chrono::high_resolution_clock::now();
        std::cout << "Double_HT runtime = "
                  << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;

        fileIn.close();
        fileIn.open("/Users/Vipolion/Documents/ALG/HashMaps/in.txt");

        fileOut << std::endl << "//////////////////----Line_Hash_Table-----//////////////////" << std::endl<< std::endl;

        start = std::chrono::high_resolution_clock::now();

        while (getline(fileIn, line)) {

            if (line.find("delete") == 0) {

                if (!LineH.remove(FindValue(line))) {

                    fileOut << "error1" << std::endl;

                }

            }

            if (line.find("print") == 0) {

                fileOut << "structure: ";
                LineH.print(fileOut);
                fileOut << std::endl;

            }

            if (line.find("add") == 0) {

                LineH.add(FindValue(line));

            }

            if (line.find("search") == 0) {

                if (!LineH.has(FindValue(line))) {

                    fileOut << FindValue(line) << " hasn't found" << std::endl;

                } else {

                    fileOut << FindValue(line) << " has found" << std::endl;

                }
            }

//        if (line == "min") {
//            fileOut << DoubleH.Min() << std::endl;
//        }
//        if (line == "max") {
//            fileOut << DoubleH.Max() << std::endl;
//        }
//        if (line == " ") {
//            fileOut << "error" << std::endl;

//        }
            }


            stop = std::chrono::high_resolution_clock::now();
            std::cout << "Line_HT runtime = "
                      << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;

            fileIn.close();
            fileIn.open("/Users/Vipolion/Documents/ALG/HashMaps/in.txt");

            fileOut << std::endl << "//////////////////----Chain_Hash_Table-----//////////////////" << std::endl<< std::endl;

            start = std::chrono::high_resolution_clock::now();

            while (getline(fileIn, line)) {

                if (line.find("delete") == 0) {

                    if (!ChainH.remove(FindValue(line))) {

                        fileOut << "error1" << std::endl;

                    }

                }

                if (line.find("print") == 0) {

                    fileOut << "structure: ";
                    ChainH.print(fileOut);
                    fileOut << std::endl;

                }

                if (line.find("add") == 0) {

                    ChainH.add(FindValue(line));

                }

                if (line.find("search") == 0) {

                    if (!ChainH.has(FindValue(line))) {

                        fileOut << FindValue(line) << " hasn't found" << std::endl;

                    } else {

                        fileOut << FindValue(line) << " has found" << std::endl;
                    }

                }
//        if (line == "min") {
//            fileOut << DoubleH.Min() << std::endl;
//        }
//        if (line == "max") {
//            fileOut << DoubleH.Max() << std::endl;
//        }
//        if (line == " ") {
//            fileOut << "error" << std::endl;
//        }
            }


            stop = std::chrono::high_resolution_clock::now();
            std::cout << "Chain_HT runtime = " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;


            fileIn.close();
            fileOut.close();


            if (FileIsEqual("/Users/Vipolion/Documents/ALG/HashMaps/out.txt",
                            "/Users/Vipolion/Documents/ALG/HashMaps/true.txt")) {

                std::cout << std::endl << "Correct";
            } else {

                std::cout << std::endl << "Not correct";

            }

            fileCorrect.close();

        }


