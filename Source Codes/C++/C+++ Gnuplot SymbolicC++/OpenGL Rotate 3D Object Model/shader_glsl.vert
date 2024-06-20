#version 330 core
     
layout (location = 0) in vec3 aPos; // Attribute data: vertex(s) X, Y, Z position via VBO set up on the CPU side
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
     
out vec3 vertex_normal;
out vec2 texture_coordinates;
out vec3 vert_pos_transformed; // Transformed model vertex position passed as interpolated
     
uniform mat4 view;
uniform mat4 projection;
uniform mat4 rotation_mat;
     
void main()
{
	texture_coordinates = aTexCoord;
	vert_pos_transformed = vec3(rotation_mat * vec4(aPos, 1.0)); // Transformed position values used for the lighting effects
     
	mat3 normal_matrix = transpose(inverse(mat3(rotation_mat)));
	vertex_normal = normal_matrix * aNormal;
     
	if (length(vertex_normal) > 0)
		vertex_normal = normalize(vertex_normal);
     
	gl_Position = projection * view * rotation_mat * vec4(aPos, 1.0);
    }

