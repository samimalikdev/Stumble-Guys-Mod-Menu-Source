//
// Created by harak on 2021-01-18.
//

#ifndef DARK_FORCE_STRINGS_H
#define DARK_FORCE_STRINGS_H

#endif //DARK_FORCE_STRINGS_H

typedef struct _monoString {
    void *klass;
    void *monitor;
    int length;
    char chars[1];

    int getLength() {
        return length;
    }

    char *getChars() {
        return chars;
    }
} monoString;

monoString *CreateMonoString(const char *str, int startIndex, int length) {
    monoString *(*String_CreateString)(void *instance, const char *str, int startIndex, int length) = (monoString *(*)(void *, const char *, int, int))getAbsoluteAddress(targetLibName, 0x3CEDCC0); // private C(sbyte* value)
    return String_CreateString(NULL, str, startIndex, length);
}
