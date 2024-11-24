#version 330 core
layout (location = 0) in vec3 aPos;      // Vertex position
layout (location = 1) in vec3 aColor;    // Vertex color (optional)
layout (location = 2) in vec2 aTextCoords; // Texture coordinates

out vec3 color;          // Color passed to fragment shader (optional)
out vec2 TextCoords;     // Texture coordinates passed to fragment shader

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    color = aColor;
    TextCoords = vec2(aTextCoords.x, 1.0 - aTextCoords.y);  // Invert Y coordinate
}
