#ifndef HOOK_H
#define HOOK_H
#pragma once

Vector3 get_position(void* transform) {
    if (!transform)
        return Vector3();
    Vector3 position;
    static const auto get_position_injected = reinterpret_cast<uint64_t(__fastcall*)(void*, Vector3&)>(getAbsoluteAddress(targetLibName, 0x39BFCF0));//UnityEngine.CoreModule
    get_position_injected(transform, position);
    return position;
}

void set_position(void* transform, Vector3 position) {

    if (transform) {
        static const auto set_position_injected = reinterpret_cast<uint64_t(__fastcall*)(void*, Vector3)>(getAbsoluteAddress(targetLibName, 0x39BFDA0));//UnityEngine.CoreModule
        set_position_injected(transform, position);
    }
}

Vector3 get_localScale(void* transform) {
    if (!transform)
        return Vector3();

    Vector3 position;

    static const auto get_localScale_injected = reinterpret_cast<uint64_t(__fastcall*)(void*, Vector3&)>(getAbsoluteAddress(targetLibName, 0x39C0BFC));//UnityEngine.CoreModule
    get_localScale_injected(transform, position);

    return position;
}

void set_localScale(void* transform, Vector3 test1) {

    if (transform) {
        static const auto set_localScale_injected = reinterpret_cast<uint64_t(__fastcall*)(void*, Vector3)>(getAbsoluteAddress(targetLibName, 0x39C0CAC));//UnityEngine.CoreModule
        set_localScale_injected(transform, test1);
    }
}

void* get_transform(void* player) {
    if (!player) return NULL;
    static const auto get_transform_injected = reinterpret_cast<uint64_t(__fastcall*)(void*)>(getAbsoluteAddress(targetLibName, 0x39AFBFC));//UnityEngine.CoreModule
    return (void*)get_transform_injected(player);
}

//Camera.WorldToScreenPoint_Injected
//public Vector3 WorldToScreenPoint(Vector3 position, MonoorSetreo..., out Vector3)
Vector3 WorldToScreenPoint(void *transform, Vector3 test) {
    if (!transform)
        return Vector3();
    Vector3 position;
    static const auto WorldToScreenPoint_Injected = reinterpret_cast<uint64_t(__fastcall *)(void *,
                                                                                            Vector3, int, Vector3 &)>(getAbsoluteAddress(
            targetLibName, 0x39A1FEC));
    WorldToScreenPoint_Injected(transform, test, 4, position);
    return position;
}

void setScale(void *component, Vector3 scale) {
    void* transform = get_transform(component);
    set_localScale(transform, scale);
}



void MeScaleDown(void *myplayer, Vector3 vector3) {
    Vector3 mysize = get_localScale(get_transform(myplayer));
    Vector3 mysize2 = mysize + Vector3(-0.5f, -0.5f, -0.5f);
    set_localScale(get_transform(myplayer), mysize2);
}


void* myPlayer = NULL;
void *enemyPlayer = NULL;

void* myPlayerloc = NULL;


int GetPlayerTeam(void* player) {
    return *(int*)((uint64_t)player + 0x6C);
}// myPlayer


bool PlayerAlive(void *player) {
    return player != NULL && GetPlayerTeam(player) > 0;
}
bool IsPlayerDead(void *player) {
    return player == NULL && GetPlayerTeam(player) < 1;
}


//CameraManager.get_Main();
void *get_camera() {
    static const auto get_camera_injected = reinterpret_cast<uint64_t(__fastcall *)()>(getAbsoluteAddress(
            targetLibName, 0x1702980));
    return (void *) get_camera_injected();
}

Vector3 GetPlayerLocation1(void *player){ Vector3 location;
    location = get_position(get_transform(player));
    return location;
}


Vector3 GetPlayerLocation(void* player){
    return get_position(get_transform(player));
}


//Screen.get_height();
int get_screen_height() {
    static const auto get_height_injected = reinterpret_cast<uint64_t(__fastcall *)()>(getAbsoluteAddress(
            targetLibName, 0x1584338));
    return (int) get_height_injected();
}

//Screen.get_width();
int get_screen_width() {
    static const auto get_width_injected = reinterpret_cast<uint64_t(__fastcall *)()>(getAbsoluteAddress(
            targetLibName, 0x15842F0));
    return (int) get_width_injected();
}

#endif