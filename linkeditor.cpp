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
    ESTAB << ctrl_sect_name << "\t" << "\t" << "000000" << endl;  // need to include address
    for (int j=0;j<addressofseparated.size();j++) {
        ESTAB << "\t" << separated.at(j) << "\t" << "00" << addressofseparated.at(j) << endl;
    }

}
/*
string convertDecimal(string x) {

    // convert hex to decimal

    vector<string> hex_values;

    // 4 digits, ex: 0023, read 0 = 0, then 0 = 0, 2 = 32, 3 = 3, thus 0023 = 35 in binary
    
    for (int i = 4; i > 0; i--) {
        hex_values.at(i) = x[i];
    }

    for (int j = 0; j < hex_values.max_size(); j++) {
        // hex_values[j] = convert to binary
        switch (hex_values.at(j)) {
            case 'a':
            case 'A':
                hex_values.at(j) = '10';
                break;
            case 'b':
            case 'B':
                hex_values.at(j) = '11';
                break;
            case 'c':
            case 'C':
                hex_values.at(j) = '12';
                break;
            case 'd':
            case 'D':
                hex_values.at(j) = '13';
                break;
            case 'e':
            case 'E':
                hex_values.at(j) = '14';
                break;
            case 'f':
            case 'F':
                hex_values.at(j) = '15';
                break;
        }
    }

    vector<int> binary_values;

    for (int k = 0; k < hex_values.max_size(); k++ {
        binary_values.at(k) = hex_values.at(k);         // convert char to int
    }

    // convert the hex into binary values
    int power = 3;
    int hex_power = 16;

    for (int f = 0; f < binary_values.max_size(); f++) {
        while (power != 0) {
            hex_power *= power;
            --power;
        }
        binary_values.at(f) *= hex_power;
    }

    int new_x = 0;

    for (int p = 0; p < binary_values.max_size(); p++) {
        new_x += binary_values.at(p);
    }
    return new_x;
} */


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




