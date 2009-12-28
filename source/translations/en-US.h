//***************************************/
//
//	This is most of the text used in the Bus Pirate interface.  
// 	en-US is the default development translation. 
//	Other translations include contact information for the translator.
//
//****************************************/
//these terms become part of the terminal text messaging system 
//one copy can be accessed from anywhere in the code, this saves a bunch of space
#define MSG_READY_T			"READY\x0D\x0A"

#define MSG_READ_T 			"READ: "
#define MSG_READBULK_T		"READ "
#define MSG_READBULK_BYTES_T " BYTES:\x0D\x0A"
#define MSG_WRITE_T 		"WRITE: "
#define MSG_WRITEBULK_T 	" TIMES"
#define MSG_ACK_T			"ACK"
#define MSG_NACK_T			"NACK"
#define MSG_I2C_START_T		"I2C START BIT\x0D\x0A"
#define MSG_I2C_STOP_T		"I2C STOP BIT\x0D\x0A"
#define MSG_CS_ENABLED_T 	"CS ENABLED\x0D\x0A"
#define MSG_CS_DISABLED_T	"CS DISABLED\x0D\x0A"
#define MSG_ADAPTER_T		"This mode requires an adapter\x0D\x0A"

#define MSG_BIT_READ_T 		"READ BIT: "
#define MSG_BIT_PEEK_T 		"DATA INPUT, STATE: "
#define MSG_BIT_NOWINPUT_T	" *pin is now HiZ\x0D\x0A"
#define MSG_BIT_CLK_T  		" CLOCK TICKS\x0D\x0A"
#define MSG_BIT_CLKH_T 		"CLOCK, 1\x0D\x0A"
#define MSG_BIT_CLKL_T 		"CLOCK, 0\x0D\x0A"
#define MSG_BIT_DATH_T 		"DATA OUTPUT, 1\x0D\x0A"
#define MSG_BIT_DATL_T 		"DATA OUTPUT, 0\x0D\x0A"

#define MSG_VREG_ON_T		"POWER SUPPLIES ON\x0D\x0A"
#define MSG_VREG_OFF_T		"POWER SUPPLIES OFF\x0D\x0A"

#define MSG_ERROR_MACRO_T 	"Unknown macro, try ? or (0) for help\x0D\x0A"
#define MSG_ERROR_MODE_T 	"Command not used in this mode\x0D\x0A"
#define MSG_ERROR_SYNTAX_T 	"* Syntax error, type ? for help\x0D\x0A"
#define MSG_ERROR_BUFFER_T	"* TERMINAL BUFFER OVERFLOW, TRY SMALLER SEGMENTS\x0D\x0A"
#define MSG_ERROR_NOMODE_T	"No mode set, M for mode\x0D\x0A"
#define MSG_ERROR_NOTHIZPIN_T "WARNING: pins not open drain (HiZ)\x0D\x0A"

