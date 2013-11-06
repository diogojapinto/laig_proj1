uniform float delta;
uniform sampler2D heightmap;
uniform sampler2D texturemap;

int main() {
	vec3 displace(delta, 0.0);
	gl_FragColor = texture2D((texturemap + displacement), gl_TexCoord[0].st);
}