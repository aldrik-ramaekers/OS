// 
static void setup_IRQ_stack()
{
   int stack, mode;stack = 0xFFFFFFFF−7;

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
   int status = 0b01010011;
   asm("msr cpsr, %[ps]" : : [ps]"r"(status));
}

void interrupts_initialize()
{

}