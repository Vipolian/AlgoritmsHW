#include <sstream>
#include <fstream>
#include <chrono>
#include "DoubleHT/DoubleHT.hpp"
#include "LineHT/LineHT.hpp"
#include "ChainTH/ChainHT.hpp"


int FindKey(const std::string &str) {
    std::istringstream iss(str);
    std::string tmp;
    iss >> tmp;
    tmp.clear();
    iss >> tmp;
    int key = atoi(tmp.c_str());
    return key;
}

int FindValue(const std::string &str) {
    std::istringstream iss(str);
    std::string tmp;
    iss >> tmp;
    tmp.clear();
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


-int main(int argc, char *argv[]) {

    std::string line;
    std::ifstream fileIn(argv[1]);
    assert(fileIn);
    std::ofstream fileOut(argv[2]);
    assert(fileOut);


    d_hash_table DoubleH(111);
    l_hash_table LineH(111);
    c_hash_table ChainH(111);

    fileOut << std::endl << "//////////////////----Double_Hash_Table-----//////////////////" << std::endl<< std::endl;

    std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
    start = std::chrono::high_resolution_clock::now();

    while (getline(fileIn, line)) {

        if (line.find("delete") == 0) {

            if (!DoubleH.remove(FindKey(line))) {

                fileOut << "error1" << std::endl;

            }

        }

        if (line.find("print") == 0) {

            fileOut << "structure: ";
            DoubleH.print(fileOut);
            fileOut << std::endl;

        }

        if (line.find("add") == 0) {

            std::pair<int,int> pair;
            pair.first=FindKey(line);
            pair.second=FindValue(line);
            DoubleH.add(pair);

        }

        if (line.find("has") == 0) {

            if (!DoubleH.has(FindKey(line))) {

                fileOut << FindValue(line) << " hasn't found" << std::endl;

            } else {

                fileOut << FindKey(line) << " has found" << std::endl;

            }
        }

        if (line.find("min") == 0) {

            fileOut << DoubleH.Min() << std::endl;

        }

        if (line.find("min") == 0) {

            fileOut << DoubleH.Max() << std::endl;

        }

    }



        stop = std::chrono::high_resolution_clock::now();

        std::cout << "Double_HT runtime = "
                  << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;

    fileIn.clear();
    fileIn.seekg(0);
//    fileOut.clear();
//    fileOut.seekp(0);

        fileOut << std::endl << "//////////////////----Line_Hash_Table-----//////////////////" << std::endl<< std::endl;

        start = std::chrono::high_resolution_clock::now();

        while (getline(fileIn, line)) {

            if (line.find("delete") == 0) {

                if (!LineH.remove(FindKey(line))) {

                    fileOut << "error1" << std::endl;

                }

            }

            if (line.find("print") == 0) {

                fileOut << "structure: ";
                LineH.print(fileOut);
                fileOut << std::endl;

            }

            if (line.find("add") == 0) {

                std::pair<int,int> pair;
                pair.first=FindKey(line);
                pair.second=FindValue(line);
                LineH.add(pair);

            }

            if (line.find("has") == 0) {

                if (!LineH.has(FindKey(line))) {

                    fileOut << FindKey(line) << " hasn't found" << std::endl;

                } else {

                    fileOut << FindKey(line) << " has found" << std::endl;

                }
            }

            if (line.find("min") == 0) {

                fileOut << LineH.Min() << std::endl;

            }

            if (line.find("min") == 0) {

                fileOut << LineH.Max() << std::endl;

            }

   
        }


            stop = std::chrono::high_resolution_clock::now();
            std::cout << "Line_HT runtime = "
                      << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;


    fileIn.clear();
    fileIn.seekg(0);
//    fileOut.clear();
//    fileOut.seekp(0);


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

                    std::pair<int,int> pair;
                    pair.first=FindKey(line);
                    pair.second=FindValue(line);
                    ChainH.add(pair);

                }

                if (line.find("has") == 0) {

                    if (!ChainH.has(FindKey(line))) {

                        fileOut << FindKey(line) << " hasn't found" << std::endl;

                    } else {

                        fileOut << FindKey(line) << " has found" << std::endl;
                    }

                }

                if (line.find("min") == 0) {

                    fileOut << ChainH.Min() << std::endl;

                }

                if (line.find("min") == 0) {

                    fileOut << ChainH.Max() << std::endl;

                }

            }


            stop = std::chrono::high_resolution_clock::now();
            std::cout << "Chain_HT runtime = " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;


            fileIn.close();
            

             if (FileIsEqual(argv[2], argv[3])) {

                 std::cout << "Correct" << std::endl;

                }

                 else {

                    std::cout << "Not correct" << std::endl;
                }

         fileOut.close();

    }


