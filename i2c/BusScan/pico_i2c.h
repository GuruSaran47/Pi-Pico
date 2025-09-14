#define I2C_PORT i2c1
#define I2C_BUS1_SDA_PIN 0x02u
#define I2C_BUS1_SCL_PIN 0x03u
#define BUS_FREQUENCY_400KHZ 400000
#define I2C_BUS1_FREQ BUS_FREQUENCY_400KHZ


/* 
The pstructure has the following values:
1. structure to the port
2. SDA Pin Number
3. SCL Pin Number
4. Frequency of the Bus
*/
typedef struct{
    i2c_inst_t *st_i2c_port;
    uint8_t st_u8_SDA_Pin;
    uint8_t st_u8_SCL_Pin;
    uint32_t st_u32_Frequency;
}st_i2c_bus_characteristics;


/* Extern Variables to other functions are here */
extern void pico_i2c_init(i2c_inst_t *ast_i2c_port, uint8_t au8_SDA_Pin, uint8_t au8_SCL_Pin, uint32_t au32_Frequency);
extern void pico_print_bus_parameters(void);
extern void pico_i2c_scan_bus(void);
/* Local Static Functions that have to be defined here */
static void pico_i2c_populate_bus_parameters(i2c_inst_t *ast_i2c_port, uint8_t *au8_SDA_Pin, uint8_t *au8_SCL_Pin, uint32_t *au32_Frequency);
