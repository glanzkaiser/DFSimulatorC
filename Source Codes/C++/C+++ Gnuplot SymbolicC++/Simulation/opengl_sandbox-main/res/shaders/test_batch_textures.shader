#shader vertex
#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texId;

out vec2 v_TexCoord;
out float v_TexId;

void main()
{
    gl_Position = position;
    v_TexCoord = texCoord;
    v_TexId = texId;
};

#shader fragment
#version 450 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexId;

uniform sampler2D u_Textures[2];

void main()
{
    int index = int(v_TexId);
    vec4 texColor = texture(u_Textures[index], v_TexCoord);
    color = texColor;
};