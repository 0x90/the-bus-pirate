//***************************************/
//
// Spanish translation started by Pastus AKA Alessandro
// for contact of information about this translation pastus@gmail.com
// revised and mantained by el_remora otaconn@gmail.com
//
//****************************************/
//these terms become part of the terminal text messaging system
//one copy can be accessed from anywhere in the code, this saves a bunch of space

#define MSG_READY_T            "LISTO\x0D\x0A"

#define MSG_READ_T            "LECTURA: "
#define MSG_READBULK_T        "LECTURA "
#define MSG_READBULK_BYTES_T " BYTES:\x0D\x0A"
#define MSG_WRITE_T         "ESCRITURA: "
#define MSG_WRITEBULK_T     " VEZ"
#define MSG_ACK_T            "ACK"
#define MSG_NACK_T            "NACK"
#define MSG_I2C_START_T        "BIT DE START I2C\x0D\x0A"
#define MSG_I2C_STOP_T        "BIT DE STOP I2C\x0D\x0A"
#define MSG_CS_ENABLED_T     "CS HABILITADO\x0D\x0A"
#define MSG_CS_DISABLED_T    "CS DESHABILITADO\x0D\x0A"
#define MSG_ADAPTER_T        "Esta modalidad necesida un adaptador\x0D\x0A"

#define MSG_BIT_READ_T         "BIT LEIDO: "
#define MSG_BIT_PEEK_T         "DATO DE ENTRADA, ESTADO: "
#define MSG_BIT_NOWINPUT_T    " *pin ahora está en HiZ\x0D\x0A"
#define MSG_BIT_CLK_T          " Pulsos de reloj\x0D\x0A"
#define MSG_BIT_CLKH_T         "RELOJ, 1\x0D\x0A"
#define MSG_BIT_CLKL_T         "RELOJ, 0\x0D\x0A"
#define MSG_BIT_DATH_T         "DATO DE SALIDA, 1\x0D\x0A"
#define MSG_BIT_DATL_T         "DATO DE SALIDA, 0\x0D\x0A"

#define MSG_VREG_ON_T        "ALIMENTACIÓN ENCENDIDA\x0D\x0A"
#define MSG_VREG_OFF_T        "ALIMENTACIÓN APAGADA\x0D\x0A"

#define MSG_ERROR_MACRO_T     "Macro desconocida, prueba ? o (0) para ayuda\x0D\x0A"
#define MSG_ERROR_MODE_T     "Comando no disponible por esa modalidad\x0D\x0A"
#define MSG_ERROR_SYNTAX_T     "* Error de sintaxis,teclea ? para ayuda\x0D\x0A"
#define MSG_ERROR_BUFFER_T    "* SOBREPASADO EL BUFFER DEL TERMINAL, INTENTAR CON SEGMENTOS MÁS CORTOS\x0D\x0A"
#define MSG_ERROR_NOMODE_T    "Ninguna modalidad seleccionada, teclea M para modo\x0D\x0A"
#define MSG_ERROR_NOTHIZPIN_T     "ATENCIÓN, los pines no están en drenador abierto (HiZ)\x0D\x0A"

