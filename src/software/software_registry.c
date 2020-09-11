static software_interface* _system_software[MAX_SOFTWARE_COUNT];

static void software_register(software_interface* interface) {
   int32_t index = software_count();
   _system_software[index] = interface;
}

void software_initialize() {
   for (int32_t i = 0; i < MAX_SOFTWARE_COUNT; i++) {
      _system_software[i] = 0;
   }

   software_register(&_pong_software);
}

int32_t software_count() {
   for (int32_t i = 0; i < MAX_SOFTWARE_COUNT; i++) {
      software_interface* interface = software_at(i);

      if (interface == 0) return i;
   }

   return MAX_SOFTWARE_COUNT;
}

inline software_interface* software_at(int32_t index) {
   return _system_software[index];
}

int32_t software_get_index(software_interface* interface) {
   if (!interface) return -1;

   for (int32_t i = 0; i < MAX_SOFTWARE_COUNT; i++) {
      software_interface* ifa = software_at(i);
      if (ifa == interface) return i;
   }

   return -1;
}