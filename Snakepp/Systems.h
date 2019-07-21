#ifndef SYSTEM_H 
#define SYSTEM_H
#include "Console.h"
#include "Map.h"
#include "Vec.h"
#include "Snake.h"
#include "Fruit.h"
#include "Systems.h"

void handleConsoleDraw(fruit_t& fruit, snake_t& snake, Console& console, Map& map) {
	wchar_t head;
	if (snake.isDead) {
		console.putLine(0, L"Score: %d => GAME OVER!!!", snake.score);
		head = 'X';
	}
	else {
		console.putLine(0, L"Score: %d                ", snake.score);
		head = 'O';
	}

	for (unsigned int row = 1; row < console.getHeight(); ++row) {
		for (unsigned int col = 0; col < console.getWidth(); ++col) {
			wchar_t value = map.get(col, row - 1) == 1 ? '#' : ' ';
			console.put(col, row, value);
		}
	}

	//Draw Snake
	for (size_t i = 0; i < snake.tailSize; i++)
		console.put(snake.tail[i].x, snake.tail[i].y + 1, 'o');
	console.put(snake.cell.x, snake.cell.y + 1, head);

	//Draw Fruit
	if (fruit.spawned)
		console.put(fruit.cell.x, fruit.cell.y + 1, 'F');

	console.flush();
}

void handleSnakeMoves(snake_t& snake, float deltaTime) {
	if (snake.isDead) return;
	if (GetAsyncKeyState((unsigned short)'A') & 0x8000) { snake.dir.x = -1; snake.dir.y = 0; }
	if (GetAsyncKeyState((unsigned short)'D') & 0x8000) { snake.dir.x = 1; snake.dir.y = 0; }
	if (GetAsyncKeyState((unsigned short)'W') & 0x8000) { snake.dir.x = 0; snake.dir.y = -1; }
	if (GetAsyncKeyState((unsigned short)'S') & 0x8000) { snake.dir.x = 0; snake.dir.y = 1; }

	vec_t<unsigned int> prevCell = snake.cell;  //copy-cstr

	snake.pos.x += snake.dir.x * snake.speed * deltaTime;
	snake.pos.y += snake.dir.y * snake.speed * deltaTime;
	snake.cell.x = static_cast<unsigned int>(snake.pos.x);
	snake.cell.y = static_cast<unsigned int>(snake.pos.y);
	if (prevCell == snake.cell) {
		snake.hasMoved = false;
		return;
	}

	snake.hasMoved = true;
	for (size_t i = 0; i < snake.tailSize; ++i)
	{
		vec_t<unsigned int> prevTailCell = snake.tail[i];  //copy-cstr
		snake.tail[i] = prevCell;                          //assign-copy-oper
		prevCell = prevTailCell;                           //assign-copy-oper
	}
}

void handleRestart(fruit_t& fruit, snake_t& snake) {
	if (GetAsyncKeyState((unsigned short)'R') & 0x8000) {
		snake = {};
		fruit = {};
	}
}

float spawnPassedTime = 0;
void handleFruitSpawn(fruit_t& fruit, snake_t& snake, Map& map, int waitSeconds, float deltaTime) {
	if (snake.isDead) return;
	if (fruit.spawned) return;
	if (spawnPassedTime < waitSeconds) { spawnPassedTime += deltaTime; return; }
	spawnPassedTime = 0;
	fruit.spawned = true;
	srand(time(NULL));
	fruit.cell.x = rand() % (map.getWidth() - 2) + 1;
	fruit.cell.y = rand() % (map.getHeight() - 2) + 1;
}

void handleFruitTaken(fruit_t& fruit, snake_t& snake) {
	if (snake.isDead) return;
	if (!fruit.isTaken) return;
	fruit.isTaken = false;
	fruit.spawned = false;
	snake.score += 10;
	snake.speed++;

	// Add 2 element to the tail
	if (snake.tailSize < snake.tailMaxSize) {
		snake.tail[snake.tailSize++] = snake.cell;
		snake.tail[snake.tailSize++] = snake.cell;
	}
}

void handleCollision(fruit_t& fruit, snake_t& snake, Map& map) {
	if (!snake.hasMoved) return;

	if (snake.isDead) return;
	if (map.get(snake.cell) == 1) snake.isDead = true;
	for (unsigned int i = 0; i < snake.tailSize; i++) {
		if (snake.cell == snake.tail[i]) {
			snake.isDead = true;
			break;
		}
	}

	if (!fruit.spawned) return;
	if (snake.cell == fruit.cell) fruit.isTaken = true;
}

#endif