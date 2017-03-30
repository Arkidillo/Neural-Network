#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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

int main(){


	char plainText[10];
	cout << "Enter plain text up to 10 characters:";
	cin >> plainText;

   char ecryptedText[10];
   cout << "Enter the encrypted text:";
   cin >> ecryptedText;
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
   double finalError[7];

	/* Mask will mast out each bit of the input string to get which bits of the input nodes should be turned on */
	char mask;
	
	/* Set up weights for syn0 and syn1*/
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 10; j++){
			syn0[i][j] = (rand() % 10)/10.0;
			syn1[j][i] = (rand() % 10)/10.0;	//Because syn0 is 7 x 10, and syn1 is 10 x 7, so syn0 and 1 will both be fully populated.
		}
	}

	/* Main loop that goes through each character at a time. */
	for (int i = 0; i < 10; i++){

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
         
         /* Apply sigmoid function to hiddenlayer sums */
         hiddenNode[j] = sigmoid(hiddenNode[j]);
		}

		/* Iterates to find outputs */
		for (int j = 0; j < 7; j++){
			/* Iterates through all synapses connecting to the jth output node */
			for (int k = 0; k < 10; k++){
				outNode[j] += hiddenNode[k] * syn1[k][j];
			}
		}
      
      /* Outputs are now calculated by this point. We now need to check against the target */
      for (int j = 0; j < 7; j++){
         finalError[j] = target[j] - outNode[j];
      }
	}
	return 0;

}

double sigmoid(double x){
	return 1/(1 + pow(2.71828183, -1*x);
}