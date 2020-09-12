#include "definitions.h"

#define STANDARD_X 320
#define STANDARD_Y 240

// System software
software_interface* _info_bar = 0;

// User software
software_interface * active_software = 0;

int main(void) {

    // Initialize system
    interrupts_initialize();
    vga_adapter_initialize();
    software_initialize();

    // Initialize system software
    _info_bar = &_info_bar_software;
    _info_bar->initialize();

    console_report_message("Welcome to coolsville...");

    while (1)
    {
        // Switch between software using switches
        for (int32_t i = 0; i < software_count(); i++) {
            if (active_software && !switch_is_on(software_get_index(active_software))) {
                active_software->destroy();
                active_software = 0;

                draw_clear_screen();
            }

            if (switch_is_on(i) && !active_software) {
                if (active_software) active_software->destroy();

                draw_clear_screen();

                active_software = software_at(i);
                active_software->initialize();
            }
        }

        // Handle system software
        _info_bar->update();
        _info_bar->draw();

        // Either draw active software or console
        if (active_software) {
            active_software->update();
            active_software->draw();
        }
        else { 
            console_draw();
        }

        vga_adapter_wait_for_vsync(_default_vga_adapter);
    }

    return 0;
}