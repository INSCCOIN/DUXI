#include <GL/glew.h>
#include "Renderer.h"

int main() {
    Renderer renderer;

    if (!renderer.Initialize()) {
        return -1;
    }

    renderer.Run();

    renderer.Shutdown();

    return 0;
}