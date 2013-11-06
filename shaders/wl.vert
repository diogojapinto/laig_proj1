uniform float delta;
uniform sampler2D heightmap;

int main() {
	vec2 tex_displace(delta, 0.0);
	vec4 hight_component = texture2D(heightmap, gl_MultiTexCoord0.st + tex_displace);
	vec3 pt_displace(delta, hight.r, 0.0);
	gl_Position = gl_ProjectionMatrix * glModelViewMatrix * (displacement + gl_Vertex);
	gl_TexCoord[0].st = gl_MultiTexCoord0.st + tex_displace;
}