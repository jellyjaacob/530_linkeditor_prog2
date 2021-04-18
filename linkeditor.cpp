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

// global variables
string ctrl_sect;

string address = "0000";



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



// methods to be called inside main
void estabFormat(char** argv, int argc) {




    ifstream listingFile;      // Open the listing file
    ofstream ESTAB;            // Open a Estab to write in

    ESTAB.open("Estab.st");        //Starts an ESTAB file



    //===============================================================================================================================================================


    for (int t = 2; t < argc; t++){

    string content;        // Save the word we are reading in this variable

    string prevcontent;    //Will hold the previous word

    string titleblock;

    string extdefwords;

    vector<string> separated;

    vector<string> addressofseparated;


    listingFile.open(argv[t]);        // argv[t] takes in the .sl file



    // This will get the title of block *****************************************************************************

    while (listingFile >> titleblock){           // This will go through the words untill it finds 0000 and then will print the next word which should be put
        if ( titleblock == "0000") {             // into "titleblock"
            listingFile >> titleblock;
            break;
        }
    }
    //***********************************************************************************************************
    // titleblock




    // This will get the extdef  **********************************************************************************

    while (listingFile >> extdefwords){      //This will get all the variables that are extdef into one string word
        if ( extdefwords == "EXTDEF"){
            listingFile >> extdefwords;   // Since we stopped at EXTDET, we need the next word which should be the definitions
            break;
        }
    }
    // *****************************************************************************************************************
    // extdefwords


    // This will separate the extdef found in previous loop into a vector each in their own cell  ************************

    stringstream s_stream(extdefwords);

    while(s_stream.good()){          // Will split the definitions into their own cells in a vector (In order)     vector "separated"
        string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        separated.push_back(substr);
    }
    //*******************************************************************************************************************
    // separated




    // Now we want to get the address of the external definitions ****************************************************************************

    string lookingfordef;      // now we are looking for the definitions in the code ( what we are currently at in regards to place when we are reading the words

    int num = 0;       // Will verify that the string we converted to number is actually a number

    stringstream ss;

    prevcontent = extdefwords;                    // So considering where we are in the file, this will take the current thing we are reading, once the while loop
                                                  // we will be reading the next thing
    int i = 0;   // index for vector



    string added;


    while(listingFile >> lookingfordef){
        stringstream ss;

        ss << prevcontent;             // so first we push our prev word to ss to convert to a number
        ss >> num;                // then return that number into num
                                // keep in mind that if the word we converted to a number is not a number then we will have 0 in "num"



        if (num != 0     &&  lookingfordef == separated.at(i)             ){


            added = hex_addition(prevcontent, address );

            addressofseparated.push_back(added);


            // HERE I WILL NEED TO ADD ADDRESS TO THE THING I AM PUSHING INTO ADDRESSOFSEPARAETED


            i = i +1;


            num = 0;

            if(separated.size() == i ){
                break;
            }
        }

        prevcontent = lookingfordef;



    }
    //**************************************************************************************************************************************************
    // addressofseparated




    // This will take in the first word of the last line which is the length of block ******************************************************************************
    string lastline;
    string length;
    string temp;      //hold length before +3
    string three = "0003";

    while(getline(listingFile, lastline)){       // at the end of this loop we have the last line in "lastline"
     }

    ss << lastline;           // Put our last line into this stream


    ss >>  temp;        // This will put the very first word of the string into "length"

    length = hex_addition(temp,three);


    // This should be the length of our block
    // *******************************************************************************************************************************************************
    // length    (length)



    // FINALLY WE ARE FORMATTING IT OUT INTO THE ESTAB ********************************************************************************************************
    ESTAB << setprecision(1) << fixed;

    ESTAB <<   titleblock << "\t\t" << setfill('0') << setw(6)   << address << "\t" << setfill('0') << setw(6)   << length<<endl;


    for(int j = 0; j<addressofseparated.size(); j++) {    //print all splitted strings

        ESTAB << "\t"<< separated.at(j) << "\t" << setfill('0')   <<setw(6) <<addressofseparated.at(j) <<endl;
    }

    //*******************************************************************************************************************************************************

    address = length ;

    separated.clear();

    addressofseparated.clear();

    //----------------------------------------------------------------------------------------------------------------------------------------------

    listingFile.close();   // Close the file we are reading so we can open the next one


}
    ESTAB.close();        // Once we are done using the estab file we created, close it
 //==================================================================================================================================================================


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

    while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        ext_def_variables.push_back(substr);
    }
    for (int i = 0; i < ext_def_variables.size(); i++) {    //print all splitted strings
        cout << ext_def_variables.at(i) << endl;
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

    string lastLine, temp;
    string three = "03";

    while (getline(listingFile, lastLine)) {
    }
    ss << lastLine;
    ss >> temp;

    ctrl_sect_address = hex_addition(ctrl_sect_address, "actual location");
    ctrl_sect_length = hex_addition(temp, three);


    // Format = H + ctrl sect + location + length
    execObjFile << "H" << ctrl_sect_name << ctrl_sect_address << ctrl_sect_length << endl;

    // EXTDEF = D + name + address 
    for (int i = 0; i < ext_def_variables.max_size(); i++) {
        execObjFile << "D " << ext_def_variables.at(i) << " " << addr_ext_def.at(i) << " ";
    }

    // EXTREF = R + name



}




int main (int argc, char* argv[]) {

    // Move this portion to estabFormate method
    //-------------------------------------------------------------------------------------------------------------------------------------------------------








    estabFormat(argv, argc);









    // test if there are 2+ arguments, led <filename>.sl
    if (argc <1 ) {
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





