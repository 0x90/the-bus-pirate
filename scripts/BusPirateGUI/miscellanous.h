/* Miscellanous */
enum bbio_pins
{
	BB_POWER = 0x08,
	BB_PULLUPS = 0x04,
	BB_AUX = 0x02,
	BB_CS = 0x01
};

enum bbio_io_pins
{
	BBIO_MOSI = 0x01,
	BBIO_CLK = 0x02,
	BBIO_MISO = 0x04,
	BBIO_CS = 0x08,
	BBIO_AUX = 0x10,
	BBIO_PULLUP = 0x20,
	BBIO_POWER = 0x40
};

enum spi_cfg
{
	SPI_OUT_TYPE = 0x08,
	SPI_IDLE = 0x04,
	SPI_CLK_EDGE = 0x02,
	SPI_SAMPLE = 0x01
};
