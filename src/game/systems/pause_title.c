#include "engine/ecs.h"
#include "engine/renderer.h"

void
system_pause_title(void) {
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    renderer_text(POSITION, SCALE, CENTER_X, CENTER_Y, COLOR, LAYER, FMT, ...);
  }
}
