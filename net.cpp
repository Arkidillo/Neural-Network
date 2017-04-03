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
 *	TODO: Save weights to a file
 *	TODO: Make static training method to train it against many caesar cipher examples
 */

int NUM_GEN;

/* 0 if in using, 1 if in training */
int userMode;

/* Input/ ouput nodes will be turned on according to the binary value of the ascii value of each letter */
int inputs[NUM_IN];
int target[NUM_OUT];

/* syn0 are the edges connecting the input nodes and the hidden layer */
double syn0[NUM_IN][NUM_HIDDEN];
double hiddenNode[NUM_HIDDEN];

/* syn1 are the edges connecting the hidden layer node and the output nodes */
double syn1[NUM_HIDDEN][NUM_OUT];

/* The ouputs will be doubles, but will be cast to ints as the output, to get the ascii value */
double outNode[NUM_OUT];

/* Mask will mast out each bit of the input string to get which bits of the input nodes should be turned on */
char mask;

/* A buffer of 100 generations that happens after it finds the right decryption, to make sure it is not a fluke/ trains itself more */
int buffer = 100;

char plainText[MAX_CHAR];
char encryptedText[MAX_CHAR];

char outString[MAX_CHAR];

int main(){

	srand(time(NULL));	

	initSyn();

	/* Total loop that will repeatedly ask the user whether they want training or using, so they can train the net, then attempt to use it for another problem */
	while (1){
		
		/* Asks the user what mode they would like to use, training or using */
		userMode = getUserMode();

		if(userMode == 2){
			caesarTrainingMode();
		} else {

			/* Gets user input, initializes the synapses to random values */
			init();
			populateShorterString();
		}
		/* Does the rest of the work of training or using */
		mainLoop();
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
 *	Populates the shorter string with spaces, so encrytion/ decryption will still work.
 */
void populateShorterString(){
	char* shorter = strlen(encryptedText) > strlen(plainText) ? plainText : encryptedText;
	char* longer = strlen(encryptedText) < strlen(plainText) ? plainText : encryptedText;

	for (int i = strlen(shorter); i < strlen(longer); i++){
		shorter[i] = ' ';
	}
}

/**
 *	Sets random synapse values for the first execution only.
 */
void initSyn(){
	/* Set up weights for syn0 and syn1*/
	for (int i = 0; i < NUM_IN; i++){
		for (int j = 0; j < NUM_OUT; j++){
			syn0[i][j] = (rand() % 10)/10.0;
		}
	}

	/* Set up weights for syn1 */
	for (int i = 0; i < NUM_HIDDEN; i++){
		for (int j = 0; j < NUM_OUT; j++){
			syn1[j][i] = (rand() % 10)/10.0;
		}
	}
}

int getUserMode(){
	cout << "Enter a command: " << endl;
	cout << "\t0: Using mode " << endl;
	cout << "\t1: Training mode " << endl;
	cout << "\t2: Caesar training mode " << endl;

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
		default:
			cout << "INVALID SELECTION." << endl;
			return getUserMode();
	}
}
/**
 *	TODO: Split this to a different function per each mode, and check if in main before calling the function.
 */
void init(){

	/* We only need the plain text for training mode. And we don't want to overwrite the current weights */
	if (userMode == 1){
		/* We only need to use the NUM_GEN in triaining, because in using, the output will always be the same because there is no weight change. Thus, we only need 1 GEN. */
		cout << "Enter number of generations: " << endl;
		cin >> NUM_GEN;
		
		/* Clears extraneous \n that has no been read in yet */
		cin.getline(plainText, sizeof(plainText));
		cout << "Enter plain text up to " << MAX_CHAR << " characters: ";
		cin.getline(plainText, sizeof(plainText));

	} else {
		/* Clears extraneous \n that has no been read in yet */
		cin.getline(encryptedText, sizeof(encryptedText));

		NUM_GEN = 1;
	}

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
	}

	/* Reset hidden Nodes and output nodes to be all 0. */
	for (int j = 0; j < NUM_HIDDEN; j++){
		hiddenNode[j] = 0;
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

	/* Iterates through hidden layer */
	for (int j = 0; j < NUM_HIDDEN; j++){
		/* Iterates through all synapses connecting to the jth hidden node */
		for (int k = 0; k < NUM_IN; k++){
			hiddenNode[j] += inputs[k] * syn0[k][j];
		}
	}

	/* Iterates to find outputs */
	for (int j = 0; j < NUM_OUT; j++){
		/* Iterates through all synapses connecting to the jth output node */
		for (int k = 0; k < NUM_HIDDEN; k++){
			outNode[j] += sigmoid(hiddenNode[k]) * syn1[k][j];
		}
	}
}
/**
 *	Computes the new weight values based on the error in the target values.
 *	Only should be called in training mode.
 */
void backPropagation(){
	/********** BACK PROPAGATION **********/

	double finalError[NUM_OUT];
  	/* Outputs are now calculated by this point. We now need to check against the target */
  	for (int j = 0; j < NUM_OUT; j++){
  		/* If the rounding of the output node (it gets rounded as per the output), equals the correct target, then say there is no error */
  		if(target[j] == (int)floor(sigmoid(outNode[j]) + 0.5)){
  			finalError[j] = 0;
  		} else {
    		finalError[j] = ((double)target[j] - sigmoid(outNode[j])) * errorSigmoid(outNode[j]);
  		}
  	}

  	double newSyn1[NUM_HIDDEN][NUM_OUT];
  	/* For every synapse, we must now change the weight to be finalError for its output node, times the hiddenLayer result and add that to the old synapse value. */
  	for (int j = 0; j < NUM_OUT; j++){
  		for (int k = 0; k < NUM_HIDDEN; k++){
  			newSyn1[k][j] = syn1[k][j] + sigmoid(hiddenNode[k]) * finalError[j]; 
  		}
  	}

  	double deltaHiddenSum[NUM_HIDDEN][NUM_OUT];
  	/* Calculates the change in hidden sum by the last value */
  	for (int j = 0; j < NUM_OUT; j++){
  		for (int k = 0; k < NUM_HIDDEN; k++){
  			deltaHiddenSum[k][j] = finalError[j] * syn1[k][j] * errorSigmoid(hiddenNode[k]);
  		}
  	}

  	/* Set the new weights of the first synapses (input to hidden) */
  	for (int j = 0; j < NUM_IN; j++){
  		for (int k = 0; k < NUM_HIDDEN; k++){
  			syn0[j][k] += deltaHiddenSum[k][j] * inputs[j];
  		}
  	}

  	/* Now set syn1 to the new weights */
  	for (int j = 0; j < NUM_HIDDEN; j++){
  		for (int k = 0; k < NUM_OUT; k++){
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
    	buffer--;

   		if (buffer == 0){
    		cout << endl << "DECRYPTION FINISHED AFTER: " << currentGen - 100 << " GENERATIONS." << endl;
    		strcpy(outString, "");
    		return true;
    	}
    } else {
    	buffer = 100;
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