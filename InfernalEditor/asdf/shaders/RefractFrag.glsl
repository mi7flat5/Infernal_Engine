#version 450 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform mat4 View;
uniform samplerCube SkyBox;

out vec4 color;

void main()////refraction fragment shader
{        
    float ratio = 1.00 / 2.2;
    vec3 I = normalize(FragPos);
	vec3 norm = normalize(Normal);
    vec3 Refraction = refract(I, norm, ratio);
	
	//vec3 Reflection = reflect(I, normalize(Normal));
	
	//Reflection = vec3 (inverse (View) * vec4 (Reflection, 0.0));
	
	
	//vec3 lightDir = vec3(.5,.5,.5);//normalize(lightPos - FragPos);
 //   float PL = max(dot(normalize(Normal), lightDir), 0.0);
 //   vec3 PLC = PL * vec3(texture(SkyBox,Reflection))*vec3(1,1,1);
 //   Reflection = Reflection +PLC;


	
	Refraction = vec3 (inverse(View) * vec4 (Refraction, 0.0));

	
  
    //vec4 RefractColor
	 color = mix(texture(SkyBox, Refraction),vec4(1,1,1,1),0.1); 
	//vec4 ReflectColor = texture(SkyBox, Refraction);
	
	
	//vec4 color1  = mix(RefractColor,ReflectColor,0.1);
	//color = mix(color1,vec4(Reflection,0),0.01);
}  
