#version 460 core
precision mediump float;

uniform sampler2D tex;
uniform vec2  source_pos;
uniform vec2  source_size;

uniform float  amount;

in	vec2 tex_coord;
out	vec4 fragColor;

void	main()
{
	vec3 color = vec3(texture(tex, tex_coord * source_size + source_pos));
	float b = 0;
	b += color.r;
	b += color.g;
	b += color.b;
	b /= 3.0;
	color = mix(color, vec3(b, b, b), amount);
	fragColor = vec4(color, 1.0);
}