#define MSP_OPT_INVALID_T        "Error, prueba otra vez>"
#define MSG_OPT_OUTPUT_TYPE_T    "Elegir tipo de salida:\x0D\x0A 1. Drenador abierto (H=HiZ, L=GND)\x0D\x0A 2. Normal (H=3.3V, L=GND)\x0D\x0A"
#define MSG_OPT_MODESET_T        "Modalidad seleccionada\x0D\x0A"
#define MSG_OPT_DISPLAYMODE_T     " 1. HEX\x0D\x0A 2. DEC\x0D\x0A 3. BIN\x0D\x0A 4. RAW\x0D\x0A"
#define MSG_OPT_DISPLAYMODESET_T "Formato de visualicación seleccionado\x0D\x0A"
#define MSG_OPT_PULLUP_T        " 1. Pull-ups activadas\x0D\x0A 2. Pull-ups desactivadas\x0D\x0A"
#define MSG_OPT_PULLUP_OFF_T     "Activar resistencias Pull-up\x0D\x0A"
#define MSG_OPT_PULLUP_ON_T     "Desactivar resistencias Pull-up\x0D\x0A"
#define MSG_OPT_VMONITOR_T        "Sensores de tensión: "
#define MSG_OPT_BITORDER_T        " 1. MSB primero \x0D\x0A 2. LSB primero \x0D\x0A"
#define MSG_OPT_BITORDER_MSB_T    "MSB seleccionado: bit MÁS significativo primero\x0D\x0A"
#define MSG_OPT_BITORDER_LSB_T    "LSB seleccionado: bit MENOS significativo primero\x0D\x0A"
#define MSG_OPT_AUXPIN_T        "Elegir función pin aux\x0D\x0A 1. AUX (por defecto)\x0D\x0A 2. CS/TMS\x0D\x0A"
#define MSG_OPT_AUXPIN_AUX_T     "a/A/@ controla pin AUX\x0D\x0A"
#define MSG_OPT_AUXPIN_CS_T     "a/A/@ controla pin CS/TMS\x0D\x0A"
#define MSG_OPT_TERMBAUD_ADJUST_T    "Ajusta el terminal y teclea espacio para continuar\x0D\x0A"
#define MSG_OPT_UART_BAUD_T     "Elegir velocidad puerto serie: (bps)\x0D\x0A 1. 300\x0D\x0A 2. 1200\x0D\x0A 3. 2400\x0D\x0A 4. 4800\x0D\x0A 5. 9600\x0D\x0A 6. 19200\x0D\x0A 7. 38400\x0D\x0A 8. 57600\x0D\x0A 9. 115200\x0D\x0A"
#define MSG_OPT_CKP_T            "Polaridad del Reloj:\x0D\x0A 1. Parado bajo *por defecto\x0D\x0A 2. Parado alto\x0D\x0A" //use these with BB library too
#define MSG_OPT_CKE_T            "Frente del reloj de salida:\x0D\x0A 1. Frente de subida\x0D\x0A 2. Frente de bajada *por defecto\x0D\x0A"
#define MSG_OPT_SMP_T            "Fase de muestro de la entrada:\x0D\x0A 1. Mitad *por defecto\x0D\x0A 2. Final \x0D\x0A"
#define MSG_OPT_BB_SPEED_T        "Elegir velocidad:\x0D\x0A 1. ~50KHz\x0D\x0A 2. ~100KHz\x0D\x0A 3. ~400KHz\x0D\x0A"

#define MSG_STATUS_OUTPUT_HIZ_T     "Salidas en drenador abierto (H=entrada, L=GND)\x0D\x0A"
#define MSG_STATUS_OUTPUT_NORMAL_T     "Salidas normales (H=V+, L=GND)\x0D\x0A"
#define MSG_STATUS_PULLUP_NOTALLOWED_T     "Resistencias de Pull-ups no permitidas\x0D\x0A"
#define MSG_STATUS_BITORDER_NOTALLOWED_T "Configuración de orden de bits no permitida\x0D\x0A"

