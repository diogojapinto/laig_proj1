#include "myHalfSphere.h"
#include <math.h>

myHalfSphere::myHalfSphere(int slices, int stacks, bool smooth) {
	if (slices < 3 || stacks <= 0) {
		slices = 0;
		stacks = 0;
		this->smooth = false;
	} else {
		this->slices = slices;
		this->stacks = stacks;
		this->smooth = smooth;
	}

	double ang_stack = 90.0 / (double) stacks;
	double ang_slice = 360.0 / (double) slices;

	x1p = (double*) new double[(slices + 1) * stacks];
	y1p = (double*) new double[(slices + 1) * stacks];
	z1p = (double*) new double[(slices + 1) * stacks];
	x2p = (double*) new double[(slices + 1) * stacks];
	y2p = (double*) new double[(slices + 1) * stacks];
	z2p = (double*) new double[(slices + 1) * stacks];
	x3p = (double*) new double[(slices + 1) * stacks];
	y3p = (double*) new double[(slices + 1) * stacks];
	z3p = (double*) new double[(slices + 1) * stacks];
	x4p = (double*) new double[(slices + 1) * stacks];
	y4p = (double*) new double[(slices + 1) * stacks];
	z4p = (double*) new double[(slices + 1) * stacks];

	for (int i = 0; i < stacks; i++) {
		for (int k = 0; k <= slices; k++) {
			x1p[(i * (slices)) + k] = sin(DegToRad(k * ang_slice))
					* sin(DegToRad(i * ang_stack));
			z1p[(i * (slices)) + k] = cos(DegToRad(k * ang_slice))
					* sin(DegToRad(i * ang_stack));
			y1p[(i * (slices)) + k] = cos(DegToRad(i * ang_stack));

			x2p[(i * (slices)) + k] = sin(DegToRad((k + 1.0) * ang_slice))
					* sin(DegToRad(i * ang_stack));
			z2p[(i * (slices)) + k] = cos(DegToRad((k + 1.0) * ang_slice))
					* sin(DegToRad(i * ang_stack));
			y2p[(i * (slices)) + k] = cos(DegToRad(i * ang_stack));

			x3p[(i * (slices)) + k] = sin(DegToRad((k + 1.0) * ang_slice))
					* sin(DegToRad((i + 1.0)) * ang_stack);
			z3p[(i * (slices)) + k] = cos(DegToRad((k + 1.0) * ang_slice))
					* sin(DegToRad((i + 1.0)) * ang_stack);
			y3p[(i * (slices)) + k] = cos(DegToRad((i + 1.0) * ang_stack));

			x4p[(i * (slices)) + k] = sin(DegToRad(k * ang_slice))
					* sin(DegToRad((i + 1.0) * ang_stack));
			z4p[(i * (slices)) + k] = cos(DegToRad(k * ang_slice))
					* sin(DegToRad((i + 1.0) * ang_stack));
			y4p[(i * (slices)) + k] = cos(DegToRad((i + 1.0) * ang_stack));

		}
	}
}

void myHalfSphere::draw() {
	if (!smooth)
		glShadeModel(GL_FLAT);
	for (int i = 0; i < stacks; i++) {
		for (int k = 0; k <= slices; k++) {
			glBegin(GL_QUADS);
			if (smooth)
				glNormal3d(x4p[(i * (slices)) + k], 0, z4p[(i * (slices)) + k]);
			else
				glNormal3d(
						x4p[(i * (slices)) + k] + x3p[(i * (slices)) + k]
								+ x2p[(i * (slices)) + k]
								+ x1p[(i * (slices)) + k], 0,
						z4p[(i * (slices)) + k] + z3p[(i * (slices)) + k]
								+ z2p[(i * (slices)) + k]
								+ z1p[(i * (slices)) + k]);
			glVertex3d(x4p[(i * (slices)) + k], y4p[(i * (slices)) + k],
					z4p[(i * (slices)) + k]);
			if (smooth)
				glNormal3d(x3p[(i * (slices)) + k], 0, z3p[(i * (slices)) + k]);
			glVertex3d(x3p[(i * (slices)) + k], y3p[(i * (slices)) + k],
					z3p[(i * (slices)) + k]);
			if (smooth)
				glNormal3d(x2p[(i * (slices)) + k], 0, z2p[(i * (slices)) + k]);
			glVertex3d(x2p[(i * (slices)) + k], y2p[(i * (slices)) + k],
					z2p[(i * (slices)) + k]);
			if (smooth)
				glNormal3d(x1p[(i * (slices)) + k], 0, z1p[(i * (slices)) + k]);
			glVertex3d(x1p[(i * (slices)) + k], y1p[(i * (slices)) + k],
					z1p[(i * (slices)) + k]);
			glEnd();
		}
	}
	if (!smooth)
		glShadeModel(GL_SMOOTH);
}
