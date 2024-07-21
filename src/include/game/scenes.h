#ifndef __SCENES_H__
#define __SCENES_H__

void scene_main_menu_on_start(void);
void scene_main_menu_on_update(void);

void scene_save_slots_menu_on_start(void);
void scene_save_slots_menu_on_update(void);

void scene_character_creation_on_start(void);
void scene_character_creation_on_update(void);

void scene_delete_save_menu_on_start(void);
void scene_delete_save_menu_on_update(void);

void scene_overworld_on_start(void);
void scene_overworld_on_update(void);
void scene_overworld_on_draw(void);

void scenes_create(void);

#endif/*__SCENES_H__*/
