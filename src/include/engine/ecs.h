#ifndef __ECS_H__
#define __ECS_H__


#include "engine/types.h"

typedef u32 Entity;
typedef i64 SignedEntity;
typedef u64 EntityReference;

typedef void(*SystemFn)(usize entites_amount);
typedef enum {
  ON_SCENE_START,
  ON_SCENE_END,
  ON_PRE_UPDATE,
  ON_UPDATE,
  ON_POS_UPDATE,
  ON_PRE_DRAW_GAME,
  ON_DRAW_GAME,
  ON_POS_DRAW_GAME,
  ON_PRE_DRAW_UI,
  ON_DRAW_UI,
  ON_POS_DRAW_UI,
  ON_PRE_DRAW_SCREEN,
  ON_DRAW_SCREEN,
  ON_POS_DRAW_SCREEN,
  ON_CREATE,
  ON_DESTROY,

  SYSTEM_EVENTS_AMOUNT
} SystemEvent;

void  ecs_create(void);
void  __ecs_component_create(usize size, const char *name, const char *file, u32 line);
void  __ecs_entity_creation_begin(usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line);
void  __ecs_entity_creation_get_reference(EntityReference *reference, const char *file, u32 line);
void *__ecs_entity_creation_setup_component(const char *comp_name, const char *file, u32 line);
void  __ecs_entity_creation_end(const char *file, u32 line);
void  __ecs_entity_remove_component(Entity e, const char *comp_name, const char *file, u32 line);
void *__ecs_entity_insert_component(Entity e, const char *comp_name, const char *file, u32 line);
void  __ecs_entity_insert_empty_component(Entity e, const char *comp_name, const char *file, u32 line);
bool  __ecs_entity_has_component(Entity e, const char *comp_name, const char *file, u32 line);
bool  __ecs_entity_is_last_frame(Entity e, const char *file, u32 line);
bool  __ecs_entity_is_first_frame(Entity e, const char *file, u32 line);
void __ecs_entity_destroy(Entity e, const char *file, u32 line);
void __ecs_entity_get_reference(EntityReference *reference, Entity e, const char *file, u32 line);
void __ecs_entity_clean_reference(EntityReference *reference, const char *file, u32 line);
void *__ecs_entity_reference_get_component(EntityReference reference, const char *comp_name, const char *file, u32 line);
void  __ecs_entity_reference_remove_component(EntityReference reference, const char *comp_name, const char *file, u32 line);
void *__ecs_entity_reference_insert_component(EntityReference reference, const char *comp_name, const char *file, u32 line);
void  __ecs_entity_reference_insert_empty_component(EntityReference reference, const char *comp_name, const char *file, u32 line);
bool  __ecs_entity_reference_has_component(EntityReference reference, const char *comp_name, const char *file, u32 line);
bool  __ecs_entity_reference_is_last_frame(EntityReference reference, const char *file, u32 line);
bool  __ecs_entity_reference_is_first_frame(EntityReference reference, const char *file, u32 line);
void  __ecs_entity_reference_destroy(EntityReference reference, const char *file, u32 line);
void *__ecs_get_component_list(const char *comp_name, const char *file, u32 line);
void  ecs_entities_terminate(void);
void  __ecs_system_create(const char *name, SystemFn fn, SystemEvent event, const char *file, u32 line);
bool  __ecs_system_exists(const char *name);
void  __ecs_system_must_have(const char *name, usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line);
void  __ecs_system_must_not_have(const char *name, usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line);
void  __ecs_system_activate(const char *name, const char *file, u32 line);
void  __ecs_system_deactivate(const char *name, const char *file, u32 line);
void ecs_system_deactivate_all(void);
void __ecs_system_pause(const char *name, const char *file, u32 line);
void __ecs_system_unpause(const char *name, const char *file, u32 line);
void ecs_system_pause_event(SystemEvent event);
void ecs_system_unpause_event(SystemEvent event);
void ecs_scene_start(void);
void ecs_scene_end(void);
void ecs_update(void);
void ecs_draw_game(void);
void ecs_draw_ui(void);
void ecs_draw_screen(void);

