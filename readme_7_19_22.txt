PINS:

GPS: TX - 19, RX - 18 (I know the MEGA is labeled with them being reversed, idk why it's like this but this is the only way it works...)

SPI: SCK - 52, MISO - 50, MOSI - 51, THERMO_CS - 13, THERMO_CS2 - 12, SD_CS - 53


FILES:

"one_thermocouple" and "two_thermocouples" are the code for the thermocouples, and both work fine.

"gps_tutorial" is the code for only the gps module, and it works fine as long as you're outside.

"sd_card_foolery" is the code for only the sd card stuff. It works perfectly with the old sd card module, but it doesn't get past initialization with the sd card chip on the new pcb.
Not sure why, any suggestions would be greatly appreciated.