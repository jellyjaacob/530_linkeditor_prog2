#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <istream>
#include <string>
#include <map>
#include <exception>


using namespace std;

// global variables
string ctrl_sect;


int main (int argc, char* argv[]) {
    
    // format for command line: led first.sl second.sl

    // test if there are 2+ arguments, led <filename>.sl
    if (argc <= 1) {
        std::cout << "Program needs to have more than 1 argument and should be called with the command of led <filename>.sl" << endl;
        exit(1);
    }

    // test if it is correct file type
    int fileNum = 1;
    string inputFile = argv[fileNum]; // will hold the inputFile

    // loops through a for loop to check the amount of arguments following led are of <filename>.sl
    for (fileNum = 1; fileNum < argc; fileNum++) {
        int exitPos = inputFile.find_last_of(".");
        if (inputFile.substr(exitPos + 1) != "sl") {
            std::cout << "Type of file is incorrect, we need .sl file" << endl; 
            exit(1);
        }
    }

    // need to check for inside the file to see if the contents are correct

}

void readListingFile(char* argv[]) {
    
    ifstream listFile(argv[0], ios::in);    // opens file
    string content;

    while(listFile >> content) {
        if(content == "0000") {
            listFile >> content;
            cout << content << endl;    // prints to output
            break;
        }
    }
    



}

void createExecutable() {

    // creates the executable file (object code)

}

// methods to be called inside main
void estabFormat() {

    string ctrl_sect;
    int estab_ctrlsectcount = 0;
    vector <string> estab_ctrlsec;

    for (int i=0;i<estab_ctrlsectcount; i++) {
        estab_ctrlsec[i].insert(ctrl_sect + \t + \t + object code)
    }


    int estab_symbolcount = 0;
    // format the estab

    vector <string> estab_symbol;
    for (int i=0;i< estab_symbolcount; i++) {
        // estab_symbol[i].insert( symbol + \t + location of symbol + \t);
    }

}

void printEstab() {

}

