
#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include "Includes/obfuscate.h"
#include "KittyMemory/MemoryPatch.h"
#include "Includes/Logger.h"
#include "Includes/Utils.h"
#include "Menu.h"

#if defined(__aarch64__)
#include <And64InlineHook/And64InlineHook.hpp>
#else

#include <Substrate/SubstrateHook.h>
#include <Substrate/CydiaSubstrate.h>
#include <iostream>
#endif

#include <Unity/Quaternion.hpp>
#include <Unity/Unity.h>
#include "Unity/Vector2.hpp"
#include "Unity/Vector3.hpp"
#include "Canvas/ESP.h"
#include "EnemyData.h"
#include "Canvas/StructsCommon.h"
#include "Unity/strings.h"
#include <Includes/Chams.h>
#include "ESPManager.h"
#include "hook.h"
#include "Color.h"
#include "Maps.h"
SamiEsp espOverlay;




struct My_Patches {
    MemoryPatch MONEY,SliderExample;
} hexPatches;


// Game Features
bool NameSpoofer = false;
int currency = 0;
bool Crowns = false;
int level = 0;
int hiddenRatings = 0;
int passtokens = 0;
bool animation = false;
bool AnyEmotes = false;
bool MONEY = false;
bool Emotes = false;
bool Footstep = false;
bool Skin = false;
bool BattlePass = false;
bool chamstoggle = false;
int speedPlayer;
bool resolutionRatio = false;
bool showFootsteps = false;
// ESP Features
bool ESPs;
bool ESPLine;
bool ESPBox;
bool Esp3dBox;
int BoxWidth = 250;
int BoxHeight = 250;
int ESP3DBOXTHICKNESS = 5;
int BoxThickness = 5;
int lineThickness = 5;
bool ESPLineOpp = false;
bool ESPInfo = false;
bool ESPLBAIXO = false;
Color ESPDistance;

Color color;
int ESPBoxStyle = 1;
int ESPLineLocation = 2.4;
float boxsize = 1.0;
float ESPstroke = 6.5f;
Color ESPBoxColor;
Color ESPLineColor;

int EnemyPos = 30;
bool ESPLine2;

bool EspObject;
bool EspAlert;

// ESP Color
int RedLine = 255;
int GreenLine = 255;
int BlueLine = 255;
int RedBox = 255;
int GreenBox = 255;
int BlueBox = 255;
int Red3DBox = 255;
int Green3DBox = 255;
int Blue3DBox = 255;
int round1Map;
int round2Map;

bool isPartyPrivate = false;
bool allowBots = false;
bool MapName = false;
const char *MapNameoff;
int roundNumber;

/// Cross And Circle //
int crosshairsize = 0;
int crosshaircolor = 0;
int resolucao = 0;
int crosshairop = 0;
int sizecircle = 0;
int circleThickness = 0;
bool EspCircle = false;
bool CustomCross = false;
float CrossSize = 50;
float CircleSize = 50;
bool customcircle = false;
bool CustomName = false;
Color changecolor = Color::Red();
Color changecolor2 = Color::Red();

bool bLoadEmotes = false;
bool bLoadSkins = false;
bool bDisplaySkin = false;
const char *nameChange1;
const char *partycode;
bool Garabage;
bool DisconnectGame = false;

// Chams
bool chams, shading, wireframe, glow, outline, rainbow = false;


// Player Size
float playersize1 = 1;
float playersize2 = 1;
float playersize3 = 1;
float enemysize1 = 1;
float enemysize2 = 1;
float enemysize3 = 1;
float playersizedown1 = 1;
float playersizedown2 = 1;
float playersizedown3 = 1;
float enemysizedown1 = 1;
float enemysizedown2 = 1;
float enemysizedown3 = 1;
int ALLMAPS = 0;


float CamYPos = 1;
float CamXPos = 1;
float CamZPos = 1;


bool telekill = false;
bool masskill = false;
bool playersize = false;
bool enemysize = false;
bool enemysizedown = false;


bool PosY = false;


bool playersizedown = false;
bool playersizescale = false;

// Camera
int CamDistance;
int xAngle;
int yAngle;

bool unlimitedDashToggle = false;
long sliderSpeed;
long sliderJumpHeight;
long sliderDash;
long BombRadius;

const char *createPartyCode;
bool RewardsUnli = false;
bool RewardsUnli1 = false;

bool RACEMODE = false;
bool SURVIVEMODE = false;
bool FOOTBALLMODE = false;
bool ROCKETEMODE = false;
bool wallhack = false;


bool changeNameinGame = false;
const char *nameChange;
bool freeNameChange = false;
bool unlockSkins = false;
bool soloParty = false;
const char *nameLobby;
bool changeLobbyName = false;
int QualifiedMaxPlayers;
int roundTimer;
const char *getlobbyName;
const char *nextRoomName;
bool enableNextRoomName = false;
bool enablLobbyName = false;
int expectedBotCount;
int expectedPlayerCount;


#define targetLibName OBFUSCATE("libil2cpp.so")

