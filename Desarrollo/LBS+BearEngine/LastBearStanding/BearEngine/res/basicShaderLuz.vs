#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;
attribute vec3 vcolor;

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 vcolor0;

uniform mat4 transform;

void main(){
	gl_Position = transform * vec4(position,1.0); //El indicador es un multiplicador para la traslacion
	texCoord0 = texCoord;
	
	normal0= (transform * vec4(normal, 0.0)).xyz;
}