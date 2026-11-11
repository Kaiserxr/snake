#include "raylib.h"
enum Screen {Menu, Game};
int main() {
    InitWindow(600, 400, "Snake");
    SetTargetFPS(60);

    Screen screen = Menu;
    Rectangle start_button {250, 90, 100, 40};
    Rectangle easy_button {250, 180, 100, 40};
    Rectangle hard_button {250, 270, 100, 40};

    Vector2 curr_pos = {100.0f, 100.0f};
    Vector2 direction = {1.0f, 0.0f};
    bool is_alive = true;
    float move_timer = 0.0f;
    float move_delay = 0.15f;

    while (!WindowShouldClose()) {
        if (screen == Menu){
            // what happen when player does stuff
            // button clicked ?
            if (CheckCollisionPointRec(GetMousePosition(), start_button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            screen = Game;
            }
    
        }
        else if (screen == Game && is_alive) {
            // change direction on key press
            if (IsKeyPressed(KEY_RIGHT) && direction.x != -1){
                direction = {1.0f, 0.0f};
            }
            if (IsKeyPressed(KEY_LEFT) && direction.x != 1){
                direction = {-1.0f, 0.0f};
            }
            if (IsKeyPressed(KEY_UP) && direction.y != 1){
                direction = {0.0f, -1.0f};
            }
            if (IsKeyPressed(KEY_DOWN) && direction.y != -1){
                direction = {0.0f, 1.0f};
            }
            move_timer += GetFrameTime();
            if (move_timer >= move_delay) {
                curr_pos.x += direction.x * 20;
                curr_pos.y += direction.y * 20;
                move_timer = 0.0f; // Reset timer
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        // just draw here
        if (screen == Menu){
            // what does the menu look like
            // draw the tile the buttons, the numbers
            DrawRectangleRec(start_button, DARKGRAY);
            DrawText("Start", 270, 100, 20, WHITE);
            DrawRectangleRec(easy_button, DARKGRAY);
            DrawText("Easy", 270, 190, 20, WHITE);
            DrawRectangleRec(hard_button, DARKGRAY);
            DrawText("Hard", 270, 280, 20, WHITE);
        }
        else if (screen == Game){
            // what does the game look like
            // draw the snake the food the score
            if (is_alive){
                DrawRectangle(curr_pos.x, curr_pos.y, 20, 20, GREEN);
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}