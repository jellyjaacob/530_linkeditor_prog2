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

using namespace std;

// global variables and changes made here
string ctrl_sect_address = "000000";        // pertains to ESTAB
string ctrl_sect_length;                    // pertains to ESTAB   
string ctrl_sect_address_obj = "000000";    // pertains to exec
string ctrl_sect_length_obj;                // pertains to exec

// Map for converting hexadecimal values to decimal
map<char, int> hex_to_dec()
{
	// Map the values to decimal values
	map<char, int> original_hex { { '0', 0 }, { '1', 1 },
					{ '2', 2 }, { '3', 3 },
					{ '4', 4 }, { '5', 5 },
					{ '6', 6 }, { '7', 7 },
					{ '8', 8 }, { '9', 9 },
					{ 'A', 10 }, { 'B', 11 },
					{ 'C', 12 }, { 'D', 13 },
					{ 'E', 14 }, { 'F', 15 } };

	return original_hex;
}

// Map for converting decimal values to hexadecimal
map<int, char> dec_to_hex()
{
	// Map the values to the
	// hexadecimal values
	map<int, char> original_hex { { 0, '0' }, { 1, '1' },
					{ 2, '2' }, { 3, '3' },
					{ 4, '4' }, { 5, '5' },
					{ 6, '6' }, { 7, '7' },
					{ 8, '8' }, { 9, '9' },
					{ 10, 'A' }, { 11, 'B' },
					{ 12, 'C' }, { 13, 'D' },
					{ 14, 'E' }, { 15, 'F' } };

	return original_hex;
}


string hex_addition(string a, string b)
{
	map<char, int> m = hex_to_dec();
	map<int, char> k = dec_to_hex();

	// check which is bigger
	if (a.length() < b.length())
		swap(a, b);

	// Store length of both strings
	int l1 = a.length(), l2 = b.length();

	string ans = "";

	// Initialize carry as zero
	int carry = 0, i, j;

	// Traverse till second string
	// get traversal completely
	for (i = l1 - 1, j = l2 - 1; j >= 0; i--, j--) {

		// Decimal value of element at a[i]
		// Decimal value of element at b[i]
		int sum = m[a[i]] + m[b[j]] + carry;

		// Hexadecimal value of sum%16
		// to get addition bit
		int addition_bit = k[sum % 16];

		// Add addition_bit to answer
		ans.push_back(addition_bit);

		// Update carry
		carry = sum / 16;
	}

	// Traverse remaining element
	// of string a
	while (i >= 0) {

		// Decimal value of element
		// at a[i]
		int sum = m[a[i]] + carry;

		// Hexadecimal value of sum%16
		// to get addition bit
		int addition_bit = k[sum % 16];

		// Add addition_bit to answer
		ans.push_back(addition_bit);

		// Update carry
		carry = sum / 16;
		i--;
	}

	// Check if still carry remains
	if (carry) {
		ans.push_back(k[carry]);
	}

	// Reverse the final string
	// for desired output
	reverse(ans.begin(), ans.end());

	// Return the answer
	return ans;
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


void createObjFile(char* argv[]) {

    ifstream listingFile;
    ofstream execObjFile;

    listingFile.open(argv[2]);

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
    execObjFile.open(ctrl_sect_name + ".obj");

    // finds 1st instance of "EXTDEF"
    string extdefwords;
    vector<string> ext_def_variables;
    stringstream s_stream(extdefwords);

    while (listingFile >> extdefwords){      //This will get all the variables that are extdef into one string word
        if ( extdefwords == "EXTDEF"){
            listingFile >> extdefwords;   // Since we stopped at EXTDET, we need the next word which should be the definitions
            break;
        }
    }

    while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        ext_def_variables.push_back(substr);
    }

    // finds 1st instance of "EXTREF"
    string extrefwords;
    vector<string> ext_ref_variables;
    stringstream s_stream1(extrefwords);


    while (listingFile >> extrefwords){      //This will get all the variables that are extref into one string word
        if ( extdefwords == "EXTREF"){
            listingFile >> extrefwords;   // Since we stopped at EXTREF, we need the next word which should be the references
            break;
        }
    }

    while (s_stream1.good()) {
        string substr;
        getline(s_stream1, substr, ',');
        ext_ref_variables.push_back(substr);
    }


    string lookingfordef;       // now we are looking for the definitions in the code ( what we are currently at in regards to place when we are reading the words
    int num = 0;                // Will verify that the string we converted to number is actually a number
    stringstream ss;
    string prevcontent;
    prevcontent = extdefwords;                    // So considering where we are in the file, this will take the current thing we are reading, once the while loop
    vector<string> addr_ext_def;
    int i = 0;   // index for vector


    // searches listingFile for definitions after "EXTDEF"
    while (listingFile >> lookingfordef) {
        stringstream ss;
        ss << prevcontent;                  // so first we push our prev word to ss to convert to a number
        ss >> num;                          // then return that number into num
                                            // keep in mind that if the word we converted to a number is not a number then we will have 0 in "num"
        if (num != 0 && lookingfordef == ext_def_variables.at(i)) {
            addr_ext_def.push_back(prevcontent);
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

    ss << lastline;            // Put our last line into this stream
    ss >> temp;                // This will put the very first word of the string into "length"

    length = hex_addition(temp,three);

    // re-open listing file -----------------------------------------------------------------------------
    
    ifstream opcode;
    stringstream ss;
    opcode.open(argv[2]);

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
    ss <<line;
    while(ss >> word){
        }
    opcode_nums.push_back(word);

    while(getline(opcode, line)){

    stringstream ss;
    ss << line;

        while(ss >> word){
         counter = counter +1;
            //cout << word.size() << endl;
        }
        if(counter > 3 && word.size() >=6){
            opcode_nums.push_back(word);
        }
        counter = 0;
    }

    for (int p = 0; p < opcode_nums.size() ; p++){
        cout << opcode_nums.at(p) << endl;
    }

    // printing to execObjFile --------------------------------------------------------------------------

    // Format = H + ctrl sect + location + length
    execObjFile << "H" << ctrl_sect_name << ctrl_sect_address_obj << ctrl_sect_length << endl;

    // EXTDEF = D + name + address 
    for (int i = 0; i < ext_def_variables.max_size(); i++) {
        execObjFile << "D " << ext_def_variables.at(i) << " " << addr_ext_def.at(i) << " ";
    }

    // EXTREF = R + name
    for (int i = 0; i < ext_ref_variables.max_size(); i++) {
        execObjFile << "D " << ext_ref_variables.at(i) << " ";
    }

}


int main (int argc, char* argv[]) {

    createObjFile(argv);
    estabFormat(argv, argc);

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



    // need to check for inside the file to see if the contents are correct

}



void readListingFile() {

    // read listing file
    // implementation: search the file for the first instance of the location of 0000, after finding that find the word following
    // it and instantiate it as the ctrl_sect name
    // ifstream ctrl_sect()


}


//------------------------------------------------------------------------------------------------





