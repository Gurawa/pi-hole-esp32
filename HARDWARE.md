# Hardware Setup and Wiring Guide

This document provides wiring diagrams and hardware setup instructions for various ESP32 configurations with the Pi-hole client.

## Basic Setup (No Display)

For the basic Pi-hole statistics client, you only need:

- **ESP32 Development Board**
- **USB Cable** (for power and programming)

No additional wiring is required. The ESP32 will connect to your Pi-hole via WiFi and output statistics to the Serial Monitor.

## OLED Display Setup (SSD1306)

### Components Needed
- ESP32 board
- SSD1306 OLED Display (128x64, I2C)
- 4 jumper wires

### Wiring Diagram

```
ESP32              SSD1306 OLED
----------------   ----------------
3.3V        -----> VCC
GND         -----> GND
GPIO 21     -----> SDA (Data)
GPIO 22     -----> SCL (Clock)
```

### Pin Configuration

| ESP32 Pin | OLED Pin | Function |
|-----------|----------|----------|
| 3.3V      | VCC      | Power    |
| GND       | GND      | Ground   |
| GPIO 21   | SDA      | I2C Data |
| GPIO 22   | SCL      | I2C Clock|

**Note:** Some OLED displays can work with 5V, but 3.3V is safer for ESP32. Check your display specifications.

### I2C Address

Most SSD1306 displays use I2C address `0x3C`. Some use `0x3D`. If the display doesn't work, try changing the address in the code:

```cpp
#define SCREEN_ADDRESS 0x3C  // or 0x3D
```

### Alternative I2C Pins

If you need to use different pins for I2C, you can customize them:

```cpp
Wire.begin(SDA_PIN, SCL_PIN);  // For example: Wire.begin(19, 23);
```

## TFT Display Setup (Coming Soon)

### Components Needed
- ESP32 board
- ST7735 or ILI9341 TFT Display
- Jumper wires

Wiring guide coming soon!

## LED Indicator Setup

### Components Needed
- ESP32 board
- LED (any color)
- 220Ω resistor
- Jumper wires

### Simple Status LED

```
ESP32              LED Circuit
----------------   ----------------
GPIO 2      -----> LED Anode (+)
                   LED Cathode (-) -> 220Ω Resistor -> GND
```

Use the LED to indicate:
- WiFi connection status
- Pi-hole enabled/disabled status
- High ad-blocking activity

## Button Control Setup

### Components Needed
- ESP32 board
- Push button
- 10kΩ pull-down resistor (optional, ESP32 has internal pull-ups)
- Jumper wires

### Basic Button Wiring

```
ESP32              Button
----------------   ----------------
GPIO 0      -----> Button Pin 1
3.3V        -----> Button Pin 2
```

Configure the button with internal pull-up:
```cpp
pinMode(0, INPUT_PULLUP);
```

Use the button to:
- Toggle Pi-hole enabled/disabled
- Change display screens
- Force statistics update

## Multiple Sensor Setup

You can add environmental sensors to create a comprehensive Pi-hole monitoring station:

### DHT22 Temperature/Humidity Sensor
- VCC -> 3.3V
- GND -> GND  
- Data -> GPIO 4

### BME280 Environmental Sensor (I2C)
- VCC -> 3.3V
- GND -> GND
- SDA -> GPIO 21 (shared with OLED)
- SCL -> GPIO 22 (shared with OLED)

## Power Considerations

### USB Power
- Standard USB provides 5V at up to 500mA
- Sufficient for ESP32 + OLED display
- Use a quality USB cable and power adapter

### Battery Power
For portable setups:
- Use a LiPo battery with protection circuit
- Add TP4056 charging module
- Typical 3.7V 2000mAh battery gives ~6-8 hours runtime

### External Power Supply
- Use a regulated 5V power supply
- Connect to 5V and GND pins
- Ensure adequate current rating (≥1A recommended)

## Enclosure Ideas

### 3D Printed Case
- Design files coming soon
- Accommodates ESP32 + OLED display
- Mounting holes for wall installation

### Off-the-shelf Options
- Hammond 1551 series small plastic boxes
- Adafruit Maker-sized project boxes
- Custom laser-cut acrylic cases

## Troubleshooting Hardware Issues

### Display Not Working
1. Check all connections are secure
2. Verify I2C address (try 0x3C and 0x3D)
3. Test with I2C scanner sketch
4. Ensure display is getting proper voltage (3.3V or 5V)

### ESP32 Won't Program
1. Try holding BOOT button while uploading
2. Check USB cable (must be data cable, not charge-only)
3. Install/update USB-to-serial drivers (CP2102 or CH340)
4. Try different USB port

### WiFi Connection Issues
1. Ensure you're using 2.4GHz network (ESP32 doesn't support 5GHz)
2. Check antenna is not obstructed (don't put in metal case without antenna extension)
3. Move closer to WiFi router
4. Check for proper grounding

### Power Issues
1. Use quality USB cable and power supply
2. Some displays draw significant current when fully lit
3. Ensure adequate power rating (≥500mA)
4. Check for loose connections

## Safety Notes

⚠️ **Important Safety Information:**

- Always disconnect power before making wiring changes
- Use appropriate resistors with LEDs to prevent burnout
- Don't exceed 3.3V on GPIO pins
- Ensure proper polarity when connecting components
- Use ESD protection when handling ESP32
- Don't short circuit power pins

## Additional Resources

- [ESP32 Pinout Reference](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)
- [I2C Scanner Sketch](https://playground.arduino.cc/Main/I2cScanner/)
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)

## Contributing

Have a cool hardware setup? Share it with the community by:
1. Taking clear photos of your setup
2. Documenting the wiring
3. Submitting a pull request with your configuration

We'd love to see your creative implementations!
