#include<iostream>
#include<string>
#include<fstream>
#include<time.h>
#include<fstream>

//Sleeping Stuff 
#include <chrono>
#include <thread>

using namespace std;

void decode();
void decodeString(string);
void decodeInt(int);

void getRandInt(int);
void getRandString(string);
void encode(string);

fstream outputFile;
ofstream SeedFile;

int SEED = time(NULL);

//Current Known Issues
//Can only take up to 100 char input (use dynamic arrays maybe)


//TODO make these parameters in the functions 
string EncodeString;
string Filename;

int main()
{
	//Saving the seed
	SeedFile.open("Seed.txt");
	srand(SEED);
	SeedFile << SEED;
	SeedFile.close();
	string choice;


	//encode a string of text
	cout << "Would you like to encode some text? (y/n)\n";
	getline(cin, choice);
	if (choice.at(0) == 'y')
	{
		cout << "What would you like the file to be named? (include file extension)\n";
		getline(cin, Filename);
		outputFile.open(Filename, fstream::in | fstream::out | fstream::trunc);

		cout << "What would you like to encode?\n";
		getline(cin, EncodeString);//sends entire line to encode string, causes overflow
		//Potential fix
		//take the encoded string and split into a bunch of seperate strings and then send those individually into encode and put spaces between them all
		//example string "Something cool to encode"

		//-----------------TEST-----------------

		//find out where each of the spaces are
		//create substrings between all of them
		//if there is no right bound that is the last word in the string

		int words = 0;
		for (int n = 0; n < EncodeString.length(); n++)
		{
			if (EncodeString.at(n) == ' ')words++;
		}

		cout << words << " is the number of spaced \n";

		//-----------------TEST-----------------

		encode(EncodeString);
		
		choice = "";
		outputFile.close();
	}

	//Decoding a specific file
	cout << "Would you like to decode a string from a file? (y/n)\n";
	getline(cin, choice);
	if(choice.at(0)=='y')
	{
		cout << "What file would you like to decode?\n";
		getline(cin, Filename);

		outputFile.open(Filename, fstream::in | fstream::out);//| fstream::trunc <- overwrites the file

		decode();
		outputFile.close();
	}

	//outputFile.close();
	system("pause");
}

void decode()
{
	//Might not have to close and reopen, check later
	outputFile.close();
	outputFile.open(Filename, fstream::in);
	cout << "file is open\n";

	//Use Dynamic Array
	string values[100];

	int n = 0;

	while ( outputFile >> values[n])//Gets all the values from the file and puts them in the array
	{
		n++;
	}


	for (int b = 0; b < n; b++)
	{
		if (values[b].at(0) == 's')//checks if the value should be a string
		{
			decodeString(values[b].substr(1));
		}

		else
		{
			decodeInt(stoi(values[b], nullptr, 10));
		}
	}
}

void decodeString(string value)
{
	//Decodes the value letter by letter
	char  ans = (SEED / stoi(value, nullptr, 10));//gets the char value of the encryted answer
	cout << ans;
}

void decodeInt(int value)
{
	value = SEED / value; // Divides the given seed with the value of the encrypted number to find the original value
	cout << value;
}

//Stack overflow called by massive recursion
//Look into not doing it recursivly
// Also look into doing it word by word maybe
void encode(string value)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));//makes me happy because it looks cool (remove for faster execution)
	if (value.size() == 0)
	{
		return;
	}
	try //Try statement used as an if(Value[0] isDigit) .... else isChar()
	{
		if (stoi(value.substr(0, 1), nullptr, 10) >= 0)
		{
			getRandInt(stoi(value.substr(0, 1), nullptr, 10));
			encode(value.substr(1));
		}
	}
	catch (...)
	{
		cout << "Outputting to the file\n";
		getRandString(value.substr(0, 1));
		encode(value.substr(1));
	}

}

//Problem with 0 sent into value read from input
void getRandInt(int Value)
{
	if(Value != 0) outputFile << SEED / Value << " ";
}


//Probably can change to char input for VERY minor memory efficency improvement 
void getRandString(string Value)
{
	char temp = Value[0];
	int ans = SEED / ((int)temp);
	string seed = to_string(ans);

	outputFile << "s" << seed << " ";
}