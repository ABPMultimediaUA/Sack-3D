#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;


varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 diff0;


uniform mat4 transform;
//uniform vec3 lightDiff;

void main(){
	gl_Position = transform * vec4(position,1.0); //El indicador es un multiplicador para la traslacion
	texCoord0 = texCoord;

//	diff0= normalize (vec3(lightDiff - position));
	//ambiente0 = ambientLight;
	normal0= (transform * vec4(normal, 0.0)).xyz;
}