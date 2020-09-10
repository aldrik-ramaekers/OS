// 
static void setup_IRQ_stack()
{
   int stack, mode;
   stack = 0xFFFFFFFF-7;

   // top of A9 on-chip memory, aligned to 8 bytes
   /* change processor to IRQ mode with interrupts disabled */
   mode = 0b11010010;
   asm("msr cpsr, %[ps]" : : [ps] "r" (mode));

   /* set banked stack pointer */
   asm("mov sp, %[ps]" : : [ps] "r" (stack));

   /* go back to SVC mode before executing subroutine return! */
   mode = 0b11010011;
   asm("msr cpsr, %[ps]" : : [ps] "r" (mode));
}

static void enable_interrupts()
{
   /* configure the HPS timer interrupt */
   *((int*) 0xFFFED8C4) = 0x01000000;
   *((int*) 0xFFFED118) = 0x00000080;
   
   /* configure the FPGA interval timer and KEYs interrupts */
   *((int*) 0xFFFED848) = 0x00000101;
   *((int*) 0xFFFED108) = 0x00000300;
   
   // Set Interrupt Priority Mask Register (ICCPMR). Enable interrupts of all priorities
   *((int*) 0xFFFEC104) = 0xFFFF;
   
   // Set CPU Interface Control Register (ICCICR). Enable signaling of interrupts
   *((int*) 0xFFFEC100) = 1; // enable = 1
   
   // Configure the Distributor Control Register (ICDDCR) to send pending interrupts to CPUs
   *((int*) 0xFFFED000) = 1; // enable = 1


   // Setup key interrupts
   {
      volatile int* KEY_ptr = (int *) 0xFF200050;
      *(KEY_ptr + 2) = 0xF; // enable interrupts for all four KEYs
   }

   // Finally, turn on interrupts
   int status = 0b01010011;
   asm("msr cpsr, %[ps]" : : [ps]"r"(status));
}

void interrupts_initialize()
{
   setup_IRQ_stack();
   enable_interrupts();
}

/* Define the IRQ exception handler */
void __attribute__ ((interrupt)) __cs3_isr_irq (void) {
   // Read the ICCIAR from the processor interface
   int int_ID = *((int*) 0xFFFEC10C);
   
   if(int_ID == 199) {  // check if interrupt is from the HPS timer     
      // not implemented 
   }
   else if(int_ID == 72) { // check if interrupt is from the Intel timer
      // not implemented 
   }
   else if(int_ID == 73) { // check if interrupt is from the KEYs
      volatile int* KEY_ptr = (int*)KEY_BASE;
      int press = press = *(KEY_ptr + 3);
      *(KEY_ptr + 3) = press; // cleanup interrupt

      if (press == 0x1) pushbutton_set_pressed(0);
      if (press == 0x2) pushbutton_set_pressed(1);
      if (press == 0x4) pushbutton_set_pressed(2);
      if (press == 0x8) pushbutton_set_pressed(3);
   }
   else {
      assert(0);
   }
   
   // Write to the End of Interrupt Register (ICCEOIR)
   *((int*) 0xFFFEC110) = int_ID;
   return;
}

// Define the remaining exception handlers */
void __attribute__ ((interrupt)) __cs3_isr_undef(void) { 
   assert(0);
}

void __attribute__ ((interrupt)) __cs3_isr_swi(void) {
   assert(0);
}

void __attribute__ ((interrupt)) __cs3_isr_pabort(void) {
   assert(0);
}

void __attribute__ ((interrupt)) __cs3_isr_dabort(void) {
   assert(0);
}

void __attribute__ ((interrupt)) __cs3_isr_fiq(void) {
   assert(0);
}