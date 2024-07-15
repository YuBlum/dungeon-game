#ifndef __SYSTEMS_H__
#define __SYSTEMS_H__

void system_set_tile(void);
void system_input_direction(void);
void system_collision(void);
void system_movement(void);
void system_draw_rect(void);
void system_draw_character_sheet(void);
void system_draw_option(void);
void system_cursor_navigation(void);
void system_select_option(void);
void system_check_save_slot(void);
void system_draw_save_slot(void);
void system_select_save_slot(void);
void system_draw_character_name_input(void);
void system_global_cursor_update(void);
void system_type_character_name_input(void);
void system_draw_option_with_u32_arg(void);
void system_total_attribute_points(void);
void system_draw_attribute_input(void);
void system_select_attribute_input(void);
void system_menu_hint(void);
void system_draw_menu_hint(void);
void system_new_character_setup(void);
void system_submit_character_input(void);
void system_submit_attribute_input(void);
void system_delete_save_slot(void);
void system_draw_terminal(void);
void system_pause(void);

void systems_create(void);

#endif/*__SYSTEMS_H__*/
