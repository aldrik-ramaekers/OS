typedef struct t_pong_player {
   int32_t score;
   uint16_t y;
} pong_player;

pong_player p1 = {0};
pong_player p2 = {0};

#define PONG_PLAYER_HEIGHT 30
#define PONG_PLAYER_WIDTH 10

static void pong_initialize() {

}

static void pong_update() {
   if (switch_is_on(9)) {
      p1.y--;
   } else {
      p1.y++;
   }

   if (switch_is_on(8)) {
      p2.y--;
   } else {
      p2.y++;
   }

   vga_adapter *adapter = vga_adapter_get_default();

   if (p1.y < 0) p1.y = 0;
   if (p1.y - PONG_PLAYER_HEIGHT > adapter->screen_height) p1.y = adapter->screen_height - PONG_PLAYER_HEIGHT;
   if (p2.y < 0) p2.y = 0;
   if (p2.y - PONG_PLAYER_HEIGHT > adapter->screen_height) p2.y = adapter->screen_height - PONG_PLAYER_HEIGHT;
}

static void pong_draw() {
   vga_adapter *adapter = vga_adapter_get_default();

   // clear player path
   draw_rectangle(adapter, 5, p1.y - 10, PONG_PLAYER_WIDTH, PONG_PLAYER_HEIGHT + 20, 0x00000000);
   draw_rectangle(adapter, adapter->screen_width - PONG_PLAYER_WIDTH - 5, p2.y - 10, PONG_PLAYER_WIDTH, PONG_PLAYER_HEIGHT + 20, 0x00000000);

   // draw players
   draw_rectangle(adapter, 5, p1.y, PONG_PLAYER_WIDTH, PONG_PLAYER_HEIGHT, 0xFFFFFFFF);
   draw_rectangle(adapter, adapter->screen_width - PONG_PLAYER_WIDTH - 5, p2.y, PONG_PLAYER_WIDTH, PONG_PLAYER_HEIGHT, 0xFFFFFFFF);
}

static void pong_destroy() {

}

software_interface _pong_software = {
   "Pong",
   pong_initialize,
   pong_update,
   pong_draw,
   pong_destroy,
};