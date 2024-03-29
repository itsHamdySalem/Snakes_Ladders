#pragma once

#include "Card.h"
#include "Player.h"
class CardEleven : public Card
{
	static int cardPrice;
	static int feesToPay;
	static Player* owner;
public:
	CardEleven(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);
	
	static Player* getOwner();
	static int getPrice();
	static int getFeesToPay();

	static void setOwner(Player*);

	virtual Card* GetCopy(CellPosition&);

	virtual ~CardEleven(); // A Virtual Destructor
};

