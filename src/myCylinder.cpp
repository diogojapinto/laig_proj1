#include "myCylinder.h"
#include <math.h>

myCylinder::myCylinder(int slices, int stacks, bool smooth) {
	if (slices < 3 || stacks <= 0) {
		slices = 0;
		stacks = 0;
		this->smooth = false;
	} else {
		this->slices = slices;
		this->stacks = stacks;
		this->smooth = smooth;
	}

	double alturaStacks = 1.0 / (double) stacks;
	double ang_slice = 360.0 / (double) slices;

	xp = (double*) new double[slices + 1];
	yp = (double*) new double[stacks + 1];
	zp = (double*) new double[slices + 1];

	xp[0] = 0.0;
	yp[0] = -0.5;
	zp[0] = 1.0;

	for (int k = 1; k <= slices; k++) {
		xp[k] = sin(DegToRad(k * ang_slice));
		zp[k] = cos(DegToRad(k * ang_slice));
	}
	for (int a = 1; a <= stacks; a++) {
		yp[a] = yp[a - 1] + alturaStacks;
	}
}

void myCylinder::draw() {
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (!smooth)
		glShadeModel(GL_FLAT);
	for (int k = 0; k < slices; k++) {
		glNormal3d(0.0, 1.0, 0.0);
		glBegin(GL_TRIANGLES);
		glVertex3d(xp[k + 1], 0.5, zp[k + 1]);
		glVertex3d(0.0, 0.5, 0.0);
		glVertex3d(xp[k], 0.5, zp[k]);
		glEnd();

		glNormal3d(0.0, -1.0, 0.0);
		glBegin(GL_TRIANGLES);
		glVertex3d(xp[k], -0.5, zp[k]);
		glVertex3d(0.0, -0.5, 0.0);
		glVertex3d(xp[k + 1], -0.5, zp[k + 1]);
		glEnd();

		for (int i = 0; i < stacks; i++) {
			glBegin(GL_QUADS);
			if (smooth)
				glNormal3d(xp[k + 1], 0, zp[k + 1]);
			else
				glNormal3d(xp[k + 1] + xp[k], 0, zp[k + 1] + zp[k]);
			glTexCoord2d((double) k / (double) slices,
					(double) i / (double) stacks);
			glVertex3d(xp[k + 1], yp[i], zp[k + 1]);
			glTexCoord2d((double) k / (double) slices,
					((double) i + 1) / (double) stacks);
			glVertex3d(xp[k + 1], yp[i + 1], zp[k + 1]);
			if (smooth)
				glNormal3d(xp[k], 0, zp[k]);
			else
				glNormal3d(xp[k + 1] + xp[k], 0, zp[k + 1] + zp[k]);
			glVertex3d(xp[k], yp[i + 1], zp[k]);
			glTexCoord2d((double) k / (double) slices,
					(double) i / (double) stacks);
			glVertex3d(xp[k], yp[i], zp[k]);
			glEnd();
		}
	}
	if (!smooth)
		glShadeModel(GL_SMOOTH);
}

void myCylinder::drawFlat() {

	if (!smooth)
		glShadeModel(GL_FLAT);
	for (int k = 0; k < slices; k++) {
		glNormal3d(0.0, 1.0, 0.0);
		glBegin(GL_TRIANGLES);
		glTexCoord2d(0.5 + xp[k + 1] * 0.5, 0.5 + (-zp[k + 1] * 0.5));
		glVertex3d(xp[k + 1], 0.5, zp[k + 1]);
		glTexCoord2d(0.5, 0.5);
		glVertex3d(0.0, 0.5, 0.0);
		glTexCoord2d(0.5 + xp[k] * 0.5, 0.5 + (-zp[k] * 0.5));
		glVertex3d(xp[k], 0.5, zp[k]);
		glEnd();

		glNormal3d(0.0, -1.0, 0.0);
		glBegin(GL_TRIANGLES);
		glVertex3d(xp[k], -0.5, zp[k]);
		glVertex3d(0.0, -0.5, 0.0);
		glVertex3d(xp[k + 1], -0.5, zp[k + 1]);
		glEnd();

		for (int i = 0; i < stacks; i++) {
			glBegin(GL_QUADS);
			if (smooth)
				glNormal3d(xp[k + 1], 0, zp[k + 1]);
			else
				glNormal3d(xp[k + 1] + xp[k], 0, zp[k + 1] + zp[k]);
			glVertex3d(xp[k + 1], yp[i], zp[k + 1]);
			glVertex3d(xp[k + 1], yp[i + 1], zp[k + 1]);
			if (smooth)
				glNormal3d(xp[k], 0, zp[k]);
			else
				glNormal3d(xp[k + 1] + xp[k], 0, zp[k + 1] + zp[k]);
			glVertex3d(xp[k], yp[i + 1], zp[k]);
			glVertex3d(xp[k], yp[i], zp[k]);
			glEnd();
		}
	}
	if (!smooth)
		glShadeModel(GL_SMOOTH);
}

myCylinder::~myCylinder() {
	delete (xp);
	delete (yp);
	delete (zp);
}
