//***************************************/
//
//	This is most of the text used in the Bus Pirate interface.  
// 	en-US is the default development translation. 
//	Other translations include contact information for the translator.
//
//****************************************/
//these terms become part of the terminal text messaging system 
//one copy can be accessed from anywhere in the code, this saves a bunch of space
#define MSG_READY_T			"PRONTO\x0D\x0A"

#define MSG_READ_T 			"LEITURA: "
#define MSG_READBULK_T		"LEITURA "
#define MSG_READBULK_BYTES_T " BYTES:\x0D\x0A"
#define MSG_WRITE_T 		"ESCREVER: "
#define MSG_WRITEBULK_T 	" VEZES"
#define MSG_ACK_T			"ACK"
#define MSG_NACK_T			"NACK"
#define MSG_I2C_START_T		"I2C START BIT\x0D\x0A"
#define MSG_I2C_STOP_T		"I2C STOP BIT\x0D\x0A"
#define MSG_CS_ENABLED_T 	"CS ACTIVADO\x0D\x0A"
#define MSG_CS_DISABLED_T	"CS DESACTIVADO\x0D\x0A"
#define MSG_ADAPTER_T		"Este modo requer um adaptador\x0D\x0A"

#define MSG_BIT_READ_T 		"LER BIT: "
#define MSG_BIT_PEEK_T 		"ENTRADA DE DADOS, ESTADO: "
#define MSG_BIT_NOWINPUT_T	" *pino está agora em HiZ\x0D\x0A"
#define MSG_BIT_CLK_T  		" CLOCK TICKS\x0D\x0A"
#define MSG_BIT_CLKH_T 		"CLOCK, 1\x0D\x0A"
#define MSG_BIT_CLKL_T 		"CLOCK, 0\x0D\x0A"
#define MSG_BIT_DATH_T 		"SAIDA DE DADOS, 1\x0D\x0A"
#define MSG_BIT_DATL_T 		"SAIDA DE DADOS, 0\x0D\x0A"

#define MSG_VREG_ON_T		"FONTES DE ALIMENTAÇÃO LIGADAS\x0D\x0A"
#define MSG_VREG_OFF_T		"FONTES DE ALIMENTAÇÃO DESLIGADAS\x0D\x0A"

#define MSG_ERROR_MACRO_T 	"Macro Desconhecida, digite ? ou (0) para obter ajuda\x0D\x0A"
#define MSG_ERROR_MODE_T 	"Comando não aplicável neste modo\x0D\x0A"
#define MSG_ERROR_SYNTAX_T 	"* Erro de sintaxe, digitee ? para ajuda\x0D\x0A"
#define MSG_ERROR_BUFFER_T	"* BUFFER OVERFLOW DO TERMINAL, TENTE COM SEGMENTOS MAIS PEQUENOS\x0D\x0A"
#define MSG_ERROR_NOMODE_T	"Não seleccionou um modo, digite M\x0D\x0A"
#define MSG_ERROR_NOTHIZPIN_T "AVISO: Os pinos não estão no modo Open Drain (HiZ)\x0D\x0A"

