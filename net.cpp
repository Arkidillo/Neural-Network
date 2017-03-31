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
double sigmoid(double x);
double errorSigmoid(double x);

int main(){
	char plainText[10];
	cout << "Enter plain text up to 10 characters:";
	cin >> plainText;

	char encryptedText[10];
	cout << "Enter the encrypted text:";
	cin >> encryptedText;
	srand(time(NULL));

	/* Input/ ouput nodes will be turned on according to the binary value of the ascii value of each letter */
	int inputs[7];
	int target[7];
	/* syn0 are the edges connecting the input nodes and the hidden layer */
	double syn0[7][10];
	double hiddenNode[10];
	/* syn1 are the edges connecting the hidden layer node and the output nodes */
	double syn1[10][7];
	/* The ouputs will be doubles, but will be cast to ints as the output, to get the ascii value */
	double outNode[7];

	/* Mask will mast out each bit of the input string to get which bits of the input nodes should be turned on */
	char mask;
	
	/* Set up weights for syn0 and syn1*/
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 10; j++){
			syn0[i][j] = (rand() % 10)/10.0;
			syn1[j][i] = (rand() % 10)/10.0;	//Because syn0 is 7 x 10, and syn1 is 10 x 7, so syn0 and 1 will both be fully populated.
		}
	}

	cout << strlen(encryptedText);
	for (int z = 0; z < 100; z++){
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
		for (int j = 0; j < 10; j++){
			/* Iterates through all synapses connecting to the jth hidden node */
			for (int k = 0; k < 7; k++){
				hiddenNode[j] += inputs[k] * syn0[k][j];
			}
         }

		/* Iterates to find outputs */
		for (int j = 0; j < 7; j++){
			/* Iterates through all synapses connecting to the jth output node */
			for (int k = 0; k < 10; k++){
				outNode[j] += sigmoid(hiddenNode[k]) * syn1[k][j];
			}
		}
      
     	 double finalError[7];
      	/* Outputs are now calculated by this point. We now need to check against the target */
      	for (int j = 0; j < 7; j++){
        	finalError[j] = (target[j] - sigmoid(outNode[j])) * errorSigmoid(outNode[j]);
      	}

      	double newSyn1[10][7];
      	/* For every synapse, we must now change the weight to be finalError for its output node, times the hiddenLayer result and add that to the old synapse value. */
      	for (int j = 0; j < 7; j++){
      		for (int k = 0; k < 10; k++){
      			newSyn1[k][j] = syn1[k][j] + sigmoid(hiddenNode[k]) * finalError[j]; 
      		}
      	}

      	double deltaHiddenSum[10][7];
      	/* Calculates the change in hidden sum by the last value */
      	for (int j = 0; j < 7; j++){
      		for (int k = 0; k < 10; k++){
      			deltaHiddenSum[k][j] = finalError[j] * syn1[k][j] * errorSigmoid(hiddenNode[k]);
      		}
      	}

      	/* Set the new weights of the first synapses (input to hidden) */
      	for (int j = 0; j < 7; j++){
      		for (int k = 0; k < 10; k++){
      			syn0[j][k] += deltaHiddenSum[k][j] * inputs[j];
      		}
      	}

      	/* Now set syn1 to the new weights */
      	for (int j = 0; j < 10; j++){
      		for (int k = 0; k < 7; k++){
      			syn1[j][k] = newSyn1[j][k];
      		}
      	}

      	char outValue;
      	/* Now, convert output back to ascii value */
      	for (int j = 0; j < 7; j++){
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