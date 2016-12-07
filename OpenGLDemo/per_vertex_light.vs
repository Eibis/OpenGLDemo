#version 410 core                                                 
        
layout (location = 0) in vec3 position;

// Transformation for the projections
uniform mat4 MVP;                            
uniform mat4 M;                            
                
// The vertex buffer input                                    
in vec3 in_Color; 
in vec3 in_Position; 
in vec3 in_Normal;  

// The output color
out vec3 pass_Color;
out vec3 pass_Normal;
out vec3 pass_FragPos;                                            
                                                                                                                               
void main(void)                                                 
{                     
	// Writes the color
	pass_Color = in_Color;  
	
	// Passes the projected position to the fragment shader / rasterization process. 
    gl_Position =  MVP * vec4(in_Position, 1.0);     
	
	pass_FragPos = vec3(M * vec4(in_Position, 1.0f));
    pass_Normal = mat3(transpose(inverse(M))) * in_Normal;          
}                                                                                                            