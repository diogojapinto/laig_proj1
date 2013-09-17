#include "Plane.h"
#include "myUnitCube.h"

//#include <fstream>

//using namespace std;
Plane::Plane(void) {
	_numDivisions = 1;
}

Plane::Plane(int n) {
	_numDivisions = n;
}

Plane::~Plane(void) {
}

void Plane::draw() {
	glPushMatrix();

	glRotatef(180.0, 1, 0, 0);
	glTranslatef(-0.5, 0.0, -0.5);
	glScalef(1.0 / (double) _numDivisions, 1, 1.0 / (double) _numDivisions);
	glNormal3f(0, -1, 0);
	for (int bx = 0; bx < _numDivisions; bx++) {
		glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d((double) bx / (double) _numDivisions, 0);
		glVertex3f(bx, 0, 0);
		for (int bz = 0; bz < _numDivisions; bz++) {
			glTexCoord2d((double) (bx + 1) / (double) _numDivisions,
					(double) bz / (double) _numDivisions);
			glVertex3f(bx + 1, 0, bz);
			glTexCoord2d((double) bx / (double) _numDivisions,
					(double) (bz + 1) / (double) _numDivisions);
			glVertex3f(bx, 0, bz + 1);
		}
		glTexCoord2d((double) (bx + 1) / (double) _numDivisions, 1);
		glVertex3d(bx + 1, 0, _numDivisions);

		glEnd();
	}
	glPopMatrix();

}

void Plane::drawUndistorted(int x_res, int y_res) {

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	if (y_res > x_res) {
		double ratio = (double) y_res / (double) x_res;
		glPushMatrix();
		glRotatef(180.0, 1, 0, 0);
		glTranslatef(-0.5, 0.0, -0.5);
		glScalef(1.0 / (double) _numDivisions, 1, 1.0 / (double) _numDivisions);
		glNormal3f(0, -1, 0);

		for (int bx = 0; bx < _numDivisions; bx++) {
			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2d((double) bx / (double) _numDivisions,
					0 - (ratio / 8.0));
			glVertex3f(bx, 0, 0);
			for (int bz = 0; bz < _numDivisions; bz++) {
				glTexCoord2d((double) (bx + 1) / (double) _numDivisions,
						(double) bz / (double) _numDivisions * ratio
								- (ratio / 8.0));
				glVertex3f(bx + 1, 0, bz);
				glTexCoord2d((double) bx / (double) _numDivisions,
						(double) (bz + 1) / (double) _numDivisions * ratio
								- (ratio / 8.0));
				glVertex3f(bx, 0, bz + 1);
			}
			glTexCoord2d((double) (bx + 1) / (double) _numDivisions,
					1 * ratio - (ratio / 8.0));
			glVertex3d(bx + 1, 0, _numDivisions);

			glEnd();
		}
		glPopMatrix();
	} else {
		double ratio = (double) x_res / (double) y_res;
		glPushMatrix();
		glRotatef(180.0, 1, 0, 0);
		glTranslatef(-0.5, 0.0, -0.5);
		glScalef(1.0 / (double) _numDivisions, 1, 1.0 / (double) _numDivisions);
		glNormal3f(0, -1, 0);

		for (int bx = 0; bx < _numDivisions; bx++) {
			glBegin(GL_TRIANGLE_STRIP);

			glTexCoord2d(
					(double) bx / (double) _numDivisions * ratio
							- (ratio / 8.0), 0);
			glVertex3f(bx, 0, 0);
			for (int bz = 0; bz < _numDivisions; bz++) {
				glTexCoord2d(
						(double) (bx + 1) / (double) _numDivisions * ratio
								- (ratio / 8.0),
						(double) bz / (double) _numDivisions);
				glVertex3f(bx + 1, 0, bz);
				glTexCoord2d(
						(double) bx / (double) _numDivisions * ratio
								- (ratio / 8.0),
						(double) (bz + 1) / (double) _numDivisions);
				glVertex3f(bx, 0, bz + 1);
			}
			glTexCoord2d(
					(double) (bx + 1) / (double) _numDivisions * ratio
							- (ratio / 8.0), 1);
			glVertex3d(bx + 1, 0, _numDivisions);

			glEnd();
		}
		glPopMatrix();
	}
}

