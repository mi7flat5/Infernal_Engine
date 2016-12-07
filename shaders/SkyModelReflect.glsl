#version 450 core

in vec3 FragPos;
in vec3 Normal;

uniform mat4 View;
uniform samplerCube SkyBoxReflector;
uniform vec3 lightPos;
out vec4 Color;

void main()//Reflection fragment shader
{        



  vec3 I = normalize (FragPos);
  vec3 norm = normalize (Normal);
  vec3 Reflection = reflect (I, norm);

  // convert from eye to world space 
  Reflection = vec3 (inverse (View) * vec4 (Reflection, 0.0));



  // vec3 lightDir = normalize(lightPos - FragPos);
  // float PL = max(dot(norm, lightDir), 0.0);
  // vec3 PLC = PL * vec3(texture(SkyBox,Reflection))*vec3(1,1,1);
  //// Reflection = Reflection +PLC;
 
  Color = texture (SkyBoxReflector, Reflection);
  //Color = mix(Color,vec4(Reflection,0),0.1); add for metallic or oily rainbow effect
} 