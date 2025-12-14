/* 
 * File:   disp_batt_levels.c
 * Author: Krishnaveni
 * Created on 23 March, 2025, 4:30 PM
 */

#include <xc.h>
#define _XTAL_FREQ 6000000

void init(void);
void lcd_command(unsigned char i);
void lcd_data(unsigned char i);
void lcdOutput(unsigned int i);
void delay(void);
void switchscanning(void);
void display(void);
void low(void);
void medium(void);
void high(void);

unsigned int voltage_whole = 17;  // Default whole number voltage
unsigned int voltage_fraction = 5;  // Default fractional voltage
unsigned char value;

void main() {
    init();
    while (1) {
        switchscanning();
    }
}

void init(void) {
    TRISC = 0x00; // Set PORTC as output
    TRISD = 0x00; // Set PORTD as output
    TRISB = 0xF0; // Set PORTB RB4 to RB7 as input for switches
    PORTB = 0x00;
    OPTION_REG &= 0x7F; // Enable pull-up resistors 0111 1111

    // LCD Initialization
    lcd_command(0x30);
    delay();
    lcd_command(0x30);
    delay();
    lcd_command(0x38); // 8-bit mode, 2-line display
    delay();
    lcd_command(0x0C); // Display ON, Cursor OFF
    delay();
    lcd_command(0x01); // Clear screen
    delay();
}

void switchscanning(void) {
    __delay_ms(20);
    value = PORTB & 0xF0; // Read switch status

    unsigned int num = (voltage_whole * 10) + voltage_fraction;

    switch (value) {
        case 0xE0: // RB4 Pressed - Display default voltage & "BATTERY LOW"
            display();
            lcd_command(0x8A);
            lcdOutput(17);
            lcd_data('.');
            lcdOutput(5);
            lcd_data('V');
            lcd_command(0xC0);
            low();
            break;

        case 0xD0: // RB5 Pressed - Increase voltage by 0.1V
            voltage_fraction += 1;//6 7 8 9 10
            if (voltage_fraction > 9) {//f f f f t
                voltage_fraction = 0;//0
                voltage_whole = voltage_whole +1;//18
                display();
            lcd_command(0x8A);
            lcdOutput(voltage_whole);//17 18
            lcd_data('.');//. ....
            lcdOutput(voltage_fraction);//6 7 8 9 0
            lcd_data('V');
            break;
            }

            num = (voltage_whole * 10) + voltage_fraction;//176 177 178 179

            if (num >= 206 && num <= 275) {//f f f f
                high();
            } else if (num >= 176 && num <= 205) {//t t t t
                medium();
            }
            display();
            lcd_command(0x8A);
            lcdOutput(voltage_whole);//17 18
            lcd_data('.');//. ....
            lcdOutput(voltage_fraction);//6 7 8 9 0
            lcd_data('V');
            break;

        case 0xB0: // RB6 Pressed - Decrease voltage by 0.1V
            if (voltage_fraction == 0) {
                voltage_fraction = 9;
                voltage_whole--;
            } else {
                voltage_fraction = voltage_fraction-1;
            }

            num = (voltage_whole * 10) + voltage_fraction;

            if (num >= 206 && num <= 275) {
                high();
            } else if (num >= 176 && num <= 205) {
                medium();
            } else {
                low();
            }

            display();
            lcd_command(0x8A);
            lcdOutput(voltage_whole);
            lcd_data('.');
            lcdOutput(voltage_fraction);
            lcd_data('V');
            break;

        case 0x70: // RB7 Pressed - Reset to 17.6V and display "BATTERY MEDIUM"
            voltage_whole = 17;
            voltage_fraction = 6;
            display();
            lcd_command(0x8A);
            lcdOutput(17);
            lcd_data('.');
            lcdOutput(6);
            lcd_data('V');
            lcd_command(0xC0);
            medium();
            break;
    }
}

void low(void) {
    lcd_command(0xC0);
    unsigned char status_low[15] = {"BATTERY LOW"    };
    for (int l = 0; l < 15; l++) {
        lcd_data(status_low[l]);
        __delay_ms(5);
    }
}

void medium(void) {
    lcd_command(0xC0);
    unsigned char status_med[15] = {"BATTERY MEDIUM "};
    for (int m = 0; m < 15; m++) {
        lcd_data(status_med[m]);
        __delay_ms(5);
    }
}

void high(void) {
    lcd_command(0xC0);
    unsigned char status_high[15] = {"BATTERY HIGH  "};
    for (int h = 0; h < 15; h++) {
        lcd_data(status_high[h]);
        __delay_ms(5);
    }
}

void display(void) {
    lcd_command(0x80);
    unsigned char display_text[11] = {"BATT VOLT:"};
    for (int x = 0; x < 11; x++) {
        lcd_data(display_text[x]);
    }
}

void lcdOutput(unsigned int i) {
    if (i == 0) {  // Special case for 0
        lcd_data('0');
        return;
    }
    
    unsigned char temp[6];
    int idx = 0;
    while (i != 0) {
        temp[idx++] = (i % 10) + '0';  // Convert each digit to ASCII
        i /= 10;
    }

    for (int f = idx - 1; f >= 0; f--) {
        lcd_data(temp[f]); // Display digits in correct order
    }
}

void lcd_command(unsigned char i) {
    PORTC &= ~0x08; // RS = 0 (Command mode)
    PORTD = i; // Send command
    PORTC |= 0x01; // Enable pulse
    PORTC &= ~0x01; // Disable pulse
    delay();
}

void lcd_data(unsigned char i) {
    PORTC |= 0x08; // RS = 1 (Data mode)
    PORTD = i; // Send data
    PORTC |= 0x01; // Enable pulse
    delay();
    PORTC &= ~0x01; // Disable pulse
}

void delay(void) {
    unsigned long d;
    for (d = 0; d <= 1000; d++);
}