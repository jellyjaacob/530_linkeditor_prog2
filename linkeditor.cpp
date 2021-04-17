#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <istream>
#include <string>
#include <map>
#include <exception>
#include <sstream>

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
}

void readListingFile(char* argv[]) {
    
    ifstream listFile(argv[0], ios::in);    // opens file
    string sectionFinder;
    string ctrl_sect_name;

    while(listFile >> sectionFinder) {
        if(sectionFinder == "0000") {
            listFile >> sectionFinder;        // finds first instance of 0000, the next string after = ctrl sect
            ctrl_sect_name = sectionFinder;   // sets the control section 
            break;
        }
    }

    // find the EXTDEF
    string symbolLoc = "EXTDEF";
    vector <string> symbols;
    string content;                 // placeholder to hold 

    // find the line where string, "EXTDEF" is located, find where in that string EXTDEF is located and take the strings after that
    // and put it into an array or something which will be the Symbols
    
    getline(listFile, content);    // assigns all of listfile into content
    content.find_first_of(symbolLoc);   // content = EXTDEF

    while (listFile >> content) {
        if(content == symbolLoc) {
            listFile >> content;
            symbols.insert(content);    // vector add the content
        }
        if(content == "0000") {     // end of line
            break;
        }
    }

    string extdefwords;
    vector<string> separated;

    stringstream s_stream(extdefwords);

    while(s_stream.good()){
        string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        separated.push_back(substr);
    }
    for(int i = 0; i< separated.size(); i++) {    //print all splitted strings
        cout << separated.at(i) << endl;
    }

    string lookingfordef;      // now we are looking for the definitions in the code ( what we are currently at in regards to place when we are reading the words

    int num = 0;       // Will verify that the string we converted to number is actually a number

    stringstream ss;

    prevcontent = extdefwords;                    // So considering where we are in the file, this will take the current thing we are reading, once the while loop
                                                  // we will be reading the next thing
    int i = 0;   // index for vector

    while (listingFile >> lookingfordef) {
        stringstream ss;
        ss << prevcontent;                  // so first we push our prev word to ss to convert to a number
        ss >> num;                          // then return that number into num
                                            // keep in mind that if the word we converted to a number is not a number then we will have 0 in "num"
        if (num != 0 && lookingfordef == separated.at(i)) {
            addressofseparated.push_back(prevcontent);
            i = i + 1;
            num = 0;
            if (separated.size() == i) {
                break;
            }
        }
        prevcontent = lookingfordef;
    }

    cout << " " << endl;
    cout << " " << endl;
    cout << " " << endl;
    cout << " " << endl;
    cout << " " << endl;
    cout << " " << endl;
    for (int j = 0; j < addressofseparated.size(); j++) {    //print all splitted strings
        cout << addressofseparated.at(j) << endl;
    }


    for (int j = 0; j < addressofseparated.size(); j++) {    //print all splitted strings
        cout << "This is vector that holds the extdef, each in its own cell, this is at index " << j << "   " << separated.at(j) << endl;
        cout << "This is vector that holds the address of extdef, each in its own cell, this is at index " << j << "      " << addressofseparated.at(j) << endl;

    }

    cout << " " << endl;
    cout << " " << endl;
    cout << " " << endl;
    cout << " " << endl;
    cout << " " << endl;
    cout << " " << endl;
    
 
}

void createExecutable() {

    // creates the executable file (object code)

    cout << "H" + ctrl_sect_name + //END OF LISTING FILE;



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

