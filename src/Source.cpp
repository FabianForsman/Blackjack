#include "Blackjack.h"

void intro();
void game();

int main() {
	srand(time(0));
	intro();
	Blackjack::deck();
	game();
	return -1;
}

void intro() {
	line();
	std::cout << "Welcome to Blackjack.\nWrite 'Play' when ready\n";
	line();
}

void game() {

	std::vector <Blackjack> players;
	std::string res[3] = { " won", " lost", " drew" };
	std::string name, ans;
	int hand = 0, round = 0;

	do {
		std::cout << "Enter name: ";
		std::cin >> name;
		line();

		if (!(name == "Play" || name == "play" || name == "p")) {
			Blackjack newPlayer(name);
			players.push_back(newPlayer);
		}

	} while (!(name == "Play" || name == "play" || name == "p"));

	Blackjack dealer("Dealer");
	players.push_back(dealer);
	
	do {
		if (!Blackjack::deckSize())
			break;
		system("CLS");
		std::cout << "Round " << ++round << "!\n";
		line();

		for (int i = 0; i < players.size(); i++) {
			players[i].handReset();
			hand = players[i].ifSwap();
		}

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < players.size(); j++)
				players[j].draw(hand);
		if (Blackjack::deckSize()) {
			for (int i = 0; i < players.size() - 1; i++) {
				while (!players[i].ifStay(hand) && players[i].getTot(hand) < 22 && Blackjack::deckSize()) {
					players[i].handPrint(hand);

					if (players[i].getTot(hand) == 21) {
						std::cout << "You've got Blackjack, " << players[i].getName() << "!\n";
						line();
						players[i].stayfunc(hand);
						Sleep(1000);
					}

					else
						players[i].action(hand);

					if (players[i].getTot(hand) > 21) {
						players[i].handPrint(hand);
						std::cout << "Bust! You went over 21.\n";
						line();
						players[i].stayfunc(hand);
						Sleep(1000);
					}

					hand = players[i].ifSwap();
				}
			}

			players[players.size() - 1].handPrint(0);

			while (players[players.size() - 1].getTot(0) < 17 || (players[players.size() - 1].getTot(1) < 17 && players[players.size() - 1].getTot(1) > 21)) {
				players[players.size() - 1].draw(0);
				players[players.size() - 1].handPrint(0);

				if (players[players.size() - 1].getTot(hand) > 21) {
					std::cout << "Bust! Dealer went over 21.\n";
					line();
				}

				if (!Blackjack::deckSize())
					break;
			}
		}

		else
			break;

		for (int i = 0; i < players.size() - 1; i++)
			for (int j = 0; j < players[i].ifSecHand() + 1; j++) {
				if (players[i].getTot(j) < 22) {
					std::cout << players[i].getName();
					if (players[players.size() - 1].getTot(0) < players[i].getTot(j) || players[players.size() - 1].getTot(0) > 21)
						std::cout << res[0]; // Win

					else if (players[players.size() - 1].getTot(0) > players[i].getTot(j) || players[i].getTot(j) > 21)
						std::cout << res[1]; // Loss

					else if (players[players.size() - 1].getTot(0) == players[i].getTot(j))
						std::cout << res[2]; // Draw
				}

				else
					std::cout << players[i].getName() << res[1]; // Loss

				if (players[i].ifSecHand() && j == 0)
					std::cout << " their first hand.\n";

				else if (j == 1)
					std::cout << " their second hand.\n";

				else
					std::cout << ".\n";
			}

		line();
		Sleep(1000);
		std::cout << "Run it back?\nYes/No\n";
		line();
		std::cin >> ans;
		ans = "Y";
		line();
		if (Blackjack::deckSize()) {
			std::cout << "Remaining cards:\n";
			Blackjack::deckPrint();
		}
		Sleep(500);
	} while ((ans == "Y" || ans == "y" || ans == "Yes" || ans == "yes") && Blackjack::deckSize());
	if (!Blackjack::deckSize())
		std::cout << "No more cards!\n";
	std::cout << "Game ended.\n";
	line();
}
