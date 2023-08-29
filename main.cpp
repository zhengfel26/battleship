#include "testers.hpp"
int main()
{
    srand((unsigned int)time(NULL));

    runSuite();

    App app;
    app.runGame();

    return 0;
}