#define MSP_OPT_INVALID_T 		"Erro, tente de novo >"
#define MSG_OPT_OUTPUT_TYPE_T	"Seleccionar tipo de saída:\x0D\x0A 1. Open drain (H=Hi-Z, L=GND)\x0D\x0A 2. Normal (H=3.3V, L=GND)\x0D\x0A"
#define MSG_OPT_MODESET_T		"Modo seleccionado\x0D\x0A"
#define MSG_OPT_DISPLAYMODE_T 	" 1. HEX\x0D\x0A 2. DEC\x0D\x0A 3. BIN\x0D\x0A 4. RAW\x0D\x0A"
#define MSG_OPT_DISPLAYMODESET_T "Formato de saída\x0D\x0A"
#define MSG_OPT_PULLUP_T		" 1. Desligar Pull-ups\x0D\x0A 2. Ligar Pull-ups\x0D\x0A"
#define MSG_OPT_PULLUP_OFF_T 	"Resistências Pull-up DESLIGADAS\x0D\x0A"
#define MSG_OPT_PULLUP_ON_T 	"Resistências Pull-up LIGADAS\x0D\x0A"
#define MSG_OPT_VMONITOR_T		"Monitor de Voltagem: "
#define MSG_OPT_BITORDER_T 		" 1. MSB primeiro\x0D\x0A 2. LSB primeiro\x0D\x0A"
#define MSG_OPT_BITORDER_MSB_T	"Configuração MSB: Bit MAIS significativo primeiro\x0D\x0A"
#define MSG_OPT_BITORDER_LSB_T	"Configuração LSB: Bit MENOS significativo primeiro\x0D\x0A"
#define MSG_OPT_AUXPIN_T		"Comandos de controlo AUX\x0D\x0A 1. AUX (defeito)\x0D\x0A 2. CS/TMS\x0D\x0A"
#define MSG_OPT_AUXPIN_AUX_T 	"a/A/@ controla o pino AUX\x0D\x0A"
#define MSG_OPT_AUXPIN_CS_T 	"a/A/@ controla o pino CS/TMS\x0D\x0A"
#define MSG_OPT_TERMBAUD_ADJUST_T	"Ajuste a velocidade do terminal e prima Espaço para continuar\x0D\x0A"
#define MSG_OPT_UART_BAUD_T 	"Velocidade da porta série: (bps)\x0D\x0A 1. 300\x0D\x0A 2. 1200\x0D\x0A 3. 2400\x0D\x0A 4. 4800\x0D\x0A 5. 9600\x0D\x0A 6. 19200\x0D\x0A 7. 38400\x0D\x0A 8. 57600\x0D\x0A 9. 115200\x0D\x0A"
#define MSG_OPT_CKP_T 			"Polaridade do Relógio:\x0D\x0A 1. Activo baixo *defeito\x0D\x0A 2. Inactivo alto\x0D\x0A" //use these with BB library too
#define MSG_OPT_CKE_T 			"Pico de saída do relógio:\x0D\x0A 1. Inactivo para activo\x0D\x0A 2. Activo para inactivo *defeito\x0D\x0A"
#define MSG_OPT_SMP_T 			"Fase de entrada:\x0D\x0A 1. Meio *defeito\x0D\x0A 2. Fim\x0D\x0A"
#define MSG_OPT_BB_SPEED_T 		"Velocidade:\x0D\x0A 1. ~5KHz\x0D\x0A 2. ~50KHz\x0D\x0A 3. ~100KHz\x0D\x0A 4. ~400KHz\x0D\x0A"

