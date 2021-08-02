#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

void line();

class Blackjack
{
	public:
		Blackjack(std::string newName);
		~Blackjack();

		static void deck();
		static int deckSize();
		void createActions();
		void handReset();

		std::string getName();
		int getTot(int hand);
		int ifSecHand();
		bool ifStay(int hand);
		bool ifSwap();

		void action(int hand);
		void draw(int hand);
		void split();
		void doubleDown(int hand);
		void stayfunc(int hand);

		void addTot(int hand, int card);

		static void deckPrint();
		void handPrint(int hand);

	private:
		static std::vector <int> cardsNum; // Deck
		static std::vector <char> cardsName; // Deck

		std::string name;
		std::vector <int> handNum[2];
		std::vector <std::string> handName[2];
		std::vector <std::string> actions;

		int tot[2][2] = { {0,0}, {0,0} };
		bool secHand = false, stay[2] = { false, false }, swap = false;
};