void Plane::drawRepeated() {
	glPushMatrix();

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glRotatef(180.0, 1, 0, 0);
	glTranslatef(-0.5, 0.0, -0.5);
	glScalef(1.0 / (double) _numDivisions, 1, 1.0 / (double) _numDivisions);
	glNormal3f(0, -1, 0);
	for (int bx = 0; bx < _numDivisions; bx++) {
		glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d((double) bx * 10 / (double) _numDivisions, 0);
		glVertex3f((float) bx, 0, 0);
		for (int bz = 0; bz < _numDivisions; bz++) {
			glTexCoord2d((double) (bx + 1) * 10 / (double) _numDivisions,
					(double) bz * 12 / (double) _numDivisions);
			glVertex3f((float) (bx + 1), 0, (float) bz);
			glTexCoord2d((double) bx * 10 / (double) _numDivisions,
					(double) (bz + 1) * 12 / (double) _numDivisions);
			glVertex3f((float) bx, 0, (float) (bz + 1));
		}
		glTexCoord2d((double) (bx + 1) * 10 / (double) _numDivisions, 1 * 12);
		glVertex3f((float) (bx + 1), 0, (float) _numDivisions);

		glEnd();
	}
	glPopMatrix();
}

void Plane::drawCentered() {
	glPushMatrix();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glRotatef(180.0, 1, 0, 0);
	glRotatef(-90.0, 0, 1, 0);
	glTranslatef(-0.5, 0.0, -0.5);
	glScalef(1.0 / (double) _numDivisions, 1, 1.0 / (double) _numDivisions);
	glNormal3f(0, -1, 0);
	for (int bx = 0; bx < _numDivisions; bx++) {
		glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d((double) bx * 3 / (double) _numDivisions - 0.85, 0 - 0.5);
		glVertex3f((float) bx, 0, 0);
		for (int bz = 0; bz < _numDivisions; bz++) {
			glTexCoord2d((double) (bx + 1) * 3 / (double) _numDivisions - 0.85,
					(double) bz * 2 / (double) _numDivisions - 0.5);
			glVertex3f((float) (bx + 1), 0, (float) bz);
			glTexCoord2d((double) bx * 3 / (double) _numDivisions - 0.85,
					(double) (bz + 1) * 2 / (double) _numDivisions - 0.5);
			glVertex3f((float) bx, 0, (float) (bz + 1));
		}
		glTexCoord2d((double) (bx + 1) * 3 / (double) _numDivisions - 0.85,
				1 * 2 - 0.5);
		glVertex3f((float) (bx + 1), 0, (float) _numDivisions);

		glEnd();
	}
	glPopMatrix();
}

void Plane::drawWithTexLimits(double s_init, double s_end, double t_init,
		double t_end) {
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glPushMatrix();

	glRotatef(180.0, 1, 0, 0);
	glTranslatef(-0.5, 0.0, -0.5);
	glScalef(1.0 / (double) _numDivisions, 1, 1.0 / (double) _numDivisions);
	glNormal3f(0, -1, 0);
	for (int bx = 0; bx < _numDivisions; bx++) {
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2d(s_init + (bx * (s_end - s_init) / (double) _numDivisions),
				t_init);
		glVertex3f(bx, 0, 0);
		for (int bz = 0; bz < _numDivisions; bz++) {
			glTexCoord2d(
					s_init
							+ ((bx + 1) * (s_end - s_init)
									/ (double) _numDivisions),
					t_init + (bz * (t_end - t_init) / (double) _numDivisions));
			glVertex3f(bx + 1, 0, bz);
			glTexCoord2d(
					s_init + (bx * (s_end - s_init) / (double) _numDivisions),
					t_init
							+ ((bz + 1) * (t_end - t_init)
									/ (double) _numDivisions));
			glVertex3f(bx, 0, bz + 1);
		}
		glTexCoord2d(
				s_init + ((bx + 1) * (s_end - s_init) / (double) _numDivisions),
				t_init
						+ (_numDivisions * (t_end - t_init)
								/ (double) _numDivisions));
		glVertex3d(bx + 1, 0, _numDivisions);
		glEnd();
	}
	glPopMatrix();

}
