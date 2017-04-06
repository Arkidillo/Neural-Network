#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <algorithm>

#include "net.h"
#include "synapseIO.h"
#include "caesarTrainer.h"

using namespace std;

/** 
 *	TODO: Save weights to a file (enter 3 to save, 4 to load)
 *	TODO: Multithread?
 */

int NUM_GEN;

/* 0 if in using, 1 if in training */
int userMode;

/* Input/ ouput nodes will be turned on according to the binary value of the ascii value of each letter */
int inputs[NUM_IN] = {0};
int target[NUM_OUT] = {0};

/* syn0 are the edges connecting the input nodes and the hidden layer */
double syn0[NUM_IN][NUM_HIDDEN] = {0};
double hiddenNode1[NUM_HIDDEN] = {0};

/* syn1 are the edges connecting the first and second hidden layers */
double syn1[NUM_HIDDEN][NUM_HIDDEN] = {0};
double hiddenNode2[NUM_HIDDEN] = {0};

/* syn2 are the edges connecting the second hiddenlayer and the output layer */
double syn2[NUM_HIDDEN][NUM_OUT] = {0};

/* The ouputs will be doubles, but will be cast to ints as the output, to get the ascii value */
double outNode[NUM_OUT] = {0};

/* Mask will mast out each bit of the input string to get which bits of the input nodes should be turned on */
char mask;

char plainText[MAX_CHAR] = {0};
char encryptedText[MAX_CHAR] = {0};

char outString[MAX_CHAR] = {0};

int main(){

	srand(time(NULL));	

	/* Initializes the synapses to random values */
	initSyn();

	/* Total loop that will repeatedly ask the user whether they want training or using, so they can train the net, then attempt to use it for another problem */
	while (1){
		
		/* Asks the user what mode they would like to use, training or using */
		userMode = getUserMode();
		switch(userMode){
			case 0:
				initUse();
				mainLoop();
				break;
			case 1:
				initTrain();
				mainLoop();
				break;
			case 2:
				caesarTrainingMode();
				break;
			case 3:
				loadSynapse(syn0, syn1, syn2);
				break;
			case 4:
				saveSynapse(syn0, syn1, syn2);
				break;
		}
	}
	return 0;

}

void mainLoop(){

	/* Loop to repeat for each generation */
	for (int z = 0; z < NUM_GEN; z++){
		/* Main loop that goes through each character at a time. */
		for (int i = 0; i < (int)strlen(encryptedText); i++){
			
			setUpInputs(i);
			calculateOutputs();

			if (userMode == 1){
				backPropagation();
			}
	      
	      	showResult();
		}

    	cout << outString;

		/* If checkResult returns true, it means the output matched the target, and we should exit the loop as training is now completed */
		if(userMode == 1){
			if(checkResult(z)){
				break;
			}
		} else {
			strcpy(outString, "");
		}

		cout << endl;
	}
}

/**
 *	Repeatedly runs the training mode with randomized strings from caesarTrainer class.
 */
void caesarTrainingMode(){
	/* Holds how many different random strings to test */
	int numTrials;

	cout << "Enter number of random strings to test: " << endl;
	cin >> numTrials;

	/* Default num_gen to 100,000 */
	NUM_GEN = 100000;

	/* For the test of the program, we can treat the mode as if it is training */
	userMode = 1;

	CaesarTrainer cTrainer;
	for (int i = 0; i < numTrials; i++){
		/* Set up plain text and ecrypted text based on caesarTrainer functions */
		cTrainer.createPlainText(plainText);
		cout << "Plain text: " << plainText << endl;

		cTrainer.encryptStr(encryptedText, plainText);
		cout << "Encrypted text: " << encryptedText << endl;

		mainLoop();
	}
}

/**
 *	Sets random synapse values for the first execution only.
 */
void initSyn(){
	/* Set up weights for syn0 */
	for (int i = 0; i < NUM_IN; i++){
		for (int j = 0; j < NUM_HIDDEN; j++){
			syn0[i][j] = (rand() % 10)/10.0;
		}
	}

	/* Set up weights for syn1 */
	for (int i = 0; i < NUM_HIDDEN; i++){
		for (int j = 0; j < NUM_HIDDEN; j++){
			syn1[i][j] = (rand() % 10)/10.0;
		}
	}

	/* Set up weights for syn2 */
	for (int i = 0; i < NUM_HIDDEN; i++){
		for (int j = 0; j < NUM_OUT; j++){
			syn2[i][j] = (rand() % 10)/10.0;
		}
	}
}

