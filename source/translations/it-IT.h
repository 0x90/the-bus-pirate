//***************************************/
//
// Italian translation by Pastus AKA Alessandro
//for contact of information about this translation pastus@gmail.com
//
//****************************************/
//these terms become part of the terminal text messaging system 
//one copy can be accessed from anywhere in the code, this saves a bunch of space
#ifdef LANGUAGE_IT_IT

#define MSG_READY_T		"PRONTO\x0D\x0A"

#define MSG_READ_T 		"LETTURA: "
#define MSG_READBULK_T		"LETTURA "
#define MSG_READBULK_BYTES_T 	" BYTES:\x0D\x0A"
#define MSG_WRITE_T 		"SCRITTURA: "
#define MSG_WRITEBULK_T 	" VOLTE"
#define MSG_ACK_T			"ACK"
#define MSG_NACK_T			"NACK"
#define MSG_I2C_START_T		"BIT DI START I2C\x0D\x0A"
#define MSG_I2C_STOP_T		"BIT DI STOP I2C\x0D\x0A"
#define MSG_CS_ENABLED_T 	"CS ABILITATO\x0D\x0A"
#define MSG_CS_DISABLED_T	"CS DISABILITATO\x0D\x0A"
#define MSG_ADAPTER_T		"Questa modalità necessita di un adattatore\x0D\x0A"
#define MSG_BIT_READ_T 		"BIT LETTO: "
#define MSG_BIT_PEEK_T 		"DATO IN INGRESSO, STATO: "
#define MSG_BIT_NOWINPUT_T	" *Adesso il pin è in Hi-Z\x0D\x0A"
#define MSG_BIT_CLK_T  		" CLOCK TICKS\x0D\x0A"
#define MSG_BIT_CLKH_T 		"CLOCK, 1\x0D\x0A"
#define MSG_BIT_CLKL_T 		"CLOCK, 0\x0D\x0A"
#define MSG_BIT_DATH_T 		"DATO IN USCITA, 1\x0D\x0A"
#define MSG_BIT_DATL_T 		"DATO IN USCITA, 0\x0D\x0A"

#define MSG_VREG_ON_T		"ALIMENTAZIONE ATTIVATA\x0D\x0A"
#define MSG_VREG_OFF_T		"ALIMENTAZIONE DISATTIVATA\x0D\x0A"

