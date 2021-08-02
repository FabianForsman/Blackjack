#include "Blackjack.h"

std::vector <int> Blackjack::cardsNum;
std::vector <char> Blackjack::cardsName;
std::vector <std::string> actions;

void line() {
	for (int i = 0; i < 32; i++)
		std::cout << "=";
	std::cout << std::endl;
}

Blackjack::Blackjack(std::string newName) {
	name = newName;
}

Blackjack::~Blackjack() {

}

void Blackjack::createActions() {
	actions.push_back("Hit");
	actions.push_back("Stay");
	actions.push_back("Split");
	actions.push_back("Double Down");
}

std::string Blackjack::getName() {
	return name;
}

int Blackjack::getTot(int hand) {
	if (tot[hand][0] > tot[hand][1] || tot[hand][1] > 21)
		return tot[hand][0];

	else if (tot[hand][0] < tot[hand][1])
		return tot[hand][1];

	else if (tot[hand][0] == tot[hand][1])
		return tot[hand][0];

	else
		return 0;
}

int Blackjack::ifSecHand() {
	return secHand;
}

bool Blackjack::ifStay(int hand) {
	return stay[hand];
}

bool Blackjack::ifSwap() {
	return swap;
}


void Blackjack::action(int hand) {
	int action = 0;
	std::cout << "What would you like to do, " << name << "?\n";

	if (handNum[hand].size() > 2)
		for (int i = 0; i < actions.size(); i++) {
			if (actions[i] == "Split")
				Blackjack::actions.erase(actions.begin() + i);

			if (actions[i] == "Double Down")
				Blackjack::actions.erase(actions.begin() + i);
		}

	if(!secHand)
		if (handNum[hand][0] != handNum[hand][1] || handNum[hand][0] > 9)
			for (int i = 0; i < actions.size(); i++) {
				if (actions[i] == "Split")
					Blackjack::actions.erase(actions.begin() + i);
			}

	for (int i = 0; i < Blackjack::actions.size(); i++)
		std::cout << "(" << i + 1 << ") " << Blackjack::actions[i] << ".\n";

	line();
	std::cin >> action;
	line();

	if (Blackjack::actions[action - 1] == "Hit")
		draw(hand);

	else if (Blackjack::actions[action - 1] == "Stay") {
		std::cout << "You decided to stay.\n";
		line();
		stayfunc(hand);
	}

	else if (Blackjack::actions[action - 1] == "Split")
		split();

	else if (Blackjack::actions[action - 1] == "Double Down")
		doubleDown(hand);
}

void Blackjack::split() {
	std::cout << "You decided to split your hand.\n";
	line();
	secHand = true;

	Blackjack::handNum[1].push_back(Blackjack::handNum[0][1]);
	Blackjack::handNum[0].pop_back();

	Blackjack::handName[1].push_back(Blackjack::handName[0][1]);
	Blackjack::handName[0].pop_back();

	for(int i = 0;i<actions.size();i++)
		if (actions[i] == "Double Down")
			Blackjack::actions.erase(actions.begin() + i);

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			tot[i][j] = 0;

	addTot(0, handNum[0][0]);
	addTot(1, handNum[1][0]);

	Blackjack::actions.erase(actions.begin() + 2);
}

void Blackjack::doubleDown(int hand) {
	std::cout << "You decided to double down.\n";
	line();
	std::cout << "Your bet has been doubled.\n";
	line();
	draw(hand);
	handPrint(hand);
	stayfunc(hand);
}

void Blackjack::stayfunc(int hand) {
	stay[hand] = true;
	if (secHand)
		swap = true;
}