#define ecs_component_create(TYPE, NAME) __ecs_component_create(sizeof (TYPE), NAME, __FILE__, __LINE__)
#define ecs_empty_component_create(NAME) __ecs_component_create(0, NAME, __FILE__, __LINE__)
#define ecs_get_component_list(COMPONENT) __ecs_get_component_list(COMPONENT, __FILE__, __LINE__)
#define ecs_entity_creation_begin(...) do { const char *comps_names[] = { __VA_ARGS__ }; __ecs_entity_creation_begin(sizeof (comps_names) / sizeof (comps_names[0]), comps_names, __FILE__, __LINE__); } while(0)
#define ecs_entity_creation_get_reference(REFERENCE_PTR) __ecs_entity_creation_get_reference(REFERENCE_PTR, __FILE__, __LINE__)
#define ecs_entity_creation_setup_component(TYPE, COMPONENT, VALUE) do { *((TYPE *)__ecs_entity_creation_setup_component(COMPONENT, __FILE__, __LINE__)) = (VALUE); } while(0)
#define ecs_entity_creation_end() __ecs_entity_creation_end(__FILE__, __LINE__);
#define ecs_entity_remove_component(ENTITY, COMPONENT) __ecs_entity_remove_component(ENTITY, COMPONENT, __FILE__, __LINE__)
#define ecs_entity_insert_component(ENTITY, TYPE, COMPONENT, VALUE) do { *(TYPE *)__ecs_entity_insert_component(ENTITY, COMPONENT, __FILE__, __LINE__) = VALUE; } while(0)
#define ecs_entity_insert_empty_component(ENTITY, COMPONENT) __ecs_entity_insert_empty_component(ENTITY, COMPONENT, __FILE__, __LINE__)
#define ecs_entity_has_component(ENTITY, COMPONENT) __ecs_entity_has_component(ENTITY, COMPONENT, __FILE__, __LINE__)
#define ecs_entity_is_last_frame(ENTITY) __ecs_entity_is_last_frame(ENTITY, __FILE__, __LINE__)
#define ecs_entity_is_first_frame(ENTITY) __ecs_entity_is_first_frame(ENTITY, __FILE__, __LINE__)
#define ecs_entity_destroy(ENTITY) __ecs_entity_destroy(ENTITY, __FILE__, __LINE__)
#define ecs_entity_get_reference(REFERENCE_PTR, ENTITY) __ecs_entity_get_reference(REFERENCE_PTR, ENTITY, __FILE__, __LINE__)
#define ecs_entity_clean_reference(REFERENCE_PTR) __ecs_entity_clean_reference(REFERENCE_PTR, __FILE__, __LINE__)
#define ecs_entity_reference_is_last_frame(REFERENCE) __ecs_entity_reference_is_last_frame(REFERENCE, COMPONENT, __FILE__, __LINE__)
#define ecs_entity_reference_is_first_frame(REFERENCE) __ecs_entity_reference_is_first_frame(REFERENCE, COMPONENT, __FILE__, __LINE__)
#define ecs_entity_reference_has_component(REFERENCE, COMPONENT) __ecs_entity_reference_has_component(REFERENCE, COMPONENT, __FILE__, __LINE__)
#define ecs_entity_reference_get_component(REFERENCE, COMPONENT) __ecs_entity_reference_get_component(REFERENCE, COMPONENT, __FILE__, __LINE__)
#define ecs_entity_reference_remove_component(REFERENCE, COMPONENT) __ecs_entity_reference_remove_component(REFERENCE, COMPONENT, __FILE__, __LINE__)
#define ecs_entity_reference_insert_component(REFERENCE, TYPE, COMPONENT, VALUE) do { *(TYPE *)__ecs_entity_reference_insert_component(REFERENCE, COMPONENT, __FILE__, __LINE__) = VALUE; } while(0)
#define ecs_entity_reference_insert_empty_component(REFERENCE, COMPONENT) __ecs_entity_reference_insert_empty_component(REFERENCE, COMPONENT, __FILE__, __LINE__)
#define ecs_entity_reference_destroy(REFERENCE) __ecs_entity_reference_destroy(REFERENCE, __FILE__, __LINE__)
#define ecs_system_create(SYSTEM, FN, EVENT) do { __ecs_system_create(SYSTEM, FN, EVENT, __FILE__, __LINE__); } while(0)
#define ecs_system_exists(SYSTEM) __ecs_system_exists(SYSTEM)
#define ecs_system_must_have(SYSTEM, ...) do { const char *comps_names[] = { __VA_ARGS__ }; __ecs_system_must_have(SYSTEM, sizeof (comps_names) / sizeof (comps_names[0]), comps_names, __FILE__, __LINE__); } while(0)
#define ecs_system_must_not_have(SYSTEM, ...) do { const char *comps_names[] = { __VA_ARGS__ }; __ecs_system_must_not_have(SYSTEM, sizeof (comps_names) / sizeof (comps_names[0]), comps_names, __FILE__, __LINE__); } while(0)
#define ecs_system_activate(SYSTEM) do { (void)SYSTEM; __ecs_system_activate(#SYSTEM, __FILE__, __LINE__); } while(0)
#define ecs_system_deactivate(SYSTEM) __ecs_system_deactivate(SYSTEM, __FILE__, __LINE__)
#define ecs_system_pause(SYSTEM) __ecs_system_pause(SYSTEM, __FILE__, __LINE__)
#define ecs_system_unpause(SYSTEM) __ecs_system_unpause(SYSTEM, __FILE__, __LINE__)

#endif/*__ECS_H__*/
