#include "ZGBMain.h"
#include "Math.h"

UINT8 next_state = StateGame;

UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
	if (current_state == StateGame && *tile_ptr == 0xFFu) {
		*tile = 0;
		return SpriteEnemy;
	}
	if (current_state == StateGame && *tile_ptr == 0x02u) {
		*tile = 0;
		return SpriteEnemyStill;
	}
	*tile = *tile_ptr;
	return 255u;
}