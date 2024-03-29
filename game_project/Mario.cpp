#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"

#include "Collision.h"
#include "Platform.h"

#include "Brick.h"
#include "Leaf.h"
#include "MushRoom.h"
#include "QuestionBrick.h"
#include "Special_Button.h"
#include "Plain.h"
#include "FireBullet.h"
#include "Koopa.h"
#include "DeadBlock.h"
#include "Effect.h"
#include "TeleportPipe.h"
#include "Node.h"
#include "HUD.h"
#include "RandomCard.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//DebugOutTitle(L"%d", state);
	int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();
	if (currentscene == SCENE_WORLD_MAP || currentscene == SCENE_INTRO)
	{
		if (isGoingNodeX == true)
		{
			if (vx * (x - startX) >= 0)
			{
				x = startX;
				vx = 0;
				vy = 0;
				isGoingNodeX = false;
			}
		}
		if (isGoingNodeY == true)
		{
			if (vy * (y - startY) >= 0)
			{
				y = startY;
				vx = 0;
				vy = 0;
				isGoingNodeY = false;
			}
		}
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
		return;
	}
	if (isChanging) // changing level so make mario can't moving
	{
		vx = 0;
		vy = 0;
	}
	else {
		vy += ay * dt;
		vx += ax * dt;
	}
	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - change_start > 600)
	{
		isChanging = false;
		change_start = 0;
	}
	if (kickable)
	{
		if (GetTickCount64() - kickable_start > 100)
		{
			kickable = 0;
			kickable_start = 0;
		}
	}
	// Hitting State
	if (GetTickCount64() - hittable_start > 500)
	{
		hittable = 0;
		hittable_start = -1;
	}
	//Using pipe
	if (isUsingPipe == true)
	{
		if (GetTickCount64() - usingPipe_start > 300)
		{
			if (usingPipeDirection == 2)
			{
				if (level != MARIO_LEVEL_SMALL)
					SetPosition(usingPipeDestination_X, usingPipeDestination_Y - 10);
				else
					SetPosition(usingPipeDestination_X, usingPipeDestination_Y);
			}
			else
				SetPosition(usingPipeDestination_X, usingPipeDestination_Y);

			if (GetTickCount64() - usingPipe_start > 600)
			{
				isUsingPipe = false;
				usingPipe_start = 0;
				usingPipeDestination_X = 0;
				usingPipeDestination_Y = 0;
				usingPipeDirection = 0;
				ay = MARIO_GRAVITY;
			}

		}
	}
	// start running
	if (GetTickCount64() - start_level_run > 500)
	{
		if (level_run < 7)
		{
			level_run++;
		}
	}
	// stop running
	if (GetTickCount64() - stop_level_run > 200)
	{
		if (level_run > 0)
		{
			level_run--;
		}
	}
	
	//flying
	if (GetTickCount64() - flyable_start > MARIO_P_TIME)
	{
		isFlying = false;
		flyable = false;
		flyable_start = -1;
	}
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	// henshin
	/*if (level == MARIO_LEVEL_TAIL && GetTickCount64() - henshin_start > 1000)
	{
		henshin_start = -1;
		vx = vy = 0;
	}*/
	if (shell != NULL && shell->GetState() == KOOPA_STATE_AWAKE)
	{
		isCarrying = false;
		isCarryingObject = false;
	}
		
	if (shell != NULL && shell->GetState() == KOOPA_STATE_CARRIED)
	{
		if (vx > 0)
		{
			shell->SetPosition(x + 16.0f, y - 1.0f);
			shell->SetDir(-1);
		}
		else if (vx < 0)
		{
			shell->SetPosition(x - 16.0f, y - 1.0f);
			shell->SetDir(1);
		}
		else
		{
			float koox, kooy;
			shell->GetPosition(koox, kooy);
			shell->SetPosition(koox, y - 1.0f);
		}
	}

	// Kick Shell
	if (GetTickCount64() - kickable_start > MARIO_KICKABLE_TIME)
	{
		kickable_start = 0;
		kickable = 0;
	}

	//Time
	if (time > 0/* && currentscene == SCENE_MAP_1_1*/)
	{
		if (!isChanging || state != MARIO_STATE_DIE)
		{
			if (GetTickCount64() - count_down_1_sec > 1000) // 1 second
			{
				time--;
				count_down_1_sec = GetTickCount64();
			}
		}
	}
	else
	{
		time = 0;
		SetState(MARIO_STATE_DIE);
	}

	//reset state
	if (GetTickCount64() - restart_state > 10000)
	{
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
		vector<LPGAMEOBJECT> objects = thisscene->GetListObjects();
		for (int i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<CBrick*>(objects[i]))
			{
				if (objects[i]->GetState() == BRICK_STATE_GOLD)
					objects[i]->SetState(BRICK_STATE_BLINK);
			}
		}
	}
	
	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();
	if (currentscene == SCENE_MAP_1_1)
	{
		if (e->ny != 0 && e->obj->IsBlocking())
		{
			vy = 0;
			if (e->ny < 0) isOnPlatform = true;
		}
		else
			if (e->nx != 0 && e->obj->IsBlocking())
			{
				vx = 0;
			}
		if (dynamic_cast<CGoomba*>(e->obj))
			OnCollisionWithGoomba(e);
		else if (dynamic_cast<CCoin*>(e->obj))
			OnCollisionWithCoin(e);
		else if (dynamic_cast<CPortal*>(e->obj))
			OnCollisionWithPortal(e);
		else if (dynamic_cast<CBrick*>(e->obj))
			OnCollisionWithBrick(e);
		else if (dynamic_cast<CLeaf*>(e->obj))
			OnCollisionWithLeaf(e);
		else if (dynamic_cast<CMushRoom*>(e->obj))
			OnCollisionWithMushRoom(e);
		else if (dynamic_cast<CQuestionBrick*>(e->obj))
			OnCollisionWithQuestionBrick(e);
		else if (dynamic_cast<CPlain*>(e->obj))
			OnCollisionWithPlain(e);
		else if (dynamic_cast<CBullet*>(e->obj))
			OnCollisionWithBullet(e);
		else if (dynamic_cast<CKoopa*>(e->obj))
			OnCollisionWithKoopa(e);
		else if (dynamic_cast<CSpecial_Button*>(e->obj))
			OnCollisionWithSpecialButton(e);
		else if (dynamic_cast<CDeadBlock*>(e->obj))
			OnCollisionWithDeadBlock(e);
		else if (dynamic_cast<CTeleportPipe*>(e->obj))
			OnCollisionWithTeleportPipe(e);
		else if (dynamic_cast<CRandomCard*>(e->obj))
			OnCollisionWithRandomCard(e);
	}
	else if (currentscene == SCENE_WORLD_MAP || currentscene == SCENE_INTRO)
	{
		if (e->obj->IsBlocking()) {
			vx = 0;
			vy = 0;
		}
		if (dynamic_cast<CNode*>(e->obj))
			OnCollisionWithNode(e);
	}
}
void CMario::OnCollisionWithRandomCard(LPCOLLISIONEVENT e)
{
	CRandomCard* randomcard = dynamic_cast<CRandomCard*>(e->obj);
	if (e->ny > 0)
	{
		int cardState = randomcard->GetState();
		SetState(MARIO_END_MAP_STATE);
		/*cardblock->SetisHit(true);
		if (card_1 == 0)
		{
			if (cardState == CARD_FLOWER_STATE)
			{
				card_1 = TYPE_CARD_FLOWER;
				dataGame->SetCard_1(card_1);
			}
			else if (cardState == CARD_MUSHROOM_STATE)
			{
				card_1 = TYPE_CARD_MUSHROOM;
				dataGame->SetCard_1(card_1);
			}
			else if (cardState == CARD_STAR_STATE)
			{
				card_1 = TYPE_CARD_STAR;
				dataGame->SetCard_1(card_1);
			}
		}
		else if (card_2 == 0)
		{
			if (cardState == CARD_FLOWER_STATE)
			{
				card_2 = TYPE_CARD_FLOWER;
				dataGame->SetCard_2(card_2);
			}
			else if (cardState == CARD_MUSHROOM_STATE)
			{
				card_2 = TYPE_CARD_MUSHROOM;
				dataGame->SetCard_2(card_2);
			}
			else if (cardState == CARD_STAR_STATE)
			{
				card_2 = TYPE_CARD_STAR;
				dataGame->SetCard_2(card_2);
			}
		}
		else if (card_3 == 0)
		{
			if (cardState == CARD_FLOWER_STATE)
			{
				card_3 = TYPE_CARD_FLOWER;
				dataGame->SetCard_3(card_3);
			}
			else if (cardState == CARD_MUSHROOM_STATE)
			{
				card_3 = TYPE_CARD_MUSHROOM;
				dataGame->SetCard_3(card_3);
			}
			else if (cardState == CARD_STAR_STATE)
			{
				card_3 = TYPE_CARD_STAR;
				dataGame->SetCard_3(card_3);
			}
		}
		if (cardState == CARD_FLOWER_STATE)
		{
			disPlaycard = TYPE_CARD_FLOWER;
		}
		else if (cardState == CARD_MUSHROOM_STATE)
		{
			disPlaycard = TYPE_CARD_MUSHROOM;
		}
		else if (cardState == CARD_STAR_STATE)
		{
			disPlaycard = TYPE_CARD_STAR;
		}*/
	}
}
void CMario::OnCollisionWithNode(LPCOLLISIONEVENT e)
{
	CNode* node = dynamic_cast<CNode*>(e->obj);
	isAllowLeft = node->GetAllowLeft();
	isAllowRight = node->GetAllowRight();
	isAllowUp = node->GetAllowUp();
	isAllowDown = node->GetAllowDown();
	if (e->nx != 0) {
		Go1NodeX(node);
	}
	if (e->ny != 0) {
		Go1NodeY(node);
	}
	if (node->GetType() == 2)
	{
		SetState(MARIO_SELECTSTAGE_STATE);
	}
}

