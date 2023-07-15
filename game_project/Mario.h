#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "Koopa.h"
#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.15f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_LEVEL_RUN_SPEED 0.01f
#define MARIO_LEVEL_RUN_MAX 7

#define MARIO_FLY_Y	0.33f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f
#define MARIO_ATTACK_ZONE 8

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301
#define MARIO_STATE_FLY				302
#define MARIO_LANDING_SPEED	0.03f
#define MARIO_KICKABLE_TIME 100

#define MARIO_STATE_HIT 1200

#define MARIO_STATE_USE_PIPE_DOWN 1101
#define MARIO_STATE_USE_PIPE_UP 1102

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_CARRY_RELEASE	900
#define MARIO_P_TIME 4000

#define MARIO_FLY_SPEED 0.12f
#define MARIO_ACCEL_FLY_X 0.0003f
#define MARIO_STATE_LANDING 1100

#define MARIO_GO_LEFT				1001
#define MARIO_GO_RIGHT				1002
#define MARIO_GO_UP					1003
#define MARIO_GO_DOWN				1004
#define MARIO_WORLDMAP_SPEED		0.1f

#define MARIO_SELECTSTAGE_STATE		1005

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_MARIO_KICK_RIGHT 220
#define ID_ANI_MARIO_KICK_LEFT	221

#define ID_ANI_MARIO_CARRY_RIGHT_IDLE 340
#define ID_ANI_MARIO_CARRY_LEFT_IDLE 341

#define ID_ANI_MARIO_CARRY_RIGHT 330
#define ID_ANI_MARIO_CARRY_LEFT 331

#define ID_ANI_MARIO_USING_PIPE 950

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 1800
#define ID_ANI_MARIO_SMALL_KICK_LEFT 1801

#define ID_ANI_MARIO_SMALL_CARRY_RIGHT_IDLE 1710
#define ID_ANI_MARIO_SMALL_CARRY_LEFT_IDLE 1711

#define ID_ANI_MARIO_SMALL_CARRY_RIGHT 1700
#define ID_ANI_MARIO_SMALL_CARRY_LEFT 1701

#define ID_ANI_MARIO_SMALL_CHANGE_TO_MARIO_BIG_RIGHT 1810
#define ID_ANI_MARIO_SMALL_CHANGE_TO_MARIO_BIG_LEFT 1811

#define ID_ANI_MARIO_SMALL_USING_PIPE 1900

// TAIL MARIO
#define ID_ANI_MARIO_BIG_CHANGE_TO_MARIO_TAIL_RIGHT 2120
#define	ID_ANI_MARIO_BIG_CHANGE_TO_MARIO_TAIL_LEFT 2121

#define ID_ANI_MARIO_TAIL_JUMP_RUN_RIGHT 2600
#define ID_ANI_MARIO_TAIL_JUMP_RUN_LEFT 2601
#define ID_ANI_MARIO_TAIL_JUMP_WALK_LEFT 2501
#define ID_ANI_MARIO_TAIL_JUMP_WALK_RIGHT 2500
#define ID_ANI_MARIO_TAIL_SIT_RIGHT 2700
#define ID_ANI_MARIO_TAIL_SIT_LEFT 2701
#define ID_ANI_MARIO_TAIL_IDLE_RIGHT 2100
#define ID_ANI_MARIO_TAIL_IDLE_LEFT 2101	
#define ID_ANI_MARIO_TAIL_BRACE_RIGHT 2400
#define ID_ANI_MARIO_TAIL_RUNNING_RIGHT 2300
#define ID_ANI_MARIO_TAIL_WALKING_RIGHT 2200
#define ID_ANI_MARIO_TAIL_KICK_RIGHT 2900

#define ID_ANI_MARIO_TAIL_BRACE_LEFT 2401
#define ID_ANI_MARIO_TAIL_RUNNING_LEFT 2301
#define ID_ANI_MARIO_TAIL_WALKING_LEFT 2201
#define ID_ANI_MARIO_TAIL_KICK_LEFT 2901
#define ID_ANI_MARIO_TAIL_FLY_RIGHT 2620
#define ID_ANI_MARIO_TAIL_FLY_LEFT 2621

#define ID_ANI_MARIO_TAIL_USING_PIPE 2800

#define ID_ANI_TAIL_LANDING_RIGHT	27000
#define ID_ANI_TAIL_LANDING_LEFT	27001

#define ID_ANI_TAIL_HIT_RIGHT	330000
#define ID_ANI_TAIL_HIT_LEFT	330001

#define ID_ANI_TAIL_CARRY_RIGHT_IDLE	310000
#define ID_ANI_TAIL_CARRY_LEFT_IDLE	310001

#define ID_ANI_MARIO_TAIL_CARRY_RIGHT 320000
#define ID_ANI_MARIO_TAIL_CARRY_LEFT 320001

#pragma endregion

#define GROUND_Y 160.0f

#define ID_ANI_MARIO_SMALL_MINI 1161
#define ID_ANI_MARIO_BIG_MINI 1170
#define ID_ANI_MARIO_TANOOKI_MINI 1180
#define ID_ANI_MARIO_INTRO 2999

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TAIL	3
#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_TAIL_BBOX_WIDTH  14
#define MARIO_TAIL_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16
#define MARIO_TAIL_SITTING_BBOX_WIDTH  18
#define MARIO_TAIL_SITTING_BBOX_HEIGHT 16