#define MSG_STATUS_OUTPUT_HIZ_T 	"Saídas Open drain (H=Hi-Z, L=GND)\x0D\x0A"
#define MSG_STATUS_OUTPUT_NORMAL_T 	"Saídas normais (H=V+, L=GND)\x0D\x0A"
#define MSG_STATUS_PULLUP_NOTALLOWED_T 	"Resistências pull-up não permitidas.\x0D\x0A"
#define MSG_STATUS_BITORDER_NOTALLOWED_T "Configuração não permitida da ordenação de bits\x0D\x0A"

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
#define OUMSG_1W_BIT_BULKWRITE " ESCREVER BIT(S) ("
#define OUMSG_1W_BIT_WRITE		"ESCREVER BIT: "
#define OUMSG_1W_BIT_WRITE_NOTE		" *próximo clock (^) irá ter este valor"
#define OUMSG_1W_MACRO_MENU		" 0.Menu de Macros"
#define OUMSG_1W_MACRO_MENU_ROM			"1WIRE ROM COMANDOS DE MACROs:\x0D\x0A 51.LER ROM (0x33) *para um unico dispositivo\x0D\x0A 85.COMPARAR ROM (0x55) *seguido de um endereço 64bit\x0D\x0A 204.IGNORAR ROM (0xCC) *seguido do comando\x0D\x0A 236.PROCURAR ALARME (0xEC)\x0D\x0A 240.PROCURAR ROM (0xF0)"
#define OUMSG_1W_MACRO_ADDRESS	"MACRO ENDEREÇO " //(#): 0 0 0 0 0 0 0 0
#define OUMSG_1W_MACRO_ADDRESS_NODEVICE "Sem dispositivo, tente a macro PROCURAR ALARME primeiro"
#define OUMSG_1W_MACRO_ALARMSEARCH_ROM 	"PROCURAR ALARME (0xEC)"
#define OUMSG_1W_MACRO_SEARCH_ROM 		"PROCURAR (0xF0)"
#define OUMSG_1W_MACRO_SEARCH_ROM_HEADER "Macro     Endereço 1WIRE"
#define OUMSG_1W_MACRO_SEARCH_ROM_NOTE	"IDs de dispositivos disponiveis pela MACRO, ver (0)."
#define OUMSG_1W_MACRO_READ_ROM 	"LER ROM (0x33): "
#define OUMSG_1W_MACRO_MATCH_ROM 	"COMPARAR ROM (0x55)"
#define OUMSG_1W_MACRO_SKIP_ROM 	"IGNORAR ROM (0xCC)"
#define OUMSG_1W_RESET			"BUS RESET "
#define OUMSG_1W_RESET_OK		"OK"
#define OUMSG_1W_RESET_ERROR	"ERRO: "
#define OUMSG_1W_RESET_SHORT	"*Curto-circuito ou pull-up inexistente "
#define OUMSG_1W_RESET_NODEV 	"*Dispositivo não encontrado "
//AUXpin//
#define OUMSG_AUX_PWM_OFF 		"PWM desactivado"
#define OUMSG_AUX_PWM_NOTE 		"Gerador de Frequências 1KHz-4,000KHz /PWM (beta)"
#define OUMSG_AUX_PWM_FREQ 		"Frequência em KHz "
#define OUMSG_AUX_PWM_PRESCALE 	"Pré-Escala:"
#define OUMSG_AUX_PWM_DUTY 		"Ciclo em % "
#define OUMSG_AUX_PWM_ON 		"PWM activo"
#define OUMSG_AUX_FREQ_PWM 		"PWM activo: tente G para desactivar PWM"
#define OUMSG_AUX_FREQCOUNT 	"Frequência no pino AUX: "
#define OUMSG_AUX_HIZ			"ENTRADA AUX/HI-Z"
#define OUMSG_AUX_HIGH			"AUX ALTO"
#define OUMSG_AUX_LOW			"AUX BAIXO"
#define OUMSG_AUX_INPUT_READ	"AUX INPUT/HI-Z, READ: "
//HD44780//
#define OUMSG_LCD_WRITE_COMMAND "CMD " //indicates writes to command register
#define OUMSG_LCD_WRITE_DATA 	"DAT " //indicates writes to data register
#define OUMSG_LCD_COMMAND_MODE 	"RS BAIXO, MODO DE COMANDO"
#define OUMSG_LCD_DATA_MODE 	"RS ALTO, MODO DE DADOS"
#define OUMSG_LCD_SETUP_ADAPTER "Tipo de LCD:\x0D\x0A 1. HD44780 (usando expansor de IO PCF8574)"
#define OUMSG_LCD_MACRO_MENU 	" 0.Menu de Macros\x0D\x0A 1.Reinicio do LCD\x0D\x0A 2.Inicializar LCD\x0D\x0A 3.Limpar LCD\x0D\x0A 4.Posição do Cursor ex:(4:0)\x0D\x0A 5.(obsoleto)\x0D\x0A 6.Escrever :numero numero de testes ex:(6:80)\x0D\x0A 7.Escrever :numero Caracteres de teste ex:(7:80)\x0D\x0A 8.Inserir texto no cursor"
#define OUMSG_LCD_MACRO_INIT_DISPLAYLINES 	"Linhas:\x0D\x0A 1. 1 \x0D\x0A 2. Multiplas"
#define OUMSG_LCD_MACRO_RESET 	"REINICIAR"
#define OUMSG_LCD_MACRO_INIT 	"INICIALIZAR"
#define OUMSG_LCD_MACRO_CLEAR 	"LIMPO"
#define OUMSG_LCD_MACRO_CURSOR	"CONFIGURAR CURSOR"
#define OUMSG_LCD_MACRO_TEXT 	"Insira texto:"
#define OUMSG_LCD_ERROR_ADAPTER "Sem ACK, verifique o adaptador"
// I2C //
#define OUMSG_I2C_READ_PEND 	"*(N) AGUARDA ACK"
#define OUMSG_I2C_CON 			"Modo I2C:\x0D\x0A 1. Software\x0D\x0A 2. Hardware"
#define OUMSG_I2C_REV3_WARN 	"AVISO: HARDWARE I2C não está operacional no PIC! (REV A3)"
#define OUMSG_I2C_HWSPEED 		"Escolha a velocidade:\x0D\x0A 1. 100KHz\x0D\x0A 2. 400KHz\x0D\x0A 3. 1MHz"
#define OUMSG_I2C_MACRO_MENU 	" 0.Menu de Macros\x0D\x0A 1.Pesquisa de endereços 7bit\x0D\x0A 2.Sniffer I2C"
#define OUMSG_I2C_MACRO_SEARCH 	"Pesquisando espaço de endereços 7bit I2C. \x0D\x0A   Encontrado dispositivo em:"
#define OUMSG_I2C_MACRO_SNIFFER	"Sniffer de bus I2C, pressione qualquer tecla para sair"
//menu//
//jtag// // Yuck, I don't want to deal with this one...
//midi//
#define OUMSG_MIDI_READ_FAIL 		"FALHOU, SEM DADOS"
#define OUMSG_MIDI_LIVE_DISPLAY_ON 	"MONITOR UART, } PARA PARAR"
#define OUMSG_MIDI_LIVE_DISPLAY_OFF "MONITOR PARADO"
//pckeyboard//
#define OUMSG_KB_TIMEOUT 		" FIM DO TEMPO LIMITE"
#define OUMSG_KB_MACRO_MENU 	" 0. Menu de Macros\x0D\x0A 1. Monitor de entrada"
#define OUMSG_KB__MACRO_LIVE 	"Monitor de entrada, pressione qualquer tecla para sair"
#define OUMSG_KB_ERROR_STARTBIT " *erro no bit de inicio"
#define OUMSG_KB_ERROR_PARITY 	" *erro de paridade"
#define OUMSG_KB_ERROR_STOPBIT 	" *erro no bit de paragem"
#define OUMSG_KB_ERROR_TIMEOUT 	" FIM DO TEMPO LIMITE"
#define OUMSG_KB_ERROR_NONE 	" NENHUM"
#define OUMSG_KB_ERROR_UNK 		" ERRO DESCONHECIDO"
//procMenu//
#define OUMSG_PM_1A_P_DEPRECATED "Configuração obsoleta, altere com W/w"
#define OUMSG_PM_RESET 			"RE-INICIO"
#define OUMSG_PM_SELFTEST_HIZ	"Auto-teste apenas no modo Hi-Z."
#define OUMSG_PM_CONVERT		"CONVERTER "
//procSyntax//
#define OUMSG_PS_DELAY			"ATRASO "
#define OUMSG_PS_DELAY_US		"uS"
#define OUMSG_PS_ADCC			"MODO VOLTIMETRO"
#define OUMSG_PS_ANY_KEY		"Pressione qualquer tecla para sair"					//could be a generic message??
#define OUMSG_PS_ADC_VOLT_PROBE	"VOLTAGEM : "
#define OUMSG_PS_ADC_VOLTS		"V"
//RAW2WIRE//
#define OUMSG_R2W_MACRO_MENU	" 0.Menu de Macros\x0D\x0A 1.ISO7816-3 ATR\x0D\x0A 2.ISO7816-3 Análise apenas\x0D\x0A"
//RAW3WIRE//
//selftest// //just leave in english for now...
// SPI //
#define OUMSG_SPI_SPEED 		"Seleccione a velocidade:\x0D\x0A 1. 30KHz\x0D\x0A 2. 125KHz\x0D\x0A 3. 250KHz\x0D\x0A 4. 1MHz"
#define OUMSG_SPI_MACRO_MENU	" 0.Menu de Macros\x0D\x0A 1.Sniffer SPI"
#define OUMSG_SPI_SNIFF_MENU	"Analizar quando:\x0D\x0A 1. CS baixo\x0D\x0A 2. CS alto\x0D\x0A 3. Todo o tráfego"
#define OUMSG_SPI_SNIFF_BEGIN	"Sniffer SPI, qualquer tecla para sair"
#define OUMSG_SPI_SNIFF_BUFFER	"BUFFER OVERFLOW!\x0D\x0A Bus demasiado rápido, tente em modo de visualização RAW"
//UART //
#define OUMSG_UART_MACRO_MENU 	" 0.Menu de Macros\x0D\x0A 1.Ponte UART Transparente\x0D\x0A 2. Monitor UART em Tempo Real\x0D\x0A 3.Ponte UART com controlo de fluxo"
#define OUMSG_UART_READ_FAIL 		"FALHOU, SEM DADOS"
#define OUMSG_UART_LIVE_DISPLAY_ON 	"VISUALIZAÇÃO EM TEMPO REAL, } PARA PARAR"
#define OUMSG_UART_LIVE_DISPLAY_OFF "VISUALIZADOR EM TEMPO REAL PARADO"
#define OUMSG_UART_DATABITS_PARITY "Bits de dados e paridade:\x0D\x0A 1. 8, NENHUM *defeito \x0D\x0A 2. 8, PAR \x0D\x0A 3. 8, IMPAR \x0D\x0A 4. 9, NENHUM"
#define OUMSG_UART_STOPBITS		 	"Bits de paragem:\x0D\x0A 1. 1 *defeito\x0D\x0A 2. 2"
#define OUMSG_UART_RXPOLARITY		"Polaridade de Recepção:\x0D\x0A 1. Inactivo 1 *defeito\x0D\x0A 2. Inactivo 0"
/************************
*
*
*	HELP TEXT
*
*
*************************/
#define HELP_TITLE_MENUS_T			"MENUS"
#define HELP_MENUS_HELP_T 			"? Ajuda"
#define HELP_MENUS_VERSION_T		"I Informação de estado"
#define HELP_MENUS_BUSMODE_T		"M Modo de Bus"
#define HELP_MENUS_TERMBAUD_T		"B Velocidade do Terminal"
#define HELP_MENUS_DISPLAYMODE_T	"O Formato de saída"
#define HELP_MENUS_VMONITOR_T		"V Verificar fontes de alimentação"
#define HELP_MENUS_FREQCOUNT_T		"F Contador de Frequência em AUX"
#define HELP_MENUS_FREQGEN_T		"G Gerador de Frequências/PWM em AUX"
#define HELP_MENUS_AUXPIN_T			"C Designação do pino AUX"
#define HELP_MENUS_BITORDER_T		"L Ordem dos Bits"
#define HELP_MENUS_PULLUPV0A_T		"P Resistências SDA/SCL"
#define HELP_MENUS_PULLUPV2_T		"P Resistências Pullup"
#define HELP_MENUS_VREG_T			"P Obsoleto, usar W/w"
#define HELP_MENUS_HDBCONVERT_T		"= Conversor HEX/DEC/BIN"
#define HELP_MENUS_SELFTEST_T		"~ Auto-teste"
#define HELP_MENUS_RESET_T			"# Re-inicio"
#define HELP_MENUS_BOOTLOADER_T		"$ Bootloader"

