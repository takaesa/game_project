#pragma once
class RandomCard
{
};
#include "GameObject.h"

#define CARD_BLOCK_WIDTH	16
#define CARD_BLOCK_HEIGHT	16

#define CARD_FLOWER_STATE	1
#define CARD_MUSHROOM_STATE	2
#define CARD_STAR_STATE	3

#define ID_ANI_HUD_CARD_MUSHROOM 30021
#define ID_ANI_HUD_CARD_FLOWER 30022
#define ID_ANI_HUD_CARD_STAR 30023

#define SHOWING_TIME	200

class CRandomCard : public CGameObject
{
protected:
	bool isHit;

	ULONGLONG showing_start;
public:
	CRandomCard(float x, float y) : CGameObject(x, y)
	{
		isHit = false;
		showing_start = 0;
		SetState(CARD_FLOWER_STATE);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetState(int state);

	void SetisHit(bool isHit) { this->isHit = isHit; }
};
