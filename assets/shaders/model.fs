#version 450 core

in vec3 fNormal;

out vec4 FragColor;

void main()
{
   vec3 light_col = vec3(0.8);
   vec3 light_pos = vec3(0, 3000, 2000);
   vec3 light_dir = normalize(light_pos - vec3(0.0));

   float diff = max(dot(fNormal, light_dir), 0.1);
   vec3 diffuse = diff * light_col;

   FragColor = vec4(diffuse, 1.0);
}