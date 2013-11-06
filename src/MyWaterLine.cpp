#include "MyWaterLine.h"

MyWaterLine::MyWaterLine() {

}

MyWaterLine::MyWaterLine(string heightmap, string bumpmap, string vert_shader,
		string frag_shader) {
	shader.init(vert_shader.c_str(), frag_shader.c_str());
	this->heightmap = heightmap;
	this->bumpmap = bumpmap;
}

MyWaterLine::~MyWaterLine() {

}

void MyWaterLine::setAppearance(string appearance) {
	MyPrimitive::setAppearance(appearance);
}

void MyWaterLine::draw() {
	shader.bind();

	shader.unbind();
}