#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500

#define SCENE_INTRO		1
#define SCENE_WORLD_MAP	2
#define SCENE_MAP_1_1	5
#define TIME_CLOCK 300

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN isUsingPipe;
	BOOLEAN isRunning;

	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	int kickable;
	int hittable;
	bool flyable = false;
	bool isChanging = false;
	int level_run;

	int time;
	ULONGLONG count_down_1_sec;

	//world map mario/////////
	bool isAllowLeft = 0;
	bool isAllowRight = 0;
	bool isAllowUp = 0;
	bool isAllowDown = 0;

	float startX = 0, startY = 0;
	bool isGoingNodeX = false;
	bool isGoingNodeY = false;
	//

	int usingPipeDirection = 0;
	float usingPipeDestination_X = 0;
	float usingPipeDestination_Y = 0;

	int live;
	int bonusItem[3] = { -1, -1, -1 };

	ULONGLONG untouchable_start;
	ULONGLONG kickable_start;
	ULONGLONG hittable_start;
	ULONGLONG change_start;
	ULONGLONG flyable_start;
	ULONGLONG henshin_start;
	ULONGLONG usingPipe_start;
	ULONGLONG start_prepare_run;
	ULONGLONG stop_level_run;
	ULONGLONG start_level_run;
	ULONGLONG restart_state;



	CKoopa* shell = NULL;
	bool isCarrying = false;
	bool isCarryingObject = false;
	bool isFlying = false;
	BOOLEAN isOnPlatform;
	int coin;
	int score;

	int card1;
	int card2;
	int card3;
	int cardCollected;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatform(LPCOLLISIONEVENT e);
	void OnCollisionWithDeadBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithMushRoom(LPCOLLISIONEVENT e);
	void OnCollisionWithPlain(LPCOLLISIONEVENT e);
	void OnCollisionWithBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithSpecialButton(LPCOLLISIONEVENT e);
	void OnCollisionWithTeleportPipe(LPCOLLISIONEVENT e);
	void OnCollisionWithNode(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdTail();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();

		live = 1;
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		kickable = 0;
		hittable = 0;
		kickable_start = -1;
		hittable_start = -1;
		change_start = -1;
		flyable_start = -1;
		henshin_start = -1;
		usingPipe_start = -1;

		level_run = 0;
		isRunning = false;
		start_level_run = -1;
		start_prepare_run = -1;
		stop_level_run = -1;
		count_down_1_sec = 0;
		restart_state = 0;

		if (currentscene == SCENE_WORLD_MAP)
		{
			isAllowRight = 1;
		}
		else if (currentscene == SCENE_INTRO)
		{
			isAllowDown = 1;
		}
		if (currentscene == SCENE_MAP_1_1)
			time = TIME_CLOCK;
		else
			time = TIME_CLOCK;

		untouchable_start = -1;
		isOnPlatform = false;
		isUsingPipe = false;
		coin = 12;
		score = 1000;

	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void SetKickable(int kick)
	{
		this->kickable = kick;
	}

	int IsCollidable()
	{
		if (isUsingPipe)
			return 0;
		if (state != MARIO_STATE_DIE)
			return 1;
		else if (state == MARIO_STATE_DIE)
			return 0;
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	int GetScore() { return score; }
	int GetCoin() { return this->coin; }
	int GetTime() { return time; }

	int GetLive() { return live; }

	int GetCard1() { return card1; }
	int GetCard2() { return card2; }
	int GetCard3() { return card3; }
	int GetCardCollected() { return cardCollected; }

	void SetisUsingPipe(bool isUsingPipe) { this->isUsingPipe = isUsingPipe; }
	int GetisUsingPipe() { return this->isUsingPipe; }
	int GetUsingPipeDirection() { return this->usingPipeDirection; }

	bool IsBrace() { return (ax * vx < 0); }

	void SetLevel(int l);
	int GetLevel() { return level; }

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartKickable() { kickable = 1; kickable_start = GetTickCount64(); }
	void StartHittable() { hittable = 1; hittable_start = GetTickCount64(); }
	void StartRunning() { isRunning = true; start_level_run = GetTickCount64(); }
	void StopRunning() { stop_level_run = GetTickCount64(); }
	void StartRestartState() { restart_state = GetTickCount64(); }
	void StartFlying() { isFlying = true; flyable_start = GetTickCount64(); ay = MARIO_GRAVITY/4; }

	int GetLevelRun() { return this->level_run; }

	bool GetCarryingState() { return isCarrying; }
	bool GetCarryingObject() { return isCarryingObject; }
	void SetCarryingObject(bool obj) { this->isCarryingObject = obj; }
	void SetCarryingState(bool a) { this->isCarrying = a; }

	bool GetFlyingState(){ return isFlying; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	BOOLEAN GetIsOnPlatform() { return isOnPlatform; }

	///world map mario
	bool GetisAllowLeft() { return isAllowLeft; }
	bool GetisAllowRight() { return isAllowRight; }
	bool GetisAllowUp() { return isAllowUp; }
	bool GetisAllowDown() { return isAllowDown; }

	void Go1NodeX(LPGAMEOBJECT gameobject);
	void Go1NodeY(LPGAMEOBJECT gameobject);

};