#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;
//varying float intensity;


void main(){

	/*gl_FragColor = texture2D(diffuse, texCoord0 )
		* clamp(dot(-vec3(0,0,1)/*lightDirection*///, normal0),0.0,1.0);//vec4(1.0, 0.0, 0.0, 1.0);
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	
	//	* clamp(dot(-vec3(0,0,1)/*lightDirection*/, normal0),0.0,1.0);

	float intensity;
	vec4 color;
	intensity = dot(-vec3(0,0,1)/*lightDirection*/, normalize(normal0));
	//if(intensity>0.95)
	if(intensity>0.5)
		color = vec4(1.0,0.5,0.5,1.0);
		//color = texture2D(diffuse , texCoord0);
	//else 	if(intensity>0.5)
	else 	if(intensity>0.4)
		//color = texture2D(diffuse , texCoord0);
//		color = vec4(0.6,0.3,0.3,1.0);
		color = vec4(1.0,0.5,0.5,1.0);

	else 	if(intensity>0.25)
//		color = vec4(0.2,0.2,0.2,1.0);
		color = vec4(1.0,0.5,0.5,1.0);
		
		//color = vec4(0.0,0.0,0.0,1.0);		
		//color = texture2D(diffuse , texCoord0);
		//color = vec4(0,0,0,1.0);
	else 
	//	color = vec4(0.2,0.1,0.1,1.0);		
		//color = texture2D(diffuse , texCoord0);
		color = vec4(0.0,0.0,0.0,1.0);		

	gl_FragColor = /*texture2D(diffuse, texCoord0 )**/color;



}

//texture2D(diffuse, texCoord0 )