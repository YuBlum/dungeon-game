#include "general/core.h"
#include "engine/scene_manager.h"
#include "engine/hashtable.h"
#include "engine/list.h"
#include "engine/ecs.h"
#include "game/scenes.h"

typedef u32 SceneID;

typedef struct {
  SceneFn on_start_fn;
  SceneFn on_update_fn;
  const char **systems_to_activate;
} Scene;

typedef struct {
  SceneID *scene_ids;
  Scene *scenes;
  u32 scene_cur;
  u32 scene_nxt;
  bool changing;
  bool first_frame;
  bool on_scenes_create;
} SceneManager;

static SceneManager scene_manager;

void
scene_manager_create(void) {
  scene_manager.scene_ids = hashtable_create(sizeof (SceneID));
  scene_manager.scenes = list_create(sizeof (Scene));
  scene_manager.scene_cur = 0;
  scene_manager.scene_nxt = 0;
  scene_manager.changing = false;
  scene_manager.first_frame = true;

  scene_manager.on_scenes_create = true;
  scenes_create();
  scene_manager.on_scenes_create = false;
}

void
__scene_manager_create_scene(const char *name, SceneFn on_start_fn, SceneFn on_update_fn, const char *file, u32 line) {
#if DEVMODE
  if (!scene_manager.on_scenes_create) ERROR("%s:%u: Function 'scene_manager_create_scene' can only be called inside 'scenes_create'", file, line);
  if (hashtable_has(scene_manager.scene_ids, name)) ERROR("%s:%u: Creating scene '%s' two times", file, line, name);
#endif
  SceneID id = list_size(scene_manager.scenes);
  list_grow(scene_manager.scenes);
  Scene *scene = &scene_manager.scenes[id];
  scene->on_start_fn = on_start_fn;
  scene->on_update_fn = on_update_fn;
  scene->systems_to_activate = list_create(sizeof (const char *));
  hashtable_insert(scene_manager.scene_ids, name, id);
}

void
__scene_manager_activate_system(const char *name, const char *system_name, const char *file, u32 line) {
#if DEVMODE
  if (!scene_manager.on_scenes_create) ERROR("%s:%u: Function 'scene_manager_activate_system' can only be called inside 'scenes_create'", file, line);
  if (!hashtable_has(scene_manager.scene_ids, name)) ERROR("%s:%u: Scene '%s' doesn't exist", file, line, name);
  if (!__ecs_system_exists(system_name)) ERROR("%s:%u: '%s' is not a system", file, line, system_name);
#endif
  Scene *scene = &scene_manager.scenes[hashtable_get(scene_manager.scene_ids, name)];
  list_push(scene->systems_to_activate, system_name);
}

bool
__scene_manager_is_current_scene(const char *name, const char *file, u32 line) {
#if DEVMODE
  if (!hashtable_has(scene_manager.scene_ids, name)) ERROR("%s:%u: Scene '%s' doesn't exist", file, line, name);
#endif
  return scene_manager.scene_cur == hashtable_get(scene_manager.scene_ids, name);
}

void
__scene_manager_goto(const char *name, const char *file, u32 line) {
#if DEVMODE
  if (!hashtable_has(scene_manager.scene_ids, name)) ERROR("%s:%u: Scene '%s' doesn't exist", file, line, name);
#endif
  scene_manager.changing = true;
  scene_manager.scene_nxt = hashtable_get(scene_manager.scene_ids, name);
}

static void
scene_manager_run_scene_create(Scene *scene) {
  for (u32 i = 0; i < list_size(scene->systems_to_activate); i++) {
    __ecs_system_activate(scene->systems_to_activate[i], __FILE__, __LINE__);
  }
  scene->on_start_fn();
  ecs_scene_start();
}

void
scene_manager_update(void) {
  if (scene_manager.first_frame) {
#if DEVMODE
    if (!list_size(scene_manager.scenes)) ERROR("The game has no scenes.");
#endif
    scene_manager.first_frame = false;
    scene_manager_run_scene_create(&scene_manager.scenes[0]);
  }
  if (scene_manager.scenes[scene_manager.scene_cur].on_update_fn)
    scene_manager.scenes[scene_manager.scene_cur].on_update_fn();
  if (!scene_manager.changing) return;
  ecs_scene_end();
  ecs_entities_terminate();
  ecs_system_deactivate_all();
  scene_manager.changing = false;
  scene_manager.scene_cur = scene_manager.scene_nxt;
  scene_manager_run_scene_create(&scene_manager.scenes[scene_manager.scene_cur]);
}
