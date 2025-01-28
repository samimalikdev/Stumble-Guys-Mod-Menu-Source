#ifndef SamiEsp_H
#define SamiEsp_H

#include <jni.h>
#include <Unity/Rect.h>
#include <hook.h>
#include "Color.h"

class SamiEsp {
private:
    JNIEnv *_env;
    jobject _cvsView;
    jobject _cvs;

public:
    SamiEsp() {
        _env = nullptr;
        _cvsView = nullptr;
        _cvs = nullptr;
    }

    SamiEsp(JNIEnv *env, jobject cvsView, jobject cvs) {
        this->_env = env;
        this->_cvsView = cvsView;
        this->_cvs = cvs;
    }

    bool isValid() const {
        return (_env != nullptr && _cvsView != nullptr && _cvs != nullptr);
    }

    int getWidth() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getWidth", "()I");
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }

    int getHeight() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getHeight", "()I");
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }

    void DrawLine(Color color, float thickness, Vector2 start, Vector2 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawLine",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.X, start.Y, end.X, end.Y);
        }
    }



    void DrawText(Color color, const char *txt, Vector2 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawText",
                                                   "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 _env->NewStringUTF(txt), pos.X, pos.Y, size);
        }
    }



    void DrawFilledCircle(Color color, Vector2 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawfilledcircle = _env->GetMethodID(canvasView, "DrawFilledCircle",
                                                           "(Landroid/graphics/Canvas;IIIIFFF)V");
            _env->CallVoidMethod(_cvsView, drawfilledcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.X, pos.Y, radius);
        }
    }

    void DrawBox(Color color, float stroke, Rect rect) {
        Vector2 v1 = Vector2(rect.x, rect.y);
        Vector2 v2 = Vector2(rect.x + rect.w, rect.y);
        Vector2 v3 = Vector2(rect.x + rect.w, rect.y + rect.h);
        Vector2 v4 = Vector2(rect.x, rect.y + rect.h);

        DrawLine(color, stroke, v1, v2);
        DrawLine(color, stroke, v2, v3);
        DrawLine(color, stroke, v3, v4);
        DrawLine(color, stroke, v4, v1);
    }

    void DrawHorizontalHealthBar(Vector2 screenPos, float width, float maxHealth, float currentHealth) {
        screenPos -= Vector2(0.0f, 8.0f);
        DrawBox(Color(0, 0, 0, 255), 3, Rect(screenPos.X, screenPos.Y, width + 2, 5.0f));
        screenPos += Vector2(1.0f, 1.0f);
        Color clr = Color(0, 255, 0, 255);
        float hpWidth = (currentHealth * width) / maxHealth;
        if (currentHealth <= (maxHealth * 0.6)) {
            clr = Color(255, 255, 0, 255);
        }
        if (currentHealth < (maxHealth * 0.3)) {
            clr = Color(255, 0, 0, 255);
        }
        DrawBox(clr, 3, Rect(screenPos.X, screenPos.Y, hpWidth, 3.0f));
    }

    void Draw3dBox(SamiEsp esp,Color espColor, Vector3 Transform,void * camera,int glHeight,int glWidth)
    {
        Vector3 position2 = add(Transform, Vector3(0.6, 1.6, 0.6));
        Vector3 position3 = add(Transform, Vector3(0.6, 0, 0.6));
        Vector3 position4 = add(Transform, Vector3(-0.5, 0, 0.6));
        Vector3 position5 = add(Transform, Vector3(-0.5, 1.6, 0.6));
        Vector3 position6 = add(add(Transform, Vector3(0.6, 1.6, 0)), Vector3(0, 0, -0.6));
        Vector3 position7 = add(add(Transform, Vector3(0.6, 0, 0)), Vector3(0, 0, -0.6));
        Vector3 position8 = add(add(Transform, Vector3(-0.5, 0, 0)), Vector3(0, 0, -0.6));
        Vector3 position9 = add(add(Transform, Vector3(-0.5, 1.6, 0)), Vector3(0, 0, -0.6));

        Vector3 vector = WorldToScreenPoint(camera, position2);
        Vector3 vector2 = WorldToScreenPoint(camera, position3);
        Vector3 vector3 = WorldToScreenPoint(camera, position4);
        Vector3 vector4 = WorldToScreenPoint(camera, position5);
        Vector3 vector5 = WorldToScreenPoint(camera, position6);
        Vector3 vector6 = WorldToScreenPoint(camera, position7);
        Vector3 vector7 = WorldToScreenPoint(camera, position8);
        Vector3 vector8 = WorldToScreenPoint(camera, position9);

        if (vector.Z > 0 && vector2.Z > 0 && vector3.Z > 0 && vector4.Z > 0 && vector5.Z > 0 && vector6.Z > 0 && vector7.Z > 0 && vector8.Z > 0 )
        {
            esp.DrawLine(espColor, 6, Vector2((glWidth -(glWidth -vector.X)), (glHeight - vector.Y)), Vector2((glWidth - (glWidth - vector2.X)), (glHeight - vector2.Y)));
            esp.DrawLine(espColor, 6, Vector2((glWidth -(glWidth -vector3.X)), (glHeight - vector3.Y)), Vector2((glWidth - (glWidth - vector2.X)), (glHeight - vector2.Y)));
            esp.DrawLine(espColor, 6, Vector2((glWidth -(glWidth -vector.X)), (glHeight - vector.Y)), Vector2((glWidth - (glWidth - vector4.X)), (glHeight - vector4.Y)));
            esp.DrawLine(espColor, 6, Vector2((glWidth -(glWidth -vector4.X)), (glHeight - vector4.Y)), Vector2((glWidth - (glWidth - vector3.X)), (glHeight - vector3.Y)));

            esp.DrawLine(espColor, 6, Vector2((glWidth -(glWidth -vector5.X)), (glHeight - vector5.Y)), Vector2((glWidth - (glWidth - vector6.X)), (glHeight - vector6.Y)));
            esp.DrawLine(espColor, 6, Vector2((glWidth -(glWidth -vector7.X)), (glHeight - vector7.Y)), Vector2((glWidth - (glWidth - vector6.X)), (glHeight - vector6.Y)));
            esp.DrawLine(espColor, 6, Vector2((glWidth -(glWidth -vector5.X)), (glHeight - vector5.Y)), Vector2((glWidth - (glWidth - vector8.X)), (glHeight - vector8.Y)));
            esp.DrawLine(espColor, 6, Vector2((glWidth -(glWidth -vector8.X)), (glHeight - vector8.Y)), Vector2((glWidth - (glWidth - vector7.X)), (glHeight - vector7.Y)));

            esp.DrawLine(espColor, 6, Vector2((glWidth -(glWidth -vector.X)), (glHeight - vector.Y)), Vector2((glWidth - (glWidth - vector5.X)), (glHeight - vector5.Y)));
            esp.DrawLine(espColor, 6, Vector2((glWidth -(glWidth -vector2.X)), (glHeight - vector2.Y)), Vector2((glWidth - (glWidth - vector6.X)), (glHeight - vector6.Y)));
            esp.DrawLine(espColor, 6, Vector2((glWidth -(glWidth -vector3.X)), (glHeight - vector3.Y)), Vector2((glWidth - (glWidth - vector7.X)), (glHeight - vector7.Y)));
            esp.DrawLine(espColor, 6, Vector2((glWidth -(glWidth -vector4.X)), (glHeight - vector4.Y)), Vector2((glWidth - (glWidth - vector8.X)), (glHeight - vector8.Y)));
        }
    }

    void DrawCircle(Color color,float stroke, Vector2 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawcircle = _env->GetMethodID(canvasView, "DrawCircle",
                                                     "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,stroke, pos.X, pos.Y, radius);
        }
    }

    void DrawCrosshair(Color clr, Vector2 center, float size = 20) {
        float x = center.X - (size / 2.0f);
        float y = center.Y - (size / 2.0f);
        DrawLine(clr, 3, Vector2(x, center.Y), Vector2(x + size, center.Y));
        DrawLine(clr, 3, Vector2(center.X, y), Vector2(center.X, y + size));
    }
};

#endif

