#pragma once

#include <include/entity.h>
#include <include/vector2f.h>
#include <include/update_task.h>
#include <include/input_task.h>
#include <include/timer.h>
#include <include/keyboard.h>

class PodeqGame;

class Ship2 : public Entity, public UpdateTask, public InputTask
{
public:
	Ship2(PodeqGame *game, Vector2f pos, Vector2f vel);
	void update(Timer *timer);
	void input(Keyboard *keyboard);
private:
	PodeqGame *game;
	Vector2f v;
	bool isThrust;
	void create_ship();
};