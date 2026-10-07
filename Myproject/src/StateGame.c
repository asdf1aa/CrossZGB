#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
UINT8 collision_tiles[] = {1, 0};
IMPORT_MAP(map);

void START(void) {
	scroll_target = SpriteManagerAdd(SpritePlayer, 24, 24);
	InitScroll(BANK(map), &map, collision_tiles, 0);
}

void UPDATE(void) {
}