#define MSG_ERROR_MACRO_T 	"MACRO SCONOSCIUTA, PROVARE CON ? O (0) PER AIUTO\x0D\x0A"
#define MSG_ERROR_MODE_T 	"Comando non presente per questa modalità\x0D\x0A"
#define MSG_ERROR_SYNTAX_T 	"* Errore di sintassi, digitare ? per l'aiuto \x0D\x0A"
#define MSG_ERROR_BUFFER_T	"* OWERFLOW DEL BUFFER DEL TERMINALE, RIPROVARE CON SEGMENTI DATI PIU' CORTI\x0D\x0A"
#define MSG_ERROR_NOMODE_T	"Nessuna modalità attivata, digitare M per l'elenco modalità\x0D\x0A"
#define MSG_ERROR_NOTHIZPIN_T 	"ATTENZIONE, pins non in open drain (HiZ)\x0D\x0A"
#define MSP_OPT_INVALID_T 	"Errore, riprovare>"
#define MSG_OPT_OUTPUT_TYPE_T	"Scegliere tipo di uscita:\x0D\x0A 1. open drain (H=Hi-z L=massa)\x0D\x0A 2. Uscita normale (H=3.3V, L=massa)\x0D\x0A"
#define MSG_OPT_MODESET_T	"Modalità selezionata\x0D\x0A"
#define MSG_OPT_DISPLAYMODE_T 	" 1. HEX\x0D\x0A 2. DEC\x0D\x0A 3. BIN\x0D\x0A 4. RAW\x0D\x0A"
#define MSG_OPT_DISPLAYMODESET_T "Formato di visualizzazione attivato\x0D\x0A"
#define MSG_OPT_PULLUP_T	" 1. Pull-ups attivo\x0D\x0A 2. Pull-ups disattivo\x0D\x0A"
#define MSG_OPT_PULLUP_OFF_T 	"Resistenze di pull-up DISATTIVATE\x0D\x0A"
#define MSG_OPT_PULLUP_ON_T 	"Resistenze di pull-up ATTIVE\x0D\x0A"
#define MSG_OPT_VMONITOR_T	"Monitor di tensione: "
#define MSG_OPT_BITORDER_T	" 1. prima MSB \x0D\x0A 2. prima LSB \x0D\x0A"
#define MSG_OPT_BITORDER_MSB_T	"MSB attivo: prima bit PIU' SIGNIFICATIVO\x0D\x0A"
#define MSG_OPT_BITORDER_LSB_T	"LSB attivo: prima bit MENO SIGNIFICATIVO\x0D\x0A"
#define MSG_OPT_AUXPIN_T	"Scegliere funzione pin aux\x0D\x0A 1. AUX (default)\x0D\x0A 2. CS/TMS\x0D\x0A"
#define MSG_OPT_AUXPIN_AUX_T 	"a/A/@ gestione pin AUX\x0D\x0A"
#define MSG_OPT_AUXPIN_CS_T 	"a/A/@ gestione pin CS/TMS\x0D\x0A"
#define MSG_OPT_TERMBAUD_ADJUST_T	"Configurare il programma terminale e premere spazio per continuare\x0D\x0A"
#define MSG_OPT_UART_BAUD_T 	"Selezionare velocità porta seriale(bps)\x0D\x0A 1. 300\x0D\x0A 2. 1200\x0D\x0A 3. 2400\x0D\x0A 4. 4800\x0D\x0A 5. 9600\x0D\x0A 6. 19200\x0D\x0A 7. 38400\x0D\x0A 8. 57600\x0D\x0A 9. 115200\x0D\x0A"
#define MSG_OPT_CKP_T 		"Polarità del Clock:\x0D\x0A 1. Inattivo basso *default\x0D\x0A 2. Inattivo alto\x0D\x0A"  //use these with BB library too
#define MSG_OPT_CKE_T 		"Fronte del clock di uscita:\x0D\x0A 1. Fronte di salita\x0D\x0A 2.Fronte di discesa *default\x0D\x0A"
#define MSG_OPT_SMP_T 		"Punto di campionamento ingresso:\x0D\x0A 1. Metà bit *default\x0D\x0A 2. Fine bit\x0D\x0A"
#define MSG_OPT_BB_SPEED_T 	"Selezionare velocità:\x0D\x0A 1. ~50KHz\x0D\x0A 2. ~100KHz\x0D\x0A 3. ~400KHz\x0D\x0A"
#define MSG_OPT_UART_DBP_T 	"Bit di dati e parità:\x0D\x0A 1. 8, NESSUNA *default \x0D\x0A 2. 8, PARI \x0D\x0A 3. 8, DISPARI \x0D\x0A 4. 9, NESSUNA \x0D\x0A"
#define MSG_OPT_UART_STOPBITS_T "Bits di stop:\x0D\x0A 1. 1 *default\x0D\x0A 2. 2 \x0D\x0A"
#define MSG_OPT_UART_RXP_T 	"Polarità di ricezione:\x0D\x0A 1. Inattivo a 1 *default\x0D\x0A 2. Inattivo a 0\x0D\x0A"
#define MSG_OPT_SPI_SPEED_T	"Selezionare velocità:\x0D\x0A 1. 30KHz\x0D\x0A 2. 125KHz\x0D\x0A 3. 250KHz\x0D\x0A 4. 1MHz\x0D\x0A"

