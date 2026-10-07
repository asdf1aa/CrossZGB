#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
typedef struct {
    INT8 vx;
} CUSTOM_DATA;
void START() {
    SetPersistent(THIS, TRUE);
    CUSTOM_DATA* data =(CUSTOM_DATA*)THIS->custom_data;
    data->vx = 1;
}

void UPDATE() {   
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    if(TranslateSprite(THIS, data->vx, 0)) {
        data->vx = -data->vx;
    }
}

void DESTROY() {
}