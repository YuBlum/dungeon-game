#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "engine/types.h"
typedef void(*SceneFn)(void);

void scene_manager_create(void);
void __scene_manager_create_scene(const char *name, SceneFn on_start_fn, SceneFn on_pre_systems_fn, SceneFn on_pos_systems_fn, SceneFn on_draw_fn, const char *file, u32 line);
void __scene_manager_activate_system(const char *name, const char *system_name, const char *file, u32 line);
bool __scene_manager_is_current_scene(const char *name, const char *file, u32 line);
void __scene_manager_goto(const char *name, const char *file, u32 line);
void scene_manager_update(void);
void scene_manager_pre_systems(void);
void scene_manager_pos_systems(void);
void scene_manager_draw(void);

#define scene_manager_create_scene(SCENE, ON_START_FN, ON_PRE_SYSTEMS_FN, ON_POS_SYSTEMS_FN, ON_DRAW_FN) __scene_manager_create_scene(SCENE, ON_START_FN, ON_PRE_SYSTEMS_FN, ON_POS_SYSTEMS_FN, ON_DRAW_FN, __FILE__, __LINE__)
#define scene_manager_activate_system(SCENE, SYSTEM) __scene_manager_activate_system(SCENE, SYSTEM, __FILE__, __LINE__)
#define scene_manager_is_current_scene(SCENE) __scene_manager_is_current_scene(SCENE, __FILE__, __LINE__)
#define scene_manager_goto(SCENE) __scene_manager_goto(SCENE, __FILE__, __LINE__)

#endif/*__SCENE_MANAGER_H__*/
