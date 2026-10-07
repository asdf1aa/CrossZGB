#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "Print.h"
#include "SpriteManager.h"
UINT8 collision_tiles[] = {1, 0};
IMPORT_MAP(map);
IMPORT_FONT(font);

UINT16 game_score = 0;

void START(void) {
	InitScroll(BANK(map), &map, collision_tiles, 0);
	scroll_target = SpriteManagerAdd(SpritePlayer, 24, 24);
	SpriteManagerAdd(Flag, 200, 16);
	INIT_FONT_EX(font, PRINT_BKG);
	INIT_HUD_EX(map, 0, 8);
	print_target = PRINT_WIN;
	PRINT(0, 0, "SCORE %u", game_score);
}

void UPDATE(void) {
}
