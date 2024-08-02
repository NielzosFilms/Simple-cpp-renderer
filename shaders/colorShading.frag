#version 400

in vec2 fragmentPosition;
in vec4 fragmentColor;

out vec4 color;

uniform int fragmentShader;
uniform float time;

// Function to generate random values
float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

void main() {
    if (fragmentShader == 0) {
        color = fragmentColor;
    } else if (fragmentShader == 1) {
        color = vec4(tan(fragmentPosition.y/fragmentPosition.x*time),tan(fragmentPosition.y/fragmentPosition.x*time),tan(fragmentPosition.y/fragmentPosition.x*time), fragmentColor.a + time);
    } else if (fragmentShader == 2) {
        color = vec4(
            (cos(fragmentPosition.x * 10 + time) + 1.0) * 0.5,
            (cos(fragmentPosition.y * 10 + time) + 1.0) * 0.5,
            (cos((fragmentPosition.x + fragmentPosition.y) * 10 + time) + 1.0) * 0.5,
            1.0
        );
    } else if (fragmentShader == 3) {
        // Center the fragment position around (0, 0)
        vec2 uv = fragmentPosition;

        // Convert Cartesian coordinates to polar coordinates
        float radius = length(uv);
        float angle = atan(uv.y, uv.x);

        // Create a swirling effect by modifying the angle over time
        float swirl = angle + time + radius * 5.0;

        // Calculate the color components using the swirl value
        float r = 0.5 + 0.5 * sin(swirl);
        float g = 0.5 + 0.5 * sin(swirl + 2.0);
        float b = 0.5 + 0.5 * sin(swirl + 4.0);

        // Combine the components into the final color
        color = vec4(r, g, b, 1.0);
    } else if (fragmentShader == 4) {
        // Rainbow wave
        color = vec4(
            1.0 * (sin(fragmentPosition.x + time) + 1.0) * 0.5,
            1.0 * (sin(fragmentPosition.x + time + 2.0) + 1.0) * 0.5,
            1.0 * (sin(fragmentPosition.x + time + 4.0) + 1.0) * 0.5,
            1.0
        );
    } else {
        color = fragmentColor;
    }
}