#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "engine/types.h"
typedef void(*SceneFn)(void);

void scene_manager_create(void);
void __scene_manager_create_scene(SceneFn scene_fn, const char *name, const char *file, u32 line);
void __scene_manager_activate_system(const char *name, const char *system_name, const char *file, u32 line);
bool __scene_manager_is_current_scene(const char *name, const char *file, u32 line);
void __scene_manager_goto(const char *name, const char *file, u32 line);
void scene_manager_update(void);

#define scene_manager_create_scene(SCENE) do { (void)SCENE; __scene_manager_create_scene(SCENE, #SCENE, __FILE__, __LINE__); } while(0)
#define scene_manager_activate_system(SCENE, SYSTEM) do { (void)SCENE; __scene_manager_activate_system(#SCENE, SYSTEM, __FILE__, __LINE__); } while(0)
#define scene_manager_is_current_scene(SCENE) __scene_manager_is_current_scene(#SCENE, __FILE__, __LINE__)
#define scene_manager_goto(SCENE) do { (void)SCENE; __scene_manager_goto(#SCENE, __FILE__, __LINE__); } while(0)

#endif/*__SCENE_MANAGER_H__*/
