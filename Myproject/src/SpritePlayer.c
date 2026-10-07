#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "SpriteManager.h"

void START() {

}

void UPDATE() {
	UINT8 i;
	Sprite* spr;

	if(KEY_PRESSED(J_UP)) {
		TranslateSprite(THIS, 0, -1);
	} 
	if(KEY_PRESSED(J_DOWN)) {
		TranslateSprite(THIS, 0, 1);
	}
	if(KEY_PRESSED(J_LEFT)) {
		TranslateSprite(THIS, -1, 0);
	}
	if(KEY_PRESSED(J_RIGHT)) {
		TranslateSprite(THIS, 1, 0);
	}
	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SpriteEnemy || spr->type == SpriteEnemyStill || spr->type == SpriteEnemyH) {
			if(CheckCollision(THIS, spr)) {
				SetState(StateGame);
			}
		}
		if(spr->type == Flag) {
			if(CheckCollision(THIS, spr)){
				game_score++;
				SetState(StateGame);
			}
		}
	}
}

void DESTROY() {
}