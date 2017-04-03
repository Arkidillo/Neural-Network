#ifndef _CAESAR_TRAINER_H_
#define _CAESAR_TRAINER_H_

class CaesarTrainer{
	public:
		/**
 		*	Generates random text for training purposes.
 		*	Saves this string into str
 		*/
		void createPlainText(char** str);

		/**
 		*	Encrypts the given str with a 3 shift caesar cipher
 		*	Loads str to decrypt from src, saves decrytpyed into dest
 		*/
		void encryptStr(char** dest, char** src);
};

#endif