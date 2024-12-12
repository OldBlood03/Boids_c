#ifndef UI
#define UI
#include"raylib.h"

typedef enum TextAlignment {
    NONE = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
} TextAlignment;

typedef struct Button{
    Rectangle rect;
    const char text[100];
} Button;

typedef struct Slider{
    Rectangle rect;
    float completion;
    float knob_radius;
    const char text[100];
} Slider;

void DrawButton(Button button);
bool IsButtonPressed(Button button);
void DrawSlider(const Slider slider[static 1], TextAlignment alignment);
void DragSlider(Slider slider[static 1]);
bool IsDraggingSlider (const Slider slider[static 1]);

#endif
