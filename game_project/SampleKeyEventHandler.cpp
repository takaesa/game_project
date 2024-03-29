#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"
#include "Mario.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();

	if (currentscene == SCENE_MAP_1_1)
	{
		switch (KeyCode)
		{
		case DIK_DOWN:
			mario->SetState(MARIO_STATE_SIT);
			if (mario->GetUsingPipeDirection() != 0)
			{
				if (mario->GetUsingPipeDirection() == 1)
					mario->SetState(MARIO_STATE_USE_PIPE_DOWN);
			}
			break;
		case DIK_UP:
			if (mario->GetUsingPipeDirection() != 0)
			{
				if (mario->GetUsingPipeDirection() == 2)
					mario->SetState(MARIO_STATE_USE_PIPE_UP);
			}
			break;
		case DIK_A:
			if (mario->GetLevel() == MARIO_LEVEL_TAIL)
			{
				mario->SetState(MARIO_STATE_HIT);
			}
			break;
		case DIK_S:
			if (mario->GetFlyingState() == true && mario->GetLevelRun() == 7)
				mario->SetState(MARIO_STATE_FLY);
			else if (mario->GetIsOnPlatform() == false && mario->GetLevel() == MARIO_LEVEL_TAIL)
				mario->SetState(MARIO_STATE_LANDING);
			else
				mario->SetState(MARIO_STATE_JUMP);
			break;
		case DIK_1:
			mario->SetLevel(MARIO_LEVEL_SMALL);
			break;
		case DIK_2:
			mario->SetLevel(MARIO_LEVEL_BIG);
			break;
		case DIK_3:
			mario->SetLevel(MARIO_LEVEL_TAIL);
			break;
		case DIK_0:
			mario->SetState(MARIO_STATE_DIE);
			break;
		case DIK_R: // reset
			//Reload();
			break;
		}
	}
	else if (currentscene == SCENE_WORLD_MAP)
	{
		switch (KeyCode)
		{
		case DIK_1:
			mario->SetLevel(MARIO_LEVEL_SMALL);
			break;
		case DIK_2:
			mario->SetLevel(MARIO_LEVEL_BIG);
			break;
		case DIK_3:
			mario->SetLevel(MARIO_LEVEL_TAIL);
			break;
		case DIK_O:
			CGame::GetInstance()->InitiateSwitchScene(5);
			break;
		case DIK_LEFT:
		{
			if (mario->GetisAllowLeft())
			{
				mario->SetState(MARIO_GO_LEFT);
			}
			break;
		}
		case DIK_RIGHT:
		{
			if (mario->GetisAllowRight())
			{
				mario->SetState(MARIO_GO_RIGHT);
			}
			break;
		}
		case DIK_UP:
		{
			if (mario->GetisAllowUp())
			{
				mario->SetState(MARIO_GO_UP);
			}
			break;
		}
		case DIK_DOWN:
		{
			if (mario->GetisAllowDown())
			{
				mario->SetState(MARIO_GO_DOWN);
			}
			break;
		}
		case DIK_S:
		{
			if (mario->GetState() == MARIO_SELECTSTAGE_STATE)
				CGame::GetInstance()->InitiateSwitchScene(5);
			break;
		}
		default:
			break;
		}
		}
	else if (currentscene == SCENE_INTRO)
	{
		switch (KeyCode)
		{
		case DIK_S:
			CGame::GetInstance()->InitiateSwitchScene(2);
			break;
		case DIK_LEFT:
		{
			if (mario->GetisAllowLeft())
			{
				mario->SetState(MARIO_GO_LEFT);
			}
			break;
		}
		case DIK_RIGHT:
		{
			if (mario->GetisAllowRight())
			{
				mario->SetState(MARIO_GO_RIGHT);
			}
			break;
		}
		case DIK_UP:
		{
			if (mario->GetisAllowUp())
			{
				mario->SetState(MARIO_GO_UP);
			}
			break;
		}
		case DIK_DOWN:
		{
			if (mario->GetisAllowDown())
			{
				mario->SetState(MARIO_GO_DOWN);
			}
			break;
		}
		default:
			break;
		}

		}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		mario->SetState(MARIO_STATE_CARRY_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int currentscene = CGame::GetInstance()->GetCurrentSceneNumber();
	if (currentscene == 5)
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{
			if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			else
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUNNING_LEFT);
			else
				mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_IDLE);
	}
}