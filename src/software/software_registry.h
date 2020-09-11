#ifndef INCLUDE_SOFTWARE_SOFTWARE_REGISTRY_H
#define INCLUDE_SOFTWARE_SOFTWARE_REGISTRY_H

#define MAX_SOFTWARE_COUNT 100

void software_initialize();
int32_t software_count();
software_interface* software_at(int32_t index);
int32_t software_get_index(software_interface* interface);

#endif