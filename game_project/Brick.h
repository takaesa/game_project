#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Mario.h"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_BLINK 22222
#define BRICK_STATE_GOLD 22223

class CBrick : public CGameObject {
public:
	CBrick(float x, float y) : CGameObject(x, y) 
	{
		SetState(BRICK_STATE_BLINK);
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetState(int state);
};