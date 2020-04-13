// Hangman!
// A C++ microgame
// by Greg Anthony Ocampo
// hangman_game.cpp

/*
*	Game will follow this steps until completion:
*		1) Choose a word
*		2) Player inputs a character
*		3) Compare that character to the chosen word
*		4) List all used letters in order
*		5) Display results
*	Players win by guessing word correctly
*	Players lose by guessing letters incorrectly 4 times
* 	Next step: Make a container for all possible words, choose one randomly
*/

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::cout << "Welcome to Hangman! v0.1" << std::endl;
	
	// game data members
	std::string HangWord;
	std::string GuessWord; // fill with -, replace - with correct chars
	char GuessChar;
	bool bIsCorrect = false;
	int Strikes = 0;
	std::vector<char> UsedChars;
	bool bGameOver = false;
	bool bGameWin = false;
	
	HangWord = "CELEBRATE";
	GuessWord.resize(HangWord.length());
	for (int iGuessWord = 0; iGuessWord < GuessWord.length(); ++iGuessWord)
	{
		GuessWord[iGuessWord] = '_';
	}	
	while (!bGameOver && !bGameWin)
	{
		// show guessed chars
		std::cout << "Used Letters:\t";
		for (int iUsedChars = 0; iUsedChars < UsedChars.size(); ++iUsedChars)
		{
			std::cout << UsedChars[iUsedChars] << " ";
		}
		// show strikes
		std::cout << "\nStrikes:\t";
		for (int iStrikes = 0; iStrikes < 4; ++iStrikes)
		{
			if (Strikes > iStrikes)
			{
				std::cout << "X";
			}
			else
			{
				std::cout << "-";
			}
		}
		// show guess word
		std::cout << "\nHangWord:\t" << GuessWord << std::endl;
		// players enter guess
		std::cout << "Enter guess: ";
		while (true)
		{
			bool bIsUsed = false;
			GuessChar = toupper(std::cin.get());
			std::cin.ignore(1, '\n');
			for (int iUsedChars = 0; iUsedChars < UsedChars.size(); ++iUsedChars)
			{
				if (GuessChar == UsedChars[iUsedChars])
				{
					bIsUsed = true;
				}
			}
			if (bIsUsed)
			{
				std::cout << "This letter has been used!\nPlease enter a new guess: ";
			}
			else
			{
				UsedChars.push_back(GuessChar);
				break;
			}
		}
		// compare guess to hangword
		for (int iHangWord = 0; iHangWord < HangWord.length(); ++iHangWord)
		{
			if (GuessChar == HangWord[iHangWord])
			{
				GuessWord[iHangWord] = GuessChar;
				bIsCorrect = true;
			}
		}
		if (!bIsCorrect)
		{
			++Strikes;
		}
		bIsCorrect = false;
		if (Strikes == 4) bGameOver = true;
		if (HangWord == GuessWord) bGameWin = true;
	}
	std::cout << "Complete HangWord: " << HangWord;
	if (bGameOver)
	{
		std::cout << "\nYou lose!";
	}
	else 
	{
		std::cout << "\nYou win!";
	}
	std::cout << std::endl;
	return 0;
}