#include<raylib.h>
#include<raymath.h>
#include<iostream>




int main(){

	const int screenWidth = 1600;
	const int screenHeight = 1000;
	InitWindow(screenWidth, screenHeight, "I hate mondays");


	Camera camera;
	camera.position = { 20.0,20.0,20.0 };
	camera.target = { 0,10,0 };
	camera.up = { 0,1,0 };
	camera.fovy = 45.0f;//just for experimenting with later
	camera.projection = CAMERA_PERSPECTIVE;

	Model knight = LoadModel("3dmodels/brute_knight.glb");
	Texture text=knight.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture;

	Vector3 pos = { 0,0,0 };
	if (knight.meshCount > 0) {
	BoundingBox bounds = GetMeshBoundingBox(knight.meshes[0]);

	}
	else {
		printf( "error occurred in loading");
		return -1;
	}

	DisableCursor();
	SetTargetFPS(60);

	while (!WindowShouldClose()) {

	BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);
		UpdateCamera(&camera, CAMERA_PERSPECTIVE);
			DrawModel(knight, pos, 1, WHITE);
			DrawGrid(20, 1.0);

		EndMode3D();

		DrawText("3d model test",500,300,20,BLACK);





		EndDrawing();

	}

	UnloadTexture(text);
	UnloadModel(knight);
	CloseWindow();


	return 0;
}