
typedef struct t_pong_player {
   int32_t score;
   int16_t y;
} pong_player;

typedef struct t_pong_ball {
   int16_t x;
   int16_t y;
   int8_t dir_y;
   int8_t dir_x;
} pong_ball;

pong_player p1 = {0};
pong_player p2 = {0};

pong_ball ball = {0};

#define PONG_PLAYER_HEIGHT 40
#define PONG_PLAYER_WIDTH 10

#define PONG_BALL_SIZE 20

static void _pong_reset_players() {
   vga_adapter *adapter = vga_adapter_get_default();
   p1.y = adapter->screen_height / 2 - PONG_PLAYER_HEIGHT / 2;
   p2.y = adapter->screen_height / 2 - PONG_PLAYER_HEIGHT / 2;
}

static void _pong_reset_ball() {
   vga_adapter *adapter = vga_adapter_get_default();
   ball.x = adapter->screen_width / 2 - PONG_BALL_SIZE / 2;
   ball.y = adapter->screen_height / 2 - PONG_BALL_SIZE / 2;

   ball.dir_y = 1;
   ball.dir_x = 1;
}
static void pong_initialize() {
   _pong_reset_ball();
   _pong_reset_players();

   seg_display_set_value(0, 0);
   seg_display_set_value(0, 5);
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

   ball.x += ball.dir_x;
   ball.y += ball.dir_y;

   vga_adapter *adapter = vga_adapter_get_default();

   if (ball.y == 0 || ball.y + PONG_BALL_SIZE == adapter->screen_height) {
      ball.dir_y = -ball.dir_y;
   }

   if (ball.x == PONG_PLAYER_WIDTH + 5 && ball.y < p1.y + PONG_PLAYER_HEIGHT && ball.y + PONG_BALL_SIZE > p1.y) {
      ball.dir_x = -ball.dir_x;
   }
   else if (ball.x + PONG_BALL_SIZE == adapter->screen_width - PONG_PLAYER_WIDTH - 5 && ball.y < p2.y + PONG_PLAYER_HEIGHT && ball.y + PONG_BALL_SIZE > p2.y) {
      ball.dir_x = -ball.dir_x;
   }
   else if (ball.x < 5 + PONG_PLAYER_WIDTH) {
      p2.score++;
      _pong_reset_ball();
      _pong_reset_players();

      int8_t ls = p2.score % 10;
      int8_t ms = p2.score / 10;
      seg_display_set_value(ls, 4);
      seg_display_set_value(ms, 5);
   }
   else if (ball.x + PONG_BALL_SIZE > adapter->screen_width - PONG_PLAYER_WIDTH - 5) {
      p1.score++;
      _pong_reset_ball();
      _pong_reset_players();

      int8_t ls = p1.score % 10;
      int8_t ms = p1.score / 10;
      seg_display_set_value(ls, 0);
      seg_display_set_value(ms, 1);
   }

   if (p1.y < 0) p1.y = 0;
   if (p1.y + PONG_PLAYER_HEIGHT > adapter->screen_height) p1.y = adapter->screen_height - PONG_PLAYER_HEIGHT;
   if (p2.y < 0) p2.y = 0;
   if (p2.y + PONG_PLAYER_HEIGHT > adapter->screen_height) p2.y = adapter->screen_height - PONG_PLAYER_HEIGHT;
}

static void pong_draw() {
   vga_adapter *adapter = vga_adapter_get_default();

   // draw players
   draw_rectangle(adapter, 5, p1.y, PONG_PLAYER_WIDTH, PONG_PLAYER_HEIGHT, 0xFFFFFFFF);
   draw_rectangle(adapter, adapter->screen_width - PONG_PLAYER_WIDTH - 5, p2.y, PONG_PLAYER_WIDTH, PONG_PLAYER_HEIGHT, 0xFFFFFFFF);

   // draw ball
   draw_rectangle(adapter, ball.x, ball.y, PONG_BALL_SIZE, PONG_BALL_SIZE, 0xFFFFFFFF);
}

static void pong_destroy() {

}

#undef PONG_PLAYER_HEIGHT
#undef PONG_PLAYER_WIDTH
#undef PONG_BALL_SIZE

software_interface _pong_software = {
   "Pong",
   pong_initialize,
   pong_update,
   pong_draw,
   pong_destroy,
};