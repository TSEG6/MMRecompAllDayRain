#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "z_en_test4.h"


RECOMP_PATCH void EnTest4_UpdateWeatherClear(EnTest4* this, PlayState* play) {
    if ((CURRENT_DAY == 2) && (CURRENT_TIME >= CLOCK_TIME(6, 30)) && (CURRENT_TIME < CLOCK_TIME(22, 59)) &&
        (play->envCtx.precipitation[PRECIP_SNOW_CUR] == 0)) {
        gWeatherMode = WEATHER_MODE_RAIN;
        Environment_PlayStormNatureAmbience(play);
        play->envCtx.lightningState = LIGHTNING_ON;
        play->envCtx.precipitation[PRECIP_RAIN_MAX] = 60;
    }
    else if ((play->envCtx.precipitation[PRECIP_RAIN_MAX] != 0) && ((play->state.frames % 4) == 0)) {
        play->envCtx.precipitation[PRECIP_RAIN_MAX]--;
        if (play->envCtx.precipitation[PRECIP_RAIN_MAX] == 8) {
            Environment_StopStormNatureAmbience(play);
        }
    }

    if (gWeatherMode == WEATHER_MODE_RAIN) {
        this->weather = THREEDAY_WEATHER_RAIN;
    }
}



