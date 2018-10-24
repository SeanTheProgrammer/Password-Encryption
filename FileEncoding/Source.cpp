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


	//Asking for user input to create specific file name 

	cout << "what would you like the file name to be?(Can include File Extenstion, Default is basic FILE)\n";
	cin >> Filename;

	outputFile.open(Filename, fstream::in | fstream::out | fstream::trunc);

	//Asking user what value they would like to be encoded

	cout << "What would you like to encode?\n";
	cin >> EncodeString;

	encode(EncodeString);
	decode();

	outputFile.close();
	system("pause");
}

void decode()
{
	//Might not have to close and reopen, check later
	outputFile.close();
	outputFile.open(Filename);


	//Use Dynamic Array
	string values[100];

	int n = 0;
	while (!outputFile.eof())//Gets all the values from the file and puts them in the array
	{
		outputFile >> values[n];
		n++;
	}

	for (int b = 0; b < n - 1; b++)
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

void getRandInt(int Value)
{
	outputFile << SEED / Value << " ";
}


//Probably can change to char input for VERY minor memory efficency improvement 
void getRandString(string Value)
{
	char temp = Value[0];
	int ans = SEED / ((int)temp);
	string seed = to_string(ans);

	outputFile << "s" << seed << " ";
}