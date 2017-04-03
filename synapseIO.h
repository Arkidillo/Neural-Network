#ifndef _SYNAPSE_IO_H_
#define _SYNAPSE_IO_H_

#define SYN0_FILE "synapse0.txt"
#define SYN1_FILE "synapse1.txt"

/**
 *	Function that saves the given synapse arrays to a text file
 */
void saveSynapse(int** syn0, int** syn1);

/**
 *	Loads the synapses from the file to 
 */
int loadSynapse(int*** syn0, int*** syn1);

#endif