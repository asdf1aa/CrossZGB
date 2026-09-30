#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "SpriteManager.h"

void START(void) {
}

void UPDATE(void) {
    if(KEY_PRESSED(J_UP)){
        THIS->y --;
    }
    if(KEY_PRESSED(J_DOWN)){
        THIS->y ++;
    }
    if(KEY_PRESSED(J_RIGHT)){
        THIS->x ++;
    }
    if(KEY_PRESSED(J_LEFT)){
        THIS->x --;
    }
}

void DESTROY(void) {
}