#define MSP_OPT_INVALID_T 		"Error, try again >"
#define MSG_OPT_OUTPUT_TYPE_T	"Select output type:\x0D\x0A 1. Open drain (H=Hi-Z, L=GND)\x0D\x0A 2. Normal (H=3.3V, L=GND)\x0D\x0A"
#define MSG_OPT_MODESET_T		"Mode selected\x0D\x0A"
#define MSG_OPT_DISPLAYMODE_T 	" 1. HEX\x0D\x0A 2. DEC\x0D\x0A 3. BIN\x0D\x0A 4. RAW\x0D\x0A"
#define MSG_OPT_DISPLAYMODESET_T "Display format set\x0D\x0A"
#define MSG_OPT_PULLUP_T		" 1. Pull-ups off\x0D\x0A 2. Pull-ups on\x0D\x0A"
#define MSG_OPT_PULLUP_OFF_T 	"Pull-up resistors OFF\x0D\x0A"
#define MSG_OPT_PULLUP_ON_T 	"Pull-up resistors ON\x0D\x0A"
#define MSG_OPT_VMONITOR_T		"Voltage monitors: "
#define MSG_OPT_BITORDER_T 		" 1. MSB first\x0D\x0A 2. LSB first\x0D\x0A"
#define MSG_OPT_BITORDER_MSB_T	"MSB set: MOST sig bit first\x0D\x0A"
#define MSG_OPT_BITORDER_LSB_T	"LSB set: LEAST sig bit first\x0D\x0A"
#define MSG_OPT_AUXPIN_T		"AUX commands control\x0D\x0A 1. AUX (default)\x0D\x0A 2. CS/TMS\x0D\x0A"
#define MSG_OPT_AUXPIN_AUX_T 	"a/A/@ controls AUX pin\x0D\x0A"
#define MSG_OPT_AUXPIN_CS_T 	"a/A/@ controls CS/TMS pin\x0D\x0A"
#define MSG_OPT_TERMBAUD_ADJUST_T	"Adjust your terminal and press space to continue\x0D\x0A"
#define MSG_OPT_UART_BAUD_T 	"Set serial port speed: (bps)\x0D\x0A 1. 300\x0D\x0A 2. 1200\x0D\x0A 3. 2400\x0D\x0A 4. 4800\x0D\x0A 5. 9600\x0D\x0A 6. 19200\x0D\x0A 7. 38400\x0D\x0A 8. 57600\x0D\x0A 9. 115200\x0D\x0A"
#define MSG_OPT_CKP_T 			"Clock polarity:\x0D\x0A 1. Idle low *default\x0D\x0A 2. Idle high\x0D\x0A" //use these with BB library too
#define MSG_OPT_CKE_T 			"Output clock edge:\x0D\x0A 1. Idle to active\x0D\x0A 2. Active to idle *default\x0D\x0A"
#define MSG_OPT_SMP_T 			"Input sample phase:\x0D\x0A 1. Middle *default\x0D\x0A 2. End\x0D\x0A"
#define MSG_OPT_BB_SPEED_T 		"Set speed:\x0D\x0A 1. Slow(~5KHz)\x0D\x0A 2. Fast(~50KHz)\x0D\x0A"

#define MSG_STATUS_OUTPUT_HIZ_T 	"Open drain outputs (H=Hi-Z, L=GND)\x0D\x0A"
#define MSG_STATUS_OUTPUT_NORMAL_T 	"Normal outputs (H=V+, L=GND)\x0D\x0A"
#define MSG_STATUS_PULLUP_NOTALLOWED_T 	"Pull-up resistors not allowed\x0D\x0A"
#define MSG_STATUS_BITORDER_NOTALLOWED_T "Bitorder configuration not allowed\x0D\x0A"

