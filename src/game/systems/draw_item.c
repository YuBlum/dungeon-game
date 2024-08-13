#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/renderer.h"
#include "engine/types.h"
#include "general/global.h"
#include "general/core.h"
#include "game/components.h"

void
system_draw_item(usize entities_amount) {
  ItemInfo *item = ecs_get_component_list("item-info");
  u32 *item_amount = ecs_entities_have_component("item-amount") ? ecs_get_component_list("item-amount") : 0;
  bool *equiped = 0;
  if (ecs_entities_have_component("item-equiped")) {
    equiped = ecs_get_component_list("item-equiped");
  }
  for (Entity e = 0; e < entities_amount; e++) {
    if (item[e].type != global.game.item_type_page || item[e].id > global.game.items_cursor_max || item[e].id < global.game.items_cursor_min) continue;
    f32 y = global.game.inventory_y - (1 + PX_TO_UNIT * 3) * (item[e].id + 1) + global.game.items_offset;
    Color bg = 0x000000ff;
    Color fg = 0xffffffff;
    Layer layer = 0;
    if (global.menu.option_id[global.game.items_cursor_id] == item[e].id) {
      bg ^= fg;
      fg ^= bg;
      bg ^= fg;
      layer = 1;
    }
    Color name_col = fg;
    const char *equip_begin = "";
    const char *equip_end = "";
    if (equiped && equiped[e] && (
      (global.game.weapon.has_item && global.game.weapon.type == item[e].type && global.game.weapon.id == item[e].id) ||
      (global.game.shield.has_item && global.game.shield.type == item[e].type && global.game.shield.id == item[e].id) ||
      (global.game.armour.has_item && global.game.armour.type == item[e].type && global.game.armour.id == item[e].id)
    )) {
      equip_begin = ">";
      equip_end = "<";
    }
    renderer_rect(V2F(UI_LEFT - PX_TO_UNIT * 2, y + PX_TO_UNIT * 2), V2F(UI_W + PX_TO_UNIT * 4, 1 + PX_TO_UNIT * 4), false, 0xffffffff, layer);
    renderer_rect(V2F(UI_LEFT - PX_TO_UNIT * 1, y + PX_TO_UNIT * 1), V2F(UI_W + PX_TO_UNIT * 2, 1 + PX_TO_UNIT * 2), false, bg, layer);
    renderer_rect(V2F(UI_RIGHT - 2.0f, y + PX_TO_UNIT * 2), V2F(PX_TO_UNIT, 1 + PX_TO_UNIT * 4), false, fg, layer);
    if (item_amount) {
      renderer_text(V2F(UI_LEFT + PX_TO_UNIT, y), 1, false, false, name_col, layer, "%s%.*s x%u%s", equip_begin, item[e].name_size, item[e].name_buff, item_amount[e], equip_end);
    } else {
      renderer_text(V2F(UI_LEFT + PX_TO_UNIT, y), 1, false, false, name_col, layer, "%s%.*s%s", equip_begin, item[e].name_size, item[e].name_buff, equip_end);
    }
    renderer_text(V2F(UI_RIGHT - 1.5f - PX_TO_UNIT, y), 1, false, false, fg, layer, "%.2u", item[e].weight);
  }
}
