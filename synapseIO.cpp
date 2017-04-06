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
void saveSynapse(double syn0[][NUM_HIDDEN], double syn1[][NUM_HIDDEN], double syn2[][NUM_OUT]){
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
void loadSynapse(double syn0[][NUM_HIDDEN], double syn1[][NUM_HIDDEN], double syn2[][NUM_OUT]){
	ifstream syn0Stream;
	ifstream syn1Stream;
	ifstream syn2Stream;

	string line;
	vector<string> tokens;
	char* tokEnd;

	int i = 0;
	syn0Stream.open(SYN0_FILE);
	while(getline(syn0Stream, line)){
		/* Convert string read in to char* for use in strtod */
		char* cArr = new char[line.length() + 1];
		copy(line.begin(), line.end(), cArr);
		cArr[line.size()] = '\0';
		
		syn0[i][0] = strtod(cArr, &tokEnd);
		
		for (int j = 1; j < NUM_HIDDEN; j++){
			syn0[i][j] = strtod(tokEnd, &tokEnd);
		}

		i++;
	}

	i = 0;
	syn0Stream.close();
	syn1Stream.open(SYN1_FILE);
	while(getline(syn1Stream, line)){
		/* Convert string read in to char* for use in strtod */
		char* cArr = new char[line.length() + 1];
		copy(line.begin(), line.end(), cArr);
		cArr[line.size()] = '\0';
		

		syn1[i][0] = strtod(cArr, &tokEnd);
		
		for (int j = 1; j < NUM_HIDDEN; j++){
			syn1[i][j] = strtod(tokEnd, &tokEnd);
		}

		i++;
	}

	i = 0;
	syn1Stream.close();
	syn2Stream.open(SYN2_FILE);
	while(getline(syn2Stream, line)){
		/* Convert string read in to char* for use in strtod */
		char* cArr = new char[line.length() + 1];
		copy(line.begin(), line.end(), cArr);
		cArr[line.size()] = '\0';
		

		syn2[i][0] = strtod(cArr, &tokEnd);
		
		for (int j = 1; j < NUM_OUT; j++){
			syn2[i][j] = strtod(tokEnd, &tokEnd);
		}

		i++;
	}

	syn2Stream.close();
}