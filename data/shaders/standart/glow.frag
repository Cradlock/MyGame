uniform sampler2D texture;
uniform float radius;
uniform vec2 center;
uniform vec4 color;
uniform vec2 resolution;

void main()
{
    vec2 fragCoord = gl_FragCoord.xy;

    // Получаем цвет из фоновой текстуры
    vec4 texColor = texture2D(texture, fragCoord / resolution);

    // Вычисляем расстояние от центра света
    float dist = distance(fragCoord, center);

    // Рассчитываем силу свечения (1.0 в центре, 0.0 вне радиуса)
    float intensity = 1.0 - smoothstep(radius * 0.5, radius, dist);

    // Итоговый цвет — фон + свечение (с альфой)
    vec4 glow = color * intensity;

    // Альфа смешивание
    gl_FragColor = texColor + glow * color.a;  

}
