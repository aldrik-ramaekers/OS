#include "definitions.h"

#define STANDARD_X 320
#define STANDARD_Y 240

software_interface * active_software = 0;

int main(void) {
    interrupts_initialize();
    vga_adapter* adapter = vga_adapter_initialize();
    software_initialize();

    console_report_message("Welcome to coolsville...");

    while (1)
    {
        // Switch between software using switches
        for (int32_t i = 0; i < software_count(); i++) {
            if (active_software && !switch_is_on(software_get_index(active_software))) {
                active_software->destroy();
                active_software = 0;

                draw_clear_screen(adapter);
            }

            if (switch_is_on(i) && !active_software) {
                if (active_software) active_software->destroy();

                draw_clear_screen(adapter);

                active_software = software_at(i);
                active_software->initialize();
            }
        }

        // Either draw active software or console
        if (active_software) {
            active_software->update();
            active_software->draw();
        }
        else { 
            console_draw();
        }

        vga_adapter_wait_for_vsync(adapter);
    }

    return 0;
}