MODE="dev"

if [ "$MODE" = "dev" ]; then
  echo "building in dev mode"
  FLAGS="-Wall -Wextra -Werror -g"
  DEFS="-DDEVMODE"
elif [ "$MODE" = "release" ]; then
  echo "building in release mode"
  FLAGS="-O3"
else
  echo "invalid build mode"
  exit 1
fi

GLAD="vendor/glad/src/glad.o"
if [ ! -f $GLAD ]; then
  echo "compiling glad"
  "cc" -c -O3 -I "vendor/glad/include/" "vendor/glad/src/glad.c" -o $GLAD
fi

CC="bear -- cc"
INCS="-I src/include/ -I vendor/glad/include/"
LIBS="-lGL -lglfw -lm -lxxhash"
OUT="-o dungeon-game"

GENERAL="
src/general/main.c   \
src/general/global.c \
"

ENGINE="
src/engine/window.c        \
src/engine/renderer.c      \
src/engine/camera.c        \
src/engine/list.c          \
src/engine/hashtable.c     \
src/engine/ecs.c           \
src/engine/hash.c          \
src/engine/input.c         \
src/engine/scene_manager.c \
src/engine/tilemap.c       \
src/engine/serialization.c \
"


GAME="
src/game/components.c                        \
src/game/scenes.c                            \
src/game/systems.c                           \
                                             \
src/game/systems/set_tile.c                  \
src/game/systems/movement.c                  \
src/game/systems/input_direction.c           \
src/game/systems/collision.c                 \
src/game/systems/draw_rect.c                 \
src/game/systems/draw_character_sheet.c      \
src/game/systems/draw_option.c               \
src/game/systems/select_option.c             \
src/game/systems/cursor_navigation_system.c  \
src/game/systems/check_save_slot.c           \
src/game/systems/draw_save_slot.c            \
src/game/systems/select_save_slot.c          \
src/game/systems/draw_character_name_input.c \
src/game/systems/global_cursor_update.c      \
src/game/systems/type_character_name_input.c \
src/game/systems/total_attribute_points.c    \
src/game/systems/draw_attribute_input.c      \
src/game/systems/select_attribute_input.c    \
src/game/systems/draw_menu_hint.c            \
src/game/systems/menu_hint.c                 \
src/game/systems/new_character_setup.c       \
src/game/systems/submit_character_input.c    \
src/game/systems/submit_attribute_input.c    \
src/game/systems/delete_save_slot.c          \
src/game/systems/draw_terminal.c             \
src/game/systems/pause.c                     \
src/game/systems/in_game_menu_title.c        \
src/game/systems/activate_game_option.c      \
src/game/systems/draw_carrying_weight.c      \
src/game/systems/inventory_header.c          \
src/game/systems/draw_item.c                 \
src/game/systems/reset_items_amount.c        \
src/game/systems/update_items_amount.c       \
src/game/systems/items_offset.c              \
                                             \
src/game/scenes/main_menu.c                  \
src/game/scenes/save_slots_menu.c            \
src/game/scenes/delete_save_menu.c           \
src/game/scenes/character_creation.c         \
src/game/scenes/overworld.c                  \
                                             \
src/game/prefabs/attribute_input.c           \
src/game/prefabs/character_name_input.c      \
src/game/prefabs/menu_cursor.c               \
src/game/prefabs/menu_hint.c                 \
src/game/prefabs/menu_option.c               \
src/game/prefabs/new_character.c             \
src/game/prefabs/player.c                    \
src/game/prefabs/save_slot.c                 \
src/game/prefabs/solid.c                     \
src/game/prefabs/terminal.c                  \
src/game/prefabs/pause.c                     \
src/game/prefabs/item.c                      \
"

$CC $FLAGS $GLAD $DEFS $GENERAL $ENGINE $GAME $INCS $LIBS $OUT
