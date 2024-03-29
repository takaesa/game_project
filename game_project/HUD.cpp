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
	DrawNumber(1, x - 35, y - 53);

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
		DrawNumber(score / 1000000, x -20, y - 45);
		DrawNumber((score / 100000) % 10, x - 20 + DISTANCE_NUMBER, y - 45);
		DrawNumber((score / 10000) % 10, x - 20 + DISTANCE_NUMBER * 2, y - 45);
		DrawNumber((score / 1000) % 10, x - 20 + DISTANCE_NUMBER * 3, y - 45);
		DrawNumber((score / 100) % 10, x - 20 + DISTANCE_NUMBER * 4, y - 45);
		DrawNumber((score / 10) % 10, x - 20 + DISTANCE_NUMBER * 5, y - 45);
		DrawNumber(score % 10, x - 20 + DISTANCE_NUMBER * 6, y - 45);

		int lives = mario->GetLive();
		if (lives / 10 > 0) {
			DrawNumber(lives / 10, x - 43, y - 45);
		}
		DrawNumber(lives %10, x - 35, y - 45);

		//WRITE CARD
		int card1 = mario->GetCard1();
		int card2 = mario->GetCard2();
		int card3 = mario->GetCard3();
		if (card1) DrawCard(card1, x + X_CARD_POSITION, y + Y_CARD_POSITION);
		if (card2) DrawCard(card2, x + X_CARD_POSITION + CARD_WIDTH, y + Y_CARD_POSITION);
		if (card3) DrawCard(card3, x + X_CARD_POSITION + CARD_WIDTH * 2, y + Y_CARD_POSITION);

		//WRITE COIN
		int coin = mario->GetCoin();
		if (coin / 10 > 0) {
			DrawNumber(coin / 10, x + 60, y - 53);
		}
		DrawNumber(coin % 10, x+68, y - 53);
		//WRITE TIME 
		int clock = mario->GetTime();
		DrawNumber(clock / 100, x + 52, y - 45);
		DrawNumber((clock / 10) % 10, x + 60, y - 45);
		DrawNumber(clock % 10, x + 68, y - 45);
		
		if (mario->GetState() == MARIO_END_MAP_STATE)
		{
			CAnimations::GetInstance()->Get(ID_ANI_END_GAME)->Render(x, y - 170);
			//DrawCard(mario->GetCardCollected(), x + 60, y - 150);
		}
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
void CHUD::DrawCard(int n, float xTemp, float yTemp) {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (!(mario->GetState() == SCENE_WORLD_MAP)) {
		if (n == HUD_CARD_MUSHROOM) CAnimations::GetInstance()->Get(ID_ANI_HUD_CARD_MUSHROOM)->Render(xTemp, yTemp);
		else if (n == HUD_CARD_FLOWER) CAnimations::GetInstance()->Get(ID_ANI_HUD_CARD_FLOWER)->Render(xTemp, yTemp);
		else if (n == HUD_CARD_STAR) CAnimations::GetInstance()->Get(ID_ANI_HUD_CARD_STAR)->Render(xTemp, yTemp);
	}
	else {
		if (n == HUD_CARD_MUSHROOM) CAnimations::GetInstance()->Get(ID_ANI_HUD_CARD_MUSHROOM_END_SCENE)->Render(xTemp, yTemp);
		else if (n == HUD_CARD_FLOWER) CAnimations::GetInstance()->Get(ID_ANI_HUD_CARD_FLOWER_END_SCENE)->Render(xTemp, yTemp);
		else if (n == HUD_CARD_STAR) CAnimations::GetInstance()->Get(ID_ANI_HUD_CARD_STAR_END_SCENE)->Render(xTemp, yTemp);
	}
	//else CAnimations::GetInstance()->Get(ID_ANI_HUD_CARD_MUSHROOM)->Render(xTemp, yTemp);
}