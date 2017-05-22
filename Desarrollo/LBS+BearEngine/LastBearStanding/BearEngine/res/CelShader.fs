#version 120
varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;
//varying float intensity;
uniform vec3 lightUnoPos;
uniform vec3 uPosCam;

uniform vec3 lightUno;
uniform vec3 lightUnoAmb;

void main(){
    vec4 color1 = gl_FrontMaterial.diffuse;
    vec4 color2;

    float intensity = dot(normalize(lightUnoPos),normal0);
    vec3 E = normalize(uPosCam - normal0);
    vec3 R = reflect(lightUnoPos,normal0);
    float cosAlpha = clamp(dot(E,R),0,1);


    float   d           = length(lightUnoPos.xyz - normal0);
    float   attenuation = 1.0/(0.25 +(0.1*d)+(0.003*d*d));

    if (intensity > 0.95)
        color2 = vec4(1.0, 1.0, 1.0, 1.0);
    else if (intensity > 0.50) 
        color2 = vec4(0.5, 0.5, 0.5, 1.0);
    else                       
        color2 = vec4(0.0, 0.0, 0.0, 1.0);

    gl_FragColor = texture2D(diffuse, texCoord0) * (color2) * 
                            vec4( lightUnoAmb
                            +(lightUno * attenuation
                            *clamp(dot(normal0, lightUnoPos ),0.0,1.0))
                            +(lightUno * attenuation * pow(cosAlpha,5))
                            , 1.00);



}

//texture2D(diffuse, texCoord0 )