/************************
*
*
*    One use messages
*    These are only used once, usually through a bpWstring,
*   and not by registration in the terminal message system above
*
*
*************************/
// 1-Wire //
#define OUMSG_1W_BIT_BULKWRITE  " ESCRIBIR BIT(S) ("
#define OUMSG_1W_BIT_WRITE        "ESCRIBIR BIT: "
#define OUMSG_1W_BIT_WRITE_NOTE        " *en el siguiente ciclo de reloj (^) tendrá este valor"
#define OUMSG_1W_MACRO_MENU        " 0.Menú de macros"
#define OUMSG_1W_MACRO_MENU_ROM            "1WIRE ROM DE COMANDOS DE MACROs:\x0D\x0A 51.READ ROM (0x33) *para un solo dispositivo en el bus\x0D\x0A 85.MATCH ROM (0x55) *seguido de dirección de 64bit\x0D\x0A 204.SKIP ROM (0xCC) *seguido de comando\x0D\x0A 236.ALARM SEARCH (0xEC)\x0D\x0A 240.SEARCH ROM (0xF0)"
#define OUMSG_1W_MACRO_ADDRESS    "DIRECCIÓN MACRO" //(#): 0 0 0 0 0 0 0 0
#define OUMSG_1W_MACRO_ADDRESS_NODEVICE "Ningún dispositivo encontrado, prueba antes con la macro (ALARM) SEARCH"
#define OUMSG_1W_MACRO_ALARMSEARCH_ROM     "ALARM SEARCH (0xEC)"
#define OUMSG_1W_MACRO_SEARCH_ROM     "SEARCH (0xF0)"
#define OUMSG_1W_MACRO_SEARCH_ROM_HEADER "Dirección macro     1WIRE"
#define OUMSG_1W_MACRO_SEARCH_ROM_NOTE    "IDs dispositivo están disponibles por MACRO, tecleando (0)."
#define OUMSG_1W_MACRO_READ_ROM     "READ ROM (0x33): "
#define OUMSG_1W_MACRO_MATCH_ROM     "MATCH ROM (0x55)"
#define OUMSG_1W_MACRO_SKIP_ROM     "SKIP ROM (0xCC)"
#define OUMSG_1W_RESET            "BUS RESET "
#define OUMSG_1W_RESET_OK        "OK"
#define OUMSG_1W_RESET_ERROR    "ERROR: "
#define OUMSG_1W_RESET_SHORT    "*Cortocitcuito o Pull-ups desactivadas "
#define OUMSG_1W_RESET_NODEV     "*Ningún dispositivo encontrado "
//AUXpin//
#define OUMSG_AUX_PWM_OFF         "PWM apagado"
#define OUMSG_AUX_PWM_NOTE         "Generador de frecuencia/PWM 1KHz-4,000KHz (beta)"
#define OUMSG_AUX_PWM_FREQ         "Frecuencia en KHz "
#define OUMSG_AUX_PWM_PRESCALE     "Prescalar:"
#define OUMSG_AUX_PWM_DUTY         "Ciclo de trabajo en % "
#define OUMSG_AUX_PWM_ON         "PWM activo"
#define OUMSG_AUX_FREQ_PWM         "PWM activo: teclear G para apagar el PWM"
#define OUMSG_AUX_FREQCOUNT     "Frecuencia en el pin AUX: "
#define OUMSG_AUX_HIZ            "AUX INPUT/HiZ"
#define OUMSG_AUX_HIGH            "AUX ALTO"
#define OUMSG_AUX_LOW            "AUX BAJO"
#define OUMSG_AUX_INPUT_READ    "AUX ENTRADA/HiZ, LECTURA: "
//HD44780//
#define OUMSG_LCD_WRITE_COMMAND     "CMD " //indicates writes to command register
#define OUMSG_LCD_WRITE_DATA         "DAT " //indicates writes to data register
#define OUMSG_LCD_COMMAND_MODE         "RS BAJO, MODO COMANDOS"
#define OUMSG_LCD_DATA_MODE         "RS ALTO, MODO DATOS"
#define OUMSG_LCD_SETUP_ADAPTER     "Tipo de LCD:\x0D\x0A 1. HD44780 (usando PCF8574)"
#define OUMSG_LCD_MACRO_MENU         " 0.Menú de macros\x0D\x0A 1.Resetear LCD\x0D\x0A 2.Inicializar LCD\x0D\x0A 3.Borrar LCD\x0D\x0A 4.Posición del cursor ex:(4:0)\x0D\x0A 5.(obsoleto)\x0D\x0A 6.Escribir :number números de test ex:(6:80)\x0D\x0A 7.Escribir :number caracteres de test ex:(7:80)\x0D\x0A 8. Inserta texto en la posición actual"
#define OUMSG_LCD_MACRO_INIT_DISPLAYLINES     "Líneas del display:\x0D\x0A 1. 1 \x0D\x0A 2. Varias"
#define OUMSG_LCD_MACRO_RESET         "RESET"
#define OUMSG_LCD_MACRO_INIT         "INICIALIZACIÓN"
#define OUMSG_LCD_MACRO_CLEAR         "BORRADO"
#define OUMSG_LCD_MACRO_CURSOR        "POSICIÓN DEL CURSOR"
#define OUMSG_LCD_MACRO_TEXT         "Insertar texto"
#define OUMSG_LCD_ERROR_ADAPTER     "No ACK, comprobar el adaptador"
// I2C //
#define OUMSG_I2C_READ_PEND     "*(N)ACK PENDIENTE"
#define OUMSG_I2C_CON            "Modo I2C:\x0D\x0A 1. Software\x0D\x0A 2. Hardware"
#define OUMSG_I2C_REV3_WARN     "ATENCIÓN: el hardware I2C puede no funcionar en este PIC! (REV A3)"
#define OUMSG_I2C_HWSPEED        "Elegir velocidad:\x0D\x0A 1. 100KHz\x0D\x0A 2. 400KHz\x0D\x0A 3. 1MHz"
#define OUMSG_I2C_MACRO_MENU     " 0.Menú de macros\x0D\x0A 1.Búsqueda de direcciones de 7bit\x0D\x0A 2.Sniffer I2C"
#define OUMSG_I2C_MACRO_SEARCH     "Buscando direcciones I2C de 7bit. \x0D\x0A   Encontrados dispositivos en la dirección:"
#define OUMSG_I2C_MACRO_SNIFFER    "Sniffer de bus I2C, presionar cualquier tecla para terminar"
//menu//
//jtag// // Yuck, I don't want to deal with this one...
//midi//
#define OUMSG_MIDI_READ_FAIL         "FALLO, NINGÚN DATO"
#define OUMSG_MIDI_LIVE_DISPLAY_ON     "MONITOR UART EN TIEMPO REAL, } PARA PARAR"
#define OUMSG_MIDI_LIVE_DISPLAY_OFF "MONITOR EN TIEMPO REAL PARADO"
//pckeyboard//
#define OUMSG_KB_TIMEOUT            " BIT TIMEOUT"
#define OUMSG_KB_MACRO_MENU         " 0. Menú de macro\x0D\x0A 1. Monitor en tiempo real"
#define OUMSG_KB__MACRO_LIVE         "Monitor de entrada, presionar cualquier tecla para terminar"
#define OUMSG_KB_ERROR_STARTBIT     " *error del bit de inicio"
#define OUMSG_KB_ERROR_PARITY         " *error del bit de paridad"
#define OUMSG_KB_ERROR_STOPBIT         " *error del bit de parada"
#define OUMSG_KB_ERROR_TIMEOUT         " BIT TIMEOUT"
#define OUMSG_KB_ERROR_NONE         " NINGUNO"
#define OUMSG_KB_ERROR_UNK            " ERROR DESCONOCIDO"
//procMenu//
#define OUMSG_PM_1A_P_DEPRECATED     "Configuración de alimentación obsoleta, usar W/w para cambiarla"
#define OUMSG_PM_RESET                "RESET"
#define OUMSG_PM_SELFTEST_HIZ        "Self-test solo en modo HiZ."
#define OUMSG_PM_CONVERT            "CONVERTIR "
//procSyntax//
#define OUMSG_PS_DELAY            "DELAY "
#define OUMSG_PS_DELAY_US        "uS"
#define OUMSG_PS_ADC_VOLT_PROBE    "MEDIDOR DE TENSIÓN: "
#define OUMSG_PS_ADC_VOLTS        "V"
//RAW2WIRE//
#define OUMSG_R2W_MACRO_MENU    " 0.Menú de macros\x0D\x0A 1.ISO7813-3 ATR\x0D\x0A 2.ISO7813-3 solo análisis\x0D\x0A"
//RAW3WIRE//
//selftest// //just leave in english for now...
//selftest//
// SPI //
#define OUMSG_SPI_SPEED            "Elegir velocidad\x0D\x0A 1. 30KHz\x0D\x0A 2. 125KHz\x0D\x0A 3. 250KHz\x0D\x0A 4. 1MHz"
#define OUMSG_SPI_MACRO_MENU    " 0.Menú de macros\x0D\x0A 1.Sniffer de bus SPI"
#define OUMSG_SPI_SNIFF_MENU    "Sniff cuando:\x0D\x0A 1. CS bajo\x0D\x0A 2. CS alto\x0D\x0A 3. Todo el trafico"
#define OUMSG_SPI_SNIFF_BEGIN    "Sniffer de bus SPI, presionar cualquier tecla para terminar"
#define OUMSG_SPI_SNIFF_BUFFER    "BUFFER OVERFLOW!\x0D\x0A Velocidad de bus demasiado alta, ententar con la modalidad RAW"
//UART //
#define OUMSG_UART_MACRO_MENU 	" 0.Menù de macros\x0D\x0A 1.UART trasparente\x0D\x0A 2.Monitor UART en tiempo real"
#define OUMSG_UART_READ_FAIL         "FALLO, NINGÚN DATO"
#define OUMSG_UART_LIVE_DISPLAY_ON     "MONITOR UART EN TIEMPO REAL, } PARA PARAR"
#define OUMSG_UART_LIVE_DISPLAY_OFF "MONITOR EN TIEMPO REAL PARADO"
#define OUMSG_UART_DATABITS_PARITY     "Bits de datos y paridad:\x0D\x0A 1. 8, NINGUNA *por defecto \x0D\x0A 2. 8, PAR \x0D\x0A 3. 8, IMPAR \x0D\x0A 4. 9, NINGUNA"
#define OUMSG_UART_STOPBITS            "Bits de parada:\x0D\x0A 1. 1 *por defecto\x0D\x0A 2. 2"
#define OUMSG_UART_RXPOLARITY        "Polaridad de recepción:\x0D\x0A 1. Inactivo con 1 *por defecto\x0D\x0A 2. Inactivo con 0"
/************************
*
*
*    HELP TEXT
*
*
*************************/
#define HELP_TITLE_MENUS_T            "MENÚS"
#define HELP_MENUS_HELP_T             "? Ayuda"
#define HELP_MENUS_VERSION_T        "I Información de estado"
#define HELP_MENUS_BUSMODE_T        "M Modo del bus"
#define HELP_MENUS_TERMBAUD_T        "B Velocidad del terminal"
#define HELP_MENUS_DISPLAYMODE_T    "O Formato de visualización datos"
#define HELP_MENUS_VMONITOR_T        "V Cromprobar tensión de alimentación"
#define HELP_MENUS_FREQCOUNT_T        "F Frecuencímetro en AUX"
#define HELP_MENUS_FREQGEN_T        "G Generador de frecuencia/PWM en AUX"
#define HELP_MENUS_AUXPIN_T            "C Asignación del pin AUX"
#define HELP_MENUS_BITORDER_T        "L Orden de los Bits"
#define HELP_MENUS_PULLUPV0A_T        "P Resistencias de Pull-up en SDA/SC"
#define HELP_MENUS_PULLUPV2_T        "P Resistencias de Pull-up"
#define HELP_MENUS_VREG_T            "P Obsoleto, usar W/w"
#define HELP_MENUS_HDBCONVERT_T        "= Convertidor HEX/DEC/BIN"
#define HELP_MENUS_SELFTEST_T        "~ Test interno"
#define HELP_MENUS_RESET_T            "# Reset"

