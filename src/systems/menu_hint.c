#include "include/components.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/scene_manager.h"

void
menu_hint_system(void) {
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (scene_manager_is_current_scene(character_creation_scene)) {
      switch (global.cursor_id) {
        case 0:
          switch (global.option_id[0]) {
            case 0:
              global.hint = "Type your name.";
              global.hint_color = 0x00ff00ff;
              break;
            case 1:
              global.hint = "Choose a class.";
              global.hint_color = 0x00ff00ff;
              break;
            case 2:
              global.hint = "Attributes defines your qualities and defects.\nYou have 5 points to ditribute among them.";
              global.hint_color = 0x00ff00ff;
              break;
            case 3:
              if (!global.has_name) {
                global.hint = "You need to type your name.";
                global.hint_color = 0xff0000ff;
              } else if (global.class == CLASS_UNKNOWN) {
                global.hint = "You need to choose a class.";
                global.hint_color = 0xff0000ff;
              } else if (global.total_attribute_points > 0) {
                global.hint = "You need to use all your attribute points.";
                global.hint_color = 0xff0000ff;
              } else {
                global.hint = "";
              }
              break;
            default:
              global.hint = "";
              break;
          }
          break;
        case 1:
          switch (global.option_id[1]) {
            case 0:
              global.hint = "Good for melee combat.\nYour Strength starts at 0.";
              global.hint_color = 0x00ff00ff;
              break;
            case 1:
              global.hint = "Good for ranged combat and exploration.\nYour Agility starts at 0.";
              global.hint_color = 0x00ff00ff;
              break;
            case 2:
              global.hint = "Good for casting spells and variety.\nYour Intelect starts at 0.";
              global.hint_color = 0x00ff00ff;
              break;
            default:
              global.hint = "";
              break;
          }
          break;
        case 2:
          switch (global.option_id[2]) {
            case 0:
              global.hint = "For ranged attacks and precision tests.";
              global.hint_color = 0x00ff00ff;
              break;
            case 1:
              global.hint = "For spell and memory tests.\nUsed to determinate your EP.";
              global.hint_color = 0x00ff00ff;
              break;
            case 2:
              global.hint = "For persuasion and perception tests.\nInfluence how others view you.\nUsed to determinate your EP.";
              global.hint_color = 0x00ff00ff;
              break;
            case 3:
              global.hint = "For melee attacks.\nUsed to determinate your HP.";
              global.hint_color = 0x00ff00ff;
              break;
            case 4:
              global.hint = "Used to determinate your HP and FP.";
              global.hint_color = 0x00ff00ff;
              break;
            default:
              global.hint = "";
              break;
          }
          break;
        default:
          break;
      }
    }
  }
}
