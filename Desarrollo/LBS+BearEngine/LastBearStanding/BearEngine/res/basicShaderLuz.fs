#version 120

varying vec2 texCoord0;
varying vec3 normal0;

//varying vec3 ambiente0;

uniform sampler2D diffuse;
/*uniform vec3 ambientLight;
uniform vec3 lightDiff;
uniform vec3 lightDiffPos;*/
uniform vec3 lightUno;
uniform vec3 lightUnoAmb;
uniform vec3 lightUnoPos;
uniform vec3 uPosCam;


void main(){
vec4 color;

vec3 E = normalize(uPosCam - normal0);
vec3 R = reflect(lightUnoPos,normal0);
float cosAlpha = clamp(dot(E,R),0,1);


float   d 			= length(lightUnoPos.xyz - normal0);
float	attenuation = 1.0/(0.25 +(0.1*d)+(0.003*d*d));

	//	d= lightDiffPos.x- normal0.x + lightDiffPos.y- normal0.y + lightDiffPos.z- normal0.z;


	//gl_FragColor = texture2D(diffuse, texCoord0 ) * normalize(vec4(ambientLight,1.0));
		//* clamp(dot(-vec3(0,0,1)/*lightDirection*///, normal0),0.0,1.0);//vec4(1.0, 0.0, 0.0, 1.0);
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	//gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0)
		/* clamp(dot(-vec3(0,0,1)/*lightDirection*,/ normal0),0.0,1.0);*/
	color= texture2D(diffuse, texCoord0 );
	gl_FragColor =  color *
					vec4(	lightUnoAmb
							+(lightUno * attenuation
							*clamp(dot(normal0, lightUnoPos ),0.0,1.0))
							+(lightUno * attenuation * pow(cosAlpha,5))
							, 1.00);
	/*if(color.a==1.0)
		color.a=0.5;*/


}