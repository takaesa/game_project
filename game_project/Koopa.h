#pragma once
#include "GameObject.h"
#include "FallWarning.h"

#define KOOPA_GRAVITY 0.0005f
#define KOOPA_JUMP_SPEED	0.45f
#define KOOPA_WALKING_SPEED 0.04f
#define KOOPA_SHELL_MOVING_SPEED	0.2f
#define KOOPA_JUMP_TIMEOUT 3000

#define KOOPA_SCORE	2000

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_HEIGHT_SHELL 14

#define KOOPA_SHELL_AWAKE	4000
#define KOOPA_SHELL_TIMEOUT 6000
#define KOOPA_RESET_TIMEOUT 1000

#define KOOPA_STATE_WALKING 100		// 100: left, 101: right

#define KOOPA_STATE_SHELL 200		// 200: green, 201: red
#define KOOPA_STATE_SHELL_MOVING	300
#define KOOPA_STATE_AWAKE	400
#define KOOPA_STATE_CARRIED	500


//ANIMATIONS
// 
// //Normal Green
#define ID_ANI_KOOPA_NORMAL_GREEN_WALKING_LEFT 91100
#define ID_ANI_KOOPA_NORMAL_GREEN_WALKING_RIGHT 91200

#define ID_ANI_KOOPA_GREEN_SHELL	91300
#define ID_ANI_KOOPA_GREEN_SHELL_AWAKE	91400

#define ID_ANI_KOOPA_GREEN_SHELL_MOVING	91500

#define ID_ANI_KOOPA_GREEN_SHELL_FLIPPED	91600

//Fly Green
#define ID_ANI_KOOPA_FLY_GREEN_WALKING_LEFT 92100
#define ID_ANI_KOOPA_FLY_GREEN_WALKING_RIGHT 92200


//Normal Red
#define ID_ANI_KOOPA_NORMAL_RED_WALKING_LEFT 93100
#define ID_ANI_KOOPA_NORMAL_RED_WALKING_RIGHT 93200
										
#define ID_ANI_KOOPA_RED_SHELL	93300
#define ID_ANI_KOOPA_RED_SHELL_AWAKE	93400

#define ID_ANI_KOOPA_RED_SHELL_MOVING	93500

#define ID_ANI_KOOPA_RED_SHELL_FLIPPED	93600


class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	int type;		// 0: green normal, 1: green fly, 2: red normal, 3: red fly
	bool minusY_flag = true;
	int dir = 1;	// 1: left, -1: right
	bool isFlipped = false;
	bool jumpable = true;


	ULONGLONG shell_start;
	ULONGLONG jump_start;
	ULONGLONG reset_start;
	BOOLEAN isOnPlatform = false;

	CFallWarning* fallwarning;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() 
	{ 
		if (isFlipped)
			return 0;
		return 1; 
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithPlain(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithDeadBlock(LPCOLLISIONEVENT e);
	//virtual void OnCollisionWithTransparentBlock(LPCOLLISIONEVENT e);
	
public:
	CKoopa(float x, float y, int type = 0);
	virtual void SetState(int state);
	virtual int GetType() { return type; }
	virtual void SetType(int level) { type = level; }
	virtual void SetDir(int dir) { this->dir = dir; }
	virtual bool GetStateFlipped() { return isFlipped; }
	virtual void SetStateFlipped(bool state) { isFlipped = state; }
	virtual void Set_ay(float AY) {
		this->ay = AY;
	}
};