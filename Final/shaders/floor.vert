attribute vec3 position;
attribute vec3 normal;
attribute vec2 uv;

uniform mat4 agk_WorldViewProj;
uniform mat4 agk_World;

uniform vec4 uvBounds0;

varying vec2 uv0Varying;

uniform vec4 camPos;

varying vec4 camDist;

void main()
{
	vec4 pos = agk_World * vec4(position, 1);
	camDist = camPos - pos;

	vec4 finalPos = agk_WorldViewProj * vec4(position,1);

	/*if(pos.x > 0.3)
	{
		finalPos.y = finalPos.y - 3;
	}*/

	gl_Position = finalPos;

	uv0Varying = uv * uvBounds0.xy + uvBounds0.zw;  
}