#define HELP_TITLE_SYNTAX_T            "SINTAXIS"
#define HELP_SYNTAX_AUXPIN_T        "A/a/@ Commuta salida AUX H/L/lectura"
#define HELP_SYNTAX_VREG_T            "W/w Commuta tensión de alimentación encendida/apagada"
#define HELP_SYNTAX_VPROBE_T        "D Medida de tensión sobre las entradas ADC"
#define HELP_SYNTAX_START_T            "[ ({) Inicia (con lectura)"
#define HELP_SYNTAX_STOP_T            "] o } Acaba"
#define HELP_SYNTAX_READ_T            "R o r Leer byte"
#define HELP_SYNTAX_WRITEBIN_T        "0b Escribe byte en BIN"
#define HELP_SYNTAX_WRITEHEX_T        "0h o 0x Escribe byte en HEX"
#define HELP_SYNTAX_WRTIEDEC_T        "0-255 Escribe byte en DEC"
#define HELP_SYNTAX_DELIMIT_T        ", Delimitador (también espacio)"
#define HELP_SYNTAX_DELAY_T            "& Delay de 1uS"
#define HELP_SYNTAX_REPEAT_T        ": Repetir (r:2, 0x0a:4, &:20, ^:2, etc.)"
#define HELP_SYNTAX_MACRO_T            "(#) Ejecuta macro, (0) para lista de macro"

#define HELP_SYNTAX_BITWISETITLE_T    "OPERACIÓN SOBRE EL BUS A BAJO NIVEL"
#define HELP_SYNTAX_BITCLKHL_T        "/\\ Reloj H/L"
#define HELP_SYNTAX_BITDATHL_T        "-/_ Dato H/L"
#define HELP_SYNTAX_BITPEEK_T        ". Leer estado del pin de entrada de datos"
#define HELP_SYNTAX_BITCLK_T        "^ Pulso de reloj"
#define HELP_SYNTAX_BITREAD_T        "! Leer bit"

//Please leave one blank line after this comment. If you don't, the compiler gets mad.