extern "C" {
JNIEXPORT void JNICALL
Java_uk_lgl_MainActivity_Toast(JNIEnv *env, jclass obj, jobject context) {
    MakeToast(env, context, OBFUSCATE("Modded by Sami Gaming Yt"), Toast::LENGTH_LONG);
}




JNIEXPORT jobjectArray
JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_getFeatureList(JNIEnv *env, jobject activityObject) {
    jobjectArray ret;

    const char *features[] = {


            OBFUSCATE("999_Category_NEW FEATURES"), //Not counted
            OBFUSCATE("100_Toggle_ENABLE SLIDE DASH"), //5
            OBFUSCATE("101_SeekBar_PLAYER SPEED_0_40"),//4
            OBFUSCATE("102_SeekBar_JUMP HEIGHT_0_70"),//4
            OBFUSCATE("103_SeekBar_SLIDE DASH SPEED_0_100"),//4
            OBFUSCATE("78_SeekBar_WALKING SPEED ANIMATION_0_300"), //6
            OBFUSCATE("911_Toggle_FREE CHANGE NAME"), //5
            OBFUSCATE("901_InputText_NAME CHANGER"),//4
            OBFUSCATE("890_Toggle_EXIT GAME"), //5


            OBFUSCATE("999_Category_MAP FEATURES"), //Not counted
            OBFUSCATE("914_Toggle_PRIVATE PARTY"), //5
            OBFUSCATE("915_Toggle_ALLOW BOTS"), //5
            OBFUSCATE("917_Spinner_SELECT MAP_MAPS OFF,SPIN GO ROUND,TILE FALL,ICY HEIGHT,HUMBLE STUMBLE,PIVOT PUSH,CANNON CLIMB,OVER UNDER,HONEY DROP,FLOOR FLIP,STUMBLE SOCCER,LAVA RUSH,BOMBARDMENT,SPACE RACE,SUPER SLIDE,LASER TRACER,LOST TEMPLE,ROCKET RUMBLE,JUNGLE ROLL,BLOCK DASH,PAINT SPLASH,LAVA LAND,BOT BASH"),//4

            OBFUSCATE("999_Category_GAME FEATURES"), //Not counted
            OBFUSCATE("65_Toggle_INVISIBLE PLAYER"), //5
            OBFUSCATE("8_Toggle_UNLOCK EMOTES"),//1
            OBFUSCATE("9_Toggle_UNLOCK SKINS"),//1
            OBFUSCATE("7_Toggle_UNLOCK ANIMATIONS"),//1
            OBFUSCATE("10_Toggle_UNLOCK FOOTSTEPS"),//1
            OBFUSCATE("12_Toggle_UNLIMITED GAME CURRENCY"),//4
            OBFUSCATE("104_Toggle_UNLIMITED CROWNS"),//1
            OBFUSCATE("14_SeekBar_SELECT PLAYER LEVEL_0_9999"),//4
            OBFUSCATE("66_Toggle_MASSKILL"), //6

            OBFUSCATE("999_Category_CAMERA FEATURES"), //Not counted
            OBFUSCATE("75_SeekBar_CAMERA_1_70"),//4
            OBFUSCATE("76_SeekBar_CAM Y AXIS_0_360"),//4
            OBFUSCATE("77_SeekBar_CAM X AXIS_0_360"),//4

            OBFUSCATE("999_Category_CHAMS FEATURES"), //Not counted
            OBFUSCATE("50_CheckBox_DEFAULT CHAMS"),//1
            OBFUSCATE("51_CheckBox_SHADING CHAMS"), //2
            OBFUSCATE("52_CheckBox_WIREFRAME CHAMS"),//3
            OBFUSCATE("53_CheckBox_GLOW CHAMS"),//4
            OBFUSCATE("54_CheckBox_OUTLINE CHAMS"), //5
            OBFUSCATE("55_CheckBox_RAINBOW CHAMS"), //6
            OBFUSCATE("56_SeekBar_LINE WIDTH_0_12"),//7
            OBFUSCATE("57_SeekBar_COLOR RED_0_255"),//8
            OBFUSCATE("58_SeekBar_COLOR GREEN_0_255"),//9
            OBFUSCATE("59_SeekBar_COLOR BLUE_0_255"),//10

            OBFUSCATE("999_Category_PLAYER FEATURES"),//62
            OBFUSCATE("60_CheckBox_ENABLE PLAYER SIZE"), //63
            OBFUSCATE("61_SeekBar_PLAYER SIZE_1_10"), //64
            OBFUSCATE("62_CheckBox_ENABLE ENEMY SIZE"), //65
            OBFUSCATE("63_SeekBar_ENEMY SIZE_1_10"), //66
            OBFUSCATE("64_CheckBox_ENABLE PLAYER DOWN SIZE"), //67
            OBFUSCATE("641_SeekBar_PLAYER DOWN SIZE_0_10"), //66
            OBFUSCATE("642_CheckBox_ENABLE ENEMY DOWN SIZE"), //67
            OBFUSCATE("643_SeekBar_ENEMY DOWN SIZE_0_10"), //66

            OBFUSCATE("999_Category_CROSSHAIR FEATURES"), //Not counted
            OBFUSCATE("27_Toggle_CUSTOM CROSSHAIR"),//18
            OBFUSCATE("28_SeekBar_CROSSHAIR SIZE_0_500"),//22
            OBFUSCATE("29_SeekBar_CROSSHAIR COLOUR_0_9"), //23
            OBFUSCATE("30_SeekBar_CROSSHAIR CAPACITY_0_100"), //2

            OBFUSCATE("999_Category_FOV FEATURES"), //Not counted
            OBFUSCATE("20_Toggle_FOV"),
            OBFUSCATE("32_SeekBar_FOV RANGE_0_500"),//22
            OBFUSCATE("33_SeekBar_FOV CIRLCE COLOUR_0_7"),//22
            OBFUSCATE("290_SeekBar_FOV THICKNESS_0_15"),//22

            OBFUSCATE("88_Spinner_CREATOR_SAMI GAMING YT,SAMI MALIK"), //
            OBFUSCATE("ButtonLink_YOUTUBE_https://www.youtube.com/channel/UCrXLUg0ZphfIYneeKEv1KIA"),//14
            OBFUSCATE("ButtonLink_INSTAGRAM_https://www.instagram.com/iamsamimalik"),//14
            OBFUSCATE("ButtonLink_TELEGRAM_https://t.me/SamiGaming"),//14
    };

    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    pthread_t ptid;
    pthread_create(&ptid, NULL, antiLeech, NULL);

    return (ret);
}

JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_Preferences_Changes(JNIEnv *env, jclass clazz, jobject obj,
                                        jint featNum, jstring featName, jint value,
                                        jboolean boolean, jstring str) {
    const char *featureName = env->GetStringUTFChars(featName, 0);
    const char *TextInput;
    if (str != NULL)
        TextInput = env->GetStringUTFChars(str, 0);
    else
        TextInput = "Empty";

    LOGD(OBFUSCATE("Feature name: %d - %s | value: = %d | Bool: = %d | Text: = %s"), featNum,
         featureName, value,
         boolean, TextInput);


    switch (featNum) {


        case 890:
            DisconnectGame = boolean;
            break;

        case 901:
            nameChange = env->GetStringUTFChars(str,0);
            break;


        case 902:
            unlockSkins = boolean;
            break;

        case 903:
            soloParty = boolean;
            break;

        case 904:
            nameLobby = env->GetStringUTFChars(str,0);
            break;



        case 908:
            nextRoomName = env->GetStringUTFChars(str,0);
            break;

        case 909:
            expectedBotCount = value;
            break;

        case 910:
            expectedPlayerCount = value;
            break;

        case 911:
            freeNameChange = boolean;
            break;


        case 914:
            isPartyPrivate = boolean;
            break;

        case 915:
            allowBots = boolean;
            break;

        case 917:
            ALLMAPS = value;
            break;



        case 100:
            unlimitedDashToggle = boolean;
            break;

        case 101:
            sliderSpeed = value;
            break;

        case 102:
            sliderJumpHeight = value;
            break;

        case 103:
            sliderDash = value;
            break;

        case 104:
            Crowns = boolean;
            break;

        case 1:
            bLoadEmotes = boolean;
            break;

        case 2:
            bDisplaySkin =  boolean;
            break;

        case 3001:
            bLoadSkins = boolean;
            break;

        case 7:
            animation = boolean;
            break;

        case 8:
            Emotes = boolean;
            break;

        case 9:
            Skin = boolean;
            break;

        case 10:
            Footstep = boolean;
            showFootsteps = boolean;
            break;

        case 12:
            MONEY = boolean;
            if (MONEY) {
                hexPatches.MONEY.Modify();
            } else {
                hexPatches.MONEY.Restore();
            }
            break;


        case 14:
            level = value;
            break;


        case 50:
            chams = boolean;
            if (chams) {
                SetWallhack(true);
            } else {
                SetWallhack(false);
            }
            break;

        case 51:
            shading = boolean;
            if (shading) {
                SetWallhackS(true);
            } else {
                SetWallhackS(false);
            }
            break;

        case 52:
            wireframe = boolean;
            if (wireframe) {
                SetWallhackW(true);
            } else {
                SetWallhackW(false);
            }
            break;

        case 53:
            glow = boolean;
            if (glow) {
                SetWallhackG(true);
            } else {
                SetWallhackG(false);
            }
            break;

        case 54:
            outline = boolean;
            if (outline) {
                SetWallhackO(true);
            } else {
                SetWallhackO(false);
            }
            break;

        case 55:
            rainbow = boolean;
            if (rainbow) {
                SetRainbow(true);
            } else {
                SetRainbow(false);
            }
            break;

        case 56:
            SetW(value);
            break;

        case 57:
            SetR(value);
            break;

        case 58:
            SetG(value);
            break;

        case 59:
            SetB(value);
            break;


        case 20:
            customcircle = boolean;
            break;

        case 27:
            CustomCross = boolean;
            break;
        case 28:
            crosshairsize = value + 30;
            break;
        case 29:
            crosshaircolor = value;
            break;
        case 290:
            circleThickness = value;
            break;
        case 30:
            crosshairop = 2.5 * value;
            break;
        case 32:
            sizecircle = value + 30;
            break;
        case 33:
            if (value >= 0 && value <= 7) {
                static const Color colors[] = {
                        Color::Red(),
                        Color::Green(),
                        Color::Black(),
                        Color::Blue(),
                        Color::Cyan(),
                        Color::Purple(),
                        Color::Yellow(),
                        Color::White()
                };
                changecolor2 = colors[value];
            }
            break;



        case 60:
            playersize = boolean;
            enemysize = boolean;
            break;

        case 61:
            playersize1 = value;
            playersize2 = value;
            playersize3 = value;
            break;
        case 62:
            enemysize = boolean;
            break;
        case 63:
            enemysizedown1 = value;
            enemysizedown2 = value;
            enemysizedown3 = value;
            break;
        case 64:
            playersizedown = boolean;
            break;

        case 641:
            if (value >= 0 && value <= 10) {
                playersizedown = -static_cast<float>(value);
            }
            break;


        case 642:
            enemysizedown = boolean;
            break;

        case 643:
            if (value >= 0 && value <= 10) {
                enemysizedown1 = -static_cast<float>(value);
            }
            break;


        case 65:
            telekill = boolean;
            break;

        case 66:
            masskill = boolean;
            break;


        case 75:
            CamDistance = value;
            break;

        case 76:
            xAngle = value;
            break;

        case 77:
            yAngle = value;
            break;

        case 78:
            speedPlayer = value;
            break;

    //    case 78:
      //      PosY = boolean;
         //   break;

 //       case 79:
   //         CamYPos = value;
     //       break;

  //      case 80:
    //        CamXPos = value;
      //      break;

  //      case 81:
    //        CamZPos = value;
      //      break;

        case 88:
            switch (value) {
                case 0:
                    LOGD(OBFUSCATE("SAMI GAMING YT"));
                    break;
                case 1:
                    LOGD(OBFUSCATE("SAMI MALIK"));
                    break;
            }
            break;
    }
}
}

