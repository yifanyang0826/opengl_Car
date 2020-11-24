		 #version 330 core

		 out vec4 FragColor; 

		 in vec3 Normal; 
		 in vec3 FragPos; 
		 in vec2 vertexUV;
		 in vec4 FragPosLightSpace;


		 struct Light {
		 vec3 position;
		 vec3 ambient;
		 vec3 diffuse;
		 vec3 specular;
			};
		 uniform Light light[5];
		 uniform vec3 viewPos[5]; 
		 uniform float transparency;
		 uniform sampler2D textureSampler; 
		 uniform sampler2D depthMap;
		 
		 uniform bool shadowFlag=true;

		 float shadowCalc()
		{
			vec3 pos=FragPosLightSpace.xyz*0.5+0.5;
			float depth =texture(depthMap,pos.xy).r;
			float bias = 0.005;
	
			return (depth+bias) <pos.z? 0.0:1.0;
		}

		 void main() 
		 {  
		    vec3 color = texture(textureSampler, vertexUV).rgb; 
			vec3 result;
			for(int i = 0; i < 5; i++){
			vec3 normal = normalize(Normal); 
		    //ambient
			vec3 ambient = light[i].ambient*color; 
			//diffuse
			vec3 lightDir = normalize(light[i].position - FragPos);    
			float diff = max(dot(lightDir,normal), 0.0); 
			vec3 diffuse = diff * light[i].diffuse;
			//specular
			vec3 viewDir = normalize(viewPos[i] - FragPos); 
			vec3 halfwayDir = normalize(lightDir + viewDir);  
			float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
			vec3 specular = spec * light[i].specular;    
			//calculate shadow
			float shadow=shadowCalc();

			if(shadowFlag==true){
			result =result+ (shadow*(diffuse+specular)+ambient) ;
			}
			else
			result =result+ (diffuse+specular+ambient);	   
			}
			result=result*color;
		    FragColor = vec4(result,transparency); 
		 } ;
