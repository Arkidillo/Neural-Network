#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
using namespace std;
/*#include "net.h"

Net::Net(void){
	for (int i = 0; i < 3; i++){
		inputs[0] = new InNode();
		hiddenNodes[0] = new HiddenNode();
		
	}
}
*/
#define MAX_CHAR 10

#define NUM_IN 7
#define NUM_HIDDEN 10
#define NUM_OUT 7

#define NUM_GEN 100

double sigmoid(double x);
double errorSigmoid(double x);

int main(){
	char plainText[MAX_CHAR];
	cout << "Enter plain text up to " << MAX_CHAR << " characters:";
	cin >> plainText;

	char encryptedText[MAX_CHAR];
	cout << "Enter the encrypted text:";
	cin >> encryptedText;
	srand(time(NULL));

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

	/* Loop to repeat for each generation */
	for (int z = 0; z < NUM_GEN; z++){
	/* Main loop that goes through each character at a time. */
	for (int i = 0; i < strlen(encryptedText); i++){

		/* For each input character, we need to mask out the bits to see what inputs will be on or off */
		mask = 1;
		for (int j = 0; j < 7; j++){	
			inputs[j] = (plainText[i] & mask) == 0 ? 0 : 1;
         	target[j] = (encryptedText[i] & mask) == 0 ? 0 : 1;
			mask = mask << 1;	//Shift mask over 1 to check for each bit 
		}


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
      
     	 double finalError[NUM_OUT];
      	/* Outputs are now calculated by this point. We now need to check against the target */
      	for (int j = 0; j < NUM_OUT; j++){
        	finalError[j] = (target[j] - sigmoid(outNode[j])) * errorSigmoid(outNode[j]);
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

      	char outValue;
      	/* Now, convert output back to ascii value */
      	for (int j = 0; j < NUM_OUT; j++){
      		outValue += outNode[j] * pow(2, j);
      	}
      	cout << outValue;
	}

	cout << endl;
}
	return 0;

}

double sigmoid(double x){
	return 1.0/(1.0 + exp(-1*x));
}

double errorSigmoid(double x){
	return exp(x)/pow((exp(x) + 1), 2.0);
}