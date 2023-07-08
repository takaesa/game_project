#include "Special_Button.h"
#include "debug.h"

void CSpecial_Button::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_SPECIAL_P)->Render(x, y);

	//RenderBoundingBox();
}

void CSpecial_Button::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SPECIAL_P_BBOX_WIDTH / 2;
	t = y - SPECIAL_P_BBOX_HEIGHT / 2;
	r = l + SPECIAL_P_BBOX_WIDTH;
	b = t + SPECIAL_P_BBOX_HEIGHT;
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
