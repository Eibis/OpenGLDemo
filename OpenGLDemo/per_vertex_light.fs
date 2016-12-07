#version 410 core                                                 

in vec3 pass_Color;
in vec3 pass_Normal;
in vec3 pass_FragPos;         
                                           
out vec4 color;   

//parameters hardcoded
float ambientStrength = 0.1f;
vec3 lightColor = vec3(1.0, 1.0, 1.0);
vec3 lightPos = vec3(15.0, 5.0, 0.0);

void main(void)                                                   
{                             
	//calc ambient light
    vec3 ambient = ambientStrength * lightColor;
    
	//calc diffuse
	vec3 norm = normalize(pass_Normal);
	vec3 lightDir = normalize(lightPos - pass_FragPos);  
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = pass_Color * (ambient + diffuse);
	                                
    color = vec4(result, 1.0);                               
}                           