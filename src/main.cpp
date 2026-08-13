#include "FelicoEngine.h"

int main(int, char*[]) {
  FelicoEngine::FelicoEngine engine("Test Game", 800, 600);
  engine.init();
  engine.run();
  engine.shutdown();
  return 0;
}
