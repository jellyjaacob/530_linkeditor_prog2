#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <istream>
#include <string>
#include <map>
#include <exception>


using namespace std;

int main (int argc, int argv[]) {
    
    // first thing to test is the arguments 
    if (argc <= 1) {
        std::cout << "Program needs to have more than 1 argument and should be called with the command of led <filename>.sl" << endl;
        exit(1);
    }

    int fileNum = 1;
    string inputFile = argv[fileNum]; // will hold the inputFile

    for (fileNum = 1; fileNum < argc; i++) {
        int exitPos = inputFile.find_last_of(".");
        if (exitPos.substr(exitPos + 1) != "sl") {
            std::cout << "Type of file is incorrect, we need .sl file" << endl; 
            exit(1);
        }
    }

    // need to check for inside the file to see if the contents are correct 

}