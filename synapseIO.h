#ifndef _SYNAPSE_IO_H_
#define _SYNAPSE_IO_H_

#define SYN0_FILE "synapse0.txt"
#define SYN1_FILE "synapse1.txt"
#define SYN2_FILE "synapse2.txt"

/**
 *	Function that saves the given synapse arrays to a text file 
 *	(using space as a separator)
 */
void saveSynapse(double syn0[][NUM_HIDDEN], double syn1[][NUM_HIDDEN], double syn2[][NUM_OUT]);

/**
 *	Loads the synapses from the file to the arrays passed in 
 */
void loadSynapse(double syn0[][NUM_HIDDEN], double syn1[][NUM_HIDDEN], double syn2[][NUM_OUT]);

#endif