#define MSG_STATUS_OUTPUT_HIZ_T 	"Uscite open drain (H=ingresso, L=massa)\x0D\x0A"
#define MSG_STATUS_OUTPUT_NORMAL_T 	"Uscita normale (H=V+, L=massa)\x0D\x0A"
#define MSG_STATUS_PULLUP_NOTALLOWED_T 	"Resistenze di pull-ups non attivabili in questa modalità\x0D\x0A"
#define MSG_STATUS_BITORDER_NOTALLOWED_T "Configurazione ordine dei bit non permessa in questa modalità\x0D\x0A"

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
#define OUMSG_1W_BIT_BULKWRITE  " SCRIVI BIT(S) ("
#define OUMSG_1W_BIT_WRITE	"SCRIVI BIT: "
#define OUMSG_1W_BIT_WRITE_NOTE	" *il prossimo clock (^) avrà questo valore"
#define OUMSG_1W_MACRO_MENU	" 0.Menù delle macro"
#define OUMSG_1W_MACRO_MENU_ROM	" 1.WIRE ROM MACRO COMANDI (RIFERITI A PROTOCOLLO 1WIRE):\x0D\x0A 51.READ ROM (0x33) *per bus con singola rom\x0D\x0A 85.MATCH ROM (0x55) *seguito da indirizzo 64bit\x0D\x0A 204.SKIP ROM (0xCC) *seguito da comando\x0D\x0A 236.ALARM SEARCH (0xEC)\x0D\x0A 240.SEARCH ROM (0xF0)"
#define OUMSG_1W_MACRO_ADDRESS	"INDIRIZZO MACRO" //(#): 0 0 0 0 0 0 0 0
#define OUMSG_1W_MACRO_ADDRESS_NODEVICE "Nessun dispositivo trovato, provare prima con macro (ALARM) SEARCH"
#define OUMSG_1W_MACRO_ALARMSEARCH_ROM 	"ALARM SEARCH (0xEC)"
#define OUMSG_1W_MACRO_SEARCH_ROM 	"SEARCH (0xF0)"
#define OUMSG_1W_MACRO_SEARCH_ROM_HEADER "Indirizzo macro     1WIRE"
#define OUMSG_1W_MACRO_SEARCH_ROM_NOTE	"ID trovati visualizzabili digitando (0)"
#define OUMSG_1W_MACRO_READ_ROM 	"READ ROM (0x33): "
#define OUMSG_1W_MACRO_MATCH_ROM 	"MATCH ROM (0x55)"
#define OUMSG_1W_MACRO_SKIP_ROM 	"SKIP ROM (0xCC)"
#define OUMSG_1W_RESET			"BUS RESET "
#define OUMSG_1W_RESET_OK		"OK"
#define OUMSG_1W_RESET_ERROR		"ERRORE: "
#define OUMSG_1W_RESET_SHORT		"*Cortocitcuito o pull-ups non attivi "
#define OUMSG_1W_RESET_NODEV 		"*Nessun dispositivo trovato "
//AUXpin//
#define OUMSG_AUX_PWM_OFF 		"PWM disabilitato"
#define OUMSG_AUX_PWM_NOTE 		"1KHz-4,000KHz frequency generator/PWM (beta)"
#define OUMSG_AUX_PWM_FREQ 		"Frequenza in KHz "
#define OUMSG_AUX_PWM_PRESCALE 		"Prescale:"
#define OUMSG_AUX_PWM_DUTY 		"Duty cycle in % "
#define OUMSG_AUX_PWM_ON 		"PWM attivo"
#define OUMSG_AUX_FREQ_PWM 		"PWM attivo: digitare G per disabilitare PWM"
#define OUMSG_AUX_FREQCOUNT 		"Frequenza letta da pin AUX: "
#define OUMSG_AUX_HIZ			"AUX INPUT/HiZ, LETTURA"
#define OUMSG_AUX_HIGH			"AUX ALTO"
#define OUMSG_AUX_LOW			"AUX BASSO"
#define OUMSG_AUX_INPUT_READ		"AUX Hi-Z, BIT LETTO: "
//HD44780//
#define OUMSG_LCD_WRITE_COMMAND 	"CMD " //indicates writes to command register
#define OUMSG_LCD_WRITE_DATA 		"DATA " //indicates writes to data register
#define OUMSG_LCD_COMMAND_MODE 		"RS BASSO, MODALITA' COMANDO"
#define OUMSG_LCD_DATA_MODE 		"RS ALTO, MODALITA' DATI"
#define OUMSG_LCD_SETUP_ADAPTER 	"Tipo di LCD:\x0D\x0A 1. HD44780 (utilizza PCF8574 I/O expander)"
#define OUMSG_LCD_MACRO_MENU 		" 0.Menù delle Macro \x0D\x0A 1.Reset LCD\x0D\x0A 2.Inizializzazione LCD\x0D\x0A 3.Pulisci LCD\x0D\x0A 4.Posiziona cursore esempio:(4:0)\x0D\x0A 5.(deprecato)\x0D\x0A 6.Test numeri: indicare numero di numeri da utilizzare ex:(6:80)\x0D\x0A 7.Test lettere: indicare numero di caratteri da utilizzare ex:(7:80)\x0D\x0A 8.Inserisci testo dalla posizione corrente"
#define OUMSG_LCD_MACRO_INIT_DISPLAYLINES 	"Linee del display:\x0D\x0A 1. 1 \x0D\x0A 2. Più di 1"
#define OUMSG_LCD_MACRO_RESET 		"RESET"
#define OUMSG_LCD_MACRO_INIT 		"INIZIALIZZATO"
#define OUMSG_LCD_MACRO_CLEAR 		"CLEARED"
#define OUMSG_LCD_MACRO_CURSOR		"CURSORE POSIZIONATO"
#define OUMSG_LCD_MACRO_TEXT 		"Inserire testo:"
#define OUMSG_LCD_ERROR_ADAPTER 	"Nessun ACK, controllare l'adattatore"
// I2C //
#define OUMSG_I2C_READ_PEND 	"*(N)ACK IN ATTESA"

