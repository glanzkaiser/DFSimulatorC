#version 330 core
     
out vec4 fragment_colour;
     
// Must be the exact same name as declared in the vertex shader
// ------------------------------------------------------------
in vec3 vert_pos_transformed; // Transformed model position coordinates received as interpolated
in vec3 vertex_normal;
in vec2 texture_coordinates;
     
uniform sampler2D image;
uniform vec3 camera_position; // -Z is into the screen... camera_position is set in main() on CPU side
     
void main()
{
	vec3 view_direction = normalize(camera_position - vert_pos_transformed);
     
	vec3 light_position = vec3(0.0, 20.0, 0.0); // A position used as a light source acts as a point light (Not a directional light)
	vec3 light_direction = normalize(vec3(light_position - vert_pos_transformed));
     
	vec4 image_colour = texture(image, texture_coordinates);
     
	float ambient_factor = 0.65; // Intensity multiplier
	vec4 ambient_result = vec4(ambient_factor * image_colour.rgb, 1.0);
     
	// Perpendicular vectors dot product = 0
	// Parallel vectors in same direction dot product = 1
	// Parallel vectors in opposite direction dot product = -1
	// -------------------------------------------------------
	float diffuse_factor = 0.85;
	float diffuse_angle = max(dot(light_direction, vertex_normal), -0.45); // [-1.0 to 0] down to -1 results in darker lighting past 90 degrees
	vec4 diffuse_result =  vec4(diffuse_factor * diffuse_angle * image_colour.rgb, 1.0);
     
	vec3 specular_colour = vec3(0.5, 0.5, 0.5);
	vec3 reflect_direction = normalize(reflect(-light_direction, vertex_normal)); // Light direction is negated here
	float specular_strength = pow(max(dot(view_direction, reflect_direction), 0), 32);
	vec4 specular_result = vec4(specular_colour * specular_strength, 1.0);
     
	fragment_colour = ambient_result + diffuse_result + specular_result;
    }

