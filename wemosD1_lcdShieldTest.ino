// LCD Shield with buttons on WeMos D1 WiFi

#include <LiquidCrystal.h>

// WeMos D1 GPIO to Arduino Uno GPIO map
// Not sure about the doubles - this is as shown on the silkscreen...
const int D1_GPIOMAP[14] =
{
     3, 1,16, 5,
     4,14,12,13,
     0, 2,15,13,
    12,14
};

typedef enum
{
    BTN_NONE = 0,
    BTN_LEFT,
    BTN_DOWN,
    BTN_UP,
    BTN_RIGHT,
    BTN_SELECT
} teButtons;

const int LCD_D4 = D1_GPIOMAP[4];
const int LCD_D5 = D1_GPIOMAP[5];
const int LCD_D6 = D1_GPIOMAP[6];
const int LCD_D7 = D1_GPIOMAP[7];
const int LCD_RS = D1_GPIOMAP[8];
const int LCD_EN = D1_GPIOMAP[9];
const int LCD_BL = D1_GPIOMAP[10];
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() 
{
    Serial.begin(115200);
    Serial.println("LCD Shield test");

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LCD_BL, OUTPUT);
    digitalWrite(LCD_BL, HIGH); // HIGH for on
    digitalWrite(LED_BUILTIN, LOW);
    
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.print("LCD shield test");
}

teButtons GetButton()
{
    int raw = analogRead(A0);
    Serial.print("Buttons raw: ");
    Serial.println(raw);
    
    if (raw > 900)  return BTN_NONE;  // Typ 1024
    if (raw > 700)  return BTN_SELECT;// ???
    if (raw > 500)  return BTN_LEFT;  // Typ 678
    if (raw > 300)  return BTN_DOWN;  // Typ 429
    if (raw > 100)  return BTN_UP;    // Typ 173
    return BTN_RIGHT; // Typ 6
}

void loop() 
{
    lcd.setCursor(0,1);
    switch (GetButton())
    {
    case BTN_NONE:  lcd.print("NONE  ");  break;
    case BTN_LEFT:  lcd.print("LEFT  ");  break;
    case BTN_UP:    lcd.print("UP    ");  break;
    case BTN_DOWN:  lcd.print("DOWN  ");  break;
    case BTN_RIGHT: lcd.print("RIGHT ");  break;
    case BTN_SELECT:lcd.print("SELECT");  break;
    default:        lcd.print("??????");  break;
    }
    
    delay(500);
}