/************************
*
*
*	One use messages
*	These are only used once, usually through a bpWstring, 
*   and not by registration in the terminal message system above
*
*
*************************/
// 1-Wire //
#define OUMSG_1W_BIT_BULKWRITE " WRITE BIT(S) ("
#define OUMSG_1W_BIT_WRITE		"WRITE BIT: "
#define OUMSG_1W_BIT_WRITE_NOTE		" *next clock (^) will also have this value"
#define OUMSG_1W_MACRO_MENU		" 0.Macro menu"
#define OUMSG_1W_MACRO_MENU_ROM			"1WIRE ROM COMMAND MACROs:\x0D\x0A 51.READ ROM (0x33) *for single device bus\x0D\x0A 85.MATCH ROM (0x55) *followed by 64bit address\x0D\x0A 204.SKIP ROM (0xCC) *followed by command\x0D\x0A 236.ALARM SEARCH (0xEC)\x0D\x0A 240.SEARCH ROM (0xF0)"
#define OUMSG_1W_MACRO_ADDRESS	"ADDRESS MACRO " //(#): 0 0 0 0 0 0 0 0
#define OUMSG_1W_MACRO_ADDRESS_NODEVICE "No device, try (ALARM) SEARCH macro first"
#define OUMSG_1W_MACRO_ALARMSEARCH_ROM 	"ALARM SEARCH (0xEC)"
#define OUMSG_1W_MACRO_SEARCH_ROM 		"SEARCH (0xF0)"
#define OUMSG_1W_MACRO_SEARCH_ROM_HEADER "Macro     1WIRE address"
#define OUMSG_1W_MACRO_SEARCH_ROM_NOTE	"Device IDs are available by MACRO, see (0)."
#define OUMSG_1W_MACRO_READ_ROM 	"READ ROM (0x33): "
#define OUMSG_1W_MACRO_MATCH_ROM 	"MATCH ROM (0x55)"
#define OUMSG_1W_MACRO_SKIP_ROM 	"SKIP ROM (0xCC)"
#define OUMSG_1W_RESET			"BUS RESET "
#define OUMSG_1W_RESET_OK		"OK"
#define OUMSG_1W_RESET_ERROR	"ERROR: "
#define OUMSG_1W_RESET_SHORT	"*Short or no pull-up "
#define OUMSG_1W_RESET_NODEV 	"*No device detected "
//AUXpin//
#define OUMSG_AUX_PWM_OFF 		"PWM disabled"
#define OUMSG_AUX_PWM_NOTE 		"1KHz-4,000KHz frequency generator/PWM (beta)"
#define OUMSG_AUX_PWM_FREQ 		"Frequency in KHz "
#define OUMSG_AUX_PWM_PRESCALE 	"Prescale:"
#define OUMSG_AUX_PWM_DUTY 		"Duty cycle in % "
#define OUMSG_AUX_PWM_ON 		"PWM active"
#define OUMSG_AUX_FREQ_PWM 		"PWM active: try G to disable PWM"
#define OUMSG_AUX_FREQCOUNT 	"Frequency on AUX pin: "
#define OUMSG_AUX_HIZ			"AUX INPUT/HI-Z"
#define OUMSG_AUX_HIGH			"AUX HIGH"
#define OUMSG_AUX_LOW			"AUX LOW"
#define OUMSG_AUX_INPUT_READ	"AUX INPUT/HI-Z, READ: "
//HD44780//
#define OUMSG_LCD_WRITE_COMMAND "CMD " //indicates writes to command register
#define OUMSG_LCD_WRITE_DATA 	"DAT " //indicates writes to data register
#define OUMSG_LCD_COMMAND_MODE 	"RS LOW, COMMAND MODE"
#define OUMSG_LCD_DATA_MODE 	"RS HIGH, DATA MODE"
#define OUMSG_LCD_SETUP_ADAPTER "LCD type:\x0D\x0A 1. HD44780 (using PCF8574 IO expander)"
#define OUMSG_LCD_MACRO_MENU 	" 0.Macro menu\x0D\x0A 1.LCD Reset\x0D\x0A 2.Init LCD\x0D\x0A 3.Clear LCD\x0D\x0A 4.Cursor position ex:(4:0)\x0D\x0A 5.(deprecated)\x0D\x0A 6.Write :number test numbers ex:(6:80)\x0D\x0A 7.Write :number test characters ex:(7:80)\x0D\x0A 8.Insert text at cursor"
#define OUMSG_LCD_MACRO_INIT_DISPLAYLINES 	"Display lines:\x0D\x0A 1. 1 \x0D\x0A 2. Multiple"
#define OUMSG_LCD_MACRO_RESET 	"RESET"
#define OUMSG_LCD_MACRO_INIT 	"INIT"
#define OUMSG_LCD_MACRO_CLEAR 	"CLEARED"
#define OUMSG_LCD_MACRO_CURSOR	"CURSOR SET"
#define OUMSG_LCD_MACRO_TEXT 	"Insert text:"
#define OUMSG_LCD_ERROR_ADAPTER "No ACK, check adapter"
// I2C //
#define OUMSG_I2C_READ_PEND 	"*(N)ACK PENDING"
#define OUMSG_I2C_CON 			"I2C mode:\x0D\x0A 1. Software\x0D\x0A 2. Hardware"
#define OUMSG_I2C_REV3_WARN 	"WARNING: HARDWARE I2C is broken on this PIC! (REV A3)"
#define OUMSG_I2C_HWSPEED 		"Set speed:\x0D\x0A 1. 100KHz\x0D\x0A 2. 400KHz\x0D\x0A 3. 1MHz"
#define OUMSG_I2C_MACRO_MENU 	" 0.Macro menu\x0D\x0A 1.7bit address search\x0D\x0A 2.I2C sniffer"
#define OUMSG_I2C_MACRO_SEARCH 	"Searching 7bit I2C address space. \x0D\x0A   Found devices at:"
#define OUMSG_I2C_MACRO_SNIFFER	"I2C bus sniffer, press any key to exit"
//menu//
//jtag// // Yuck, I don't want to deal with this one...
//midi//
#define OUMSG_MIDI_READ_FAIL 		"FAILED, NO DATA"
#define OUMSG_MIDI_LIVE_DISPLAY_ON 	"UART LIVE DISPLAY, } TO STOP"
#define OUMSG_MIDI_LIVE_DISPLAY_OFF "LIVE DISPLAY STOPPED"
//pckeyboard//
#define OUMSG_KB_TIMEOUT 		" BIT TIMEOUT"
#define OUMSG_KB_MACRO_MENU 	" 0. Macro menu\x0D\x0A 1. Live input monitor"
#define OUMSG_KB__MACRO_LIVE 	"Input monitor, any key exits"
#define OUMSG_KB_ERROR_STARTBIT " *startbit error"
#define OUMSG_KB_ERROR_PARITY 	" *parity error"
#define OUMSG_KB_ERROR_STOPBIT 	" *stopbit error"
#define OUMSG_KB_ERROR_TIMEOUT 	" BIT TIMEOUT"
#define OUMSG_KB_ERROR_NONE 	" NONE"
#define OUMSG_KB_ERROR_UNK 		" UNKNOWN ERROR"
//procMenu//
#define OUMSG_PM_1A_P_DEPRECATED "Supply config deprecated, toggle with W/w"
#define OUMSG_PM_RESET 			"RESET"
#define OUMSG_PM_SELFTEST_HIZ	"Self-test in HiZ mode only."
#define OUMSG_PM_CONVERT		"CONVERT "
//procSyntax//
#define OUMSG_PS_DELAY			"DELAY "
#define OUMSG_PS_DELAY_US		"uS"
#define OUMSG_PS_ADC_VOLT_PROBE	"VOLTAGE PROBE: "
#define OUMSG_PS_ADC_VOLTS		"V"
//RAW2WIRE//
#define OUMSG_R2W_MACRO_MENU	" 0.Macro menu\x0D\x0A 1.ISO7816-3 ATR\x0D\x0A 2.ISO7816-3 parse only\x0D\x0A"
//RAW3WIRE//
//selftest// //just leave in english for now...
// SPI //
#define OUMSG_SPI_SPEED 		"Set speed:\x0D\x0A 1. 30KHz\x0D\x0A 2. 125KHz\x0D\x0A 3. 250KHz\x0D\x0A 4. 1MHz"
#define OUMSG_SPI_MACRO_MENU	" 0.Macro menu\x0D\x0A 1.SPI bus sniffer"
#define OUMSG_SPI_SNIFF_MENU	"Sniff when:\x0D\x0A 1. CS low\x0D\x0A 2. CS high\x0D\x0A 3. All traffic"
#define OUMSG_SPI_SNIFF_BEGIN	"SPI bus sniffer, any key exists"
#define OUMSG_SPI_SNIFF_BUFFER	"BUFFER OVERFLOW!\x0D\x0A Bus too fast, try raw display mode"
//UART //
#define OUMSG_UART_MACRO_MENU 	" 0.Macro menu\x0D\x0A 1.Transparent UART bridge\x0D\x0A 2. Live UART monitor\x0D\x0A 3.UART bridge with flow control"
#define OUMSG_UART_READ_FAIL 		"FAILED, NO DATA"
#define OUMSG_UART_LIVE_DISPLAY_ON 	"UART LIVE DISPLAY, } TO STOP"
#define OUMSG_UART_LIVE_DISPLAY_OFF "LIVE DISPLAY STOPPED"
#define OUMSG_UART_DATABITS_PARITY "Data bits and parity:\x0D\x0A 1. 8, NONE *default \x0D\x0A 2. 8, EVEN \x0D\x0A 3. 8, ODD \x0D\x0A 4. 9, NONE"
#define OUMSG_UART_STOPBITS		 	"Stop bits:\x0D\x0A 1. 1 *default\x0D\x0A 2. 2"
#define OUMSG_UART_RXPOLARITY		"Receive polarity:\x0D\x0A 1. Idle 1 *default\x0D\x0A 2. Idle 0"
/************************
*
*
*	HELP TEXT
*
*
*************************/
#define HELP_TITLE_MENUS_T			"MENUS"
#define HELP_MENUS_HELP_T 			"? Help"
#define HELP_MENUS_VERSION_T		"I Status info"
#define HELP_MENUS_BUSMODE_T		"M Bus mode"
#define HELP_MENUS_TERMBAUD_T		"B Terminal speed"
#define HELP_MENUS_DISPLAYMODE_T	"O Data display format"
#define HELP_MENUS_VMONITOR_T		"V Check supply voltages"
#define HELP_MENUS_FREQCOUNT_T		"F Frequency count on AUX"
#define HELP_MENUS_FREQGEN_T		"G Frequency generator/PWM on AUX"
#define HELP_MENUS_AUXPIN_T			"C AUX pin assignment"
#define HELP_MENUS_BITORDER_T		"L Bit order"
#define HELP_MENUS_PULLUPV0A_T		"P SDA/SCL pullup resistors"
#define HELP_MENUS_PULLUPV2_T		"P Pullup resistors"
#define HELP_MENUS_VREG_T			"P Deprecated, use W/w"
#define HELP_MENUS_HDBCONVERT_T		"= HEX/DEC/BIN converter"
#define HELP_MENUS_SELFTEST_T		"~ Self test"
#define HELP_MENUS_RESET_T			"# Reset"