void CMario::Go1NodeX(LPGAMEOBJECT gameobject) {
	float tempY;
	gameobject->GetPosition(startX, tempY);
	isGoingNodeX = true;
}
void CMario::Go1NodeY(LPGAMEOBJECT gameobject) {
	float tempX;
	gameobject->GetPosition(tempX, startY);
	isGoingNodeY = true;
}

void CMario::OnCollisionWithTeleportPipe(LPCOLLISIONEVENT e)
{
	CTeleportPipe* pipe = (CTeleportPipe*)e->obj;
	usingPipeDirection = pipe->GetDirect();
	usingPipeDestination_X = pipe->GetdesX();
	usingPipeDestination_Y = pipe->GetdesY();
}

void CMario::OnCollisionWithDeadBlock(LPCOLLISIONEVENT e)
{
	CDeadBlock* deadblock = dynamic_cast<CDeadBlock*>(e->obj);

	if (e->ny < 0)
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
	}
}
void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	float goox, gooy;
	goomba->GetPosition(goox, gooy);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{

		if (goomba->GetState() == GOOMBA_STATE_WALKING&& goomba->GetType() == 1)
		{
			goomba->SetType(0);
			goomba->Set_ay(MARIO_GRAVITY);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (goomba->GetState() == GOOMBA_STATE_WALKING && goomba->GetType()==0)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
			CEffect* effect = new CEffect(goox , gooy, 2000);
			thisscene->AddObjectToScene(effect);
			score += 2000;
		}
	}
	else // hit by Goomba
	{
		if (hittable == 1)
		{
			if (e->nx < 0 && nx > 0)
				goomba->SetState(GOOMBA_STATE_FLIPPED);
			else if (e->nx > 0 && nx < 0)
				goomba->SetState(GOOMBA_STATE_FLIPPED);
		}
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = level - 1;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	shell = koopa;
	float koox, kooy;
	koopa->GetPosition(koox, kooy);

	// Jump on top >> Koopa turns into shell and Mario deflects a bit 
	if (e->ny < 0)
	{
		if (koopa->GetType() == 1)
		{
			koopa->SetType(0);
			koopa->Set_ay(MARIO_GRAVITY);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			koopa->SetPosition(koox, kooy - 5);
			
		}
		else if (koopa->GetState() != KOOPA_STATE_SHELL && koopa->GetType() != 1)// When Koopa is in turtle form
		{
			koopa->SetState(KOOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
			CEffect* effect = new CEffect(koox, kooy, 4000);
			thisscene->AddObjectToScene(effect);
			score += 4000;
		}
		else if (koopa->GetState() == KOOPA_STATE_SHELL)// When Koopa is in shell form
		{
			float koox, kooy;
			koopa->GetPosition(koox, kooy);
			koopa->SetPosition(koox, kooy - 5);
			if (this->x < koox)
			{
				koopa->SetDir(-1);
				StartKickable();
			}
			else
			{
				koopa->SetDir(1);
				StartKickable();
			}

			koopa->SetState(KOOPA_STATE_SHELL_MOVING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopa->GetState() == KOOPA_STATE_SHELL_MOVING)	// When Koopa is in shell form and moving
		{
			koopa->SetState(KOOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // Collide X with Koopa
	{
		if (hittable == 1)
		{
			if (e->nx < 0 && nx > 0)
			{
				koopa->SetStateFlipped(true);
				koopa->SetState(KOOPA_STATE_SHELL);
				LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
				CEffect* effect = new CEffect(koox, kooy, 4000);
				thisscene->AddObjectToScene(effect);
				score += 4000;
			}
			else if (e->nx > 0 && nx < 0)
			{
				koopa->SetStateFlipped(true);
				koopa->SetState(KOOPA_STATE_SHELL);
				LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
				CEffect* effect = new CEffect(koox, kooy, 4000);
				thisscene->AddObjectToScene(effect);
				score += 4000;
			}
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
			/*CEffect* effect = new CEffect(x + 10, y, KOOPA_SCORE);
			thisscene->AddObjectToScene(effect);
			score += KOOPA_SCORE;*/

		}
		else if (koopa->GetState() == KOOPA_STATE_SHELL || koopa->GetState() == KOOPA_STATE_SHELL + 1 || koopa->GetState() == KOOPA_STATE_CARRIED)
		{
			if (abs(ax) == abs(MARIO_ACCEL_RUN_X))
			{
				isCarrying = true;
				//SetCarryingObject(true);
				koopa->SetState(KOOPA_STATE_CARRIED);
				SetKickable(0);
			}
			else if (abs(ax) == abs(MARIO_ACCEL_WALK_X))
			{
				StartKickable();
				float koox, kooy;
				koopa->GetPosition(koox, kooy);
				koopa->SetPosition(koox, kooy - 5);
				if (e->nx < 0)
					koopa->SetDir(-1);
				else
					koopa->SetDir(1);

				koopa->SetState(KOOPA_STATE_SHELL_MOVING);
				SetKickable(0);
			}
			SetCarryingObject(false);
		}
		else if (untouchable == 0)
		{
			if (koopa->GetState() != KOOPA_STATE_SHELL && koopa->GetState() != KOOPA_STATE_SHELL + 1
				&& kickable != 1 && koopa->GetState() != KOOPA_STATE_CARRIED)
			{
				if (level == MARIO_LEVEL_TAIL)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	CCoin* newcoin = dynamic_cast<CCoin*>(e->obj);
	float cx, cy;
	newcoin->GetPosition(cx, cy);
	e->obj->Delete();
	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
	CEffect* effect = new CEffect(cx , cy, 100);
	thisscene->AddObjectToScene(effect);
	coin++;
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	float lx, ly;
	leaf->GetPosition(lx, ly);
	if (level == MARIO_LEVEL_BIG)
	{
		y = y - Push_Up_Platform * 2;
		//henshin_start = GetTickCount64();
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
		CEffect* effect = new CEffect(lx , ly, 4000);
		CEffect* henshin = new CEffect(x, y-5, 0);
		thisscene->AddObjectToScene(effect);
		//thisscene->AddObjectToScene(henshin);
		SetLevel(MARIO_LEVEL_TAIL);
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		y = y - Push_Up_Platform * 2;
		//henshin_start = GetTickCount64();
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
		CEffect* effect = new CEffect(lx, ly, 4000);
		CEffect* henshin = new CEffect(x, y - 5, 0);
		thisscene->AddObjectToScene(effect);
		//thisscene->AddObjectToScene(henshin);
		SetLevel(MARIO_LEVEL_BIG);
	}
	else if (level == MARIO_LEVEL_TAIL)
	{
		//henshin_start = GetTickCount64();
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
		CEffect* effect = new CEffect(lx, ly, 4000);
		CEffect* henshin = new CEffect(x, y - 5, 0);
		thisscene->AddObjectToScene(effect);
		//thisscene->AddObjectToScene(henshin);
	}
	leaf->Delete();
}

void CMario::OnCollisionWithMushRoom(LPCOLLISIONEVENT e)
{
	CMushRoom* objmushroom = dynamic_cast<CMushRoom*>(e->obj);
	float mx, my;
	objmushroom->GetPosition(mx, my);
	y = y - Push_Up_Platform * 2;
	if (objmushroom->Gettype() == 0)
	{
		if (level == MARIO_LEVEL_SMALL)
		{
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
			CEffect* effect = new CEffect(mx, my, 2000);
			CEffect* henshin = new CEffect(x + 10, y, 0);
			thisscene->AddObjectToScene(effect);
			//thisscene->AddObjectToScene(henshin);
			SetLevel(MARIO_LEVEL_BIG);
		}
	}
	else if (objmushroom->Gettype() == 1)
	{
		live++;
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
		CEffect* effect = new CEffect(mx, my, 2);
		thisscene->AddObjectToScene(effect);
	}
	e->obj->Delete();

}

void CMario::OnCollisionWithSpecialButton(LPCOLLISIONEVENT e)
{
	CSpecial_Button* special_button = dynamic_cast<CSpecial_Button*>(e->obj);
	//LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

	if (e->ny < 0 && special_button->GetPressable() == true)
	{
		special_button->SetPressable(false);
		special_button->SetState(SPECIAL_P_STATE_PRESSED);
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		StartRestartState();
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);

	switch (platform->getType())
	{
	case 3:
		if (isSitting && e->ny < 0)
			platform->SetState(PLATFORM_PASSABLE);
		break;
	case 1:
		if (e->ny < 0)
		{
			y -= Push_Up_Platform;
			platform->SetState(-1);
		}
		else
		{
			platform->SetState(PLATFORM_PASSABLE);
		}
		break;
	case 2:
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
		break;
	}
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	float bx, by;
	brick->GetPosition(bx, by);

	if ((e->nx != 0 && hittable == 1 && (y - by <= MARIO_ATTACK_ZONE)) || e->ny > 0)
	{
		/*CBrickPiece* leftp1 = new CBrickPiece(bx - PIECE_X_OFFSET, by - PIECE_Y_OFFSET, 0);
		CBrickPiece* leftp2 = new CBrickPiece(bx - PIECE_X_OFFSET, by + PIECE_Y_OFFSET, 0);
		CBrickPiece* rightp1 = new CBrickPiece(bx + PIECE_X_OFFSET, by - PIECE_Y_OFFSET, 1);
		CBrickPiece* rightp2 = new CBrickPiece(bx + PIECE_X_OFFSET, by + PIECE_Y_OFFSET, 1);

		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

		thisscene->AddNewObject(leftp1);
		thisscene->AddNewObject(leftp2);
		thisscene->AddNewObject(rightp1);
		thisscene->AddNewObject(rightp2);

		if (objbrick->GetType() == 1)
		{
			CQuestionBlock* qblock = new CQuestionBlock(bx, by, 0);
			qblock->SetHasItem(false);
			CButton* btn = new CButton(bx, by - BUTTON_WIDTH);

			thisscene->AddNewObject(qblock);
			thisscene->AddNewObject(btn);
		}*/

		brick->Delete();
		hittable = -1;
	}
}
void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionbrick = dynamic_cast<CQuestionBrick*>(e->obj);
	
	if (e->ny > 0 && questionbrick->IsEmpty() == false || hittable == 1 && questionbrick->IsEmpty() == false)
	{
		if (questionbrick->GetBrickType() == 0) // coin
		{
			questionbrick->SetEmpty(true);
			float bx, by;
			questionbrick->GetPosition(bx, by);

			CCoin* coin = new CCoin(bx, by - 2*COIN_WIDTH, 1);
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

			thisscene->AddObjectToScene(coin);

			coin->SetFly(true);
			questionbrick->SetPosition(bx, by);

			CEffect* effect = new CEffect(bx, by, 100);
			thisscene->AddObjectToScene(effect);
			coin++;
			
			/*CGame::GetInstance()->GetCurrentScene()->SetCoin(coin);*/
		}
		else if (questionbrick->GetBrickType() == 1) // mushroom
		{
			questionbrick->SetEmpty(true);
			float bx, by;
			questionbrick->GetPosition(bx, by);

			CQuestionBrick* newQuestionBrick = new CQuestionBrick(bx, by, 0);
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
			

			questionbrick->Delete();
			newQuestionBrick->SetPosition(bx, by);

			CMushRoom* mushroom = new CMushRoom(bx, by-32, 0);
			newQuestionBrick->SetEmpty(true);

			thisscene->AddObjectToScene(mushroom);
			thisscene->AddObjectToScene(newQuestionBrick);
		}
		else if (questionbrick->GetBrickType() == 2) //leaf
		{
			if (level == MARIO_LEVEL_SMALL)
			{
				questionbrick->SetEmpty(true);
				float bx, by;
				questionbrick->GetPosition(bx, by);

				CQuestionBrick* newQuestionBrick = new CQuestionBrick(bx, by, 0);
				LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();


				questionbrick->Delete();
				newQuestionBrick->SetPosition(bx, by);

				CMushRoom* mushroom = new CMushRoom(bx, by - 32);
				newQuestionBrick->SetEmpty(true);

				thisscene->AddObjectToScene(mushroom);
				thisscene->AddObjectToScene(newQuestionBrick);
			}
			else {
				questionbrick->SetEmpty(true);
				float bx, by;
				questionbrick->GetPosition(bx, by);

				LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
				CQuestionBrick* newQuesttionBrick = new CQuestionBrick(bx, by);

				questionbrick->Delete();
				newQuesttionBrick->SetPosition(bx, by);

				CLeaf* leaf = new CLeaf(bx + 16, by - 32);
				newQuesttionBrick->SetEmpty(true);

				thisscene->AddObjectToScene(leaf);
				thisscene->AddObjectToScene(newQuesttionBrick);
			}
		}
		else if (questionbrick->GetBrickType() == 4)		//LIFE_UP
		{
			questionbrick->SetEmpty(true);
			float bx, by;
			questionbrick->GetPosition(bx, by);

			CQuestionBrick* newQuestionBrick = new CQuestionBrick(bx, by, 0);
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

			questionbrick->Delete();
			newQuestionBrick->SetPosition(bx, by);

			CMushRoom* mushroom = new CMushRoom(bx, by - 32, 1);
			newQuestionBrick->SetEmpty(true);

			thisscene->AddObjectToScene(mushroom);
			thisscene->AddObjectToScene(newQuestionBrick);
		}
	}
}

void CMario::OnCollisionWithPlain(LPCOLLISIONEVENT e)
{
	CPlain* objplain = dynamic_cast<CPlain*>(e->obj);
	float px, py;
	objplain->GetPosition(px, py);

	if (hittable == 1)
	{
		if (e->nx < 0 && nx > 0)
		{
			objplain->Delete();
		}
		else if (e->nx > 0 && nx < 0)
		{
			objplain->Delete();
		}
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
		CEffect* score = new CEffect(px, py, 4000);
		CEffect* effect = new CEffect(px, py, 0);
		thisscene->AddObjectToScene(effect);
		thisscene->AddObjectToScene(score);
		score+= 4000;
	}
	else if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_TAIL)
			level = MARIO_LEVEL_BIG;
		else if (level == MARIO_LEVEL_BIG)
			level = MARIO_LEVEL_SMALL;
		else
			SetState(MARIO_STATE_DIE);

		StartUntouchable();
	}
}

void CMario::OnCollisionWithBullet(LPCOLLISIONEVENT e)
{
	CBullet* bullet = dynamic_cast<CBullet*>(e->obj);

	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_TAIL)
			level = MARIO_LEVEL_BIG;
		else if (level == MARIO_LEVEL_BIG)
			level = MARIO_LEVEL_SMALL;
		else
			SetState(MARIO_STATE_DIE);

		StartUntouchable();
	}

	bullet->Delete();
}


//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isChanging)
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
			}
		}
		else if (kickable == 1)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
		}
		else if (isUsingPipe)
		{
			aniId = ID_ANI_MARIO_SMALL_USING_PIPE;
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_SIT_LEFT;
			}
			else
				if (vx == 0)
				{
					if (isCarrying == false)
					{
						if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
						else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
					}
					else
					{
						if (nx > 0) aniId = ID_ANI_MARIO_SMALL_CARRY_RIGHT_IDLE;
						else aniId = ID_ANI_MARIO_SMALL_CARRY_LEFT_IDLE;
					}
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X && isCarrying == true)
						aniId = ID_ANI_MARIO_SMALL_CARRY_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X && vx == maxVx)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X || vx != maxVx)
					{
						if (kickable == 1)
							aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
						else
							aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
					}
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X && isCarrying == true)
						aniId = ID_ANI_MARIO_SMALL_CARRY_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X && abs(vx) == abs(maxVx))
						aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X || vx != -maxVx)
					{
						if (kickable == 1)
							aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
						else
							aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
					}
				}
	}
	

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isChanging)
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
		}
		else if (kickable == 1)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_KICK_LEFT;
		}
		else if (isUsingPipe)
		{
			aniId = ID_ANI_MARIO_USING_PIPE;
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_SIT_LEFT;
			}
			else if (kickable == 1)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_KICK_RIGHT;
				else
					aniId = ID_ANI_MARIO_KICK_LEFT;
			}
			else
				if (vx == 0)
				{
					if (isCarrying == false)
					{
						if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
						else aniId = ID_ANI_MARIO_IDLE_LEFT;
					}
					else
					{
						if (nx > 0) aniId = ID_ANI_MARIO_CARRY_RIGHT_IDLE;
						else aniId = ID_ANI_MARIO_CARRY_LEFT_IDLE;
					}
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X && isCarrying == true)
						aniId = ID_ANI_MARIO_CARRY_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X && vx == maxVx)
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X || vx != maxVx)
					{
						if (kickable == 1)
							aniId = ID_ANI_MARIO_KICK_RIGHT;
						else
							aniId = ID_ANI_MARIO_WALKING_RIGHT;
					}
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X && isCarrying == true)
						aniId = ID_ANI_MARIO_CARRY_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X && abs(vx) == abs(maxVx))
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X || vx != -maxVx)
					{
						if (kickable == 1)
							aniId = ID_ANI_MARIO_KICK_LEFT;
						else
							aniId = ID_ANI_MARIO_WALKING_LEFT;
					}
				}
	}
	else
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_SMALL_CHANGE_TO_MARIO_BIG_RIGHT;
		else
			aniId = ID_ANI_MARIO_SMALL_CHANGE_TO_MARIO_BIG_LEFT;
	}
	
	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdTail()
{
	int aniId = -1;
	if (!isChanging)
	{
		if (!isOnPlatform)
		{
			if (isFlying)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_TAIL_FLY_RIGHT;
				else
					aniId = ID_ANI_MARIO_TAIL_FLY_LEFT;
			}
			else if (abs(ax) == MARIO_ACCEL_RUN_X || vx != 0.0f)
			{
				if (nx > 0)
					aniId = ID_ANI_TAIL_LANDING_RIGHT;
				else
					aniId = ID_ANI_TAIL_LANDING_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_TAIL_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_TAIL_JUMP_WALK_LEFT;
			}
		}
		else if (kickable == 1)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_TAIL_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_TAIL_KICK_LEFT;
		}
		else if (isUsingPipe)
		{
			aniId = ID_ANI_MARIO_TAIL_USING_PIPE;
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_TAIL_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_TAIL_SIT_LEFT;
			}
			else
				if (vx == 0)
				{
					if (hittable)
					{
						if (nx > 0) aniId = ID_ANI_TAIL_HIT_RIGHT;
						else aniId = ID_ANI_TAIL_HIT_LEFT;
					}
					else if (isCarrying == false)
					{
						if (nx > 0) aniId = ID_ANI_MARIO_TAIL_IDLE_RIGHT;
						else aniId = ID_ANI_MARIO_TAIL_IDLE_LEFT;
					}
					else
					{
						if (nx > 0) aniId = ID_ANI_TAIL_CARRY_RIGHT_IDLE;
						else aniId = ID_ANI_TAIL_CARRY_LEFT_IDLE;
					}
				}
				else if (vx > 0)
				{
					if (hittable)
					{
						if (nx > 0) aniId = ID_ANI_TAIL_HIT_RIGHT;
						else aniId = ID_ANI_TAIL_HIT_LEFT;
					}
					else if (ax < 0)
						aniId = ID_ANI_MARIO_TAIL_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X && isCarrying == true)
						aniId = ID_ANI_MARIO_TAIL_CARRY_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X && vx == maxVx)
						aniId = ID_ANI_MARIO_TAIL_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X || vx != maxVx)
					{
						if (kickable)
							aniId = ID_ANI_MARIO_TAIL_KICK_RIGHT;
						else
							aniId = ID_ANI_MARIO_TAIL_WALKING_RIGHT;
					}
				}
				else // vx < 0
				{
					if (hittable)
					{
						if (nx > 0) aniId = ID_ANI_TAIL_HIT_RIGHT;
						else aniId = ID_ANI_TAIL_HIT_LEFT;
					}
					else if (ax > 0)
						aniId = ID_ANI_MARIO_TAIL_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X && isCarrying == true)
						aniId = ID_ANI_MARIO_TAIL_CARRY_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X && abs(vx) == abs(maxVx))
						aniId = ID_ANI_MARIO_TAIL_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X || vx != -maxVx)
					{
						if (kickable)
							aniId = ID_ANI_MARIO_TAIL_KICK_LEFT;
						else
							aniId = ID_ANI_MARIO_TAIL_WALKING_LEFT;
					}
				}
	}
	else
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_BIG_CHANGE_TO_MARIO_TAIL_RIGHT;
		else
			aniId = ID_ANI_MARIO_BIG_CHANGE_TO_MARIO_TAIL_LEFT;
	}
	
	if (aniId == -1) aniId = ID_ANI_MARIO_TAIL_IDLE_RIGHT;

	return aniId;
}


