#ifndef __PREFABS_H__
#define __PREFABS_H__

#include "game/components.h"
#include "engine/ecs.h"
#include "engine/math.h"

void prefab_player(V2f position);
void prefab_solid(V2f position);
void prefab_menu_option(V2f position, Tag tag, Callback callback, CallbackArg callback_arg, u32 id, u32 cursor_id);
void prefab_menu_cursor(u32 options_amount, u32 id, bool horizontal);
void prefab_save_slot(V2f position, u32 id, u32 cursor_id);
void prefab_character_name_input(V2f position, u32 id, u32 cursor_id, Callback get_character_name);
void prefab_menu_option_with_u32_arg(V2f position, Tag tag, Callback callback, CallbackArg callback_arg, u32 id, u32 cursor_id, u32 arg_starting_value, const char *extra_component);
void prefab_attribute_input(V2f position, AttributeType attribute_type, u32 id, u32 cursor_id, Callback get_attribute);
void prefab_menu_hint(V2f position);
void prefab_new_character(EntityReference *reference);
void prefab_terminal(void);
void prefab_pause(void);

#endif/*__PREFABS_H__*/
