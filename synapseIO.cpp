#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <cstring>

#include "net.h"
#include "synapseIO.h"

using namespace std;

/**
 *	Function that saves the given synapse arrays to a text file
 *	(using space as a separator)
 */
void saveSynapse(double** syn0, double** syn1, double** syn2){
	ofstream syn0Stream;
	ofstream syn1Stream;
	ofstream syn2Stream;

	syn0Stream.open(SYN0_FILE);
	int i, j;

	for (i = 0; i < NUM_IN; i++){
		for (j = 0; j < NUM_HIDDEN - 1; j++){
			syn0Stream << syn0[i][j] << ' ';
		}

		syn0Stream << syn0[i][j] << '\n';
	}

	syn0Stream.close();
	syn1Stream.open(SYN1_FILE);

	for (i = 0; i < NUM_HIDDEN; i++){
		for (j = 0; j < NUM_HIDDEN - 1; j++){
			syn1Stream << syn1[i][j] << ' ';
		}

		syn1Stream << syn1[i][j] << '\n';
	}

	syn1Stream.close();
	syn2Stream.open(SYN2_FILE);

	for (i = 0; i < NUM_HIDDEN; i++){
		for (j = 0; j < NUM_OUT; j++){
			syn2Stream << syn2[i][j] << ' ';
		}

		syn2Stream << syn2[i][j] << '\n';
	}

	syn2Stream.close();

}

/**
 *	Loads the synapses from the file to the arrays passed in
 */
void loadSynapse(double** syn0, double** syn1, double** syn2){
	ifstream syn0Stream;
	ifstream syn1Stream;
	ifstream syn2Stream;

	string line;
	vector<string> tokens;
	char* tokEnd;

	int j = 0;

	syn0Stream.open(SYN0_FILE);
	while(getline(syn0Stream, line)){
		/* Convert string read in to char* for use in strtod */
		char* cArr = new char[line.length() + 1];
		copy(line.begin(), line.end(), cArr);
		cArr[line.size()] = '\n';
		

		syn0[0][j] = strtod(cArr, &tokEnd);
		
		for (int i = 1; i < NUM_HIDDEN; i++){
			syn0[i][j] = strtod(tokEnd, &tokEnd);
		}

		j++;
	}

	syn0Stream.close();
	syn1Stream.open(SYN1_FILE);
	while(getline(syn1Stream, line)){
		/* Convert string read in to char* for use in strtod */
		char* cArr = new char[line.length() + 1];
		copy(line.begin(), line.end(), cArr);
		cArr[line.size()] = '\n';
		

		syn0[0][j] = strtod(cArr, &tokEnd);
		
		for (int i = 1; i < NUM_HIDDEN; i++){
			syn1[i][j] = strtod(tokEnd, &tokEnd);
		}

		j++;
	}

	syn1Stream.close();
	syn2Stream.open(SYN2_FILE);
	while(getline(syn2Stream, line)){
		/* Convert string read in to char* for use in strtod */
		char* cArr = new char[line.length() + 1];
		copy(line.begin(), line.end(), cArr);
		cArr[line.size()] = '\n';
		

		syn0[0][j] = strtod(cArr, &tokEnd);
		
		for (int i = 1; i < NUM_OUT; i++){
			syn2[i][j] = strtod(tokEnd, &tokEnd);
		}

		j++;
	}

	syn2Stream.close();
}