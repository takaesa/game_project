#include "TeleportPipe.h"
void CTeleportPipe::Render()
{
	RenderBoundingBox();
}

void CTeleportPipe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CTeleportPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 10 / 2;
	t = y - 16 / 2;
	r = l + 10;
	b = t + 16;
}