#define OUMSG_I2C_CON 		"Modalità I2C:\x0D\x0A 1. Software\x0D\x0A 2. Hardware"
#define OUMSG_I2C_REV3_WARN 	 "ATTENZIONE: La periferica hardware I2C non è disponibile su questo PIC! (REV A3)\x0D\x0A"
#define OUMSG_I2C_HWSPEED 	"Selezionare velocità:\x0D\x0A 1. 100KHz\x0D\x0A 2. 400KHz\x0D\x0A 3. 1MHz"
#define OUMSG_I2C_MACRO_MENU 	" 0.Menù delle macro\x0D\x0A 1.Indirizzo di ricerca a 7bit\x0D\x0A 2.Sniffer I2C"
#define OUMSG_I2C_MACRO_SEARCH 	"Ricerca su I2C con indirizzamento a 7bit. \x0D\x0A   Trovato dispositivo all'indirizzo:"
#define OUMSG_I2C_MACRO_SNIFFER	"Sniffer su bus I2C, Premere un tasto qualsiasi per terminare"
//menu//
//jtag// // Yuck, I don't want to deal with this one...
//midi//
#define OUMSG_MIDI_READ_FAIL 		"FALLITO, NESSUN DATO"
#define OUMSG_MIDI_LIVE_DISPLAY_ON 	"MONITOR UART IN TEMPO REALE, } PER TERMINARE"
#define OUMSG_MIDI_LIVE_DISPLAY_OFF 	"MONITOR IN TEMPO REALE FERMATO"
//pckeyboard//
#define OUMSG_KB_TIMEOUT 		" BIT TIMEOUT"
#define OUMSG_KB_MACRO_MENU 		" 0. Menù delle macro\x0D\x0A 1. Monitor in tempo reale"
#define OUMSG_KB__MACRO_LIVE 		"Monitor di input, premere un tasto qualsiasi per terminare"
#define OUMSG_KB_ERROR_STARTBIT 	" *errore su bit di start"
#define OUMSG_KB_ERROR_PARITY 		" *errore su bit di parità"
#define OUMSG_KB_ERROR_STOPBIT 		" *errore su bit di stop"
#define OUMSG_KB_ERROR_TIMEOUT 		" BIT TIMEOUT"
#define OUMSG_KB_ERROR_NONE 		" NESSUN ERRORE"
#define OUMSG_KB_ERROR_UNK 		" ERRORE SCONOSCIUTO"
//procMenu//
#define OUMSG_PM_1A_P_DEPRECATED 	"Configurazione della tensione di alimentazione deprecata, usare W/w per modificare"
#define OUMSG_PM_RESET 			"RESET"
#define OUMSG_PM_SELFTEST_HIZ		"Self-test in modalità solo Hi-Z."
#define OUMSG_PM_CONVERT		"CONVERTI "
//procSyntax//
#define OUMSG_PS_DELAY			"RITARDO "
#define OUMSG_PS_DELAY_US		"uS"
#define OUMSG_PS_ADC_VOLT_PROBE		"TENSIONE IN INGRESSO ADC: "
#define OUMSG_PS_ADC_VOLTS		"V"
//RAW2WIRE//
#define OUMSG_R2W_MACRO_MENU	" 0.Menù delle macro\x0D\x0A 1.ISO7813-3 ATR\x0D\x0A 2.ISO7813-3 solo parse\x0D\x0A"
//RAW3WIRE//
//selftest// //just leave in english for now...
//selftest//
// SPI //
#define OUMSG_SPI_SPEED 	"Selezionare velocità:\x0D\x0A 1. 30KHz\x0D\x0A 2. 125KHz\x0D\x0A 3. 250KHz\x0D\x0A 4. 1MHz"
#define OUMSG_SPI_MACRO_MENU	" 0.Menù delle macro\x0D\x0A 1.Sniffer bus SPI"
#define OUMSG_SPI_SNIFF_MENU	"Sniffa quando:\x0D\x0A 1. CS basso\x0D\x0A 2. CS alto\x0D\x0A 3. Tutto il traffico"
#define OUMSG_SPI_SNIFF_BEGIN	"Sniffer bus SPI, premere un tasto qualsiasi per terminare"
#define OUMSG_SPI_SNIFF_BUFFER	"BUFFER OVERFLOW!\x0D\x0A Velocità del bus troppo elevata, riprovare con modalità di visualizzazione RAW"
//UART //
#define OUMSG_UART_MACRO_MENU 		" 0.Menù delle macro\x0D\x0A 1.UART trasparente\x0D\x0A 2.Monitor UART in tempo reale"
#define OUMSG_UART_READ_FAIL 		"FALLITO, NESSUN DATO"
#define OUMSG_UART_LIVE_DISPLAY_ON 	"MONITOR UART IN TEMPO REALE, } PER FERMARE"
#define OUMSG_UART_LIVE_DISPLAY_OFF 	"MONITOR IN TEMPO REALE FERMATO"
#define OUMSG_UART_DATABITS_PARITY 	"Bit di dati e parità:\x0D\x0A 1. 8, NESSUNA *default \x0D\x0A 2. 8, PARI \x0D\x0A 3. 8, DISPARI \x0D\x0A 4. 9, NESSUNA"
#define OUMSG_UART_STOPBITS		"Bit di stop:\x0D\x0A 1. 1 *default\x0D\x0A 2. 2"
#define OUMSG_UART_RXPOLARITY		"Polarità di ricezione:\x0D\x0A 1. Inattivo a 1 *default\x0D\x0A 2. Inattivo a 0"
/************************
*
*
*	HELP TEXT
*
*
*************************/
#define HELP_TITLE_MENUS_T			"MENU'"
#define HELP_MENUS_HELP_T 			"? Aiuto"
#define HELP_MENUS_VERSION_T		"I Informazioni di stato"
#define HELP_MENUS_BUSMODE_T		"M Modalità del bus"
#define HELP_MENUS_TERMBAUD_T		"B Velocità del terminale"
#define HELP_MENUS_DISPLAYMODE_T	"O Formato di visulizzazione dei dati"
#define HELP_MENUS_VMONITOR_T		"V Monitor tensioni di alimentazione"
#define HELP_MENUS_FREQCOUNT_T		"F Frequenziometro su pin AUX"
#define HELP_MENUS_FREQGEN_T		"G Generatore di frequenza/PWM su pin AUX"
#define HELP_MENUS_AUXPIN_T			"C Assegnamento pin di AUX"
#define HELP_MENUS_BITORDER_T		"L Ordine dei Bit"
#define HELP_MENUS_PULLUPV0A_T		"P Resistenze di pullup su SDA/SC"
#define HELP_MENUS_PULLUPV2_T		"P Resistenze di pullup"
#define HELP_MENUS_VREG_T			"P deprecato, usare W/w"
#define HELP_MENUS_HDBCONVERT_T		"= Convertitore HEX/DEC/BIN"
#define HELP_MENUS_SELFTEST_T		"~ Auto test"
#define HELP_MENUS_RESET_T			"# Reset"

