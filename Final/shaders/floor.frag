#ifdef GL_ES
precision highp float;
#endif

uniform sampler2D texture0; 

varying vec2 uv0Varying;

varying vec4 camDist;

void main()
{
	vec4 diffuseColor = vec4(0.8, 0.7, 0.4, 1.);
	float viewDist = 7;
	float diffuseAmount = 1 - (length(camDist) / viewDist);

	clamp(diffuseAmount, 1, 0);

	vec4 finalColor = texture2D(texture0, uv0Varying) * (diffuseColor * diffuseAmount);

	gl_FragColor =  finalColor;
}