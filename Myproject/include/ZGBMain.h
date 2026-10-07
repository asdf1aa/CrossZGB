#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
STATE_DEF_END

#define SPRITES \
_SPRITE(SpritePlayer, player, FLIP_NONE)\
_SPRITE(SpriteEnemy, enemy, FLIP_NONE)\
_SPRITE_EX(SpriteEnemyStill, SpriteEnemyStill, enemy, FLIP_NONE)\
_SPRITE_EX(SpriteEnemyH, SpriteEnemyH, enemy, FLIP_NONE)\
_SPRITE(Flag, flag, FLIP_NONE)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

extern UINT16 game_score;

#endif