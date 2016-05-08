#include <GL/freeglut.h>
#include "ship.h"
#include <include/shapes.h>
#include <include/timer.h>
#include "planet.h"
#include <include/gaf_math.h>
#include "defines.h"
#include "start_params.h"
#include <include/textutils.h>

Ship::Ship(GLfloat ivx, GLfloat ivy, Planet *planet) : BaseActor()
{
	this->planet = planet;
    vx = ivx;
    vy = ivy;
    hidx = -1;
    maxh = -1;
	transform->rotation = 45.0f;
}

void Ship::draw_me()
{
    glColor4ub(0, 192, 0, 100);
    
	//GLfloat radius = 0.1f;
    //glSolidCircle(radius, 12);
	GLfloat w = ship_size;
	glIsoTriangle(w * 0.75f, w, w / 3.0f);
    
    /*for (int i = 0; i <= maxh; i++)
    {
		reset();
        int dh = (i <= hidx) ? (hidx - i) : (hidx + hist_size - i);
        GLfloat dhf = 1.0f - ((float)dh / (float)hist_size);
        GLubyte c = (int) (dhf * 192.0f); 
        glColor4ub(0, c, 0, 0);
        glTranslatef(hx[i], hy[i], 0);
        glSolidCircle(0.05f, 3);
	}*/

	glPushMatrix();
	glLoadIdentity();
	glColor3ub(192, 192, 192);
	textReset(2);
	textOutFloat(r_to_d(planetSurfacePosition));
	glPopMatrix();
}

void Ship::update(Timer *timer)
{
	save_history(timer);

	GLfloat rs = distanceSquared(planet->transform, transform);
	GLfloat a = GravConstant * planet->mass / rs;
	GLfloat t = angleTo(transform, planet->transform);
	GLfloat ax = a * cos(t);
	GLfloat ay = a * sin(t);

	if (isThrust)
	{
		GLfloat force = ship_thrust;
		ax -= force * sin(d_to_r(transform->rotation));
		ay += force * cos(d_to_r(transform->rotation));
	}

	vx += ax * timer->intervalSeconds();
	vy += ay * timer->intervalSeconds();

    GLfloat dx = vx * timer->intervalSeconds();
    GLfloat dy = vy * timer->intervalSeconds();
    transform->translate_x += dx;
    transform->translate_y += dy;

	calc_readings();
}

void Ship::calc_readings()
{
	planetSurfacePosition = angleTo(planet->transform, transform);
}

void Ship::input(Keyboard * keyboard)
{
	GLfloat rotateInc = 5.0f;

	if (keyboard->special[GLUT_KEY_LEFT])
	{
		transform->rotation += rotateInc;
	}
	if (keyboard->special[GLUT_KEY_RIGHT])
	{
		transform->rotation -= rotateInc;
	}

 	isThrust = keyboard->special[GLUT_KEY_UP];
}

void Ship::save_history(Timer *timer)
{
    if ((timer->totalTicks - lastHist) < 100)
    {
        return;
    }
    lastHist = timer->totalTicks;
    
    hidx++;
    if (hidx >= hist_size)
    {
        hidx = 0;
    }
    if (hidx > maxh)
    {
        maxh = hidx;
    }
    
    hx[hidx] = transform->translate_x;
    hy[hidx] = transform->translate_y;
}