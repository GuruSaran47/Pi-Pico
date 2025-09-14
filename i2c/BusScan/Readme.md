# This file defines how the entire process of scanning the i2c bus

### How did we do this?

- We are doing this using the existing pico/sdk for c/c++, According to the protocol first we need to add pull-up the i2c lines. Both SDA and SCK lines using a 4.7k ohm resistors.
- Now the steps for scanning the bus is simple.
-  1. The i2c uses a 7-bit addressing scheme, for a 7Bit Address number we have a search range of (0x00 to 0x7F)
   2. This makes the operation more simpler, we need to use the SDK to read a Byte from the range of all teh Addresses that are reachable.
   3. According to the protocol, there are normal addresses and reserved addresses. So accordingly the device you'd have connected to the bus would have the register between 0x08 to 0x77 where 0x00 to 0x07 and 0x77 to 0x7F are reserved
   4. Now using a method within the i2c_read_blocking() or even writing like i2c_write_blocking(): According to the Pico SDK these functions are designed to return the result based on weather the function has successfully returned or not.
   5. If we have any neagative response means that the device address we are looking for doesn't exist.
