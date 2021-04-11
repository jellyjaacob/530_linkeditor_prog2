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
void estabFormat(char* argv[]) {

    string content;        // Save the word we are reading in this variable

    cout << argv[2]<< '\n';    // checking to see what the file is named
    cout << " " << endl;


    ifstream listingFile;      // Open the listing file
    ofstream ESTAB;            // Open a Estab to write in

    listingFile.open(argv[2]);
    ESTAB.open("Estab.st");
    }

    ESTAB << "It worked baby" <<  endl;       //We write into a file named Estab.st

}

void printEstab() {

}

