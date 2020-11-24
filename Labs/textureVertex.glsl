		 #version 330 core
		 layout (location = 0) in vec3 aPos; 
		 layout (location = 1) in vec3 aNormal; 
		 layout (location = 2) in vec2 aUV; 
		  
		 uniform mat4 worldMatrix; 
		 uniform mat4 viewMatrix = mat4(1.0);   // default value for view matrix (identity)
		 uniform mat4 projectionMatrix = mat4(1.0); 
		 uniform mat4 lightSpaceMatrix;

		 
		 out vec3 FragPos; 
		 out vec3 Normal; 
		 out vec2 vertexUV; 
		 out vec4 FragPosLightSpace;

		 void main() 
		 { 
			FragPos = vec3( worldMatrix * vec4(aPos, 1.0)); 
			Normal = transpose(inverse(mat3(worldMatrix))) *aNormal;
			vertexUV = aUV;
			FragPosLightSpace=lightSpaceMatrix*vec4(FragPos,1.0);
		    gl_Position = projectionMatrix * viewMatrix *vec4(FragPos, 1.0); 		    
		 } ;