#include "ZGBMain.h"
#include "Math.h"

UINT8 next_state = StateGame;

UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
	if (current_state == StateGame) {
		if (*tile_ptr == 0xFDu) {
			*tile = 0;
			return SpriteEnemy;
		}
		if (*tile_ptr == 0xFEu) {
			*tile = 0;
			return SpriteEnemyStill;
		}
		if (*tile_ptr == 0x02u) {
			*tile = 0;
			return SpriteEnemyH;
		}
	}
	*tile = *tile_ptr;
	return 255u;
}