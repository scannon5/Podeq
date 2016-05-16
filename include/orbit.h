#pragma once

#include <include/gaf.h>
#include <include/update_task.h>
#include <include/timer.h>

class Ship2;
class Planet;

class Orbit : public UpdateTask
{
public:
    Orbit(Planet *planet, Ship2 *ship);

    glf Rp;
	glf Ra;
	glf nu;
	glf angle;
	glf e;
	glf a;
	glf mean_motion;

	glf debug;

    void calc(glf rx, glf ry, glf vx, glf vy, glf GM);
    void calc(glf planet_x, glf planet_y, glf ship_x, glf ship_y, glf vx, glf vy, glf GM);
	void calc();
	void update(Timer *timer);
	bool is_hyperbolic();
	Vector2f position_at_time(glf t);
private:
	Planet *planet;
	Ship2 *ship;
	
};