void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();
	if (currentscene == SCENE_MAP_1_1)
	{
		if (state == MARIO_STATE_DIE)
			aniId = ID_ANI_MARIO_DIE;
		else if (level == MARIO_LEVEL_BIG)
			aniId = GetAniIdBig();
		else if (level == MARIO_LEVEL_SMALL)
			aniId = GetAniIdSmall();
		else if (level == MARIO_LEVEL_TAIL)
			aniId = GetAniIdTail();
		if (!untouchable)
		{
			animations->Get(aniId)->Render(x, y);
		}
		else if (untouchable)
		{
			int check = rand() % 2;
			if (check == 0)
			{
				animations->Get(aniId)->Render(x, y);
			}
	}
	else if (currentscene == SCENE_WORLD_MAP)
	{
		//if (level == MARIO_LEVEL_SMALL)
			aniId = ID_ANI_MARIO_SMALL_MINI;
		/*else if (level == MARIO_LEVEL_BIG)
			aniId = ID_ANI_MARIO_BIG_MINI;
		else if (level == MARIO_LEVEL_TAIL)
			aniId = ID_ANI_MARIO_TANOOKI_MINI;*/

		animations->Get(aniId)->Render(x, y);
	}
	else if (currentscene == SCENE_INTRO)
	{
		aniId = ID_ANI_MARIO_INTRO;
		animations->Get(aniId)->Render(x, y);
	}
	
	}
	RenderBoundingBox();
	
	//DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_END_MAP_STATE)return;
	int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();
	if (currentscene == SCENE_MAP_1_1)
	{
		if (this->state == MARIO_STATE_DIE && live > 0)
		{
			SetPosition(15, 150);
			live--;
			level = MARIO_LEVEL_SMALL;
		}
		else if (this->state == MARIO_STATE_DIE && live == 0) return;

		switch (state)
		{
		case MARIO_END_MAP_STATE:
		{
			maxVx = MARIO_WALKING_SPEED;
			ax = MARIO_ACCEL_WALK_X;
			nx = 1;
			isRunning = false;

			break;
		}
		case MARIO_STATE_USE_PIPE_DOWN:
			ay = MARIO_GRAVITY / 6;
			isUsingPipe = true;
			usingPipe_start = GetTickCount64();
			break;
		case MARIO_STATE_USE_PIPE_UP:
			ay = MARIO_GRAVITY;
			vy = -MARIO_JUMP_SPEED_Y;
			isUsingPipe = true;
			usingPipe_start = GetTickCount64();
			break;
		case MARIO_STATE_HIT:
			if (level == MARIO_LEVEL_TAIL && hittable_start == -1)
				StartHittable();
			break;
		case MARIO_STATE_CARRY_RELEASE:
			if (isCarrying == true)
			{
				isCarrying = false;
				shell->SetState(KOOPA_STATE_SHELL_MOVING);
			}
			break;
		case MARIO_STATE_RUNNING_RIGHT:
			if (isSitting) break;
			StopRunning();
			if (isFlying && !isOnPlatform && flyable)
				maxVx = MARIO_FLY_SPEED;
			else if (isCarrying)
				maxVx = MARIO_RUNNING_SPEED;
			else if (isOnPlatform)
				maxVx = MARIO_RUNNING_SPEED;

			if (vx < 0)
				ax = MARIO_ACCEL_RUN_X * 3;
			else if (isFlying == true && !isOnPlatform && flyable)
				ax = MARIO_ACCEL_FLY_X;
			else if (isOnPlatform)
				ax = MARIO_ACCEL_RUN_X;

			nx = 1;
			break;
		case MARIO_STATE_RUNNING_LEFT:
			if (isSitting) break;
			StopRunning();
			if (isFlying && !isOnPlatform && flyable)
				maxVx = -MARIO_FLY_SPEED;
			else if (isCarrying)
				maxVx = -MARIO_RUNNING_SPEED;
			else if (isOnPlatform)
				maxVx = -MARIO_RUNNING_SPEED;

			if (vx > 0)
				ax = -MARIO_ACCEL_RUN_X * 3;
			else if (isFlying == true && !isOnPlatform && flyable)
				ax = -MARIO_ACCEL_FLY_X;
			else if (isOnPlatform)
				ax = -MARIO_ACCEL_RUN_X;
			nx = -1;
			break;
		case MARIO_STATE_WALKING_RIGHT:
			if (isSitting) break;
			StartRunning();
			maxVx = MARIO_WALKING_SPEED;
			ax = MARIO_ACCEL_WALK_X;
			nx = 1;
			break;
		case MARIO_STATE_WALKING_LEFT:
			if (isSitting) break;
			StartRunning();
			maxVx = -MARIO_WALKING_SPEED;
			ax = -MARIO_ACCEL_WALK_X;
			nx = -1;
			break;
		case MARIO_STATE_LANDING:
			vy = -MARIO_LANDING_SPEED / 2;
			break;
		case MARIO_STATE_FLY:
			if (isFlying)
				vy = -(2 * MARIO_JUMP_SPEED_Y / 3);
			flyable = true;
			break;
		case MARIO_STATE_JUMP:
			if (isSitting) break;
			if (isOnPlatform)
			{
				if (abs(vx) == abs(MARIO_RUNNING_SPEED) && level == MARIO_LEVEL_TAIL && level_run == 7)
				{
					StartFlying();
					vy = -MARIO_JUMP_SPEED_Y;
				}
				else if (abs(this->vx) == MARIO_RUNNING_SPEED)
					vy = -MARIO_JUMP_RUN_SPEED_Y;
				else
					vy = -MARIO_JUMP_SPEED_Y;
			}
			break;

		case MARIO_STATE_RELEASE_JUMP:
			if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
			break;

		case MARIO_STATE_SIT:
			if (isOnPlatform && level != MARIO_LEVEL_SMALL)
			{
				state = MARIO_STATE_IDLE;
				isSitting = true;
				vx = 0; vy = 0.0f;
				y += MARIO_SIT_HEIGHT_ADJUST;
			}
			break;

		case MARIO_STATE_SIT_RELEASE:
			if (isSitting)
			{
				isSitting = false;
				state = MARIO_STATE_IDLE;
				y -= MARIO_SIT_HEIGHT_ADJUST;
			}
			break;

		case MARIO_STATE_IDLE:
			StartRunning();
			ax = 0.0f;
			vx = 0.0f;
			ay = MARIO_GRAVITY;
			break;

		case MARIO_STATE_DIE:
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			vx = 0;
			ax = 0;
			break;
		}

	}
	else if (currentscene == SCENE_WORLD_MAP)
	{
		switch (state)
		{
		case MARIO_GO_LEFT:
		{
			vy = 0.0f;
			vx = -MARIO_WORLDMAP_SPEED;
			break;
		}
		case MARIO_GO_RIGHT:
		{
			vy = 0.0f;
			vx = MARIO_WORLDMAP_SPEED;
			break;
		}
		case MARIO_GO_UP:
		{
			vx = 0.0f;
			vy = -MARIO_WORLDMAP_SPEED;
			break;
		}case MARIO_GO_DOWN:
		{
			vx = 0.0f;
			vy = MARIO_WORLDMAP_SPEED;
			break;
		}
		default:
			break;
		}
	}
	else if (currentscene == SCENE_INTRO)
	{
		switch (state)
		{
		case MARIO_GO_LEFT:
		{
			vy = 0.0f;
			vx = -MARIO_WORLDMAP_SPEED;
			break;
		}
		case MARIO_GO_RIGHT:
		{
			vy = 0.0f;
			vx = MARIO_WORLDMAP_SPEED;
			break;
		}
		case MARIO_GO_UP:
		{
			vx = 0.0f;
			vy = -MARIO_WORLDMAP_SPEED;
			break;
		}case MARIO_GO_DOWN:
		{
			vx = 0.0f;
			vy = MARIO_WORLDMAP_SPEED;
			break;
		}
		default:
			break;
		}
	}

	

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_TAIL)
	{
		if (isSitting)
		{
			left = x - MARIO_TAIL_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_TAIL_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_TAIL_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_TAIL_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_TAIL_BBOX_WIDTH / 2;
			top = y - MARIO_TAIL_BBOX_HEIGHT / 2;
			right = left + MARIO_TAIL_BBOX_WIDTH;
			bottom = top + MARIO_TAIL_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}

}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= 10;
	}
	else if (this->level == MARIO_LEVEL_BIG)
	{
		y -= 10;
	}else if (this->level == MARIO_LEVEL_TAIL)
	{
		y -= 10;
	}
	isChanging = true;
	change_start = GetTickCount64();
	level = l;
	
}

