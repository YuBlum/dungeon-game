#ifndef __ECS_H__
#define __ECS_H__


#include "include/types.h"

typedef u32 Entity;
typedef i64 SignedEntity;
typedef struct System System;

typedef void(*SystemFn)(void);
typedef enum {
  SYS_PRE_UPDATE,
  SYS_UPDATE,
  SYS_POS_UPDATE,
  SYS_PRE_DRAW,
  SYS_DRAW,
  SYS_POS_DRAW,

  SYSTEM_EVENTS_AMOUNT
} SystemEvent;

void ecs_create(void);
void __ecs_component_create(usize size, const char *name, const char *file, u32 line);
void __ecs_entity_creation_begin(usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line);
void *__ecs_entity_creation_setup_component(const char *comp_name, const char *file, u32 line);
void __ecs_entity_creation_end(const char *file, u32 line);
void __ecs_entity_remove_component(Entity e, const char *comp_name, const char *file, u32 line);
void *__ecs_entity_insert_component(Entity e, const char *comp_name, const char *file, u32 line);
bool __ecs_entity_has_component(Entity e, const char *comp_name, const char *file, u32 line);
void __ecs_entity_destroy(Entity e, const char *file, u32 line);
void *__ecs_get_component_list(const char *comp_name, const char *file, u32 line);
usize ecs_entities_amount(void);
void __ecs_system_create(const char *name, SystemFn fn, SystemEvent event, const char *file, u32 line);
void __ecs_system_must_have(const char *name, usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line);
void __ecs_system_must_not_have(const char *name, usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line);
void __ecs_system_activate(const char *name, const char *file, u32 line);
void __ecs_system_deactivate(const char *name, const char *file, u32 line);
void ecs_system_deactivate_all(void);
void ecs_update(void);
void ecs_draw(void);

#define ecs_component_create(TYPE, NAME) __ecs_component_create(sizeof (TYPE), NAME, __FILE__, __LINE__)
#define ecs_get_component_list(COMPONENT) __ecs_get_component_list(COMPONENT, __FILE__, __LINE__)
#define ecs_entity_creation_begin(...) do { const char *comps_names[] = { __VA_ARGS__ }; __ecs_entity_creation_begin(sizeof (comps_names) / sizeof (comps_names[0]), comps_names, __FILE__, __LINE__); } while(0)
#define ecs_entity_creation_setup_component(TYPE, COMPONENT, VALUE) do { *((TYPE *)__ecs_entity_creation_setup_component(COMPONENT, __FILE__, __LINE__)) = (VALUE); } while(0)
#define ecs_entity_creation_end() __ecs_entity_creation_end(__FILE__, __LINE__);
#define ecs_entity_remove_component(ENTITY, COMPONENT) __ecs_entity_remove_component(ENTITY, COMPONENT, __FILE__, __LINE__)
#define ecs_entity_insert_component(ENTITY, TYPE, COMPONENT, VALUE) do { *(TYPE *)__ecs_entity_insert_component(ENTITY, COMPONENT, __FILE__, __LINE__) = VALUE; } while(0)
#define ecs_entity_has_component(ENTITY, COMPONENT) __ecs_entity_has_component(ENTITY, COMPONENT, __FILE__, __LINE__)
#define ecs_entity_destroy(ENTITY) __ecs_entity_destroy(ENTITY, __FILE__, __LINE__)
#define ecs_system_create(FN, EVENT) __ecs_system_create(#FN, FN, EVENT, __FILE__, __LINE__)
#define ecs_system_must_have(SYSTEM, ...) do { const char *comps_names[] = { __VA_ARGS__ }; __ecs_system_must_have(#SYSTEM, sizeof (comps_names) / sizeof (comps_names[0]), comps_names, __FILE__, __LINE__); } while(0)
#define ecs_system_must_not_have(SYSTEM, ...) do { const char *comps_names[] = { __VA_ARGS__ }; __ecs_system_must_not_have(#SYSTEM, sizeof (comps_names) / sizeof (comps_names[0]), comps_names, __FILE__, __LINE__); } while(0)
#define ecs_system_activate(SYSTEM) __ecs_system_activate(#SYSTEM, __FILE__, __LINE__)
#define ecs_system_deactivate(SYSTEM) __ecs_system_deactivate(#SYSTEM, __FILE__, __LINE__)

#endif/*__ECS_H__*/
