#include "Brick.h"
#include "Coin.h"
void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
	switch (state)
	{
	case BRICK_STATE_GOLD:
	{
		this->Delete();
		CCoin* coin = new CCoin(this->x, this->y);
		thisscene->AddObjectToScene(coin);
		break;
	}
	default:
		break;
	}
}