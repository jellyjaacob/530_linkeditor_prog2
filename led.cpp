#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <istream>
#include <string>
#include <map>
#include <exception>
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

// global variables and changes made here
string ctrl_sect_address = "000000";        // pertains to ESTAB
string ctrl_sect_length;                    // pertains to ESTAB
string ctrl_sect_address_obj = "000000";    // pertains to exec
string ctrl_sect_length_obj;                // pertains to exec



string hexConvert (int a) {

    stringstream ss9;
    string convertedHex;

    ss9 << std::hex << a;
    ss9 >> convertedHex;
    ss9.clear();
    std::transform(convertedHex.begin(), convertedHex.end(),convertedHex.begin(), ::toupper);
    return convertedHex;

}

int decimalConvert(string ko){
    stringstream ss8;

    int convertedDecimal;

    ss8 << std::hex << ko;
    ss8 >> convertedDecimal;
    ss8.clear();
    return convertedDecimal;
}


int addDecimal(int a, int b){
    int added;

    added = a + b;

    return added;
}


string hex_addition(string a, string b){
    string addedHex;
    int addedDec;
    int c;
    int d;

    c = decimalConvert(a);
    d = decimalConvert(b);

    addedDec = c+d;

    addedHex = hexConvert(addedDec);

    return addedHex;

}



void estabFormat(char** argv, int argc) {

    ifstream listingFile;      // Open the listing file
    ofstream ESTAB;            // Open a Estab to write in

    ESTAB.open("Estab.st");        //Starts an ESTAB file

    for (int t = 2; t < argc; t++) {

        string content;        // Save the word we are reading in this variable
        string prevcontent;    // Will hold the previous word
        string titleblock;     // holds the control section
        string extdefwords;    // holds the EXTDEF

        vector<string> separated;           // vector to hold EXTDEF words
        vector<string> addressofseparated;  // vector to hold EXTDEF addresses


        listingFile.open(argv[t]);        // argv[t] takes in the .sl file


        while (listingFile >> titleblock){           // This will go through the words untill it finds 0000 and then
            if ( titleblock == "0000") {             // will print the next word, control section put into "titleblock"
                listingFile >> titleblock;
                break;
            }
        }

        // This will get the EXTDEF
        while (listingFile >> extdefwords){      // This will get all the variables that are extdef into one string word
            if ( extdefwords == "EXTDEF"){
                listingFile >> extdefwords;   // Since we stopped at EXTDEF, we need the next word which should be the clusterered definitions
                break;
            }
        }

        // This will separate the extdef found in previous loop into a vector each in their own cell
        stringstream s_stream(extdefwords);

        while(s_stream.good()){          // Will split the definitions into their own cells in a vector (In order) vector "separated"
            string substr;
            getline(s_stream, substr, ','); //get first string delimited by comma
            separated.push_back(substr);
        }

        string lookingfordef;           // now we are looking for the definitions in the code
        int num = 0;                    // Will verify that the string we converted to number is actually a number
        stringstream ss;
        prevcontent = extdefwords;      // So considering where we are in the file, this will take the current thing we are reading, once the while loop
                                        // we will be reading the next thing
        int i = 0;                      // index for vector
        string added;

        while(listingFile >> lookingfordef){
            stringstream ss;

            ss << prevcontent;      // so first we push our prev word to ss to convert to a number
            ss >> num;              // then return that number into num
                                    // keep in mind that if the word we converted to a number is not a number then we will have 0 in "num"


            if (num != 0 && lookingfordef == separated.at(i) ){

                added = hex_addition(prevcontent, ctrl_sect_address);
                addressofseparated.push_back(added);
                i = i +1;
                num = 0;
                if(separated.size() == i){
                    break;
                }
            }
            prevcontent = lookingfordef;
        }

        // This will take in the first word of the last line which is the length of block
        string lastline;
        string length;
        string temp;                // hold length before +3
        string three = "0003";

        while(getline(listingFile, lastline)){       // at the end of this loop we have the last line in "lastline"
        }

        ss << lastline;            // Put our last line into this stream
        ss >> temp;                // This will put the very first word of the string into "length"

        length = hex_addition(temp,three);


        // FINALLY WE ARE FORMATTING IT OUT INTO THE ESTAB
        ESTAB << titleblock << "\t\t" << setfill('0') << setw(6) << ctrl_sect_address << "\t" << setfill('0') << setw(6)  << length << endl;

        for (int j = 0; j < addressofseparated.size(); j++) {    // print all splitted strings
            ESTAB << "\t"<< separated.at(j) << "\t" << setfill('0')  << setw(6) << addressofseparated.at(j) << endl;
        }

        ctrl_sect_address = length;     // updates the control section to the new length
        separated.clear();              // resets the EXTDEF
        addressofseparated.clear();     // resets the EXTDEF addresses

        listingFile.close();   // Close the file we are reading so we can open the next one
    }

    ESTAB.close();        // Once we are done using the estab file we created, close it
}


