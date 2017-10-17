# version 330 core

layout (location = 0) in vec3 position;

out vec4 Position;

void main() {
     gl_Position = vec4(position, 1.0f);
	Position = ec4(position, 1.0f);
}

