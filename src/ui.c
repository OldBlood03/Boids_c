#include"ui.h"
#include<assert.h>

static bool isDragging = false;

bool is_mouse_in_box (int x, int y, int width, int height){
    int mx = GetMouseX();
    int my = GetMouseY();
    if ((x <= mx) && (mx <= (x+width)) && (y <= my) && (my <= (y+height))) return true;
    return false;
}

static bool Fits (Rectangle rect, const char text[static 100], int font_size){
    if (rect.height < font_size) return false;
    if (rect.width < MeasureText(text, font_size)) return false;
    return true;
}

static bool IsTight (Rectangle rect, const char text[static 100], int font_size){
    if ((rect.height == font_size) && (rect.width == MeasureText(text, font_size))) return true;
    return false;
}

static int FitTextToRect (Rectangle rect, const char text[static 100]){
    constexpr unsigned max_iters = 20;
    int font_size = GetFontDefault().baseSize;

    while (Fits(rect, text, font_size)){
        font_size *= 2;
    }

    int mid_point = font_size/2;
    for (unsigned i = 0; i < max_iters; i++){

        if (IsTight(rect, text, mid_point)) {
            return mid_point;
        }

        if (Fits(rect, text, mid_point)){
            mid_point += (font_size - mid_point)/2;
            continue;
        }

        font_size = mid_point;
        mid_point = mid_point/2;

    }
    return mid_point;
}

void DrawButton(Button button){
    int x = button.rect.x;
    int y = button.rect.y;
    int width = button.rect.width;
    int height = button.rect.height;
    Color rect_color = RED;
    Color text_color = WHITE;
    int font_size = FitTextToRect(button.rect, button.text);

    DrawRectangle(x,y,width,height, rect_color);
    DrawText(button.text, x, y, font_size, text_color);
}

bool IsButtonPressed(Button button){
    int x = GetMouseX();
    int y = GetMouseY();
    int rect_x = button.rect.x;
    int rect_y = button.rect.y;
    int rect_width = button.rect.width;
    int rect_height = button.rect.height;
    if ((x < rect_x) || (x > (rect_x + rect_width)) || (y < rect_y) || (y > (rect_y + rect_height))){
        return false;
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        return true;
    }
    return false;
}

bool IsDraggingSlider (const Slider slider[static 1]){
    const Vector2 cursor_pos = {.x = GetMouseX(), .y = GetMouseY()};
    const Vector2 knob_pos = {.x = slider->rect.x + (int)(slider->rect.width * slider->completion),
        .y = slider->rect.y + slider->rect.height/2};

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        isDragging = false;
    }
    if (CheckCollisionPointCircle(cursor_pos, knob_pos, slider -> knob_radius) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        isDragging = true; 
    }
    return isDragging;
}

void DragSlider(Slider slider[static 1]){
    int mousex = GetMouseX();
    slider->completion = (mousex - slider->rect.x)/(slider->rect.width);
    slider->completion = slider->completion >= 0.0 ? slider->completion : 0.f;
    slider->completion = slider->completion <= 1.0 ? slider->completion : 1.f;
}

static Vector2 PositionText(TextAlignment alignment, int font_size, const Slider slider[static 1]){
    const int vertical_padding = (slider -> knob_radius) - (slider -> rect.height/2);
    const int horizontal_padding = (slider -> knob_radius);

    switch (alignment){
        case NONE:
            // just position it off screen 
            return (Vector2) {.x = -MeasureText(slider -> text, font_size), .y = -font_size};
        case UP:
            return (Vector2) {.x = (slider -> rect.x), .y = (slider -> rect.y) - vertical_padding - font_size};
        case DOWN:
            return (Vector2) {.x = (slider -> rect.x), .y = (slider -> rect.y) + (slider -> rect.height) + vertical_padding + font_size};
        case LEFT:
            return (Vector2) {.x = (slider -> rect.x) - MeasureText(slider -> text, font_size) - horizontal_padding, .y = (slider -> rect.y)};
        case RIGHT:
            return (Vector2) {.x = (slider -> rect.x) + horizontal_padding, .y = (slider -> rect.y)};
    }
    assert (0 && "UNEXPECTED TEXT ALLIGNMENT VALUE");
}

void DrawSlider(const Slider slider[static 1], TextAlignment alignment){
    constexpr float roundness = 1.f;
    constexpr int parts = 10; 
    constexpr int font_size = 3;

    int x = slider -> rect.x + (int)(slider -> rect.width * slider -> completion);
    int y = slider -> rect.y + slider -> rect.height/2;

    const Vector2 text_position = PositionText(alignment, font_size, slider);

    DrawRectangleRounded(slider -> rect, roundness, parts, RED);
    DrawCircle(x, y, slider -> knob_radius, WHITE);
    DrawText(slider -> text, text_position.x, text_position.y, font_size, WHITE);

}
