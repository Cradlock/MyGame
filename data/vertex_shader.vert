// vertex_shader.glsl
void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  
}
