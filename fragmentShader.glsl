#version 330 core

in vec4 outColor; // Output color from the vertexShader

out vec4 FragColor; // Color of the fragment

uniform int isBackgroundShader;
uniform vec2 resolution;
uniform float time;

float myrandom(vec2 co) {
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
    if (isBackgroundShader == 1) {
        // Normalized pixel coordinate with respect to window height
        vec2 uv = gl_FragCoord.xy / resolution.xy;

        // Pseudorandom pattern for stars
        float stars = myrandom(uv);

        // Adjust the threshold to control the density of stars
        float threshold = 0.9995; // Increase this value to reduce the number of stars

        // Add a very subtle twinkling effect
        stars += smoothstep(0.0, 2.0, sin(time * 0.5)) * 0.001; // Adjust the smoothstep range and multiplier for minimal twinkling

        // Determine star size variation
        float starSize = 1.0;
        if (stars > threshold) {
            starSize = 1.0 + myrandom(uv) * 2.0; // Randomly scale star size between 1.0 and 3.0
        }

        // Add stars to the sky and make them fall
        if (stars > threshold) {
            FragColor = vec4(vec3(uv.y) * starSize, 1.0); // Set the pixel color based on uv.y for brightness, scaled by starSize
        } else {
            FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Otherwise, set pixel to black
        }
    } else {
        // Set the fragment color to the global variable of the color
        FragColor = outColor;
    }
}
