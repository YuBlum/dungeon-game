#include "include/ecs.h"
#include "include/hashflag.h"
#include "include/types.h"
#include "include/window.h"
#include "include/renderer.h"
#include <stdio.h>

void
update_system(void) {
}

void
draw_system(void) {
  renderer_request_quad(V2F(-0.6, 0), V2F(1, 1), C_YELLOW, 0);
  renderer_request_quad(V2F(+0.6, 0), V2F(1, 1), C_BLUE, 0);
}

i32
main(void) {
  HashFlag *flags = hashflag_create();
  hashflag_set(flags, "test");
  hashflag_set(flags, "yuri");
  hashflag_set(flags, "thomas");
  hashflag_set(flags, "gustavo");
  hashflag_set(flags, "brenda");
  hashflag_set(flags, "ein");
  hashflag_set(flags, "rebecca");
  hashflag_set(flags, "marcos");
  hashflag_set(flags, "krause");
  hashflag_set(flags, "amon");
  hashflag_set(flags, "isabelle");
  hashflag_set(flags, "almeida");
  hashflag_set(flags, "fausto cipriano");
  hashflag_set(flags, "cavaleiros");
  hashflag_set(flags, "ednaldo");
  hashflag_set(flags, "pereira");
  hashflag_set(flags, "ednaldo pereira");
  hashflag_set(flags, "pogchamp");
  hashflag_set(flags, "supla");
  hashflag_set(flags, "relampago");
  hashflag_set(flags, "maconheiro fantasma");
  hashflag_set(flags, "eu não sei mais");
  hashflag_set(flags, "socorro");
  hashflag_clear(flags, "almeida");
  hashflag_clear(flags, "brenda");
  hashflag_clear(flags, "marcos");
  hashflag_clear(flags, "eu não sei mais");
  hashflag_clear(flags, "pereira");
  hashflag_clear(flags, "krause");
  printf("test: %u\n", hashflag_get(flags, "test"));
  printf("yuri: %u\n", hashflag_get(flags, "yuri"));
  printf("thomas: %u\n", hashflag_get(flags, "thomas"));
  printf("gustavo: %u\n", hashflag_get(flags, "gustavo"));
  printf("brenda: %u\n", hashflag_get(flags, "brenda"));
  printf("ein: %u\n", hashflag_get(flags, "ein"));
  printf("rebecca: %u\n", hashflag_get(flags, "rebecca"));
  printf("marcos: %u\n", hashflag_get(flags, "marcos"));
  printf("krause: %u\n", hashflag_get(flags, "krause"));
  printf("amon: %u\n", hashflag_get(flags, "amon"));
  printf("isabelle: %u\n", hashflag_get(flags, "isabelle"));
  printf("almeida: %u\n", hashflag_get(flags, "almeida"));
  printf("fausto cipriano: %u\n", hashflag_get(flags, "fausto cipriano"));
  printf("cavaleiros: %u\n", hashflag_get(flags, "cavaleiros"));
  printf("ednaldo: %u\n", hashflag_get(flags, "ednaldo"));
  printf("pereira: %u\n", hashflag_get(flags, "pereira"));
  printf("ednaldo pereira: %u\n", hashflag_get(flags, "ednaldo pereira"));
  printf("pogchamp: %u\n", hashflag_get(flags, "pogchamp"));
  printf("supla: %u\n", hashflag_get(flags, "supla"));
  printf("relampago: %u\n", hashflag_get(flags, "relampago"));
  printf("maconheiro fantasma: %u\n", hashflag_get(flags, "maconheiro fantasma"));
  printf("eu não sei mais: %u\n", hashflag_get(flags, "eu não sei mais"));
  printf("socorro: %u\n", hashflag_get(flags, "socorro"));
  hashflag_destroy(flags);
  return 0;
  window_create();
  renderer_create();
  ecs_create();
  ecs_system_create(update_system, SYS_UPDATE);
  ecs_system_create(draw_system, SYS_DRAW);

  ecs_component_create(V2f, "position");
  ecs_component_create(V2f, "size");
  Entity e;
  ecs_entity_create(&e, "position", "size");
  *((V2f *)ecs_entity_get_component(e, "position")) = V2F(0,0);
  *((V2f *)ecs_entity_get_component(e, "size")) = V2F(1,1);

  while (window_is_running()) {
    window_frame_start();
    ecs_update();
    renderer_batch_start();
    ecs_draw();
    renderer_batch_end();
    window_frame_end();
  }
  return 0;
}
