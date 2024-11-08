#include "renderer.h"
#include <iostream>
#include <cmath>

const int WIDTH = 80;
const int HEIGHT = 24;

void renderFrame(double time)
{
    char buffer[HEIGHT][WIDTH] = {};
    float zBuffer[HEIGHT][WIDTH] = {};

    float A = time;
    float B = time / 2;

    const char *chars = ".,-~:;=!*#$@";

    for (float theta = 0; theta < 2 * M_PI; theta += 0.07f)
    {
        for (float phi = 0; phi < 2 * M_PI; phi += 0.02f)
        {
            float sinTheta = std::sin(theta), cosTheta = std::cos(theta);
            float sinPhi = std::sin(phi), cosPhi = std::cos(phi);
            float sinA = std::sin(A), cosA = std::cos(A);
            float sinB = std::sin(B), cosB = std::cos(B);

            float circleX = cosTheta + 2;
            float circleY = sinTheta;

            float x = circleX * (cosB * cosPhi - sinA * sinB * sinPhi) - circleY * cosA * sinB;
            float y = circleX * (sinB * cosPhi + sinA * cosB * sinPhi) + circleY * cosA * cosB;
            float z = 1 / (circleX * sinA * sinPhi + circleY * sinA + cosA + 5);
            int xp = static_cast<int>((WIDTH / 2) + 10 * z * x);
            int yp = static_cast<int>((HEIGHT / 2) - 10 * z * y);
            int luminance = static_cast<int>(8 * (cosPhi * cosTheta * sinB - cosA * cosTheta * sinPhi - sinA * cosB));

            if (luminance > 0 && xp >= 0 && xp < WIDTH && yp >= 0 && yp < HEIGHT && z > zBuffer[yp][xp])
            {
                zBuffer[yp][xp] = z;
                buffer[yp][xp] = chars[luminance];
            }
        }
    }

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            std::cout << (buffer[i][j] ? buffer[i][j] : ' ');
        }
        std::cout << '\n';
    }
}
