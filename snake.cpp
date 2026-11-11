#include "raylib.h"
#include <vector>
enum Screen {Menu, Game};

void DrawHoverButton(Rectangle btn, const char* text, int id = -1, int* activeId = nullptr) {
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), btn);
    
    // update id 

    if (activeId != nullptr && isHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        *activeId = id;
    }
    // check if the button is selected
    bool isActive = (activeId != nullptr && *activeId == id);

    float expand = isHovered ? 8.0f : 0.0f;
    Rectangle drawRect = { 
        btn.x - expand / 2.0f, 
        btn.y - expand / 2.0f, 
        btn.width + expand, 
        btn.height + expand 
    };

    Color btnColor = isActive ? RED : (isHovered ? GRAY : DARKGRAY);
    Color btnText = isActive ? WHITE : YELLOW;

    DrawRectangleRec(drawRect, btnColor);

    int fontSize = isHovered ? 22 : 20;
    int textWidth = MeasureText(text, fontSize);
    int textX = drawRect.x + (drawRect.width - textWidth) / 2;
    int textY = drawRect.y + (drawRect.height - fontSize) / 2;
    DrawText(text, textX, textY, fontSize, btnText);
}



int main() {
    InitWindow(600, 400, "Snake");
    SetTargetFPS(60);

    Screen screen = Menu;
    Rectangle start_button {250, 90, 100, 40};
    Rectangle easy_button {250, 180, 100, 40};
    Rectangle hard_button {250, 270, 100, 40};
    Rectangle retry_button {250, 270, 100, 40};
    std::vector<Vector2> snake = {{100.0f, 100.0f}, {80.0f, 100.0f}, {60.0f, 100.0f}};
    Vector2 fruit = {300.0f, 200.0f};

    Vector2 direction = {1.0f, 0.0f};
    Vector2 next_direction = {1.0f, 0.0f};

    bool is_alive = true;
    float move_timer = 0.0f;
    float move_delay = 0.15f;
    int active_difficulty = -1;
    int score = 0;

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
                        score += 1;
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
        else if (screen == Game && !is_alive){
            if (CheckCollisionPointRec(GetMousePosition(), retry_button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                screen = Menu;
                is_alive = true;
                snake = {{100.0f, 100.0f}, {80.0f, 100.0f}, {60.0f, 100.0f}};
                direction = {1.0f, 0.0f};
                next_direction = {1.0f, 0.0f};
                fruit = {300.0f, 200.0f};
                move_timer = 0.0f;
                score = 0;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        // just draw here
        if (screen == Menu){
            // what does the menu look like
            // draw the tile the buttons, the numbers
            DrawHoverButton(start_button, "Start"); 
            DrawHoverButton(easy_button, "Easy", 0, &active_difficulty);
            DrawHoverButton(hard_button, "Hard", 1, &active_difficulty);
        }

        else if (screen == Game){
            // what does the game look like
            // draw the snake the food the score
            if (is_alive){
                DrawRectangle(fruit.x, fruit.y, 20, 20, RED);

                for (int i = 0; i < snake.size(); i ++ ){
                    DrawRectangle(snake[i].x, snake[i].y, 20, 20, GREEN);
                }
                
                // score board
                DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
            }
            if (!is_alive){
                DrawText("GAME OVER", 210, 180, 30, WHITE);
                DrawHoverButton(retry_button, "Retry"); 
                DrawText(TextFormat("Final Score: %d", score), 230, 230, 20, YELLOW);
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}