#define HELP_TITLE_SYNTAX_T			"SINTAXE"
#define HELP_SYNTAX_AUXPIN_T		"A/a/@ Alterar saída de AUX (H/L/ler)"
#define HELP_SYNTAX_VREG_T			"W/w Alterar Fonte de alimentação ligado/desligado"
#define HELP_SYNTAX_VPROBE_T		"d (D) Medir voltagem no pino ADC (contínuo)"
#define HELP_SYNTAX_START_T			"[ ({) Iniciar (Leitura)"
#define HELP_SYNTAX_STOP_T			"] ou } Parar"
#define HELP_SYNTAX_READ_T			"R ou r Ler byte"
#define HELP_SYNTAX_WRITEBIN_T		"0b Escrever byte BIN"
#define HELP_SYNTAX_WRITEHEX_T		"0h ou 0x Escrever byte HEX"
#define HELP_SYNTAX_WRTIEDEC_T		"0-255 Escrever byte DEC"
#define HELP_SYNTAX_DELIMIT_T		", Delimitador (ou Espaço)"
#define HELP_SYNTAX_DELAY_T			"& Atraso de 1uS"
#define HELP_SYNTAX_REPEAT_T		": Repetir (r:2, 0x0a:4, &:20, ^:2, etc.)" 
#define HELP_SYNTAX_MACRO_T			"(#) Executar macro, (0) para lista de macros"

#define HELP_SYNTAX_BITWISETITLE_T	"OPERAÇÕES RAW BUS"
#define HELP_SYNTAX_BITCLKHL_T		"/\\ Clock H/L"
#define HELP_SYNTAX_BITDATHL_T		"-/_ Dados H/L"
#define HELP_SYNTAX_BITPEEK_T		". Ler dados de estado no pino de entrada"
#define HELP_SYNTAX_BITCLK_T		"^ Clock tick"
#define HELP_SYNTAX_BITREAD_T		"! Ler bit"

//Please leave one blank line after this comment. If you don't, the compiler gets mad.

