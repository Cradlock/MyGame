// fragment_shader.glsl
uniform vec4 color;  // Принимаем цвет как uniform vec4

void main() {
    gl_FragColor = color;  // Применяем переданный цвет к каждому пикселю
}
