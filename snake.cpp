#include "raylib.h"
#include <vector>
enum Screen {Menu, Game};
int main() {
    InitWindow(600, 400, "Snake");
    SetTargetFPS(60);

    Screen screen = Menu;
    Rectangle start_button {250, 90, 100, 40};
    Rectangle easy_button {250, 180, 100, 40};
    Rectangle hard_button {250, 270, 100, 40};

    std::vector<Vector2> snake = {{100.0f, 100.0f}, {80.0f, 100.0f}, {60.0f, 100.0f}};
    Vector2 fruit = {300.0f, 200.0f};

    Vector2 direction = {1.0f, 0.0f};
    Vector2 next_direction = {1.0f, 0.0f};

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
            if (CheckCollisionPointRec(GetMousePosition(), easy_button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                move_delay = 0.15f;
            }
            if (CheckCollisionPointRec(GetMousePosition(), hard_button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                move_delay = 0.08f;
            }
    
        }
        else if (screen == Game && is_alive) {
            // change direction on key press
            if (IsKeyPressed(KEY_RIGHT) && direction.x != -1){
                next_direction = {1.0f, 0.0f};
            }
            if (IsKeyPressed(KEY_LEFT) && direction.x != 1){
                next_direction = {-1.0f, 0.0f};
            }
            if (IsKeyPressed(KEY_UP) && direction.y != 1){
                next_direction = {0.0f, -1.0f};
            }
            if (IsKeyPressed(KEY_DOWN) && direction.y != -1){
                next_direction = {0.0f, 1.0f};
            }
            move_timer += GetFrameTime();
            if (move_timer >= move_delay) {
                direction = next_direction;
                
                // calculate where head will be
                Vector2 next_head = {
                    snake[0].x + direction.x * 20,
                    snake[0].y + direction.y * 20
                };

                // check wall window size 600 * 400
                if (next_head.x < 0 || next_head.x >= 600 || next_head.y < 0 || next_head.y >= 400){
                    is_alive = false;
                }
                //check tail collision
                for (int i = 0; i < snake.size(); i ++){
                    if (next_head.x == snake[i].x && next_head.y == snake[i].y){
                        is_alive = false;
                    }
                }
                // move snake and check fruit

                if (is_alive){
                    snake.insert(snake.begin(), next_head);
                    if (next_head.x == fruit.x && next_head.y == fruit.y){
                        fruit.x = GetRandomValue(0, 29) * 20;
                        fruit.y = GetRandomValue(0, 19) * 20;
                    }
                    else{
                        snake.pop_back();
                    }
                }

                move_timer = 0.0f;
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
                DrawRectangle(fruit.x, fruit.y, 20, 20, RED);

                for (int i = 0; i < snake.size(); i ++ ){
                    DrawRectangle(snake[i].x, snake[i].y, 20, 20, GREEN);
                }
            
            }
            if (!is_alive){
                DrawText("GAME OVER", 210, 180, 30, WHITE);
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}