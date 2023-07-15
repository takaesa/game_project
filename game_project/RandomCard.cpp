#include "RandomCard.h"

void CRandomCard::Render()
{
	int sprite = -1;
	switch (state)
	{
	case CARD_FLOWER_STATE:
		sprite = ID_ANI_HUD_CARD_FLOWER;
		break;
	case CARD_STAR_STATE:
		sprite = ID_ANI_HUD_CARD_STAR;
		break;
	case CARD_MUSHROOM_STATE:
		sprite = ID_ANI_HUD_CARD_MUSHROOM;
		break;
	default:
		break;
	}
	if (isHit == false)
	{
		CSprites* sprites = CSprites::GetInstance();
		sprites->Get(sprite)->Draw(x, y);
	}

}

void CRandomCard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == CARD_FLOWER_STATE && GetTickCount64() - showing_start > SHOWING_TIME)
	{
		showing_start = 0;
		SetState(CARD_MUSHROOM_STATE);

	}
	if (state == CARD_STAR_STATE && GetTickCount64() - showing_start > SHOWING_TIME)
	{
		showing_start = 0;
		SetState(CARD_FLOWER_STATE);

	}
	if (state == CARD_MUSHROOM_STATE && GetTickCount64() - showing_start > SHOWING_TIME)
	{
		showing_start = 0;
		SetState(CARD_STAR_STATE);

	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CRandomCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CARD_BLOCK_WIDTH / 2;
	t = y - CARD_BLOCK_HEIGHT / 2;
	r = l + CARD_BLOCK_WIDTH;
	b = t + CARD_BLOCK_HEIGHT;
}

void CRandomCard::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CARD_FLOWER_STATE:
		showing_start = GetTickCount64();
		break;
	case CARD_STAR_STATE:
		showing_start = GetTickCount64();
		break;
	case CARD_MUSHROOM_STATE:
		showing_start = GetTickCount64();
		break;
	default:
		break;
	}
}