void createObjFile(char* argv[], int argc) {

    ifstream listingFile;
    ofstream execObjFile;

    for( int j= 2; j < argc;  j++  ){

    listingFile.open(argv[j]);

    string ctrl_sect_name;
    string sectionFinder;

    // finds 1st instance of 0000, next string = ctrl sect
    while (listingFile >> sectionFinder) {
        if (sectionFinder == "0000") {
            listingFile >> sectionFinder;
            ctrl_sect_name = sectionFinder;
            break;
        }
    }

    // names the executable object file
    execObjFile.open(ctrl_sect_name + ".obj");   // ?????????????????????????????????????????????????????????????????? change back to .obj

    // finds 1st instance of "EXTDEF"
    string extdefwords;
    vector<string> ext_def_variables;


    while (listingFile >> extdefwords){      //This will get all the variables that are extdef into one string word
        if ( extdefwords == "EXTDEF"){
            listingFile >> extdefwords;   // Since we stopped at EXTDET, we need the next word which should be the definitions
            break;
        }
    }

    stringstream s_stream(extdefwords);

    while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, ',');
        ext_def_variables.push_back(substr);
    }


    // finds 1st instance of "EXTREF"
    string extrefwords;
    vector<string> ext_ref_variables;



    while (listingFile >> extrefwords){      //This will get all the variables that are extref into one string word
        if ( extrefwords == "EXTREF"){
            listingFile >> extrefwords;   // Since we stopped at EXTREF, we need the next word which should be the references
            break;
        }
    }

    stringstream s_stream1(extrefwords);


    while (s_stream1.good()) {
        string substr;
        getline(s_stream1, substr, ',');
        ext_ref_variables.push_back(substr);
    }




    string lookingfordef;       // now we are looking for the definitions in the code ( what we are currently at in regards to place when we are reading the words
    int num = 0;                // Will verify that the string we converted to number is actually a number
    stringstream ss;
    string prevcontent;
    string added;
    prevcontent = extdefwords;                    // So considering where we are in the file, this will take the current thing we are reading, once the while loop
    vector<string> addr_ext_def;
    int i = 0;   // index for vector


    // searches listingFile for definitions after "EXTDEF"
    while (listingFile >> lookingfordef) {
        stringstream ss5;
        ss5 << prevcontent;                  // so first we push our prev word to ss to convert to a number
        ss5 >> num;                          // then return that number into num
                                            // keep in mind that if the word we converted to a number is not a number then we will have 0 in "num"
        if (num != 0 && lookingfordef == ext_def_variables.at(i)) {

            added = hex_addition(prevcontent, ctrl_sect_address_obj);
            addr_ext_def.push_back(added);
            i++;
            num = 0;
            if (ext_def_variables.size() == i) {
                break;
            }
        }
        prevcontent = lookingfordef;
    }



    // This will take in the first word of the last line which is the length of block


    string lastline;
    string length;
    string temp;                // hold length before +3
    string three = "0003";

    while(getline(listingFile, lastline)){       // at the end of this loop we have the last line in "lastline"
    }


    ss <<lastline;            // Put our last line into this stream
    ss >> temp;                // This will put the very first word of the string into "length"

    length = hex_addition(temp,three);

    ctrl_sect_length = length;

    listingFile.close();


    // re-open listing file -----------------------------------------------------------------------------


    ifstream opcode;
    stringstream ss2;
    opcode.open(argv[j]);

    string first;
    int counter = 0;

    string line;
    string word;

    vector<string> opcode_nums;

    string theline;


    while(opcode >> first){

        if (first == "FIRST"){
            break;
        }
    }

    getline(opcode, line);
    ss2 <<line;
    while(ss2 >> word){
        }
    opcode_nums.push_back(word);



    string last_address_of_lastline;
    string last_opcode_of_lastline;


    while(getline(opcode, line)){

    stringstream ss;
    ss << line;

        while(ss >> word){
         counter = counter +1;

         if(word == "END"){       // Finds last address and opcode
            stringstream ss6;

            getline(opcode, line); //+++++++++++++++++++++++++++++++ getting last line

            ss6 << line;
            ss6 >> last_address_of_lastline;  // first word of last line(address)
            while(ss6 >>last_opcode_of_lastline ){
                // Finds the last word of the last line (opcode)
            }

            break;
         }                                 // --------------------change here for end
            //cout << word.size() << endl;
        }
        if(counter > 3 && word.size() >=6){
            opcode_nums.push_back(word);
        }
        counter = 0;
    }