float get_3D_Distance(float Self_x, float Self_y, float Self_z, float Object_x, float Object_y, float Object_z)
{
    float x, y, z;
    x = Self_x - Object_x;
    y = Self_y - Object_y;
    z = Self_z - Object_z;
    return (float)(sqrt(x * x + y * y + z * z));
}

//CANVAS
void DrawESP(SamiEsp esp, int screenWidth, int screenHeight) {
    esp.DrawText(Color::Yellow(), "Sami Gaming Yt", Vector2(screenWidth / 2, screenHeight / 1.02f),
                 25.0f);

    Vector2 Screen(screenWidth, screenHeight);

    if (CustomCross) {
        esp.DrawCrosshair(changecolor, Vector2(screenWidth / 2, screenHeight / 2), CrossSize);
    }

    if (EspCircle) {
        esp.DrawCircle(changecolor2, 1,
                       Vector2(screenWidth / 2, screenHeight / 2), CircleSize);
    }


    if (customcircle) {
        esp.DrawCircle(changecolor2, circleThickness,
                       Vector2(screenWidth / 2, screenHeight / 2), sizecircle);
    }

    if (CustomCross == 0 || CustomCross) {
        Color color;
        switch (crosshaircolor) {
            case 0: color = Color(255, 0, 0, crosshairop); break;
            case 1: color = Color(0, 0, 255, crosshairop); break;
            case 2: color = Color(255, 255, 255, crosshairop); break;
            case 3: color = Color(0, 255, 0, crosshairop); break;
            case 4: color = Color(255, 0, 0, crosshairop); break;
            case 5: color = Color(255, 38, 106, crosshairop); break;
            case 6: color = Color(255, 255, 0, crosshairop); break;
            case 7: color = Color(243, 20, 255, crosshairop); break;
            default: return;
        }
        esp.DrawCrosshair(color, Vector2(screenWidth / 2, screenHeight / 2), crosshairsize);
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_DrawOn(JNIEnv *env, jclass clazz, jobject esp, jobject canvas) {
    espOverlay = SamiEsp(env, esp, canvas);
}
// ---------- Hooking ---------- //





int (*old_GetLevel)(void* instance);
int GetLevel(void* instance) {
    return (instance != nullptr && level > 1) ? (int)level : old_GetLevel(instance);
}

bool (*old_OwnsCosmetic_Animation)(void* instance, monoString* id);
bool OwnsCosmetic_Animation(void* instance, monoString* id) {
    return (instance != nullptr && animation) ? true : old_OwnsCosmetic_Animation(instance, id);
}

bool (*old_OwnsCosmetic_Emote)(void* instance, monoString* id);
bool OwnsCosmetic_Emote(void* instance, monoString* id) {
    return (instance != nullptr && Emotes) ? true : old_OwnsCosmetic_Emote(instance, id);
}

bool (*old_OwnsCosmetic_Footstep)(void* instance, monoString* id);
bool OwnsCosmetic_Footstep(void* instance, monoString* id) {
    return (instance != nullptr && Footstep) ? true : old_OwnsCosmetic_Footstep(instance, id);
}

bool (*old_OwnsCosmetic_Skins)(void* instance, monoString* id);
bool OwnsCosmetic_Skins(void* instance, monoString* id) {
    return (instance != nullptr && Skin) ? true : old_OwnsCosmetic_Skins(instance, id);
}


bool (*old_OwnsCosmetic_Variant)(void* instance, monoString* id);
bool OwnsCosmetic_Variant(void* instance, monoString* id) {
    return (instance != nullptr && Skin) ? true : old_OwnsCosmetic_Variant(instance, id);
}

void (*old_CameraFollow_LateUpdate)(void* instance);
void CameraFollow_LateUpdate(void* instance) {
    if (instance != nullptr) {
        if (CamDistance) {
            *(float*)((uint64_t)instance + 0x18) = CamDistance;

        }
       if (xAngle) {
           *(float *) ((uint64_t) instance + 0x10) = xAngle;
       }
        if (yAngle) {
            *(float*)((uint64_t)instance + 0xC) = yAngle;
        }
    }
    old_CameraFollow_LateUpdate(instance);
}




// void (*set_position1)(void* transform, Vector3 position);
// void (*set_position1)(void* transform, Vector3 position);



void (*old_PlayerVisualController_update)(void* player,void *frame);
void PlayerVisualController_update(void* player,void *frame) {


    bool isLocal = *(bool *) ((uint64_t) player + 0x70); // isLocal


    if (isLocal) {
        myPlayer = player;
        myPlayerloc = player;
    }

    if (myPlayer) {
        if (GetPlayerTeam(myPlayer) != GetPlayerTeam(player)) {
            enemyPlayer = player;
        }
    }

    if (enemyPlayer) {
        if (masskill) {
            Vector3 PlayerLocation = GetPlayerLocation1(myPlayer);
            set_position(get_transform(enemyPlayer),
                         Vector3(PlayerLocation.X, PlayerLocation.Y,
                                 PlayerLocation.Z + 1));

        }
    } else {
        enemyPlayer = NULL;
        return;
    }

    if (enemyPlayer) {

        if (telekill) {
            Vector3 enemyLocation = GetPlayerLocation1(enemyPlayer);

            set_position(get_transform(myPlayer),
                         Vector3(enemyLocation.X, enemyLocation.Z,
                                 enemyLocation.Y - 1));
        }
    } else {
        enemyPlayer = NULL;
        return;
    }


    if (playersizedown) {
        setScale(myPlayerloc, Vector3(playersizedown1, playersizedown2, playersizedown3));
    }

    if (enemysizedown) {
        setScale(enemyPlayer, Vector3(enemysizedown1, enemysizedown2, enemysize3));
    }

    if (playersize) {
        setScale(myPlayerloc, Vector3(playersize1, playersize2, playersize3));
    }

    if (enemysize) {
        setScale(enemyPlayer, Vector3(enemysizedown1, enemysizedown2, enemysizedown3));
    }

    // if (PosY){
    //    set_position1(get_transform(myPlayerloc), Vector3(CamXPos,CamYPos,CamZPos));
    // }



    old_PlayerVisualController_update(player,frame);
}



void (*old_MovementSystem)(void *instance, void* frame, void* FallGirlFilter);
void MovementSystem(void *instance, void* frame, void* FallGirlFilter){
    if (instance != nullptr) {

        void *FallGirl = *(void **) ((uint64_t) FallGirlFilter + 0x10); // FallGirl

        if (FallGirl != nullptr) {
            if (unlimitedDashToggle) {
                *(int *) ((uint64_t) FallGirl + 0x40) = 0x1; // CanDash
            }
            if (sliderSpeed) {
                *(long *) ((uint64_t) FallGirl + 0xF0) = sliderSpeed * 0x9C40;  // MaxSpeed
                *(long *) ((uint64_t) FallGirl + 0xF8) = sliderSpeed * 0x4E20; // MaxSpeedMultiplier
                *(long *) ((uint64_t) FallGirl + 0x120) = sliderSpeed * 0xC350; // SpeedMultiplier
            }
            if (sliderJumpHeight) {
                *(long *) ((uint64_t) FallGirl + 0xE8) = 0x0; // JetpackingTimer
                *(long *) ((uint64_t) FallGirl + 0xE0) = sliderJumpHeight * 0xC350; // JumpImpulse
            }
            if (sliderDash) {
                *(long *) ((uint64_t) FallGirl + 0xB8) = sliderDash * 0x9C40; // DashPower
                *(long *) ((uint64_t) FallGirl + 0x110) = 0x0; // SlideDashTimer
            }
        }
    }
    return old_MovementSystem(instance, frame, FallGirlFilter);
}

void (*old_set_Crowns)(void *instance, int value);
void set_Crowns(void *instance, int value) {
    return old_set_Crowns(instance, (instance && Crowns) ? 0xF423F : value);
}

void (*old_ShowInterstitial)(void *instance, void *callback, void *notLoadedCallBack, bool forceNoAd);
void ShowInterstitial(void *instance, void *callback, void *notLoadedCallBack, bool forceNoAd) {
    return old_ShowInterstitial(instance, callback, notLoadedCallBack,true );
}

void (*old_ChangeName)(void *instance, monoString *name, bool isFree);
void ChangeName(void *instance, monoString *name, bool isFree) {
    return old_ChangeName(instance,
                          (instance != nullptr && nameChange) ? CreateMonoString(nameChange, 0, strlen(nameChange)) : name,
                          (instance != nullptr && freeNameChange) ? true : isFree);
}




void (*old_CreateParty)(void *instance, monoString *playerId, bool allowReconnect, monoString *lobbyName, bool allowBots, bool isPartyPrivate, void *localPlayerProperties, int maxQualified, int roundTime, monoArray<int> *disableEmotes, monoString *Cluster);
void CreateParty(void *instance, monoString *playerId, bool allowReconnect, monoString *lobbyName, bool allowBots, bool isPartyPrivate, void *localPlayerProperties, int maxQualified, int roundTime, monoArray<int> *disableEmotes, monoString *Cluster) {
    return old_CreateParty(instance, playerId, allowReconnect, lobbyName, allowBots, isPartyPrivate, localPlayerProperties,
                           (instance && QualifiedMaxPlayers) ? QualifiedMaxPlayers : maxQualified,
                           (instance && roundTime) ? roundTimer : roundTime, disableEmotes, Cluster);
}




void (*MasterStartParty)(void *instance);
void (*GetMatchmakingPool)(void *instance,int rating);

/*void (*old_UpdateMatchmakingRoomSetup)(void *instance,int pool);
void UpdateMatchmakingRoomSetup(void *instance,int pool){
    if (instance != nullptr){
        MasterStartParty(instance);
        GetMatchmakingPool(instance,ratings);
    }
    return old_UpdateMatchmakingRoomSetup(instance,pool);
}*/
enum DisconnectCause {
    None,
    ExceptionOnConnect,
    Exception,
    ServerTimeout,
    ClientTimeout,
    DisconnectByServerLogic,
    DisconnectByServerReasonUnknown,
    InvalidAuthentication,
    CustomAuthenticationFailed,
    AuthenticationTicketExpired,
    MaxCcuReached,
    InvalidRegion,
    OperationNotAllowedInCurrentState,
    DisconnectByClientLogic,
};

void (*old_OnDisconnected)(void *instance, int DisconnectCause);
void OnDisconnected(void *instance, int DisconnectCause) {
    return old_OnDisconnected(instance, (instance != nullptr && DisconnectGame) ? DisconnectCause::DisconnectByServerReasonUnknown : DisconnectCause);
}



void (*old_MultiplayerRoomManager)(void *instance);
void MultiplayerRoomManager(void *instance){
    if (instance != nullptr){

        if (DisconnectGame){
            OnDisconnected(instance,DisconnectCause::DisconnectByServerReasonUnknown);
            OnDisconnected(instance,DisconnectCause::DisconnectByServerLogic);
            OnDisconnected(instance,DisconnectCause::DisconnectByClientLogic);
        }



if (isPartyPrivate){
            *(bool *)((uint64_t)instance + 0x62) = true;
        }

        if (soloParty){
            *(bool *)((uint64_t)instance + 0x59) = true;
            *(bool *)((uint64_t)instance + 0x58) = true;
        }

        if (allowBots){
            *(bool *)((uint64_t)instance + 0x61) = true;
        }


    }
    return old_MultiplayerRoomManager(instance);
}



void (*old_set_Username)(void *instance, monoString *value);
void set_Username(void *instance, monoString *value) {
    if (instance) {
        value = nameChange1 ? CreateMonoString(nameChange1, 0, strlen(nameChange1)) : value;
    }
    return old_set_Username(instance, value);
}



monoString* (*old_GetMapName)(void *instance);
monoString* GetMapName (void *instance){
    if (instance != nullptr) {
        if (ALLMAPS) {
            switch (ALLMAPS) {
                case 0:
                    return (CreateMonoString(OBFUSCATE(""), 0, strlen("")));
                    break;
                case 1:
                    return (CreateMonoString(OBFUSCATE("level_whirly"), 0, strlen("level_whirly")));
                    break;
                case 2:
                    return (CreateMonoString(OBFUSCATE("level2_tile"), 0, strlen("level2_tile")));
                    break;
                case 3:
                    return (CreateMonoString(OBFUSCATE("level3_Ice"), 0, strlen("level3_Ice")));
                    break;
                case 4:
                    return (CreateMonoString(OBFUSCATE("level4_pushy"), 0, strlen("level4_pushy")));
                    break;
                case 5:
                    return (CreateMonoString(OBFUSCATE("level5_pivot"), 0, strlen("level5_pivot")));
                    break;
                case 6:
                    return (CreateMonoString(OBFUSCATE("level6_hill"), 0, strlen("level6_hill")));
                    break;
                case 7:
                    return (CreateMonoString(OBFUSCATE("level7_moving"), 0, strlen("level7_moving")));
                    break;
                case 8:
                    return (CreateMonoString(OBFUSCATE("level8_honey"), 0, strlen("level8_honey")));
                    break;
                case 9:
                    return (CreateMonoString(OBFUSCATE("level9_seesaw"), 0, strlen("level9_seesaw")));
                    break;
                case 10:
                    return (CreateMonoString(OBFUSCATE("level10_soccer"), 0, strlen("level10_soccer")));
                    break;
                case 11:
                    return (CreateMonoString(OBFUSCATE("level11_lava"), 0, strlen("level11_lava")));
                    break;
                case 12:
                    return (CreateMonoString(OBFUSCATE("level12_bomb"), 0, strlen("level12_bomb")));
                    break;
                case 13:
                    return (CreateMonoString(OBFUSCATE("level13_gravity"), 0, strlen("level13_gravity")));
                    break;
                case 14:
                    return (CreateMonoString(OBFUSCATE("level14_slide"), 0, strlen("level14_slide")));
                    break;
                case 15:
                    return (CreateMonoString(OBFUSCATE("level15_laser"), 0, strlen("level15_laser")));
                    break;
                case 16:
                    return (CreateMonoString(OBFUSCATE("level16_temple"), 0, strlen("level16_temple")));
                    break;
                case 17:
                    return (CreateMonoString(OBFUSCATE("level17_rocket"), 0, strlen("level17_rocket")));
                    break;
                case 18:
                    return (CreateMonoString(OBFUSCATE("level18_jungle"), 0, strlen("level18_jungle")));
                    break;
                case 19:
                    return (CreateMonoString(OBFUSCATE("level19 block"), 0, strlen("level19 block")));
                    break;
                case 20:
                    return (CreateMonoString(OBFUSCATE("level20_paint"), 0, strlen("level20_paint")));
                    break;
                case 21:
                    return (CreateMonoString(OBFUSCATE("level21_pillar"), 0, strlen("level21_pillar")));
                    break;
                case 22:
                    return (CreateMonoString(OBFUSCATE("level22_bot"), 0, strlen("level22_bot")));
                    break;
            }
        }
    }
    return old_GetMapName(instance);
}




void (*old_CreateParty1)(void *instance);
void CreateParty1 (void *instance){
        if (Garabage){
            return;
        }
    return old_CreateParty1(instance);
}

void (*old_OnPlayButton)(void *instance);
void OnPlayButton (void *instance){
        if (Garabage){
            return;
        }
    return old_OnPlayButton(instance);
}



void (*old_FreeRewardsHelper)(void *instance);
void FreeRewardsHelper (void *instance){
    if (instance != nullptr) {
        if (Garabage) {
            *(int *) ((uint64_t) instance + 0x10) = 999999;
            *(int *) ((uint64_t) instance + 0x8) = 999999;
            *(int *) ((uint64_t) instance + 0xC) = 999999;
            *(int *) ((uint64_t) instance + 0x14) = 999999;
        }
    }
    return old_FreeRewardsHelper(instance);
}



    void *hack_thread(void *) {

        ProcMap il2cppMap;
        do {
            il2cppMap = KittyMemory::getLibraryMap(targetLibName);
            sleep(1);
        } while (!il2cppMap.isValid() && mlovinit());
        setShader(OBFUSCATE("_SkinColor"));
        LogShaders();
        Wallhack();
    espManager = new ESPManager();





    hexPatches.MONEY = MemoryPatch::createWithHex(targetLibName,
                                                    string2Offset(OBFUSCATE("0xD6D93C")),
                                                    OBFUSCATE("62 01 0C 00 1E FF 2F E1"));





  //  Screen_SetResuolution = (void(*)(int, int, bool))getAbsoluteAddress(targetLibName,0x156D5DC);
  //  Screen_SetResuolution = (void(*)(void *,int, int, bool))getAbsoluteAddress(targetLibName, 0x156D6B4);

  /*
    OnSkinUseButton = (void(*)(void *))getAbsoluteAddress(targetLibName,0x6A987C);
    DisplaySkin = (void(*)(void *))getAbsoluteAddress(targetLibName,0x6A6A38);
    LoadEmotes = (void(*)(void *))getAbsoluteAddress(targetLibName,0x6A7B84);



    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x6A92BC", '?'))), // 4 PUT =)
            (void *) CustomizeViewController,
            (void **) &old_CustomizeViewController);
*/




    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0xAB01A8", '?'))), // 4 PUT =)
            (void *) PlayerVisualController_update,
            (void **) &old_PlayerVisualController_update);

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x3FEF18C", '?'))), // 4 PUT =)
            (void *) MovementSystem,
            (void **) &old_MovementSystem);

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0xD6D430", '?'))), // 4 PUT =)
            (void *) set_Crowns,
            (void **) &old_set_Crowns);


    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0xF6A794", '?'))), // 4 PUT =)
            (void *) GetLevel,
            (void **) &old_GetLevel); // ExperienceManager

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0xC54074", '?'))), // 4 PUT =)
            (void *) OwnsCosmetic_Animation,
            (void **) &old_OwnsCosmetic_Animation);

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0xC55408", '?'))), // 4 PUT =)
            (void *) OwnsCosmetic_Emote,
            (void **) &old_OwnsCosmetic_Emote);

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0xC568A4", '?'))), // 4 PUT =)
            (void *) OwnsCosmetic_Footstep,
            (void **) &old_OwnsCosmetic_Footstep);

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0xC58010", '?'))), // 4 PUT =)
            (void *) OwnsCosmetic_Skins,
            (void **) &old_OwnsCosmetic_Skins);


