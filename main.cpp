#include "raylib.h"

struct Ball {
	float x, y;
	float speedX, speedY;
	float radius;
	Color color;

	Vector2 GetVec() {
		return Vector2{ x, y };
	}

	void Draw() {
		DrawCircle((int)x, (int)y, radius, color);
	}
};

struct Paddle {
	float x, y;
	float speed;
	float width, height;
	Color color;

	Rectangle GetRect() {
		return Rectangle{ x - width / 2, y - height / 2, width, height };
	}

	void Draw() {
		DrawRectangleRec(GetRect(), color);
	}
};


int main() {
	InitWindow(800, 600, "Ping Pong by notflask");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;

	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 250;
	ball.speedY = 250;
	ball.color = WHITE;

	Paddle lPaddle;

	lPaddle.x = 50;
	lPaddle.y = GetScreenHeight() / 2;
	lPaddle.speed = 500;
	lPaddle.width = 10;
	lPaddle.height = 100;
	lPaddle.color = WHITE;

	Paddle rPaddle;

	rPaddle.x = GetScreenWidth() - 50;
	rPaddle.y = GetScreenHeight() / 2;
	rPaddle.speed = 500;
	rPaddle.width = 10;
	rPaddle.height = 100;
	rPaddle.color = WHITE;

	const char* winnerText = nullptr;

	while (!WindowShouldClose()) {
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		if (ball.y < 0) {
			ball.y = 0;
			ball.speedY *= -1;
		} else if (ball.y > GetScreenHeight()) {
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}
		
		if (IsKeyDown(KEY_W)) { lPaddle.y -= lPaddle.speed * GetFrameTime(); }
		if (IsKeyDown(KEY_S)) { lPaddle.y += lPaddle.speed * GetFrameTime(); }
		if (IsKeyDown(KEY_UP)) { rPaddle.y -= rPaddle.speed * GetFrameTime(); }
		if (IsKeyDown(KEY_DOWN)) { rPaddle.y += rPaddle.speed * GetFrameTime(); }

		if (CheckCollisionCircleRec(ball.GetVec(), ball.radius, rPaddle.GetRect())) {
			
			if (ball.speedX > 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rPaddle.y) / (rPaddle.height / 2) * -ball.speedX;
			}
		}
		if (CheckCollisionCircleRec(ball.GetVec(), ball.radius, lPaddle.GetRect())) {
			if (ball.speedX < 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - lPaddle.y) / (lPaddle.height / 2) * ball.speedX;
			}
		}

		if (ball.x < 0) {
			winnerText = "		  Right Player Wins!\nPress Space to Restart.";

			rPaddle.speed = 0;
			lPaddle.speed = 0;
		}

		if (ball.x > GetScreenWidth()) {
			winnerText = "		  Left Player Wins!\nPress Space to Restart.";
			rPaddle.speed = 0;
			lPaddle.speed = 0;
		}

		if (winnerText && IsKeyDown(KEY_SPACE)) {
			ball.x = GetScreenWidth() / 2.0f;
			ball.y = GetScreenHeight() / 2.0f;
			ball.radius = 5;
			ball.speedX = 250;
			ball.speedY = 250;
			ball.color = WHITE;

			lPaddle.x = 50;
			lPaddle.y = GetScreenHeight() / 2;
			lPaddle.speed = 500;
			lPaddle.width = 10;
			lPaddle.height = 100;
			lPaddle.color = WHITE;

			rPaddle.x = GetScreenWidth() - 50;
			rPaddle.y = GetScreenHeight() / 2;
			rPaddle.speed = 500;
			rPaddle.width = 10;
			rPaddle.height = 100;
			rPaddle.color = WHITE;


			winnerText = nullptr;
		}

		BeginDrawing();
			ClearBackground(BLACK);

			ball.Draw();
			lPaddle.Draw();
			rPaddle.Draw();

			if (winnerText) {
				int textWidth = MeasureText(winnerText, 36);
				DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 36, WHITE);
			}

			DrawFPS(10, 10);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}