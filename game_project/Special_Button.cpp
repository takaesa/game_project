#include "Special_Button.h"
#include "debug.h"
#include"PlayScene.h"

void CSpecial_Button::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(pressable == true)
		animations->Get(ID_ANI_SPECIAL_P)->Render(x, y);
	else if(pressable == false)
		animations->Get(ID_ANI_SPECIAL_P_PRESSED)->Render(x, y+5);
	RenderBoundingBox();
}

void CSpecial_Button::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == SPECIAL_P_STATE_NORMAL)
	{
		l = x - SPECIAL_P_BBOX_WIDTH / 2;
		t = y - SPECIAL_P_BBOX_HEIGHT / 2;
		r = l + SPECIAL_P_BBOX_WIDTH;
		b = t + SPECIAL_P_BBOX_HEIGHT;
	}
	
	if (state == SPECIAL_P_STATE_PRESSED)
	{
		l = x - SPECIAL_P_PRESSED_BBOX_WIDTH / 2;
		t = y - SPECIAL_P_PRESSED_BBOX_HEIGHT / 2;
		r = l + SPECIAL_P_PRESSED_BBOX_WIDTH;
		b = t + SPECIAL_P_PRESSED_BBOX_HEIGHT;
	}
}

void CSpecial_Button::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	flyDistance += vy;
	if (this->flyable == true)
	{
		if (flyDistance > SPECIAL_P_DISTANCE)
		{
			vy = -vy;
		}
		//else if (flyDistance < 0)
		//{
		//	this->Delete();
		//}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CSpecial_Button::SetState(int state)
{
	CGameObject::SetState(state);
	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
	switch (state)
	{
	case SPECIAL_P_STATE_PRESSED:
	{
		stop_changing = GetTickCount64();
		vector<LPGAMEOBJECT> objects = thisscene->GetListObjects();
		for (int  i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<CBrick*>(objects[i]))
			{
				if (objects[i]->GetState() == BRICK_STATE_BLINK)
					objects[i]->SetState(BRICK_STATE_GOLD);
			}
		}
	}
	}
}