/*
    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0xF04A58", '?'))), // 4 PUT =)
            (void *) CameraFollow_LateUpdate,
            (void **) &old_CameraFollow_LateUpdate); // CameraBase*/

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0xBE3228", '?'))), // 4 PUT =)
            (void *) ShowInterstitial,
            (void **) &old_ShowInterstitial);

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0xAB0F70", '?'))), // 4 PUT =)
            (void *) ChangeName,
            (void **) &old_ChangeName);

  //  MSHookFunction(
   //         (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x72EF58", '?'))), // 4 PUT =)
    //        (void *) SkinManager_Awake,
     //       (void **) &old_SkinManager_Awake);

   /* MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x6E6804", '?'))), // 4 PUT =)
            (void *) CreateParty,
            (void **) &old_CreateParty);
*//*
    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x6E90E4", '?'))), // 4 PUT =)
            (void *) UpdateMatchmakingRoomSetup,
            (void **) &old_UpdateMatchmakingRoomSetup);*/

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0xE41E4C", '?'))), // 4 PUT =)
            (void *) OnDisconnected,
            (void **) &old_OnDisconnected);

 //   MSHookFunction(
  //          (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x62EF10", '?'))), // 4 PUT =)
   //         (void *) OpenPopup,
    //        (void **) &old_OpenPopup);

   // MSHookFunction(
    //        (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x63848C", '?'))), // 4 PUT =)
     //       (void *) SetHeaderAndContent,
      //      (void **) &old_SetHeaderAndContent);


    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0xD6D338", '?'))), // 4 PUT =)
            (void *) set_Username,
            (void **) &old_set_Username);

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0xE32990", '?'))), // 4 PUT =)
            (void *) GetMapName,
            (void **) &old_GetMapName);



    /*MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x6E6690", '?'))), // 4 PUT =)
            (void *) CreateParty1,
            (void **) &old_CreateParty1);
*/

    // MSHookFunction(
   //         (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x70B0B8", '?'))), // 4 PUT =)
   //         (void *) FinishRoundV,
    //        (void **) &old_FinishRoundV);

 //   MSHookFunction(
  //          (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x70B160", '?'))), // 4 PUT =)
   //         (void *) FinishRoundV2,
    //        (void **) &old_FinishRoundV2);



