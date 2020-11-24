#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct Light {
vec3 position;
vec3 ambient;
vec3 diffuse;
vec3 specular;
	};

uniform sampler2D texture_diffuse;
uniform Light light;
uniform vec3 viewPos; 

void main()
{    
			//FragColor = vec4(texNormal, 1.0f);
			vec4 color = texture(texture_diffuse, TexCoords);
			vec3 normal = normalize(Normal); 
		    //ambient
			vec4 ambient = vec4(light.ambient,1.0)*color; 
			//diffuse
			vec3 lightDir = normalize(light.position - FragPos);    
			float diff = max(dot(lightDir,normal), 0.0); 
			vec4 diffuse = vec4(diff * light.diffuse,1.0);
			//specular
			vec3 viewDir = normalize(viewPos - FragPos); 
			vec3 halfwayDir = normalize(lightDir + viewDir);  
			float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
			vec4 specular = vec4(spec * light.specular,1.0);    

	
			vec4 result = (diffuse+specular+ambient);	   
		
		    FragColor = result*color;
}