#ifndef __SYSTEMS_H__
#define __SYSTEMS_H__

void set_tile_system(void);
void input_direction_system(void);
void collision_system(void);
void movement_system(void);
void draw_rect_system(void);
void draw_character_sheet_system(void);
void draw_option_system(void);
void cursor_navigation_system(void);
void select_option_system(void);
void check_save_slot_system(void);
void draw_save_slot_system(void);
void select_save_slot_system(void);
void draw_character_name_input_system(void);
void global_cursor_update_system(void);
void type_character_name_input_system(void);
void draw_option_with_u32_arg_system(void);
void total_attribute_points_system(void);
void draw_attribute_input_system(void);
void select_attribute_input(void);
void menu_hint_system(void);
void draw_menu_hint_system(void);
void new_character_setup_system(void);
void submit_character_input_system(void);
void submit_attribute_input_system(void);
void delete_save_slot_system(void);

void systems_create(void);

#endif/*__SYSTEMS_H__*/
