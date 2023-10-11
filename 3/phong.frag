
#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
in vec3 LightPos;
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // TODO: Replace with your code...
    // If gl_Position was set correctly, this gives a totally red cube
    
    //color = vec4(vec3(1.f,0.f,0.f), 1.0f);   // red cube   

    vec3 norm = normalize(Normal); // Diffuse
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    vec3 viewDir = normalize(-FragPos);  //Specular
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * lightColor; 

    // 0.1 Ambient + 1.0 Diffuse + 0.5 Specular
    vec3 combinedPhong = ((0.1 *lightColor) + (1.0 * diffuse) + (0.5 * specular)) * objectColor;
    color = vec4(combinedPhong, 1.0);

} 