/**
 *	Asks the user if they want (returns the number):
 *	0: Using
 *	1: Training
 *	2: CaesarTraining
 *	3: Load synapses
 *	4: Save synapses
 *	5: Exit
 */
int getUserMode(){
	cout << "Enter a command: " << endl;
	cout << "\t0: Using mode " << endl;
	cout << "\t1: Training mode " << endl;
	cout << "\t2: Caesar training mode " << endl;
	cout << "\t3: Load synapses" << endl;
	cout << "\t4: Save synapses" << endl;
	cout << "\t5: Exit" << endl;
	
	int mode;
	cin >> mode;

	switch(mode){
		case 0:
			cout << "USING MODE SELECTED." << endl;
			return mode;
		case 1:
			cout << "TRAINING MODE SELECTED." << endl;
			return mode;
		case 2:
			cout << "CAESAR TRAINING MODE SELECTED." << endl;
			return mode;
		case 3:
			cout << "LOADING SYNAPSES." << endl;
			return mode;
		case 4:
			cout << "SAVING SYNAPSES." << endl;
			return mode;
		case 5:
			cout << "EXITING" << endl;
			exit(0);
		default:
			cout << "INVALID SELECTION." << endl;
			return getUserMode();
	}
}

/**
 *	Asks user for plain text,
 *	encrypted text,
 *	and number of generations
 */
void initTrain(){

	/* We only need the plain text for training mode. And we don't want to overwrite the current weights */
	cout << "Enter number of generations: " << endl;
	cin >> NUM_GEN;
	
	/* Clears extraneous \n that has no been read in yet */
	cin.getline(plainText, sizeof(plainText));
	cout << "Enter plain text up to " << MAX_CHAR << " characters: ";
	cin.getline(plainText, sizeof(plainText));


	cout << "Enter the encrypted text: ";
	cin.getline(encryptedText, sizeof(encryptedText));

}

/**
 *	Asks user for encrypted text
 */
void initUse(){

	/* Clears extraneous \n that has no been read in yet */
	cin.getline(encryptedText, sizeof(encryptedText));

	NUM_GEN = 1;
	
	cout << "Enter the encrypted text: ";
	cin.getline(encryptedText, sizeof(encryptedText));

}

/**
 *	Correctly sets the input values and target values (if training).
 *	Also resets the values stored in the hidden nodes and the outNodes to 0 for the next iteration.
 */
void setUpInputs(int i) {
	/********** SET UP INPUTS **********/

	/* For each input character, we need to mask out the bits to see what inputs will be on or off */
	mask = 1;
	for (int j = 0; j < NUM_IN; j++){	
		inputs[j] = (encryptedText[i] & mask) == 0 ? 0 : 1;

		if (userMode == 1){
     		target[j] = (plainText[i] & mask) == 0 ? 0 : 1;
		}

		mask = mask << 1;	//Shift mask over 1 to check for each bit 

		cout << inputs[j];
	}

	for (int j = 0; j < NUM_IN; j++){
		cout << target[j];
	}

	cout << endl;

	/* Reset hidden Nodes and output nodes to be all 0. */
	for (int j = 0; j < NUM_HIDDEN; j++){
		hiddenNode1[j] = 0;
		hiddenNode2[j] = 0;
	}
	for (int j = 0; j < NUM_OUT; j++){
		outNode[j] = 0;
	}
}

/**
 *	Computes the values for the hidden layer, then the output layer.	
 */
void calculateOutputs(){
	/********** CALCULATE OUTPUTS **********/

	/* Iterates through hidden layer1 */
	for (int j = 0; j < NUM_HIDDEN; j++){
		/* Iterates through all synapses connecting to the jth hidden node */
		for (int k = 0; k < NUM_IN; k++){
			hiddenNode1[j] += inputs[k] * syn0[k][j];
		}
	}

	/* Iterates through hidden layer2 */
	for (int j = 0; j < NUM_HIDDEN; j++){
		for (int k = 0; k < NUM_HIDDEN; k++){
			hiddenNode2[j] += sigmoid(hiddenNode1[k]) * syn1[k][j];
		}
	}

	/* Iterates to find outputs */
	for (int j = 0; j < NUM_OUT; j++){
		/* Iterates through all synapses connecting to the jth output node */
		for (int k = 0; k < NUM_HIDDEN; k++){
			outNode[j] += sigmoid(hiddenNode2[k]) * syn2[k][j];
		}
	}
}

/**
 *	Computes the new weight values based on the error in the target values.
 *	Only should be called in training mode.
 */
