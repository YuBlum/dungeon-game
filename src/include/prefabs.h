#ifndef __PREFABS__
#define __PREFABS__

#include "include/components.h"
#include "include/math.h"

void prefab_player(V2f position);
void prefab_solid(V2f position);
void prefab_menu_option(V2f position, const char *tag, OptionCallback callback, i32 option_id);
void prefab_menu_cursor(i32 options_amount);
void prefab_save_slot(V2f position, i32 option_id);

#endif/*__PREFABS__*/
