// Blackjack!
// A microgame
// By Greg Anthony Ocampo
// started 3/2/2020
/*
Design notes:

A limited 6 decks of 52 cards - suit will not matter, only value
 - A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K - (13 cards/suit * 4 suits/deck * 6 decks = 312 cards

use standard template library vector
to shuffle and pop cards in gameplay
each Card will have the char for the card type - A - K
A will have 2 values - 1 or 11
all others will have v1 = v2

use a vector for the player hand
erase vector elements between rounds

use a vector for the dealer hand
erase vector elements between rounds

next step:
a game loop for multiple rounds of play
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

struct Card
{
	char type;
	int val; // A can be 1 or 11 so be sure to account for that in gameplay
};

void start_menu()
{
	std::cout << "=====================================\n"
			  << "|  - [1] Play                       |\n"
			  << "|  - [2] Quit                       |\n"
			  << "-------------------------------------\n";
}

void game_interface()
{
	std::cout << "=====================================\n"
			  << "|  - [1] Hit                        |\n"
			  << "|  - [2] Stay                       |\n"
			  << "-------------------------------------\n"
			  << " What would you like to do? ";
}

void populate(std::vector<Card> &d)
{
	d.clear();
	char card_types[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
	int values[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
	for (int i = 0; i < 52; i++)
	{
		d.push_back({card_types[i % 13], values[i % 13]});
	}
}

void shuffle(std::vector<Card> &d)
{
	for (int i = 0; i < d.size(); i++)
	{
		int t = i + (rand() % (d.size() - i));
		Card temp =  d[t];
		d[t] = d[i];
		d[i] = temp;
	}
}

void deal(std::vector<Card> &player, std::vector<Card> &house, std::vector<Card> &d)
{
	player.push_back(d.back());
	d.pop_back();
	house.push_back(d.back());
	d.pop_back();
	player.push_back(d.back());
	d.pop_back();
	house.push_back(d.back());
	d.pop_back();
}

void peek(std::vector<Card> &hand)
{
	if (hand[0].type == 'T') std::cout << "10";
	else std::cout << hand[0].type;
	std::cout << " ?" << std::endl;
}

void show_hand(std::vector<Card> &hand)
{
	for (int i = 0; i < hand.size(); i++)
	{
		if (hand[i].type == 'T') std::cout << "10";
		else std::cout << hand[i].type;
		std::cout << " ";
	}
	std::cout << std::endl;
}

int hand_value(std::vector<Card> &hand)
{
	int total = 0;
	for (int i = 0; i < hand.size(); i++)
	{
		total += hand[i].val;
	}
	for (int i = 0; i < hand.size(); i++)
	{
		if (hand[i].type == 'A' && total < 12)
			total += 10;
	}
	return total;
}

void hit(std::vector<Card> &hand, std::vector<Card> &d)
{
	hand.push_back(d.back());
	d.pop_back();
}

int main()
{
	srand(time(0));
	std::cout << "----       Blackjack! v0.9       ----" << std::endl;
	
	std::vector<Card> deck;
	std::vector<Card> player_hand;
	std::vector<Card> house_hand;
	char input;
	bool quit = false;
	bool stay = false;
	int pHand;
	int dHand;
	bool blackjack = false;
	bool d_blackjack = false;
	bool bust = false;
	
	populate(deck);
	shuffle(deck);
	shuffle(deck);
	
	// main menu
	while (!quit)
	{
		quit = false;
		stay = false;
		blackjack = false;
		d_blackjack = false;
		bust = false;
		start_menu();
		while (true)
		{
			std::cout << " What would you like to do? ";
			std::cin >> input;
			std::cin.ignore(1000, '\n');
			if (input == '1' || input == '2') break;
			else std::cout << " Invalid input!" << std::endl;
		}
		if (input == '1')
		{
			// game loop
			std::cout << " Dealing cards!\n";
			deal(player_hand, house_hand, deck);
			std::cout << " - Dealer shows: ";
			peek(house_hand);
			std::cout << " - Player cards: ";
			show_hand(player_hand);
			pHand = hand_value(player_hand);
			std::cout << " You have: " << pHand << std::endl;
			if (pHand == 21) blackjack = true;
			dHand = hand_value(house_hand);
			if (dHand == 21) d_blackjack = true;
			
			// player turn
			while (!stay && !d_blackjack)
			{
				if (pHand >= 21) break;
				game_interface();
				while (true)
				{
					std::cin >> input;
					std::cin.ignore(1000, '\n');
					if (input == '1' || input == '2') break;
					else
					{
						std::cout << " Please enter a valid input! ";
					}
				}
				if (input == '1')
				{
					hit(player_hand, deck);
				} else if (input == '2')
				{
					stay = true;
				}
				std::cout << " - Player cards: ";
				show_hand(player_hand);
				pHand = hand_value(player_hand);
				std::cout << " You have: " << pHand << std::endl;
			}
			if (pHand > 21) bust = true;
			
			// resolve dealer cards
			std::cout << " - Dealer cards: ";
			show_hand(house_hand);
			dHand = hand_value(house_hand);
			std::cout << " Dealer score: " << dHand << std::endl;
			while (!bust)
			{
				if (dHand >= 17) break;
				else hit(house_hand, deck);
				std::cout << " - Dealer cards: ";
				show_hand(house_hand);
				dHand = hand_value(house_hand);
				std::cout << " Dealer has: " << dHand << std::endl;
			}
			std::cout << "-------------- Scoring --------------\n";
			std::cout << " - Dealer cards: ";
			show_hand(house_hand);
			dHand = hand_value(house_hand);
			std::cout << " Dealer score: " << dHand << std::endl;
			
			std::cout << " - Player cards: ";
			show_hand(player_hand);
			pHand = hand_value(player_hand);
			std::cout << " Player score: " << pHand << std::endl;

			// resolve scores
			if (blackjack)
			{
				if (d_blackjack)
				{
					std::cout << "    Push.\n";
				} else
				{
					std::cout << "    Blackjack! You win!\n";
				}
			} else if (bust)
			{
				std::cout << "    Bust! You lose...\n";
			} else if (dHand > 21)
			{
				std::cout << "    Dealer bust! You win!\n";
			} else if (d_blackjack)
			{
				std::cout << "    Dealer blackjack! You lose...\n";
			} else
			{
				if (pHand == dHand) std::cout << "    Push.\n";
				else if (pHand < dHand) std::cout << "    You lose...\n";
				else std::cout << "    You win!\n";
			}

			// delete used cards
			player_hand.clear();
			house_hand.clear();
			
			// if 9 or less cards left, reshuffle (populate)
			std::cout << " Cards left in deck: " << deck.size() << std::endl;
			if (deck.size() <= 9) 
			{
				populate(deck);
				shuffle(deck);
			}
		}
		else if (input == '2') quit = true;
	}
	
	std::cout << "Quitting Blackjack!";
	
	std::cout << std::endl;
	return 0;	
}
