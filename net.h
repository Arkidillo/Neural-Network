#ifndef _NET_H_
#define _NET_H_

#define MAX_CHAR 1000

#define NUM_IN 7
#define NUM_HIDDEN 10
#define NUM_OUT 7


void mainLoop();

/**
 *	Repeatedly runs the training mode with randomized strings from caesarTrainer class.
 */
void caesarTrainingMode();

/**
 *	Populates the shorter string with spaces, so encrytion/ decryption will still work.
 */
void populateShorterString();

/**
 *	Sets random synapse values for the first execution only.
 */
void initSyn();

//TODO: Add comment
int getUserMode();

//TODO: Add comment
void init();

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