#ifndef __PREFABS_H__
#define __PREFABS_H__

#include "game/components.h"
#include "engine/ecs.h"
#include "engine/math.h"

void prefab_player(V2f position);
void prefab_solid(V2f position);
void prefab_menu_option(V2f position, Tag tag, Callback callback, CallbackArg callback_arg, u32 id, u32 cursor_id, bool active);
void prefab_menu_option_with_u32_arg(V2f position, Tag tag, Callback callback, CallbackArg callback_arg, u32 id, u32 cursor_id, bool active, u32 arg_starting_value, const char *extra_component);
void prefab_menu_cursor(u32 id, bool horizontal, bool wrap);
void prefab_save_slot(V2f position, u32 id, u32 cursor_id);
void prefab_character_name_input(V2f position, u32 id, u32 cursor_id, Callback get_character_name);
void prefab_attribute_input(V2f position, AttributeType attribute_type, u32 id, u32 cursor_id, Callback get_attribute);
void prefab_menu_hint(V2f position);
void prefab_new_character(EntityReference *reference);
void prefab_terminal(void);
void prefab_pause(void);
void prefab_in_game_menu_option(V2f position, Tag tag, Callback callback, CallbackArg callback_arg, u32 id, u32 cursor_id, bool active, InGameMenuType type);
void prefab_in_game_menu_option_with_u32_arg(V2f position, Tag tag, Callback callback, CallbackArg callback_arg, u32 id, u32 cursor_id, bool active, u32 arg_starting_value, const char *extra_component, InGameMenuType type);
void prefab_item_melee(const char *name, u32 weight, u32 id, bool equiped, u32 dice_amount, u32 dice_faces, u32 test_modifier, u32 critical_hit, u32 attribute_threshold);
void prefab_item_ranged(const char *name, u32 weight, u32 id, bool equiped, u32 dice_amount, u32 dice_faces, u32 test_modifier, u32 critical_hit, u32 attribute_threshold, AmmoType ammo_type);
void prefab_item_staff(const char *name, u32 weight, u32 id, bool equiped, SpellType spell_type, u32 reduce_spell_dt, u32 attribute_threshold);
void prefab_item_ammo(const char *name, u32 weight, u32 id, AmmoType ammo_type, u32 amount);
void prefab_item_defensive(const char *name, u32 weight, u32 id, bool equiped, u32 attribute_threshold, DefensiveType defensive_type, u32 extra_armour_points);
void prefab_item_lockpick(const char *name, u32 weight, u32 id, LockpickType lockpick_type, u32 amount);
void prefab_item_potion(const char *name, u32 weight, u32 id, u32 dice_amount, u32 dice_faces, u32 test_modifier, PotionType potion_type, u32 amount);
void prefab_item_magic_component(const char *name, u32 weight, u32 id, MagicComponentType magic_component_type, u32 amount);
void prefab_all_items(void);

#endif/*__PREFABS_H__*/
