#include "game/components.h"
#include "general/global.h"
#include "engine/ecs.h"
#include "engine/renderer.h"
#include "engine/scene_manager.h"

void
menu_hint_system(void) {
  Tag *tag = ecs_get_component_list("tag");
  Color *color = ecs_get_component_list("color");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (scene_manager_is_current_scene(character_creation_scene)) {
      switch (global.menu.cursor_id) {
        case 0:
          switch (global.menu.option_id[0]) {
            case 0:
              tag[e] = "Type your name.";
              color[e] = 0x00ff00ff;
              break;
            case 1:
              tag[e] = "Choose a class.";
              color[e] = 0x00ff00ff;
              break;
            case 2:
              tag[e] = "Attributes defines your qualities and defects.\nYou have 5 points to ditribute among them.";
              color[e] = 0x00ff00ff;
              break;
            case 3:
              if (!global.character_creation.has_name) {
                tag[e] = "You need to type your name.";
                color[e] = 0xff0000ff;
              } else if (global.character_creation.class == CLASS_UNKNOWN) {
                tag[e] = "You need to choose a class.";
                color[e] = 0xff0000ff;
              } else if (global.character_creation.total_attribute_points > 0) {
                tag[e] = "You need to use all your attribute points.";
                color[e] = 0xff0000ff;
              } else {
                tag[e] = "";
              }
              break;
            default:
              tag[e] = "";
              break;
          }
          break;
        case 1:
          switch (global.menu.option_id[1]) {
            case 0:
              tag[e] = "Good for melee combat.\nYour Strength starts at 0.";
              color[e] = 0x00ff00ff;
              break;
            case 1:
              tag[e] = "Good for ranged combat and exploration.\nYour Agility starts at 0.";
              color[e] = 0x00ff00ff;
              break;
            case 2:
              tag[e] = "Good for casting spells and variety.\nYour Intelect starts at 0.";
              color[e] = 0x00ff00ff;
              break;
            default:
              tag[e] = "";
              break;
          }
          break;
        case 2:
          switch (global.menu.option_id[2]) {
            case 0:
              tag[e] = "For ranged attacks and precision tests.";
              color[e] = 0x00ff00ff;
              break;
            case 1:
              tag[e] = "For spell casts and memory tests.\nUsed to determinate your EP.";
              color[e] = 0x00ff00ff;
              break;
            case 2:
              tag[e] = "For persuasion and perception tests.\nInfluence how others view you.\nUsed to determinate your EP.";
              color[e] = 0x00ff00ff;
              break;
            case 3:
              tag[e] = "For melee attacks.\nUsed to determinate your HP.";
              color[e] = 0x00ff00ff;
              break;
            case 4:
              tag[e] = "Used to determinate your HP and FP.";
              color[e] = 0x00ff00ff;
              break;
            default:
              tag[e] = "";
              break;
          }
          break;
        default:
          break;
      }
    }
  }
}
