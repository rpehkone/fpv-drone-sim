#version 460 core
precision mediump float;

#include random.glsl

uniform sampler2D tex;
uniform vec2  source_pos;
uniform vec2  source_size;

uniform float  seed;
uniform float  amount;
uniform float  texture_width;

in	vec2 tex_coord;
out	vec4 fragColor;

void	main()
{
	vec2 uv = tex_coord;
	float offx = (rand_float(tex_coord.y + seed) * 2.0 - 1.0) * amount;
	uv.x += offx / texture_width;
	vec3 color = vec3(texture(tex, uv * source_size + source_pos));
	fragColor = vec4(color, 1.0);
}
