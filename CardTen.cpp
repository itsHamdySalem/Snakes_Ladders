#include "CardTen.h"

Player* CardTen::owner = nullptr;
int CardTen::cardPrice = 0;
int CardTen::feesToPay = 0;

CardTen::CardTen(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 10; // set the inherited cardNumber data member with the card number (10 here)
}

CardTen::~CardTen(void)
{
}

Player* CardTen::getOwner() {
	return CardTen::owner;
}

int CardTen::getPrice() {
	return CardTen::cardPrice;
}

int CardTen::getFeesToPay() {
	return CardTen::feesToPay;
}

void CardTen::setOwner(Player* newOwner) {
	CardTen::owner = newOwner;
}


void CardTen::ReadCardParameters(Grid* pGrid)
{

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Card 10: Enter its price ...");
	CardTen::cardPrice = pIn->GetInteger(pOut);

	pOut->PrintMessage("New Card 10: Enter fees the passing player should pay ...");
	CardTen::feesToPay = pIn->GetInteger(pOut);

	pOut->ClearStatusBar();

}

void CardTen::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	if (owner == nullptr) { // if station is not bought

		if (pPlayer->GetWallet() < cardPrice) return;

		pOut->PrintMessage("Do you want to buy this station for " + to_string(cardPrice) + " coins? (1 For Yes, 0 For No)");
		int chose = pIn->GetInteger(pOut);
		if (chose == 1) {
			pPlayer->SetWallet(pPlayer->GetWallet() - cardPrice);
		}
		CardTen::owner = pPlayer;

	}
	else {

		if (pPlayer != owner) {
			pOut->PrintMessage("You must PAY " + to_string(feesToPay) + " to Player " + to_string(owner->getPlayerNumber()));
			pPlayer->SetWallet(pPlayer->GetWallet() - feesToPay);
			owner->SetWallet(owner->GetWallet() + feesToPay);
		}
		else {
			pOut->PrintMessage("Welcome to Your station");
		}

	}

}

Card* CardTen::GetCopy(CellPosition& Pos)
{
	Card* pCard = new CardTen(Pos);
	((CardTen*)pCard)->cardPrice = cardPrice;
	((CardTen*)pCard)->feesToPay = feesToPay;
	((CardTen*)pCard)->owner = owner;
	return pCard;
}