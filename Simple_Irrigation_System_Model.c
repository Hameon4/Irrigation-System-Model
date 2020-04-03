#include <hidef.h>      /* common defines and macros */
#include <mc9s12dg256.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dg256b"
#include "main_asm.h" /* interface to the assembly module */
int light_val, Tc_val, val, speed;
void main(void) {
    PLL_init();        // set system clock frequency to 24 MHz
    ad0_enable();
    lcd_init();
    motor0_init();
    led_enable();
    seg7_disable();
    SW_enable();

    while(1){
//Reading analog input of the light sensor
      light_val = ad0conv(4);
      light_val = light_val >> 1;
      set_lcd_addr(0x00);
      type_lcd("Light:");
      write_int_lcd(light_val);
      ms_delay(100);
//Reading analog input of the temperature sensor
     Tc_val = ad0conv(5);
     Tc_val = Tc_val - 20;
      set_lcd_addr(0x40);
      type_lcd("Temp:");
      write_int_lcd(Tc_val);
      ms_delay(100);


      if ( (Tc_val > 15) && (light_val > 60)) { //If this is true, then activate the water pump
      leds_on(SW1_dip());
      val = ad0conv(7);
      speed = val;
      motor0(speed);
      set_lcd_addr(0x4a);
      write_int_lcd(speed);
      ms_delay(100);
      }
      else{

      motor0(0);
      }
    }
}
