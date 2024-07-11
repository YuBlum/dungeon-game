#ifndef __SYSTEMS_H__
#define __SYSTEMS_H__

void set_tile_system(void);
void input_direction_system(void);
void collision_system(void);
void movement_system(void);
void draw_rect_system(void);
void draw_char_sheet_system(void);
void draw_option_system(void);
void hover_over_option_system(void);
void select_option_system(void);
void check_save_slot_system(void);
void draw_save_slot_system(void);

void systems_create(void);

#endif/*__SYSTEMS_H__*/
