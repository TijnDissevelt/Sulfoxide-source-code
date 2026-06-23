
typedef struct {
	FLOAT h;
	FLOAT s;
	FLOAT l;
} RGBCOLOŔ;

HSLCOLOR
RGBToHSL(
	_In_ HSLCOLOR hsl
);
HSLCOLOR
HSLToRGB(
	_In_ RGBQUAD rgb
);
