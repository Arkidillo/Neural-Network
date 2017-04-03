#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "caesarTrainer.h"

/**
 *	Generates random text for training purposes.
 *	Saves this string into str
 */
void CaesarTrainer::createPlainText(char** str){
	srand(time(NULL));

	/* We choose a random length for the string 1-10 */
	int n = (rand() % 20) + 1;

	for (int i = 0; i < n; i++){
		/* Sets each letter in the new string to a random ascii value from 57(A) to 122(z) */
		str[0][i] = (rand() % 58) + 65;
	}
}

/**
 *	Encrypts the given str with a 3 shift caesar cipher
 *	Loads str to encrypt from src, saves encrypted into dest
 */
void CaesarTrainer::encryptStr(char** dest, char** src){
	for (int i = 0; i < strlen(*dest); i++){
		dest[0][i] = src[0][i] + 3;
	}
}