/*
    for (int p = 0; p < opcode_nums.size() ; p++){
        cout << opcode_nums.at(p) << endl;
    }
*/


    // printing to execObjFile --------------------------------------------------------------------------

    // Format = H + ctrl sect + location + length
    execObjFile << "H" << ctrl_sect_name << ctrl_sect_address_obj << setfill('0') << setw(6) << ctrl_sect_length << endl;

    // EXTDEF = D + name + address
    execObjFile << "D" ;
    for (int i = 0; i < ext_def_variables.size(); i++) {
        execObjFile  << ext_def_variables.at(i)  << addr_ext_def.at(i)  ;
    }
    execObjFile << endl;


    execObjFile << "R";
    // EXTREF = R + name
    for (int i = 0; i < ext_ref_variables.size(); i++) {
        execObjFile  << ext_ref_variables.at(i) ;
    }
    execObjFile << endl;













    int bits_counter = 0;

    string sizeofcell;

    string opcode_addr = "0000";

    string opcode_line;

    string opcode_line_before_adding;

    string len_code;



    execObjFile << "T" << setfill('0') << setw(6) << opcode_addr ;   //1D and line




    for (int m = 0; m < opcode_nums.size(); m++){

        sizeofcell = opcode_nums.at(m);   // size of the cell

        bits_counter = bits_counter + (sizeofcell.size() / 2) ;   // bits we arew on

        opcode_line = opcode_line + opcode_nums.at(m);        // the line with numbers


        if(bits_counter > 30){


            bits_counter = bits_counter - (sizeofcell.size() / 2);
            //cout << " ( " + opcode_addr + " ) " << endl;


            //cout << " ( " + hex_addition("0000", "001D") + " ) " << endl;


            opcode_addr = hex_addition( hexConvert(bits_counter), opcode_addr);

            //cout << " ( " + hexConvert(bits_counter) + " ) " << endl;
            //cout << " ( " + opcode_addr + " ) " << endl;

            execObjFile << hexConvert(bits_counter) << opcode_line_before_adding  << endl;     // has one opcode less than opcode_line

            execObjFile << "T" << setfill('0') << setw(6) << opcode_addr ;

            opcode_line = opcode_nums.at(m);

            sizeofcell = opcode_nums.at(m);

            bits_counter =  sizeofcell.size() / 2;

        }

        opcode_line_before_adding = opcode_line;      // same thing
      }
      execObjFile << setfill('0')<< setw(2) <<hexConvert(bits_counter)<< opcode_line_before_adding  << endl;



    bits_counter = last_opcode_of_lastline.size() / 2;
    execObjFile << "T" << setfill('0') <<setw(6) << last_address_of_lastline << setfill('0') <<setw(2) << bits_counter << last_opcode_of_lastline <<endl;




    // modification method


    execObjFile << "E" << ctrl_sect_address_obj;

    //ctrl_sect_address_obj = length;
    ext_def_variables.clear();
    addr_ext_def.clear();
    opcode_nums.clear();

    execObjFile.close();  // file we are inputting to
    listingFile.close(); // file we are reading
    opcode.close();
    }

}


int main (int argc, char* argv[]) {


    

    estabFormat(argv, argc);

    createObjFile(argv, argc);


    //estabFormat(argv, argc);

    // test if there are 2+ arguments, led <filename>.sl
    if (argc < 1 ) {
        std::cout << "Program needs to have more than 1 argument and should be called with the command of led <filename>.sl" << endl;
        exit(1);
    }

    // test if it is correct file type
    int fileNum = 1;
    string inputFile = argv[fileNum]; // will hold the inputFile

    // loops through a for loop to check the amount of arguments following led are of <filename>.sl
    for (fileNum; fileNum < argc; fileNum++) {
        int exitPos = inputFile.find_last_of(".");
        if (inputFile.substr(exitPos + 1) != "sl") {
            std::cout << "Type of file is incorrect, we need .sl file \n" << endl;
            exit(1);
        }
    }

}

