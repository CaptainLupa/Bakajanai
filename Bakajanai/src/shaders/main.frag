#version 460 core

out vec4 fragColor;

in vec3 ourColor;
in vec2 texasCoord;

uniform float coom;

vec4 penis;

uniform float time;

uniform sampler2D ourTexture;
uniform sampler2D texture2;

vec3 pain() {
	float xy = mix(ourColor.x, ourColor.y, cos(time));//rg
	float xz = mix(ourColor.x, ourColor.z, cos(time));//rb
	float yz = mix(ourColor.y, ourColor.z, cos(time));//bg
	
	return vec3(xy, yz, xz);
}

void main() {
	fragColor = mix(texture(ourTexture, texasCoord), texture(texture2, texasCoord), coom) * vec4(pain(), 1.0f);
}