#ifndef __SYSTEMS_H__
#define __SYSTEMS_H__

#include "engine/types.h"

void system_set_tile(usize entities_amount);
void system_input_direction(usize entities_amount);
void system_collision(usize entities_amount);
void system_movement(usize entities_amount);
void system_draw_rect(usize entities_amount);
void system_draw_character_sheet(usize entities_amount);
void system_draw_option(usize entities_amount);
void system_cursor_navigation(usize entities_amount);
void system_select_option(usize entities_amount);
void system_check_save_slot(usize entities_amount);
void system_draw_save_slot(usize entities_amount);
void system_select_save_slot(usize entities_amount);
void system_draw_character_name_input(usize entities_amount);
void system_type_character_name_input(usize entities_amount);
void system_draw_option_with_u32_arg(usize entities_amount);
void system_total_attribute_points(usize entities_amount);
void system_draw_attribute_input(usize entities_amount);
void system_select_attribute_input(usize entities_amount);
void system_menu_hint(usize entities_amount);
void system_draw_menu_hint(usize entities_amount);
void system_new_character_setup(usize entities_amount);
void system_submit_character_input(usize entities_amount);
void system_submit_attribute_input(usize entities_amount);
void system_delete_save_slot(usize entities_amount);
void system_draw_terminal(usize entities_amount);
void system_pause(usize entities_amount);
void system_activate_game_option(usize entities_amount);
void system_draw_carrying_weight(usize entities_amount);
void system_inventory_header(usize entities_amount);
void system_draw_item(usize entities_amount);
void system_grow_items_amount(usize entities_amount);
void system_shrink_items_amount(usize entities_amount);
void system_items_offset(usize entities_amount);
void system_select_item(usize entities_amount);

void systems_create(void);

#endif/*__SYSTEMS_H__*/
