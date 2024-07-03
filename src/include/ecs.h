#ifndef __ECS_H__
#define __ECS_H__


#include "include/types.h"

typedef u64 Entity;
typedef u32 EntityID;

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
void *__ecs_get_component_list(const char *comp_name, const char *file, u32 line);
usize ecs_entities_amount(void);
void __ecs_entity_create(Entity *out, usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line);
void *__ecs_entity_get_component(Entity entity, const char *comp_name, const char *file, u32 line);
void __ecs_entity_destroy(Entity entity, const char *file, u32 line);
void __ecs_system_create(SystemFn fn, SystemEvent event, usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line);
void ecs_update(void);
void ecs_draw(void);

#define ecs_component_create(TYPE, NAME) __ecs_component_create(sizeof (TYPE), NAME, __FILE__, __LINE__)
#define ecs_get_component_list(COMPONENT) __ecs_get_component_list(COMPONENT, __FILE__, __LINE__)
#define ecs_entity_create(OUT_ENTITY, ...) do { const char *comps_names[] = { __VA_ARGS__ }; __ecs_entity_create(OUT_ENTITY, sizeof (comps_names) / sizeof (comps_names[0]), comps_names, __FILE__, __LINE__); } while(0)
#define ecs_entity_get_component(ENTITY, COMPONENT) __ecs_entity_get_component(ENTITY, COMPONENT, __FILE__, __LINE__)
#define ecs_entity_destroy(ENTITY) __ecs_entity_destroy(ENTITY, __FILE__, __LINE__)
#define ecs_system_create(FN, EVENT, ...) do { const char *comps_names[] = { __VA_ARGS__ }; __ecs_system_create(FN, EVENT, sizeof (comps_names) / sizeof (comps_names[0]), comps_names, __FILE__, __LINE__); } while(0)

#endif/*__ECS_H__*/
