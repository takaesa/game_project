#include "HUD.h"
#include"Game.h"
#include"Textures.h"
#include "Sprites.h"
#include"PlayScene.h"
#include "Mario.h"
CHUD::CHUD(float x, float y) {
	this->x = x;
	this->y = y;


}

void CHUD::Render()
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x, y);


	//background
	CAnimations::GetInstance()->Get(ID_ANI_BLACK_BACKGROUND)->Render(x, y-2);

	// HUD
	CAnimations::GetInstance()->Get(ID_ANI_HUD)->Render(x + 40, y - 50);

	//CAnimations::GetInstance()->Get(ID_ANI_0)->Render(x + 40, y - 50);

	// WRITE WORLD
	DrawNumber(1, x + POSITION_WORLD_X, y - ADJUST_Y_POWER_POSITION);

	//WRITE M SYMBOL
	CAnimations::GetInstance()->Get(ID_ANI_M_SYMBOL)->Render(x-64, y - 46);

	if (!mario) {}
	else {
		//RENDER ON HUD
			//Write POWER UP
		if (mario->GetLevelRun() > 1)
		{
			CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - 20, y - 53);
		}
		if (mario->GetLevelRun() > 2) {
			CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - 20 + DISTANCE_EVERY_LEVEL_RUN, y - 53);
		}
		if (mario->GetLevelRun() > 3) {
			CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - 20 + DISTANCE_EVERY_LEVEL_RUN * 2, y - 53);
		}
		if (mario->GetLevelRun() > 4) {
			CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - 20 + DISTANCE_EVERY_LEVEL_RUN * 3, y - 53);
		}
		if (mario->GetLevelRun() > 5) {
			CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - 20 + DISTANCE_EVERY_LEVEL_RUN * 4, y - 53);
		}
		if (mario->GetLevelRun() > 6) {
			CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - 20 + DISTANCE_EVERY_LEVEL_RUN * 5, y - 53);
		}
		if (mario->GetLevelRun() == 7) {
			CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD_MAX)->Render(x - 15 + DISTANCE_EVERY_LEVEL_RUN * 6, y - 53);
		}
		//WRITE SCORE
		int score = mario->GetScore();
		DrawNumber(score / 1000000, x + POSITION_SCORE_X, y - ADJUST_Y_POWER_POSITION_UNDER);
		DrawNumber((score / 100000) % 10, x + POSITION_SCORE_X + DISTANCE_NUMBER, y - ADJUST_Y_POWER_POSITION_UNDER);
		DrawNumber((score / 10000) % 10, x + POSITION_SCORE_X + DISTANCE_NUMBER * 2, y - ADJUST_Y_POWER_POSITION_UNDER);
		DrawNumber((score / 1000) % 10, x + POSITION_SCORE_X + DISTANCE_NUMBER * 3, y - ADJUST_Y_POWER_POSITION_UNDER);
		DrawNumber((score / 100) % 10, x + POSITION_SCORE_X + DISTANCE_NUMBER * 4, y - ADJUST_Y_POWER_POSITION_UNDER);
		DrawNumber((score / 10) % 10, x + POSITION_SCORE_X + DISTANCE_NUMBER * 5, y - ADJUST_Y_POWER_POSITION_UNDER);
		DrawNumber(score % 10, x + POSITION_SCORE_X + DISTANCE_NUMBER * 6, y - ADJUST_Y_POWER_POSITION_UNDER);




	//	//WRITE CARD
	//	int card1 = mario->GetCard1();
	//	int card2 = mario->GetCard2();
	//	int card3 = mario->GetCard3();
	//	if (card1) DrawCard(card1, x + X_CARD_POSITION, y + Y_CARD_POSITION);
	//	if (card2) DrawCard(card2, x + X_CARD_POSITION + CARD_WIDTH, y + Y_CARD_POSITION);
	//	if (card3) DrawCard(card3, x + X_CARD_POSITION + CARD_WIDTH * 2, y + Y_CARD_POSITION);
	//	//DebugOutTitle(L"[CARD 1 2 3 hjhj] %d %d %d \n", card1, card2, card3);
	//	// WRITE UP
	//	int up = mario->GetUp();
	//	if (up / 10 > 0) {
	//		DrawNumber(up / 10, x + POSITION_UP_X, y - ADJUST_Y_POWER_POSITION_UNDER);
	//	}
	//	DrawNumber(up % 10, x + POSITION_UP_X + DISTANCE_NUMBER, y - ADJUST_Y_POWER_POSITION_UNDER);
		//WRITE COIN
		int coin = mario->GetCoin();
		if (coin / 10 > 0) {
			DrawNumber(coin / 10, x + 60, y - 53);
		}
		DrawNumber(coin % 10, x+68, y - 53);
		//WRITE CLOCK
		int clock = mario->GetClock();
		DrawNumber(clock / 100, x + POSITION_CLOCK_X, y - ADJUST_Y_POWER_POSITION_UNDER);
		DrawNumber((clock / 10) % 10, x + POSITION_CLOCK_X + DISTANCE_NUMBER, y - ADJUST_Y_POWER_POSITION_UNDER);
		DrawNumber(clock % 10, x + POSITION_CLOCK_X + DISTANCE_NUMBER * 2, y - ADJUST_Y_POWER_POSITION_UNDER);
	}
}
void CHUD::DrawNumber(int n, float xTemp, float yTemp) {
	if (n == 0) CAnimations::GetInstance()->Get(ID_ANI_0)->Render(xTemp, yTemp);
	else if (n == 1) CAnimations::GetInstance()->Get(ID_ANI_1)->Render(xTemp, yTemp);
	else if (n == 2) CAnimations::GetInstance()->Get(ID_ANI_2)->Render(xTemp, yTemp);
	else if (n == 3) CAnimations::GetInstance()->Get(ID_ANI_3)->Render(xTemp, yTemp);
	else if (n == 4) CAnimations::GetInstance()->Get(ID_ANI_4)->Render(xTemp, yTemp);
	else if (n == 5) CAnimations::GetInstance()->Get(ID_ANI_5)->Render(xTemp, yTemp);
	else if (n == 6) CAnimations::GetInstance()->Get(ID_ANI_6)->Render(xTemp, yTemp);
	else if (n == 7) CAnimations::GetInstance()->Get(ID_ANI_7)->Render(xTemp, yTemp);
	else if (n == 8) CAnimations::GetInstance()->Get(ID_ANI_8)->Render(xTemp, yTemp);
	else  CAnimations::GetInstance()->Get(ID_ANI_9)->Render(xTemp, yTemp);
}
