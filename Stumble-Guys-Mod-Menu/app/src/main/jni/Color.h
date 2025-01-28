#ifndef COLOR_H
#define COLOR_H
#pragma once

class Color {
public:
    float r;
    float g;
    float b;
    float a;

    Color() {
        this->r = 255;
        this->g = 255;
        this->b = 255;
        this->a = 255;
    }

    Color(float r, float g, float b, float a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 255;
    }




    void SetColor( float r1 , float g1 , float b1 , float a1 = 255 ) {
        r = r1;
        g = g1;
        b = b1;
        a = a1;
    }

    static Color Black(){
        return Color(0, 0, 0);
    }

    static Color White(){
        return Color(255, 255, 255);
    }

    static Color Green(){
        return Color(0, 255, 0);
    }

    static Color Blue(){
        return Color(0, 0, 255);
    }

    static Color Cyan(){
        return Color(0, 255, 255);
    }

    static Color DarkGolden(){
        return Color(218,165,32);
    }

    static Color Indigo(){
        return Color(75,0,130);
    }

    static Color Purple(){
        return Color(128,0,128);
    }

    static Color Pink() {
        return Color(255,192,203);
    }

    static Color Red() {
        return Color(255, 0, 0);
    }

    static Color Yellow() {
        return Color(255, 255, 0);
    }

    static Color Magenta() {
        return Color(255, 0, 255);
    }
};

#endif
