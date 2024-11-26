#include<raylib.h>
#include<iostream>


void load_cube(Vector3 pos) {

	DrawCube(pos, 2.0, 2.0, 2.0, RED);
	DrawCubeWires(pos, 2.0, 2.0, 2.0f, BLUE);
}


Vector2 Screensizes[2] = {
		{GetScreenWidth(), GetScreenHeight()}, 
		{ 800,800 }
};


int main() {
	

	int option = 0;


	InitWindow(Screensizes[option].x,Screensizes[option].y,"3d with raylib");
	
	SetTargetFPS(60);
	Vector3 initpos = { 0,0,0 };

	Camera3D camera = { 0};
	camera.target = {10,10,10};
	camera.up = { 0,1,0 };
	camera.fovy = { 45.0 };
	camera.projection = { CAMERA_FREE};
	
	UpdateCamera(&camera, CAMERA_FREE);

	while (!WindowShouldClose()) {
		HideCursor();

		BeginDrawing();
		DrawText("Welcome to 3d test", GetScreenWidth() / 2, 150, 20, BLUE);
		DrawText("to move camera in y ,Press up-down",GetScreenWidth()-300,150,15,RED);
		DrawText("to move camera in x ,Press right-left", GetScreenWidth() - 300, 200, 15, RED);
		DrawText("to change screen size,Press x", GetScreenWidth() - 300, 250, 15, RED);

		ClearBackground(RAYWHITE);
		BeginMode3D(camera);
		load_cube(initpos);
		DrawGrid(50, 1.0f);
		DrawLine3D({ 0,-50,0 }, { 0,50,0 },BLACK);

		if (IsKeyPressed(KEY_S)) {
			initpos.x -= 10;
		}
		if (IsKeyPressed(KEY_W)) {
			initpos.x += 10;
		}
		if (IsKeyPressed(KEY_D)) {
			initpos.z += 10;
		}
		if (IsKeyPressed(KEY_A)) {
			initpos.z -= 10;
		}


		if (IsKeyDown(KEY_RIGHT)) {
			camera.position.x++;
		}
		if (IsKeyDown(KEY_LEFT)) {
			camera.position.x--;
		}
		if (IsKeyDown(KEY_UP)) {
			camera.position.y++;
		}
		if (IsKeyDown(KEY_DOWN)) {
			camera.position.y--;
		}
		if (IsKeyDown(KEY_SPACE)) {
			camera.position.z++;
		}
		if (IsKeyDown(KEY_LEFT_CONTROL)) {
			camera.position.z--;
		}
		EndDrawing();
		EndMode3D();
	}


	CloseWindow();
	return 0;
}