#define HELP_TITLE_SYNTAX_T			"SINTASSI"
#define HELP_SYNTAX_AUXPIN_T		"A/a/@ Commuta uscita AUX H/L/lettura"
#define HELP_SYNTAX_VREG_T			"W/w Commuta tensione di alimentazione on/off"
#define HELP_SYNTAX_VPROBE_T		"D Misura di tensione sulgli ingressi ADC"
#define HELP_SYNTAX_START_T			"[ ({) Start (con lettura)"
#define HELP_SYNTAX_STOP_T			"] o } Stop"
#define HELP_SYNTAX_READ_T			"R o r lettura byte"
#define HELP_SYNTAX_WRITEBIN_T		"0b Scrive byte in BIN"
#define HELP_SYNTAX_WRITEHEX_T		"0h o 0x Scrive byte in HEX"
#define HELP_SYNTAX_WRTIEDEC_T		"0-255 Scrive byte in DEC"
#define HELP_SYNTAX_DELIMIT_T		", Delimitatore (anche spazio)"
#define HELP_SYNTAX_DELAY_T			"& ritardo di 1uS"
#define HELP_SYNTAX_REPEAT_T		": Ripeti (r:2, 0x0a:4, &:20, ^:2, etc.)"
#define HELP_SYNTAX_MACRO_T			"(#) Avvia macro, (0) per esecuzione lista di macro"

#define HELP_SYNTAX_BITWISETITLE_T	"OPERAZIONI SU BUS A BASSO LIVELLO"

#define HELP_SYNTAX_BITCLKHL_T		"/\\ Clock H/L"
#define HELP_SYNTAX_BITDATHL_T		"-/_ Data H/L"
#define HELP_SYNTAX_BITPEEK_T		". Lettura stato dei pin di input"
#define HELP_SYNTAX_BITCLK_T		"^ Clock tick"
#define HELP_SYNTAX_BITREAD_T		"! Lettura bit"

#endif

//Please leave one blank line after this comment. If you don't, the compiler gets mad.
