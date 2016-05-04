#include <math.h>
#include <GL/freeglut.h>
#include "gaf_math.h" 
#include <include/transform.h>

GLfloat angleBetween(GLfloat ux, GLfloat uy, GLfloat vx, GLfloat vy)
{
    GLfloat angle = atan2(vy, vx) - atan2(uy, ux);
    if (angle < 0)
    {
        angle += TWO_PI;
    }
    return angle;
}

GLfloat r_to_d(GLfloat r)
{
	return 360.0f * (r / TWO_PI);
}

GLfloat d_to_r(GLfloat r)
{
	return TWO_PI * (r / 360.0f);
}

GLfloat distanceSquared(Transform *t1, Transform *t2)
{
	return SQR(t1->translate_x - t2->translate_x) + SQR(t1->translate_y - t2->translate_y);
}

GLfloat angleTo(Transform *me, Transform *target)
{
	GLfloat dx = (target->translate_x - me->translate_x);
	GLfloat dy = (target->translate_y - me->translate_y);
	if (dx == 0)
	{
		return dy > 0 ? PI_BY_2 : 3 * PI_BY_2;
	}
	else
	{
		GLfloat res = atan(dy / dx);
		if (dx < 0)
		{
			res += PI;
		}
		else if (dy < 0)
		{
			res += TWO_PI;
		}
		return res;
	}
}
