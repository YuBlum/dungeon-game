#ifndef __PREFABS_H__
#define __PREFABS_H__

#include "include/components.h"
#include "include/math.h"

void prefab_player(V2f position);
void prefab_solid(V2f position);
void prefab_menu_option(V2f position, const char *tag, OptionCallback callback, u32 id, u32 cursor_id);
void prefab_menu_cursor(u32 options_amount, u32 id, bool horizontal);
void prefab_save_slot(V2f position, u32 id, u32 cursor_id);
void prefab_character_name_input(V2f position, u32 id, u32 cursor_id);

#endif/*__PREFABS_H__*/
