#include "main.h"

int main()
{
    setupConsole(); // Initialize platform-specific console settings

    double time = 0.0;
    while (true)
    {
        clearScreen();     // Clear the screen for each frame
        renderFrame(time); // Render the 3D shape frame
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        time += 0.05; // Increment time for animation
    }

    resetConsole(); // Reset console to default state
    return 0;
}