#define HELP_TITLE_SYNTAX_T			"SYNTAX"
#define HELP_SYNTAX_AUXPIN_T		"A/a/@ AUX output toggle H/L/read"
#define HELP_SYNTAX_VREG_T			"W/w Power supply toggle on/off"
#define HELP_SYNTAX_VPROBE_T		"D Measure voltage on ADC probe"
#define HELP_SYNTAX_START_T			"[ ({) Start (with read)"
#define HELP_SYNTAX_STOP_T			"] or } Stop"
#define HELP_SYNTAX_READ_T			"R or r Read byte"
#define HELP_SYNTAX_WRITEBIN_T		"0b Write BIN byte"
#define HELP_SYNTAX_WRITEHEX_T		"0h or 0x Write HEX byte"
#define HELP_SYNTAX_WRTIEDEC_T		"0-255 Write DEC byte"
#define HELP_SYNTAX_DELIMIT_T		", Delimiter (also space)"
#define HELP_SYNTAX_DELAY_T			"& 1uS delay"
#define HELP_SYNTAX_REPEAT_T		": Repeat (r:2, 0x0a:4, &:20, ^:2, etc.)" 
#define HELP_SYNTAX_MACRO_T			"(#) Run macro, (0) for macro list"

#define HELP_SYNTAX_BITWISETITLE_T	"RAW BUS OPERATIONS"
#define HELP_SYNTAX_BITCLKHL_T		"/\\ Clock H/L"
#define HELP_SYNTAX_BITDATHL_T		"-/_ Data H/L"
#define HELP_SYNTAX_BITPEEK_T		". Read data input pin state"
#define HELP_SYNTAX_BITCLK_T		"^ Clock tick"
#define HELP_SYNTAX_BITREAD_T		"! Read bit"

//Please leave one blank line after this comment. If you don't, the compiler gets mad.

