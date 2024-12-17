#include<string>
#include<iostream>
#include<raylib.h>

int endstate=5;

Color Green = Color{ 38, 183, 154, 255 };
Color darkblue = Color{ 28, 38, 221, 90 };
Color Cyan = Color{ 29, 215, 222, 50 };

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum Gamescreen { Title=0,Main_menu = 1,gameplay=2, ending=3 }Gamescreen;


class ball {

	
public:
	int radius;
	float x;
	float y;

	int speed_x = 6;
	int speed_y = 6;
	
public:
	ball() {
		radius = 20;
		x = 900;
		y = 500;
	}

	void Draw() {
		DrawCircle(x, y, radius, WHITE);

	}
	void update() {
		x += speed_x;
		y += speed_y;

		if (y + radius == GetScreenHeight() || (y-radius)<=0) {
			speed_y *= -1;
		}
		if (x + radius >= GetScreenWidth() || (x+radius<=0)) {
			speed_x *= -1;
		}
	}

};

int main() {

	//--------------------------------------------------------------------------------------
	//setting the window dimensions
	//--------------------------------------------------------------------------------------
	const int window_length = 1800;
	const int window_height = 1000;
	 float paddle_length = 100;//height
	 float paddle_width = 20;
	
	ball Ball;
	
	float player1_x = 50;
	float player2_x =window_length-50 ;
	float player1_y = (window_height / 2) - paddle_length;
	float player2_y = player1_y;

	
	int player1_score = 0;
	
	int player2_score = 0;
	

	int framecounter = 0;

	InitWindow(window_length, window_height, "pong");
	SetTargetFPS(60);
	Gamescreen current_screen = Title;
	//main game loop
	while (!WindowShouldClose()) {

		HideCursor();
		BeginDrawing();
		ClearBackground(BLACK);

		//checking for collisions

		

		switch (current_screen) {

			case Title: //we will make it count frames for 2 seconds for example then switch 
			{

			DrawText("Pong ", window_length/2, 0, 30, Cyan);
			DrawText("presented to you by :", window_length/2, 200, 30, Cyan);
			DrawText("bookey", window_length/2, 400, 30, Cyan);
			framecounter++;

			//wait for 3 seconds before anything happens
			if (framecounter > 120) {
				current_screen = Main_menu;
			}


		}break;

			case Main_menu: {

			DrawText("Main menu ", window_length/2, 400, 30, WHITE);
			DrawText("Press enter to start ", window_length/2, 500, 30, RAYWHITE);
			if (IsKeyPressed(KEY_ENTER)) {
				current_screen = gameplay;
			}
		}break;

		case gameplay:
		{
			DrawFPS(window_length-100,100);
			std::string score1 = std::to_string(player1_score);

			std::string score2 = std::to_string(player2_score);

			if ((Ball.x) + (Ball.radius) >= window_length) {
				player1_score++;

			}
			if ((Ball.x) + Ball.radius <= 0) {
				player2_score++;
			}
			Rectangle paddle1 = { player1_x,player1_y,paddle_width,paddle_length };
			Rectangle paddle2 = { player2_x,player2_y,paddle_width,paddle_length };

			
			Vector2 ballposition = { Ball.x,Ball.y };

			

			if (CheckCollisionCircleRec(ballposition, Ball.radius, paddle1)) {

				Ball.speed_x *= -1;

			}

			if (CheckCollisionCircleRec(ballposition, Ball.radius, paddle2)) {

				Ball.speed_x *= -1;

			
			}

			Ball.update();
			//----------------------------------------------------------
			//here the gameplay starts
			//----------------------------------------------------------
			
			//start position first 

			ClearBackground(Green);

			DrawText("Start ", window_length / 2 -50, 0, 30, DARKGRAY);
			DrawText(score1.c_str(),(window_length / 2)-150,0,30,GREEN );
			DrawText(score2.c_str(), (window_length / 2) + 150, 0, 30, RED);
			//first paddle 
			DrawRectangle(player1_x,player1_y,paddle_width,paddle_length,RAYWHITE);
			//second paddle
			DrawRectangle(player2_x,player2_y, paddle_width, paddle_length, RAYWHITE);

			DrawLine(window_length / 2, 0, window_length / 2, window_height,GRAY);
			
			Ball.Draw();

			
			
			if (IsKeyDown('w') || IsKeyDown('W')) {
				player1_y -=10;
			}
			if (IsKeyDown('s') || IsKeyDown('S')) {
				player1_y += 10;
			}
			if (IsKeyDown('i') || IsKeyDown('I')) {
				player2_y -= 10;
			}
			if (IsKeyDown('K') || IsKeyDown('k')) {
				player2_y += 10;
			}
			
			if (player1_y > window_height-paddle_length) {
				player1_y = window_height-paddle_length;

			}
			if (player1_y < 0) {
				player1_y = 0;
			}

			if (player2_y > window_height - paddle_length) {
				player2_y = window_height - paddle_length;

			}
			if (player2_y < 0) {
				player2_y = 0;
			}

			if (player1_score == 3) {
				endstate = 0;
				current_screen = ending;
			}
			if (player2_score == 3) {
				endstate = 1;
				current_screen = ending;
			}
			
			if(IsKeyPressed(KEY_SPACE) || IsGestureDetected(KEY_SPACE)){
				CloseWindow();
				break;
				
			}
			
		}break;
		case ending:
		{
			ClearBackground(BLACK);

			if (endstate == 0) {
				DrawText("player 1 has won !!", window_length / 2, 0, 30, DARKGREEN);
			}
			else if (endstate == 1) {
				DrawText("player 2 has won !!", window_length / 2, 0, 30, DARKGREEN);
			}
			else DrawText("sth wrong has occured",window_length / 2, 0, 30, DARKGREEN);
		};
		default:break;

		}
		EndDrawing();
	}
	





	
	return 0;
	}
