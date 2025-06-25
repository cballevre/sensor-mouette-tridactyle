# sensor-mouette-tridactyle

## Sensors

- Wind : Wind Speed Sensor Voltage Type 0-5V SKU SEN0170 ([docs](https://wiki.dfrobot.com/Wind_Speed_Sensor_Voltage_Type_0-5V__SKU_SEN0170))
- Temperature and humidity : DHT22 ([docs](https://wiki.seeedstudio.com/Grove-Temperature_and_Humidity_Sensor_Pro/))
- Luminosity : I2C Waterproof Ambient Light Sensor 1-65535lx ([docs](https://wiki.dfrobot.com/SKU_SEN0562_Gravity_I2C_Waterproof_Ambient_Light_Sensor_1_65535lx))
- Temperature : Fermion: MCP9808 High Accuracy I2C Temperature Sensor ([docs](https://wiki.dfrobot.com/Fermion_MCP9808_High_Accuracy_I2C_Temperature_Sensor_SKU_SEN0435))

## Schema

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

## Libraries needed

- https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor
- https://github.com/DFRobot/DFRobot_MCP9808
