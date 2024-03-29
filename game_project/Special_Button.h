#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Mario.h"


#define SPECIAL_P_DISTANCE 3.0f
#define	SPECIAL_P_WIDTH 15
#define SPECIAL_P_BBOX_WIDTH 15
#define SPECIAL_P_BBOX_HEIGHT 15

#define SPECIAL_P_PRESSED_BBOX_WIDTH 15
#define SPECIAL_P_PRESSED_BBOX_HEIGHT 7
#define SPECIAL_P_SPEED 0.169f

#define SPECIAL_P_STATE_NORMAL 12020
#define ID_ANI_SPECIAL_P 12020

#define SPECIAL_P_STATE_PRESSED 12021
#define ID_ANI_SPECIAL_P_PRESSED 12021



class CSpecial_Button : public CGameObject
{
	bool flyable = false;
	float flyDistance = 0;
	ULONGLONG stop_changing;
	bool pressable = true;

public:

	CSpecial_Button(float x, float y) : CGameObject(x, y) {
		pressable = true;
		stop_changing = -1;
		SetState(SPECIAL_P_STATE_NORMAL);
	}
	void Render();
	/*virtual void OnNoCollision(DWORD dt);*/
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetFly(bool state) { this->flyable = state; }
	void SetPressable(bool state) { this->pressable = state; }
	bool GetPressable() { return pressable; }
	void OnNoCollision(DWORD dt) { y -= vy * dt; }
	int IsBlocking() { return 0; }
	void SetState(int state);
};

