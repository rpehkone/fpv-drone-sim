#version 460 core
precision mediump float;

#include random.glsl

uniform sampler2D tex;
uniform vec2  source_pos;
uniform vec2  source_size;

uniform float  seed;
uniform float  amount;

in	vec2 tex_coord;
out	vec4 fragColor;

void	main()
{
	vec3 color = vec3(texture(tex, tex_coord * source_size + source_pos));
	float r = rand_float((tex_coord.x * tex_coord.y) * seed);
	color = mix(color, vec3(r), amount);
	fragColor = vec4(color, 1.0);
}