/*    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x6C068C", '?'))), // 4 PUT =)
            (void *) FreeRewardsHelper,
            (void **) &old_FreeRewardsHelper);*/

   // GetMapName = (monoString* (*)(void *))getAbsoluteAddress(targetLibName, 0x6E4430);
  //  RewardedState = (void (*)(void *))getAbsoluteAddress(targetLibName, 0x714BF0);
  /*  MasterStartParty = (void (*)(void *))getAbsoluteAddress(targetLibName, 0x6E70A0);
    GetMatchmakingPool = (void (*)(void *, int))getAbsoluteAddress(targetLibName, 0x6E8F40);*/
  //  GetSkin = (void (*)(void *, monoString*))getAbsoluteAddress(targetLibName, 0x7272E8);



/*
    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x630818", '?'))), // 4 PUT =)
            (void *) OnPlayButton,
            (void **) &old_OnPlayButton);

*/



    return NULL;
    }


/*

#if defined(__aarch64__)

#else

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x832848", '?'))), // 4 PUT =)
            (void *) GetBalance,
            (void **) &old_GetBalance);

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x654E00", '?'))), // 4 PUT =)
            (void *) GetLevel,
            (void **) &old_GetLevel);

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x8325F0", '?'))), // 4 PUT =)
            (void *) HasAnimation,
            (void **) &old_HasAnimation);


    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x832720", '?'))), // 4 PUT =)
            (void *) HasEmote,
            (void **) &old_HasEmote);

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x832688", '?'))), // 4 PUT =)
            (void *) HasFootstep,
            (void **) &old_HasFootstep);

    MSHookFunction(
            (void *) getAbsoluteAddress(targetLibName, string2Offset(OBFUSCATE_KEY("0x832470", '?'))), // 4 PUT =)
            (void *) HasSkins,
            (void **) &old_HasSkins);



    LOGI(OBFUSCATE("Done"));
#endif

    return NULL;
}
*/

__attribute__((constructor))
void lib_main() {
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}


