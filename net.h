#ifndef _NET_H_
#define _NET_H_

#define MAX_CHAR 25

#define NUM_IN 7
#define NUM_HIDDEN 10
#define NUM_OUT 7


void mainLoop();

/**
 *	Takes null characters (ascii = 0) in the given string to '@'
 *	The purpose of this is so that the synapses don't have to change that much to account for null characters.
 */
void convertNull(char* str);

/**
 *	Repeatedly runs the training mode with randomized strings from caesarTrainer class.
 */
void caesarTrainingMode();

/**
 *	Sets random synapse values for the first execution only.
 */
void initSyn();

/**
 *	Asks the user if they want (returns the number):
 *	0: Using
 *	1: Training
 *	2: CaesarTraining
 */
int getUserMode();

/**
 *	Asks user for plain text,
 *	encrypted text,
 *	and number of generations
 */
void initTrain();

/**
 *	Asks user for encrypted text
 */
void initUse();

/**
 *	Correctly sets the input values and target values (if training).
 *	Also resets the values stored in the hidden nodes and the outNodes to 0 for the next iteration.
 */
void setUpInputs(int i);

/**
 *	Computes the values for the hidden layer, then the output layer.	
 */
void calculateOutputs();

/**
 *	Computes the new weight values based on the error in the target values.
 *	Only should be called in training mode.
 */
void backPropagation();

/**
 *	Displays the result string based on the value of the output nodes.
 */
void showResult();

/**
 *	For training mode only
 *	Checks the result of the output nodes, and compares it to the plain text
 *	Returns true when result matches
 *	Should exit the training mode when this happens.
 */
bool checkResult(int currentGen);

//TODO: Add comments
double sigmoid(double x);
double errorSigmoid(double x);


#endif