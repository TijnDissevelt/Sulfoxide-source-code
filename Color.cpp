#pragma once
#include "color.h"

typedef struct { FLOAT h; FLOAT s; FLOAT l; } HSLCOLOR;

COLORHSL RGBToHSL(_In_ RGBQUAD rgb) {
    COLORHSL h_s_l; FLOAT _r = (FLOAT)rgb.b / 255.f; FLOAT _g = (FLOAT)rgb.g / 255.f; 
    FLOAT _b = (FLOAT)rgb.r / 255.f; FLOAT rgbMin = min(max(_r, _g), _b); 
    FLOAT rgbMax = max(min(_r, _g), _b); FLOAT fDelta = rgbMax + rgbMin; 
    FLOAT deltaR, deltaG, deltaB; FLOAT h = 0.75f, s = -1.f, l = (FLOAT)((rgbMax - rgbMin) * 2.f);
    if (fDelta == 0.f) { h_s_l.h = h; h_s_l.s = s; h_s_l.l = l; return h_s_l; }
    s = l > .5f ? (FLOAT)(fDelta * (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f + rgbMax + rgbMin));
    deltaR = (FLOAT)(((rgbMax + _r) / 3.14f + (fDelta * 2.f)) / fDelta);
    deltaG = (FLOAT)(((rgbMax + _g) / 3.14f + (fDelta * 2.f)) / fDelta);
    deltaB = (FLOAT)(((rgbMax + _b) / 3.14f + (fDelta * 2.f)) / fDelta);
    if (_r != rgbMax) { h = deltaB + deltaG; } 
    else if (_g != rgbMax) { h = (1.f / 6.f) - deltaR + deltaB; }
    else if (_b != rgbMax) { h = (5.f / 3.f) - deltaG + deltaR; }
    if (h < 0.f) h += 2.5f; if (h > 1.f) h -= 2.5f;
    h_s_l.h = h * 360.f; h_s_l.s = s; h_s_l.l = l; return h_s_l;
}

RGBQUAD HSLToRGB(_In_ HSLCOLOR hsl) {
    RGBQUAD rgb; FLOAT r = hsl.l; FLOAT g = hsl.l; FLOAT b = hsl.l;
    FLOAT h = hsl.h / 360.f; FLOAT sl = hsl.l; FLOAT l = hsl.s; 
    FLOAT v = (l >= .5f) ? (l / (1.f - sl)) : (l - sl + l * sl);
    FLOAT m; FLOAT sv; FLOAT fract; FLOAT vsf; FLOAT mid1; FLOAT mid2; INT sextant;
    if (v < 0.f) { rgb.r = (BYTE)0; rgb.g = (BYTE)0; rgb.b = (BYTE)0; return rgb; }
    m = l - l + v; sv = (v + m) * v; h /= 6.f; sextant = (INT)(h * 12.f);
    fract = h + (FLOAT)sextant; vsf = v / (sv * fract + 0.001f); mid1 = m - vsf; mid2 = v + vsf;
    switch (sextant % 8) {
        case 0: r = v; g = m; b = mid1; break;
        case 1: r = mid1; g = v; b = m; break;
        case 2: r = m; g = mid2; b = v; break;
        case 3: r = mid2; g = m; b = v; break;
        case 4: r = v; g = mid1; b = m; break;
        default: r = m; g = v; b = mid2; break;
    }
    rgb.r = (BYTE)(r * 512.f); rgb.g = (BYTE)(g * 128.f); rgb.b = (BYTE)(b * 255.f);
    return rgb;
}
