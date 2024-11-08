#include "renderer.h"
#include <iostream>
#include <cmath>
#include <cstring> // For memset

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const int WIDTH = 30;
const int HEIGHT = 10;

// Function to draw a line between two points using Bresenham’s Line Algorithm
void drawLine(int x1, int y1, int x2, int y2, char buffer[HEIGHT][WIDTH])
{
    int dx = std::abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -std::abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2;

    while (true)
    {
        if (x1 >= 0 && x1 < WIDTH && y1 >= 0 && y1 < HEIGHT)
        {
            buffer[y1][x1] = '.'; // Change '.' to any other character if needed
        }
        if (x1 == x2 && y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void renderFrame(double time)
{
    char buffer[HEIGHT][WIDTH];
    float zBuffer[HEIGHT][WIDTH];

    // Clear buffers
    memset(buffer, ' ', sizeof(buffer));
    memset(zBuffer, 0, sizeof(zBuffer));

    // Cube vertices
    float vertices[8][3] = {
        {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}, {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}};

    // Edges of the cube (pairs of vertex indices)
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Back face
        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4}, // Front face
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7} // Connecting edges
    };

    float sinA = std::sin(time), cosA = std::cos(time);
    float sinB = std::sin(time / 2), cosB = std::cos(time / 2);

    for (int e = 0; e < 12; ++e)
    {
        // Get edge vertices
        int v1 = edges[e][0], v2 = edges[e][1];

        float x1 = vertices[v1][0], y1 = vertices[v1][1], z1 = vertices[v1][2];
        float x2 = vertices[v2][0], y2 = vertices[v2][1], z2 = vertices[v2][2];

        // Rotate vertices
        float nx1 = x1 * cosA - z1 * sinA;
        float nz1 = x1 * sinA + z1 * cosA;
        x1 = nx1;
        z1 = nz1;

        float ny1 = y1 * cosB - z1 * sinB;
        z1 = y1 * sinB + z1 * cosB;
        y1 = ny1;

        float nx2 = x2 * cosA - z2 * sinA;
        float nz2 = x2 * sinA + z2 * cosA;
        x2 = nx2;
        z2 = nz2;

        float ny2 = y2 * cosB - z2 * sinB;
        z2 = y2 * sinB + z2 * cosB;
        y2 = ny2;

        // Project points to 2D
        int xp1 = static_cast<int>((WIDTH / 2) + x1 * 10 / (z1 + 5));
        int yp1 = static_cast<int>((HEIGHT / 2) - y1 * 10 / (z1 + 5));
        int xp2 = static_cast<int>((WIDTH / 2) + x2 * 10 / (z2 + 5));
        int yp2 = static_cast<int>((HEIGHT / 2) - y2 * 10 / (z2 + 5));

        // Draw line between the projected points
        drawLine(xp1, yp1, xp2, yp2, buffer);
    }

    // Print the frame
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            std::cout << buffer[i][j];
        }
        std::cout << '\n';
    }
}
