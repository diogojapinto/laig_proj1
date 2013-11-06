#include "MyWaterLine.h"
#include "GL/gl.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "Scene.h"
#include <time.h>

MyWaterLine::MyWaterLine() : Plane(100) {
	delta = 0;
	prev_delta = 0;
}

MyWaterLine::MyWaterLine(string heightmap, string texturemap, string vert_shader,
		string frag_shader) : Plane(100) {
	shader.init(vert_shader.c_str(), frag_shader.c_str());
	Scene::getInstance()->addTexture("wl_height", heightmap);
	Scene::getInstance()->addTexture("wl_text", texturemap);
	height.setTextProp("wl_height", 1, 1);
	text.setTextProp("wl_height", 1, 1);
	delta = 0;
	prev_delta = 0;
	glutTimerFunc(ANIMATION_TIME, updateWaterLine, 0);
}

MyWaterLine::~MyWaterLine() {

}

void MyWaterLine::setAppearance(string appearance) {
	MyPrimitive::setAppearance(appearance);
}

void MyWaterLine::draw() {
	shader.bind();
	GLint delta_loc = glGetUniformLocation(shader.id(), "delta");
	glUniform1f(delta_loc, delta);

	GLint text_loc = glGetUniformLocation(shader.id(), "texturemap");
	glUniform1i(delta_loc, 0);

	GLint height_loc = glGetUniformLocation(shader.id(), "heightmap");
	glUniform1i(delta_loc, 1);

	glActiveTexture(GL_TEXTURE0);
	text.apply();
	glActiveTexture(GL_TEXTURE1);
	height.apply();
	Plane::draw();
	shader.unbind();
	glActiveTexture(GL_TEXTURE0);
}

void updateWaterLine(int i) {
	struct timespec t;

	clock_gettime(CLOCK_MONOTONIC, &t);
	MyWaterLine::prev_delta = MyWaterLine::delta;
	MyWaterLine::delta = MyWaterLine::prev_delta + (t.tv_nsec * 0.000000001) / 10.0;
	if (MyWaterLine::delta > 1) {
		MyWaterLine::delta -= 1;
	}
}
