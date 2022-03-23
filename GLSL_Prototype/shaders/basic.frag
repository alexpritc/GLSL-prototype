#version 460

in vec3 color;
in vec3 normal;
in vec3 fragPos;
in vec2 UV;

in vec3 Ka;
in vec3 Kd;
in vec3 Ks;

layout (location = 0) out vec4 fragColor;

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform float lightIntensity;

uniform vec3 viewPos;

uniform sampler2D ourTexture;

void main() {

    // Ambient
    vec3 ambient = Ka * lightIntensity * lightColor;
  	
    // Diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 textDiff = texture( ourTexture, UV ).rgb;
    vec3 diffuse = Kd * diff * lightColor * textDiff;
    
    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = Ks * specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular);
    fragColor = vec4(result, 1.0);
}
