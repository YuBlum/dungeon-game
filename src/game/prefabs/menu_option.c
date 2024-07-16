#include "game/components.h"
#include "engine/ecs.h"
#include "engine/math.h"

static void
base_option(V2f position, Tag tag, Callback callback, CallbackArg callback_arg, u32 id, u32 cursor_id, bool active) {
  ecs_entity_creation_setup_component(V2f, "position", position);
  ecs_entity_creation_setup_component(Callback, "callback", callback);
  ecs_entity_creation_setup_component(CallbackArg, "callback-arg", callback_arg);
  ecs_entity_creation_setup_component(Tag, "tag", tag);
  ecs_entity_creation_setup_component(u32, "option-id", id);
  ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
  ecs_entity_creation_setup_component(bool, "active", active);
}

void
prefab_menu_option(V2f position, Tag tag, Callback callback, CallbackArg callback_arg, u32 id, u32 cursor_id, bool active) {
  ecs_entity_creation_begin("position", "callback", "callback-arg", "tag", "option-id", "cursor-id", "active");
    base_option(position, tag, callback, callback_arg, id, cursor_id, active);
  ecs_entity_creation_end();
}

void
prefab_menu_option_with_u32_arg(V2f position, Tag tag, Callback callback, CallbackArg callback_arg, u32 id, u32 cursor_id, bool active, u32 arg_starting_value, const char *extra_component) {
  ecs_entity_creation_begin("position", "callback", "tag", "callback-arg", "option-id", "cursor-id", "u32-arg", "active", extra_component);
    base_option(position, tag, callback, callback_arg, id, cursor_id, active);
    ecs_entity_creation_setup_component(u32, "u32-arg", arg_starting_value);
  ecs_entity_creation_end();
}

void
prefab_in_game_menu_option(V2f position, Tag tag, Callback callback, CallbackArg callback_arg, u32 id, u32 cursor_id, bool active, InGameMenuType type) {
  ecs_entity_creation_begin("position", "callback", "callback-arg", "tag", "option-id", "cursor-id", "active", "in-game-menu-type");
    base_option(position, tag, callback, callback_arg, id, cursor_id, active);
    ecs_entity_creation_setup_component(InGameMenuType, "in-game-menu-type", type);
  ecs_entity_creation_end();
}

void
prefab_in_game_menu_option_with_u32_arg(V2f position, Tag tag, Callback callback, CallbackArg callback_arg, u32 id, u32 cursor_id, bool active, u32 arg_starting_value, const char *extra_component, InGameMenuType type) {
  ecs_entity_creation_begin("position", "callback", "tag", "callback-arg", "option-id", "cursor-id", "u32-arg", "active", "in-game-menu-type", extra_component);
    base_option(position, tag, callback, callback_arg, id, cursor_id, active);
    ecs_entity_creation_setup_component(u32, "u32-arg", arg_starting_value);
    ecs_entity_creation_setup_component(InGameMenuType, "in-game-menu-type", type);
  ecs_entity_creation_end();
}
