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
    
    ifstream listFile;    // opens file
    
    // creating ESTAB 
    ofstream ESTAB;            
    listFile.open(argv[2]);
    ESTAB.open("Estab.st");

    string sectionFinder;
    string ctrl_sect_name;
    
    // finds 1st instance of 0000, next string = ctrl sect
    while(listFile >> sectionFinder) {
        if(sectionFinder == "0000") {
            listFile >> sectionFinder;     
            ctrl_sect_name = sectionFinder;   
            break;
        }
    }

    // finds 1st instance of "EXTDEF"
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

    string lookingfordef;       // now we are looking for the definitions in the code ( what we are currently at in regards to place when we are reading the words
    int num = 0;                // Will verify that the string we converted to number is actually a number
    stringstream ss;
    string prevcontent;
    prevcontent = extdefwords;                    // So considering where we are in the file, this will take the current thing we are reading, once the while loop
    vector<string> addressofseparated;
    int i = 0;   // index for vector


    // searches listFile for definitions after "EXTDEF"
    while (listFile >> lookingfordef) {
        stringstream ss;
        ss << prevcontent;                  // so first we push our prev word to ss to convert to a number
        ss >> num;                          // then return that number into num
                                            // keep in mind that if the word we converted to a number is not a number then we will have 0 in "num"
        if (num != 0 && lookingfordef == separated.at(i)) {
            addressofseparated.push_back(prevcontent);
            i++;
            num = 0;
            if (separated.size() == i) {
                break;
            }
        }
        prevcontent = lookingfordef;
    }

    // finding =C'EOF' so that we can find the end of the file and its length
    string look_for_length;
    string end_variable;
    string length_of_ls;

    while (listFile >> look_for_length) {
        
    }

    // formatting ESTAB
    ESTAB << ctrl_sect_name << "\t\t" << "0000" << endl;
    for (int j=0;j<addressofseparated.size();j++) {
        ESTAB << "\t" << separated.at(j) << "\t" << addressofseparated.at(j) << endl;
    }

}