void Blackjack::draw(int hand) {
	if (deckSize()) {
		int card;
		char type;
		std::string nameNum;
		std::string nameType;

		int random = rand() % cardsNum.size();
		card = cardsNum[random];
		type = cardsName[random];

		switch (card) {
		case 1:
			nameNum = "Ace";
			break;
		case 11:
			nameNum = "Jack";
			break;
		case 12:
			nameNum = "Queen";
			break;
		case 13:
			nameNum = "King";
			break;
		default:
			nameNum = "number";
			break;
		}

		switch (type) {
		case 'H':
			nameType = "Hearts";
			break;
		case 'D':
			nameType = "Diamonds";
			break;
		case 'S':
			nameType = "Spades";
			break;
		case 'C':
			nameType = "Clubs";
			break;
		default:
			break;
		}

		if (!secHand) {
			if (tot[hand][0] < 21) {
				Blackjack::handNum[hand].push_back(card);
				Blackjack::handName[hand].push_back(nameType);

				if (nameNum == "number") {
					if (name == "Dealer" && handNum[hand].size() == 2)
						std::cout << name << " drew a second card.\n";
					else
						std::cout << name << " drew " << card << " of " << nameType << ".\n";
				}

				else {
					if (name == "Dealer" && handNum[hand].size() == 2)
						std::cout << name << " drew a second card.\n";
					else
						std::cout << name << " drew " << nameNum << " of " << nameType << ".\n";
				}
				addTot(hand, card);
			}
		}

		else if (secHand) {
			if (tot[hand][0] < 21 && hand == 0) {
				Blackjack::handNum[0].push_back(card);
				Blackjack::handName[0].push_back(nameType);

				if (nameNum == "number")
					std::cout << name << " drew " << card << " of " << nameType << "\nfor their first hand.\n";

				else
					std::cout << name << " drew " << nameNum << " of " << nameType << "\nfor their first hand.\n";

				addTot(hand, card);
			}
			else if (tot[hand][0] < 21 && hand == 1) {
				Blackjack::handNum[1].push_back(card);
				Blackjack::handName[1].push_back(nameType);

				if (nameNum == "number")
					std::cout << name << " drew " << card << " of " << nameType << "\nfor their second hand.\n";

				else
					std::cout << name << " drew " << nameNum << " of " << nameType << "\nfor their second hand.\n";

				addTot(hand, card);
			}
		}

		Blackjack::cardsNum.erase(cardsNum.begin() + random);
		Blackjack::cardsName.erase(cardsName.begin() + random);

		line();
		Sleep(200);
	}
}

void Blackjack::addTot(int hand, int card) {
	if (card > 10)
		card = 10;

	tot[hand][0] += card;

	if (card == 1) {
		if (tot[hand][1] < 11)
			hand[tot][1] += 11;
		else
			hand[tot][1] += 1;
	}

	else
		tot[hand][1] += card;
}

void Blackjack::handPrint(int hand) {
	int card;
	std::string cardName;

	std::cout << name << "'s ";

	if (secHand) {
		if(hand == 0)
			std::cout << "first ";

		if (hand == 1)
			std::cout << "second ";
	}

	std::cout << "hand contains\n\n";
	
	for (int i = 0; i < handNum[hand].size(); i++) {
		card = handNum[hand][i];

		switch (card) {
			case 1:
				cardName = "Ace";
				std::cout << cardName << " of " << handName[hand][i] << std::endl;
				break;
			case 11:
				cardName = "Jack";
				std::cout << cardName << " of " << handName[hand][i] << std::endl;
				break;
			case 12:
				cardName = "Queen";
				std::cout << cardName << " of " << handName[hand][i] << std::endl;
				break;
			case 13:
				cardName = "King";
				std::cout << cardName << " of " << handName[hand][i] << std::endl;
				break;
			default:
				std::cout << card << " of " << handName[hand][i] << std::endl;
				break;
		}
	}

	std::cout << std::endl;

	if (tot[hand][0] == tot[hand][1] || tot[hand][1] > 21 || tot[hand][1] == 0)
		std::cout << tot[hand][0] << " total.\n";

	else if (tot[hand][1] < 22 && tot[hand][1] > 0)
		std::cout << tot[hand][0] << " or " << tot[hand][1] << " total.\n";
	
	line();
	Sleep(500);
}

void Blackjack::deck() {
	for (int k = 0; k < 4; k++)
		for (int i = 0; i < 4; i++)
			for (int j = 1; j < 14; j++) {
				Blackjack::cardsNum.push_back(j);
				switch (i) {
					case 0:
						Blackjack::cardsName.push_back('H');
						break;
					case 1:
						Blackjack::cardsName.push_back('D');
						break;
					case 2:
						Blackjack::cardsName.push_back('S');
						break;
					case 3:
						Blackjack::cardsName.push_back('C');
						break;
				}
			}
}

void Blackjack::deckPrint() {
	for (int i = 0; i < Blackjack::cardsNum.size() - 1; i++) {
		if (i < Blackjack::cardsNum.size()) {
			std::cout << Blackjack::cardsNum[i];

			if (cardsNum[i] > cardsNum[i + 1])
				std::cout << "\n";

			else
				std::cout << ", ";
		}
	}

	std::cout << Blackjack::cardsNum[Blackjack::cardsNum.size() - 1] << std::endl;
	line();
}

int Blackjack::deckSize() {
	return cardsNum.size();
}

void Blackjack::handReset() {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			tot[i][j] = 0;

	handNum[0].clear();
	handNum[1].clear();
	handName[0].clear();
	handName[1].clear();
	actions.clear();
	createActions();

	swap = false;
	secHand = false;
	stay[0] = false;
	stay[1] = false;
}
