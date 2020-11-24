		 #version 330 core

		 out vec4 FragColor; 

		 in vec3 Normal; 
		 in vec3 FragPos; 
		
		struct Material {
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float shininess;
		}; 
		struct Light {
		vec3 position;
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
			};
	     
		 uniform Light light[5];
		 uniform Material material;
		 uniform vec3 viewPos; 
		 uniform float transparency=1.0f;

		 void main() 
		 { 
		vec3 result;
		for(int i = 0; i < 5; i++){
		
		//ambient
		 vec3 ambient = light[i].ambient*material.ambient; 

		//diffuse
		 vec3 norm = normalize(Normal); 
		 vec3 lightDir = normalize(light[i].position - FragPos);    
		 float diff = max(dot(norm, lightDir), 0.0); 
		 vec3 diffuse = light[i].diffuse * (diff * material.diffuse);

		//specular
		 vec3 viewDir = normalize(viewPos - FragPos); 
		 vec3 reflectDir = reflect(-lightDir, norm);  
		 float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); 
		 vec3 specular = light[i].specular * (spec * material.specular);  

		  result=result+ ambient + diffuse+specular;
		 }
		    FragColor = vec4(result,transparency); 
		 } ;