void backPropagation(){
	/********** BACK PROPAGATION **********/

	double finalError[NUM_OUT] = {0};
  	/* Outputs are now calculated by this point. We now need to check against the target */
  	for (int j = 0; j < NUM_OUT; j++){
  		/* If the rounding of the output node (it gets rounded as per the output), equals the correct target, then say there is no error */
  		if(target[j] == (int)floor(sigmoid(outNode[j]) + 0.5)){
  			finalError[j] = 0;
  		} else {
    		finalError[j] = ((double)target[j] - sigmoid(outNode[j])) * errorSigmoid(outNode[j]);
  		}
  	}

  	double newSyn2[NUM_HIDDEN][NUM_OUT] = {0};
  	/* For every synapse, we must now change the weight to be finalError for its output node, times the hiddenLayer result and add that to the old synapse value. */
  	for (int j = 0; j < NUM_OUT; j++){
  		for (int k = 0; k < NUM_HIDDEN; k++){
  			newSyn2[k][j] = syn2[k][j] + sigmoid(hiddenNode2[k]) * finalError[j]; 
  		}
  	}

  	double deltaHiddenSum2[NUM_HIDDEN] = {0};
  	/* Calculates the change in hidden sum2 by the last value */
  	for (int j = 0; j < NUM_OUT; j++){
  		for (int k = 0; k < NUM_HIDDEN; k++){
  			deltaHiddenSum2[k] += finalError[j] * syn2[k][j] * errorSigmoid(hiddenNode2[k]);
  		}
  	}

  	double newSyn1[NUM_HIDDEN][NUM_HIDDEN] = {0};
  	/*
  	 * Set the new weights of the first synapses (input to hidden) 
  	 * Similar to first newSyn2, but instead of having the finalError as our error margin, we have deltaHiddenSum2 as our error margin
  	 */
  	for (int j = 0; j < NUM_HIDDEN; j++){
  		for (int k = 0; k < NUM_HIDDEN; k++){
  			newSyn1[j][k] = syn1[j][k] +  sigmoid(hiddenNode1[j]) * deltaHiddenSum2[k];
  		}
  	}

	double deltaHiddenSum1[NUM_HIDDEN] = {0};
  	/* Calculates the change in hidden sum1 by the last value */
  	for (int j = 0; j < NUM_HIDDEN; j++){
  		for (int k = 0; k < NUM_HIDDEN; k++){
  			deltaHiddenSum1[j] += deltaHiddenSum2[j] * syn1[k][j] * errorSigmoid(hiddenNode1[k]);
  		}
  	}

  	/* Set the new weights of the first synapses (input to hidden) */
  	for (int j = 0; j < NUM_IN; j++){
  		for (int k = 0; k < NUM_HIDDEN; k++){
  			syn0[j][k] += deltaHiddenSum1[k] * inputs[j];
  		}
  	}

  	/* Now set syn1 and syn2 to the new weights */
  	for (int j = 0; j < NUM_HIDDEN; j++){
  		for (int k = 0; k < NUM_OUT; k++){
  			syn2[j][k] = newSyn2[j][k];
  		}
  	}
  	for (int j = 0; j < NUM_HIDDEN; j++){
  		for (int k = 0; k < NUM_HIDDEN; k++){
  			syn1[j][k] = newSyn1[j][k];
  		}
  	}

}

/**
 *	Displays the result string based on the value of the output nodes.
 */
void showResult(){
    /********** OUTPUT **********/

  	int outValue = 0;
  	/* Now, convert output back to ascii value */
  	for (int j = 0; j < NUM_OUT; j++){
  		/* We want the output value to be a 1 or 0. */
  		outValue += (floor(sigmoid(outNode[j]) + 0.5) >= 1 ? 1 << j : 0);
  	}
  	cout << outValue;
  	sprintf(outString, "%s%c", outString, (char)outValue);
}

/**
 *	For training mode only
 *	Checks the result of the output nodes, and compares it to the plain text
 *	Returns true when result matches
 *	Should exit the training mode when this happens.
 */
bool checkResult(int currentGen){
	/********** CHECK RESULT **********/

    if(strcmp(outString, plainText) == 0){
		cout << endl << "DECRYPTION FINISHED AFTER: " << currentGen << " GENERATIONS." << endl;
		strcpy(outString, "");
		return true;

    }
    /* Reset outString to blank for the next iteration */
	strcpy(outString, "");

	return false;
}

double sigmoid(double x){
	return 1.0/(1.0 + exp(-1*x));
}

double errorSigmoid(double x){
	return exp(x)/pow((exp(x) + 1), 2.0);
}