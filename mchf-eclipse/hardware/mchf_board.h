/*  -*-  mode: c; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4; coding: utf-8  -*-  */
/************************************************************************************
**                                                                                 **
**                               mcHF QRP Transceiver                              **
**                             K Atanassov - M0NKA 2014                            **
**                                                                                 **
**---------------------------------------------------------------------------------**
**                                                                                 **
**  File name:                                                                     **
**  Description:                                                                   **
**  Last Modified:                                                                 **
**  Licence:		GNU GPLv3                                                      **
************************************************************************************/
#ifndef __MCHF_BOARD_H
#define __MCHF_BOARD_H
#include "mchf_mcu.h"
// some special switches
//#define 	DEBUG_BUILD

#define alternate_NR
//#define debug_alternate_NR

#ifdef alternate_NR
#define NR_FFT_SIZE 128
#endif

#define USE_FREEDV //uncomment to use freedv instead of SNAP function
// #define DEBUG_FREEDV
// hardware specific switches
//#define HY28BHISPEED			true		// uncomment for using new HY28B in SPI with bus speed 50MHz instead of 25MHz

// #define USE_FREEDV_AND_SNAP // experimental!!!


#ifdef USE_FREEDV_AND_SNAP
  #define USE_SNAP
  #define USE_FREEDV
#endif


// use the STM32 internal RTC with an external quartz and
// M1 and F3 connected to PD14 and PD15 (D0 and D1 of LCD) instead of PC14 and PC15 (to which the 32768 Hz quartz has to be connected)
#define USE_RTC_LSE

#include "mchf_mcu.h"
// HW libs
#ifdef STM32F7
#include "stm32f7xx_hal_rcc.h"
#include "stm32f7xx_hal_gpio.h"
#include "stm32f7xx_hal_spi.h"
#include "stm32f7xx_hal_dma.h"
#include "stm32f7xx_hal_i2c.h"
#include "stm32f7xx_hal_i2s.h"
#include "stm32f7xx_hal_adc.h"
#include "stm32f7xx_hal_dac.h"
#include "stm32f7xx_hal_tim.h"
#include "stm32f7xx_hal_rtc.h"
#include "stm32f7xx_hal_pwr.h"
#include "stm32f7xx_hal_flash.h"
#include "core_cm7.h"
#else
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_i2c.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_dac.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_rtc.h"
#include "stm32f4xx_hal_pwr.h"
#include "stm32f4xx_hal_flash.h"
#include "core_cm4.h"
#endif

#include "freedv_api.h"

#include "mchf_types.h"
#include "audio_filter.h"
#include "ui_si570.h"
#include "ui_lcd_hy28.h"

#include "comp.h"
#include "dac.h"
//

#include "mchf_board_config.h"

// Buttons map structure
typedef struct ButtonMap
{
    GPIO_TypeDef 	*port;
    ushort			button;
    const char*     label;

} ButtonMap;

typedef struct
{
    const ButtonMap* map;
    uint32_t num;
} mchf_buttons_t;

// Button definitions
//
enum
{
    BUTTON_M2_PRESSED = 0,  // 0
    BUTTON_G3_PRESSED,  	// 1
    BUTTON_G2_PRESSED,  	// 2
    BUTTON_BNDM_PRESSED,    // 3
    BUTTON_G4_PRESSED,  	// 4
    BUTTON_M3_PRESSED,  	// 5
    BUTTON_STEPM_PRESSED,   // 6
    BUTTON_STEPP_PRESSED,   // 7
    BUTTON_M1_PRESSED,  	// 8
    BUTTON_F3_PRESSED,  	// 9 - Press and release handled in UiDriverProcessFunctionKeyClick()
    BUTTON_F1_PRESSED,  	// 10 - Press and release handled in UiDriverProcessFunctionKeyClick()
    BUTTON_F2_PRESSED,  	// 11 - Press and release handled in UiDriverProcessFunctionKeyClick()
    BUTTON_F4_PRESSED,  	// 12 - Press and release handled in UiDriverProcessFunctionKeyClick()
    BUTTON_BNDP_PRESSED,    // 13
    BUTTON_F5_PRESSED,  	// 14 - Press and release handled in UiDriverProcessFunctionKeyClick()
    BUTTON_G1_PRESSED,  	// 15
    BUTTON_POWER_PRESSED,   // 16 - Used for press and release
    TOUCHSCREEN_ACTIVE, 	// 17 - Touchscreen touched, needs to last entry before BUTTON_NUM,
    //      init code relies on this
    BUTTON_NUM // How many buttons we have defined
};

extern mchf_buttons_t  buttons;
extern const ButtonMap  bm_sets[2][BUTTON_NUM];

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#define POWER_BUTTON_HOLD_TIME	1000000

#define TRX_MODE_RX				0
#define TRX_MODE_TX				1

#define DEMOD_USB				0
#define DEMOD_LSB				1
#define DEMOD_CW				2
#define DEMOD_AM				3
#define	DEMOD_SAM				4
#define	DEMOD_FM				5
#define DEMOD_DIGI				6
#define DEMOD_MAX_MODE			6

// codec x demod
// analog USB LSB CW AM FM SAM
// FreeDV USB LSB -  -  -  -



#define RTC_OSC_FREQ			32768

#define	TCXO_OFF				0		// TXCO temperature compensation off
#define	TCXO_ON					1		// TCXO temperature compensation on
#define	TCXO_STOP				2		// Stop reading of temperature sensor
#define	TCXO_TEMP_STATE_MAX		2		// Maximum setting for TCXO setting state

// Transverter oscillator adds shift
#define		TRANSVT_FREQ_A	 	42000000

//
#define		MIN_FREQ_CAL		-999		// Minimum and maximum range of frequency calibration in 10xppm
#define		MAX_FREQ_CAL		999
//
// Total bands supported
//
#define	MIN_BANDS				0		// lowest band number
#define	MAX_BANDS				17		// Highest band number:  17 = General coverage (RX only) band
#define	MAX_BAND_NUM			(MAX_BANDS+1)		// Number of Bands

//  multiplier to convert between dial_freq and tune_freq
#define TUNE_MULT				4

#define	KHZ_MULT			(TUNE_MULT*1000)	// multiplier to convert oscillator frequency or band size to display kHz, used below
//
// Bands definition
// - ID
// - SI570 startup freq
// - size in Hz
//
#define	BAND_MODE_80			0
#define	BAND_FREQ_80			3500*KHZ_MULT		// 3500 kHz
#define	BAND_SIZE_80			500*KHZ_MULT		// 500 kHz in size (Region 2)
//
#define	BAND_MODE_60			1
#define	BAND_FREQ_60			5250*KHZ_MULT		// 5250 kHz
#define	BAND_SIZE_60			200*KHZ_MULT		// 200 kHz in size to allow different allocations
//
#define	BAND_MODE_40			2
#define	BAND_FREQ_40			7000*KHZ_MULT		// 7000 kHz
#define	BAND_SIZE_40			300*KHZ_MULT		// 300 kHz in size (Region 2)
//
#define	BAND_MODE_30			3
#define	BAND_FREQ_30			10100*KHZ_MULT		// 10100 kHz
#define	BAND_SIZE_30			50*KHZ_MULT		// 50 kHz in size
//
#define	BAND_MODE_20			4
#define	BAND_FREQ_20			14000*KHZ_MULT		// 14000 kHz
#define	BAND_SIZE_20			350*KHZ_MULT		// 350 kHz in size
//
#define	BAND_MODE_17			5
#define	BAND_FREQ_17			18068*KHZ_MULT		// 18068 kHz
#define	BAND_SIZE_17			100*KHZ_MULT		// 100 kHz in size
//
#define	BAND_MODE_15			6
#define	BAND_FREQ_15			21000*KHZ_MULT		// 21000 kHz
#define	BAND_SIZE_15			450*KHZ_MULT		// 450 kHz in size
//
#define	BAND_MODE_12			7
#define	BAND_FREQ_12			24890*KHZ_MULT		// 24890 kHz
#define	BAND_SIZE_12			100*KHZ_MULT		// 100 kHz in size
//
#define	BAND_MODE_10			8
#define	BAND_FREQ_10			28000*KHZ_MULT		// 28000 kHz
#define	BAND_SIZE_10			1700*KHZ_MULT		// 1700 kHz in size
//
#define	BAND_MODE_6			9
#define	BAND_FREQ_6			50000*KHZ_MULT		// 50000 kHz
#define	BAND_SIZE_6			2000*KHZ_MULT		// 2000 kHz in size (Region 2)
//
#define	BAND_MODE_4			10
#define	BAND_FREQ_4			70000*KHZ_MULT		// 70000 kHz
#define	BAND_SIZE_4			500*KHZ_MULT		// 500 kHz in size (Region 2)
//
#define	BAND_MODE_2			11
#define	BAND_FREQ_2			144000*KHZ_MULT		// 144000 kHz
#define	BAND_SIZE_2			2000*KHZ_MULT		// 2000 kHz in size (Region 1)
//
#define	BAND_MODE_70			12
#define	BAND_FREQ_70			430000*KHZ_MULT		// 430000 kHz
#define	BAND_SIZE_70			10000*KHZ_MULT		// 10000 kHz in size (Region 1)
//
#define	BAND_MODE_23			13
#define	BAND_FREQ_23			450000*KHZ_MULT		// 1240000 kHz
#define	BAND_SIZE_23			10000*KHZ_MULT		// 60000 kHz in size (Region 1)
//
#define	BAND_MODE_2200			14
#define	BAND_FREQ_2200			135.7*KHZ_MULT		// 135.7 kHz
#define	BAND_SIZE_2200			2.1*KHZ_MULT		// 2.1 kHz in size (Region 1)
//
#define	BAND_MODE_630			15
#define	BAND_FREQ_630			472*KHZ_MULT		// 472 kHz
#define	BAND_SIZE_630			7*KHZ_MULT		// 7 kHz in size (Region 1)
//
#define	BAND_MODE_160			16
#define	BAND_FREQ_160			1800*KHZ_MULT		// 1810 kHz
#define	BAND_SIZE_160			190*KHZ_MULT		// 190 kHz in size (Region 1)
//
#define	BAND_MODE_GEN			17			// General Coverage
#define	BAND_FREQ_GEN			10000*KHZ_MULT		// 10000 kHz
#define	BAND_SIZE_GEN			1*KHZ_MULT		// Dummy variable

//
//
//
//	Frequency limits for filters, in Hz, for bandpass filter selection - MODIFY AT YOUR OWN RISK!
//
#define	BAND_FILTER_UPPER_160		2500000				// Upper limit for 160 meter filter
//
#define	BAND_FILTER_UPPER_80		4250000				// Upper limit for 80 meter filter
//
#define	BAND_FILTER_UPPER_40		8000000				// Upper limit for 40/60 meter filter
//
#define	BAND_FILTER_UPPER_20		16000000			// Upper limit for 20/30 meter filter

#define	BAND_FILTER_UPPER_10		32000000			// Upper limit for 10 meter filter
//
#define	BAND_FILTER_UPPER_6		40000000			// Upper limit for 6 meter filter
//
#define	BAND_FILTER_UPPER_4		70000000			// Upper limit for 4 meter filter
//
#define	DEFAULT_FREQ_OFFSET		4000				// Amount of offset (at LO freq) when loading "default" frequency
//
// encoder one
typedef enum {
    ENC_ONE_MODE_AUDIO_GAIN	 = 0,
    ENC_ONE_MODE_ST_GAIN,
    ENC_ONE_NUM_MODES
} EncoderOneModes;
//
// encoder two
typedef enum {
    ENC_TWO_MODE_RF_GAIN =		0,
    ENC_TWO_MODE_SIG_PROC,
    ENC_TWO_MODE_NR,
    ENC_TWO_MODE_NOTCH_F,
    ENC_TWO_MODE_PEAK_F,
    ENC_TWO_MODE_BASS_GAIN,
    ENC_TWO_MODE_TREBLE_GAIN,
    ENC_TWO_NUM_MODES
} EncoderTwoModes;
//
// encoder three
typedef enum {
    ENC_THREE_MODE_RIT =			0,
    ENC_THREE_MODE_CW_SPEED,
    ENC_THREE_MAX_MODE
} EncoderThreeModes;

//
//
#define CW_MODE_IAM_B				0
#define CW_MODE_IAM_A				1
#define CW_MODE_STRAIGHT			2
#define CW_MODE_ULTIMATE			3
#define CW_MAX_MODE					3

// PA power level setting enumeration
typedef enum
{
    PA_LEVEL_FULL = 0,
    PA_LEVEL_5W,
    PA_LEVEL_2W,
    PA_LEVEL_1W,
    PA_LEVEL_0_5W,
    PA_LEVEL_TUNE_KEEP_CURRENT
} mchf_power_level_t;
//
#define	PA_LEVEL_DEFAULT		PA_LEVEL_2W		// Default power level

#define	US_DELAY			15  // 15 gives 1 uS delay in loop without optimization(O0)

#define	CW_SIDETONE_FREQ_DEFAULT	750	// Default CW Audio Sidetone and TX offset frequency
//
#define	CW_SIDETONE_FREQ_MIN		400
#define	CW_SIDETONE_FREQ_MAX		1000
//
#define	SSB_TUNE_FREQ			750	// Frequency at which the SSB TX IQ gain and phase adjustment is to be done
//
#define SSB_RX_DELAY			450	// Delay for switching when going from TX to RX (this is 0.66uS units)
//
#define	CW_RX_DELAY_MAX			50	// Maximum TX to RX turnaround setting
#define	CW_RX_DELAY_DEFAULT		8
//

// Audio sources for TX modulation
#define TX_AUDIO_MIC			0
#define TX_AUDIO_LINEIN_L		1
#define TX_AUDIO_LINEIN_R		2
#define TX_AUDIO_DIG			3
#define TX_AUDIO_DIGIQ			4
#define TX_AUDIO_MAX_ITEMS		4
#define TX_AUDIO_NUM			(TX_AUDIO_MAX_ITEMS +1)
//
#define	LINE_GAIN_MIN			3
#define	LINE_GAIN_MAX			31
#define	LINE_GAIN_DEFAULT		12		// Original fixed gain setting
//
#define	MIC_GAIN_MIN			2
#define	MIC_GAIN_MAX			99
#define	MIC_GAIN_DEFAULT		15		// Default value - close to original fixed setting
//
//
#define	TX_POWER_FACTOR_MIN		3		// Minimum power factor setting (3 = 0.03)
#define TX_POWER_FACTOR_MAX_INTERNAL 0.55 // we limit power factor  to 55 (.55) . This limit is independent of the possible scale factor 4 for the power factor
#define	TX_POWER_FACTOR_MAX		(TX_POWER_FACTOR_MAX_INTERNAL*400.0)		// Please keep in mind that this is only a setting value maximum. Depending on the flags this reduced by 4 before further use.
                                        //And the true maximum is defined above in TX_POWER_FACTOR_MAX_INTERNAL

//
// Default power factors for 5 watt and FULL settings in percent
// These power factors are based on the original fixed values
//
#define TX_POWER_FACTOR_80_DEFAULT	50
#define	TX_POWER_FACTOR_60_DEFAULT	20
#define	TX_POWER_FACTOR_40_DEFAULT	10
#define	TX_POWER_FACTOR_30_DEFAULT	13
#define	TX_POWER_FACTOR_20_DEFAULT	30
#define	TX_POWER_FACTOR_17_DEFAULT	40
#define	TX_POWER_FACTOR_15_DEFAULT	50
#define	TX_POWER_FACTOR_12_DEFAULT	75
#define	TX_POWER_FACTOR_10_DEFAULT	75
#define TX_POWER_FACTOR_6_DEFAULT	75
#define TX_POWER_FACTOR_4_DEFAULT	75
#define TX_POWER_FACTOR_2_DEFAULT	75
#define TX_POWER_FACTOR_70_DEFAULT	75
#define TX_POWER_FACTOR_23_DEFAULT	75
#define TX_POWER_FACTOR_2200_DEFAULT	50
#define TX_POWER_FACTOR_630_DEFAULT	50
#define TX_POWER_FACTOR_160_DEFAULT	50
//
// Enumeration of colours used in spectrum scope display
//
typedef enum
{
    SPEC_WHITE = 0,
    SPEC_GREY,
    SPEC_BLUE,
    SPEC_RED1,
    SPEC_RED2,
    SPEC_RED3,
    SPEC_MAGENTA,
    SPEC_GREEN,
    SPEC_CYAN,
    SPEC_YELLOW,
    SPEC_ORANGE,
    SPEC_CREAM,
    SPEC_BLACK,
    SPEC_GREY1,
    SPEC_GREY2,
    SPEC_GREY3,
    SPEC_GREY4,
    SPEC_GREY5,
    SPEC_GREY6,
    SPEC_MAX_COLOUR,
} mchf_color_t;

typedef struct {
    const uint32_t value;
    const char* name;
} ColorNameValue;

// this data structure needs to be in sync with the color definitions above
// otherwise strange colors may become visible in the UI.
extern const ColorNameValue MchfColor_Id2ValueName[SPEC_MAX_COLOUR];

// Enumeration of transmit meter modes
enum
{
    METER_SWR = 0,
    METER_AUDIO,
    METER_ALC,
    METER_MAX,
};
//
#define	BACKLIGHT_BLANK_TIMING_DEFAULT	8		// default number of SECONDS for backlight blanking
#define LCD_STARTUP_BLANKING_TIME	3000		// number of DECISECONDS (e.g. SECONDS * 100) after power-up before LCD blanking occurs if no buttons are pressed/knobs turned

#define FILT_DISPLAY_WIDTH      256     // width, in pixels, of the spectral display on the screen - this value used to calculate Hz/pixel for indicating width of filter



// Enumeration of transmit tune  modes
typedef enum
{
    TUNE_TONE_SINGLE = 0,
    TUNE_TONE_TWO,
    TUNE_TONE_MAX,
} TuneToneMode;


typedef struct Gain_s
{
    uint8_t value;
    uint8_t max;
    uint8_t value_old;
    float   active_value;
} Gain;

typedef enum {
    IQ_TRANS_OFF = 0,
    IQ_TRANS_ON,
    IQ_TRANS_NUM
} iq_trans_idx_t;


typedef struct {
    int32_t value[IQ_TRANS_NUM];
}
iq_balance_data_t;


//
// Bands tuning values - WORKING registers - used "live" during transceiver operation
// (May contain VFO A, B or "Memory" channel values)
//
struct vfo_reg_s
{
    uint32_t dial_value;
    uint32_t decod_mode;
//    uint32_t filter_mode;
};

typedef struct vfo_reg_s VfoReg;

struct band_regs_s
{
    VfoReg band[MAX_BANDS+1];
};
typedef struct band_regs_s BandRegs;

enum
{
    // VFO_WORK = 0
    VFO_A = 0,
    VFO_B,
    VFO_MAX
};
// Working register plus VFO A and VFO B registers.
extern BandRegs vfo[VFO_MAX];


// Transceiver state public structure
typedef struct TransceiverState
{
    // Sampling rate public flag
    ulong 	samp_rate;

    // Virtual pots public values
    short  	rit_value;

#define RX_AUDIO_SPKR 0
#define RX_AUDIO_DIG  1
    Gain    rx_gain[2]; //ts.rx_gain[RX_AUDIO_SPKR].value

    int 	rf_gain;			// RF gain control
    uint8_t lineout_gain;            // lineout gain to control lineout level


#define MAX_RF_CODEC_GAIN_VAL       9       // Maximum RF gain setting
#define DEFAULT_RF_CODEC_GAIN_VAL   9       // Default RF gain setting (9 = AUTO mode)
#define RF_CODEC_GAIN_AUTO   9       // Default RF gain setting (9 = AUTO mode)

    uchar	rf_codec_gain;		// gain for codec (A/D converter) in receive mode
    uchar 	nb_setting;
    uchar	st_gain;
    uchar	pa_bias;
    uchar	pa_cw_bias;

    // timer for muting of input into signal processing chains (TX/RX)
    uint16_t    audio_processor_input_mute_counter;
#define IQ_ADJUST_POINTS_NUM 4

    // corresponding frequencies are stored in const array iq_adjust_freq
#define IQ_80M 0
#define IQ_10M 1
#define IQ_20M 2

    iq_balance_data_t tx_iq_gain_balance[IQ_ADJUST_POINTS_NUM];  // setting for TX IQ gain balance
    iq_balance_data_t tx_iq_phase_balance[IQ_ADJUST_POINTS_NUM]; // setting for TX IQ phase balance
    iq_balance_data_t rx_iq_gain_balance[IQ_ADJUST_POINTS_NUM];  // setting for RX IQ gain balance
    iq_balance_data_t rx_iq_phase_balance[IQ_ADJUST_POINTS_NUM]; // setting for RX IQ phase balance

    iq_float_t tx_adj_gain_var[IQ_TRANS_NUM];    // active variables for adjusting tx gain balance
    iq_float_t rx_adj_gain_var;    // active variables for adjusting rx gain balance

    // Equalisation factor
    float32_t	tx_power_factor;

    int	freq_cal;				// frequency calibration

    // Frequency synthesizer
    ulong	tune_freq;			// main synthesizer frequency
    ulong	tune_freq_req;		// used to detect change of main synthesizer frequency

    // Transceiver calibration mode flag
    //uchar	calib_mode;

    // Transceiver menu mode variables
    uchar	menu_mode;		// TRUE if in menu mode
    int16_t	menu_item;		// Used to indicate specific menu item
    int		menu_var;		// Used to change specific menu item
    bool	menu_var_changed;	// TRUE if something changed in a menu and that an EEPROM save should be done!

    // Ham band public flag
    // index of bands table in Flash
    uchar 	band;
    bool	rx_temp_mute;
    uchar	filter_band;		// filter selection band:  1= 80, 2= 60/40, 3=30/20, 4=17/15/12/10 - used for selection of power detector coefficient selection.
    //
    // Receive/Transmit public flag
    uchar 	txrx_mode;

    // TX/RX IRQ lock, to prevent reentrance
    //uchar	txrx_lock;
    bool	ptt_req;
    bool tx_stop_req;


    // Demodulator mode public flag
    uchar 	dmod_mode;


    uchar 	enc_one_mode;
    uchar 	enc_two_mode;
    uchar 	enc_thr_mode;

    uchar	tx_meter_mode;				// meter mode

    // Audio filter ID
    // uchar	filter_id;
    //
    uint8_t   filter_select[AUDIO_FILTER_NUM];


#define FILTER_PATH_MEM_MAX 5
    uint16_t   filter_path_mem[FILTER_MODE_MAX][FILTER_PATH_MEM_MAX];

    uint16_t  filter_path;
    //

    uchar	filter_cw_wide_disable;		// TRUE if wide filters are disabled in CW mode
    uchar	filter_ssb_narrow_disable;	// TRUE if narrow filters are disabled in SSB modes
    //
    uint16_t	demod_mode_disable;			// TRUE if AM mode is to be disabled
#define DEMOD_AM_DISABLE    (0x0001)
#define DEMOD_CW_DISABLE    (0x0002)
#define DEMOD_DIGI_DISABLE  (0x0004)




    // AGC mode
    uchar	agc_mode;
    uchar	agc_custom_decay;

    uchar	max_rf_gain;

    // Eth to UI driver requests flag
    uchar	LcdRefreshReq;

    // Eth to UI public flag
    uchar	new_band;
    uchar	new_mode;
    uchar	new_digi_mode;

    // Current CW mode
    uchar	keyer_mode;
    uchar	keyer_speed;
    ulong	sidetone_freq;
    uchar	paddle_reverse;
    uchar	cw_rx_delay;
    ulong	audio_spkr_unmute_delay_count;

    uchar	power_level;

    uchar 	tx_audio_source;
    ulong	tx_mic_gain_mult;
    uchar	tx_gain[TX_AUDIO_NUM];
    int16_t	tx_comp_level;			// Used to hold compression level which is used to calculate other values for compression.  0 = manual.

    // Global tuning flag - in every demod mode
    uchar 	tune;

    uint16_t ee_init_stat;

    uchar	powering_down;

    // Spectrum Scope config - placed here since "sd." not defined at time of init

    uchar	scope_speed;	// update rate for spectrum scope

    uchar	spectrum_filter;	// strength of filter in spectrum scope

    uchar	scope_trace_colour;	// color of spectrum scope trace;
    uchar	scope_grid_colour;	// saved color of spectrum scope grid;
    ulong	scope_grid_colour_active;	// active color of spectrum scope grid;
    uchar	spectrum_centre_line_colour;	// color of center line of scope grid
    ulong	scope_centre_grid_colour_active;	// active colour of the spectrum scope center grid line
    uchar	spectrum_freqscale_colour;	// color of spectrum scope frequency scale
    uchar	scope_rescale_rate;	// rescale rate on the 'scope
    uchar	scope_agc_rate;		// agc rate on the 'scope
    uchar	spectrum_db_scale;	// db/Division scale setting on spectrum scope
    uchar	waterfall_speed;	// speed of update of the waterfall
    //
    bool	radio_config_menu_enable;	// TRUE if radio configuration menu is to be visible
    //
    uchar	xverter_mode;		// TRUE if transverter mode active
    ulong	xverter_offset;		// frequency offset for transverter (added to frequency display)

    bool	refresh_freq_disp;		// TRUE if frequency display display is to be refreshed
    //
    // Calibration factors for output power, in percent (100 = 1.00)
    //
#define ADJ_5W 0
#define ADJ_FULL_POWER 1
    uchar	pwr_adj[2][MAX_BAND_NUM];
    //
    ulong	alc_decay;					// adjustable ALC release time - EEPROM read/write version
    ulong	alc_decay_var;				// adjustable ALC release time - working variable version
    ulong	alc_tx_postfilt_gain;		// amount of gain after the TX audio filtering - EEPROM read/write version
    ulong	alc_tx_postfilt_gain_var;	// amount of gain after the TX audio filtering - working variable version
    //
#define FREQ_STEP_SWAP_BTN	0xf0
    uchar	freq_step_config;			// configuration of step size (line, step button reversal) - setting any of the 4 upper bits -> step button switch, any of the lower bits -> frequency marker display enabled

#define DSP_NR_ENABLE 	  		0x01	// DSP NR mode is on (| 1)
#define DSP_NR_POSTAGC_ENABLE 	0x02	// DSP NR is to occur post AGC (| 2)
#define DSP_NOTCH_ENABLE		0x04	// DSP Notch mode is on (| 4)
#define DSP_NB_ENABLE			0x08	// DSP is to be displayed on screen instead of NB (| 8)
#define DSP_MNOTCH_ENABLE		0x10	// Manual Notch enabled
#define DSP_MPEAK_ENABLE		0x20	// Manual Peak enabled

    uchar	dsp_active;					// Used to hold various aspects of DSP mode selection
    uchar	dsp_mode;					// holds the mode chosen in the DSP
	uchar	temp_nb;
    uchar 	digital_mode;				// holds actual digital mode
    uchar	dsp_active_toggle;			// holder used on the press-hold of button G2 to "remember" the previous setting
    uchar	dsp_nr_strength;			// "Strength" of DSP Noise reduction - to be converted to "Mu" factor
    ulong	dsp_nr_delaybuf_len;		// size of DSP noise reduction delay buffer
    uchar	dsp_nr_numtaps;				// Number of FFT taps on the DSP Noise reduction
    uchar	dsp_notch_numtaps;
    uchar	dsp_notch_mu;				// mu adjust of notch DSP LMS
    uint8_t	dsp_notch_delaybuf_len;		// size of DSP notch delay buffer
    uint8_t dsp_inhibit;				// if != 0, DSP (NR, Notch) functions are inhibited.  Used during power-up and switching


    uchar	lcd_backlight_brightness;	// LCD backlight brightness, 0-3:  0 = full, 3 = dimmest

#define LCD_BLANKING_ENABLE 0x80
#define LCD_BLANKING_TIMEMASK 0x0f
    uchar	lcd_backlight_blanking;		// for controlling backlight auto-off control
    //
    uchar	tune_step;					// Used for press-and-hold tune step adjustment
    ulong	tune_step_idx_holder;		// used to hold the original step size index during the press-and-hold
    //
    bool	frequency_lock;				// TRUE if frequency knob is locked
    //

#define TX_DISABLE_OFF          0
#define TX_DISABLE_ALWAYS       1
#define TX_DISABLE_USER         2
#define TX_DISABLE_OUTOFRANGE	4
    uchar	tx_disable;		// >0 if no transmit permitted, use RadioManagement_IsTxDisabled() to get boolean


    uint16_t	flags1;					// Used to hold individual status flags, stored in EEPROM location "EEPROM_FLAGS1"
#define FLAGS1_TX_AUTOSWITCH_UI_DISABLE 0x01    // if on-screen AFG/(STG/CMP) and WPM/(MIC/LIN) indicators are changed on TX
#define FLAGS1_SWAP_BAND_BTN			0x02    // if BAND-/BAND+ buttons are to be swapped in their positions
#define FLAGS1_MUTE_LINEOUT_TX			0x04    // if TX audio output from LINE OUT is to be muted during transmit (audio output only enabled when translate mode is DISABLED
#define FLAGS1_AM_TX_FILTER_DISABLE		0x08    // if AM TX has transmit filter DISABLED
#define FLAGS1_SWAP_FWDREV_SENSE		0x10    // if FWD/REV A/D inputs from RF power detectors are to be reversed
#define FLAGS1_FREQ_LIMIT_RELAX			0x20    // if Frequency tuning is to be relaxed
#define FLAGS1_SSB_TX_FILTER_DISABLE	0x40    // if SSB TX has transmit filter DISABLED
#define FLAGS1_WFALL_SCOPE_TOGGLE		0x80    // 0 = Spectrum Scope (analyzer), 1 = Waterfall display
#define FLAGS1_CAT_MODE_ACTIVE			0x100   // 0 = CAT is disabled, 1 = CAT is enabled
#define FLAGS1_DYN_TUNE_ENABLE			0x200   // 0 = dynamic tune is disabled, 1 = dynamic tune is enabled
#define FLAGS1_SAM_ENABLE				0x400   // 0 = SAM mode is disabled, 1 = SAM mode is enabled
#define FLAGS1_CAT_IN_SANDBOX			0x800   // 0 = CAT works on band storage, 1 = CAT works in sandbox
#define FLAGS1_SCOPE_LIGHT_ENABLE		0x1000  // 0 = Spectrum normal, 1 = Spectrum light
#define FLAGS1_TX_OUTSIDE_BANDS			0x2000  // 1 = TX outside bands enabled
#define FLAGS1_REVERSE_TOUCHSCREEN		0x4000  // 1 = X direcction of touchscreen is mirrored

    uint16_t	flags2;							// Used to hold individual status flags, stored in EEPROM location "EEPROM_FLAGS2"
#define FLAGS2_FM_MODE_ENABLE 			0x01    // 0 if FM mode is DISABLED, 1 if FM mode is ENABLED
#define FLAGS2_FM_MODE_DEVIATION_5KHZ 	0x02    // 0 if 2.5 kHz FM deviation, 1 for 5 kHz FM deviation
#define FLAGS2_KEY_BEEP_ENABLE 			0x04    // 1 if key/button beep is enabled
#define FLAGS2_LOW_BAND_BIAS_REDUCE 	0x08    // 1 if bias values for lower bands  below 8Mhz have lower influence factor
#define FLAGS2_FREQ_MEM_LIMIT_RELAX 	0x10    // 1 if memory-save versus frequency restrictions are to be relaxed
#define FLAGS2_HIGH_BAND_BIAS_REDUCE    0x40    // 1 if bias values for higher bands  above 8Mhz have lower influence factor

    uint32_t	sysclock;				// This counts up from zero when the unit is powered up at precisely 100 Hz over the long term.  This
    // is NEVER reset and is used for timing certain events.
    uint16_t	version_number_minor;		// version number - minor - used to hold version number and detect change
    uint16_t	version_number_major;		// version number - build - used to hold version number and detect change
    uint16_t	version_number_release;		// version number - release - used to hold version number and detect change
    uchar	nb_agc_time_const;			// used to calculate the AGC time constant
    uchar	cw_offset_mode;				// CW offset mode (USB, LSB, etc.)
    bool	cw_lsb;					// flag used to indicate that CW is to operate in LSB when TRUE
    uchar	iq_freq_mode;				// used to set/configure the I/Q frequency/conversion mode
    uchar	lsb_usb_auto_select;			// holds setting of LSB/USB auto-select above/below 10 MHz
    bool	conv_sine_flag;				// FALSE until the sine tables for the frequency conversion have been built (normally zero, force 0 to rebuild)
    ulong	last_tuning;				// this is a timer used to prevent too fast tuning per second
    ulong	lcd_blanking_time;			// this holds the system time after which the LCD is blanked - if blanking is enabled
    bool	lcd_blanking_flag;			// if TRUE, the LCD is blanked completely (e.g. backlight is off)
    bool	xvtr_adjust_flag;			// set TRUE if transverter offset adjustment is in process

#define VFO_MEM_MODE_SPLIT 0x80
#define VFO_MEM_MODE_VFO_B 0x40
    ulong	vfo_mem_mode;				// this is used to record the VFO/memory mode (0 = VFO "A" = backwards compatibility)
    // LSB+6 (0x40):  0 = VFO A, 1 = VFO B
    // LSB+7 (0x80): 0 = normal mode, 1 = Split mode (e.g. LSB=0:  RX=A, TX=B;  LSB=1:  RX=B, TX=A)
    ulong	voltmeter_calibrate;			// used to calibrate the voltmeter
    uchar	waterfall_color_scheme;			// stores waterfall color scheme
    uchar	waterfall_vert_step_size;		// vertical step size in waterfall mode
    int32_t	waterfall_offset;			// offset for waterfall display
    ulong	waterfall_contrast;			// contrast setting for waterfall display
    uchar	spectrum_scheduler;		// timer for scheduling the next update of the spectrum scope update, updated at DMA rate
    uchar	spectrum_scope_nosig_adjust;		// Adjustment for no signal adjustment conditions for spectrum scope
    uchar	waterfall_nosig_adjust;			// Adjustment for no signal adjustment conditions for waterfall
    uchar	spectrum_size;				// size of waterfall display (and other parameters) - size setting is in lower nybble, upper nybble/byte reserved
    uchar	fft_window_type;			// type of windowing function applied to scope/waterfall.  At the moment, only lower 4 bits are used - upper 4 bits are reserved
    bool	dvmode;					// TRUE if alternate (stripped-down) RX and TX functions (USB-only) are to be used
    uchar	txrx_switch_audio_muting_timing;			// timing value used for muting TX audio when keying PTT to suppress "click" or "thump"
    uint32_t	audio_dac_muting_timer;			// timer value used for muting TX audio when keying PTT to suppress "click" or "thump"
    uint32_t audio_dac_muting_buffer_count; // the audio dac out will be muted for number of buffers
    uchar	filter_disp_colour;			// used to hold the current color of the line that indicates the filter passband/bandwidth
    bool	audio_dac_muting_flag;			// when TRUE, audio is to be muted after PTT/keyup
    bool	vfo_mem_flag;				// when TRUE, memory mode is enabled
    bool	mem_disp;				// when TRUE, memory display is enabled
    bool	load_eeprom_defaults;			// when TRUE, load EEPROM defaults into RAM when "UiDriverLoadEepromValues()" is called - MUST be saved by user IF these are to take effect!
    ulong	fm_subaudible_tone_gen_select;		// lookup ("tone number") used to index the table tone generation (0 corresponds to "tone disabled")
    uchar	fm_tone_burst_mode;			// this is the setting for the tone burst generator
    ulong	fm_tone_burst_timing;			// this is used to time/schedule the duration of a tone burst
    uchar	fm_sql_threshold;			// squelch threshold "dial" setting
//	uchar	fm_rx_bandwidth;			// bandwidth setting for FM reception
    ulong	fm_subaudible_tone_det_select;		// lookup ("tone number") used to index the table for tone detection (0 corresponds to "disabled")
    bool	beep_active;				// TRUE if beep is active
    ulong	beep_frequency;				// beep frequency, in Hz
    ulong	beep_timing;				// used to time/schedule the duration of a keyboard beep
    uchar	beep_loudness;				// loudness of the keyboard/CW sidetone test beep
    bool	load_freq_mode_defaults;		// when TRUE, load frequency/mode defaults into RAM when "UiDriverLoadEepromValues()" is called - MUST be saved by user IF these are to take effect!

#define EEPROM_SER_NONE 0
#define EEPROM_SER_WRONG_SIG 1
#define EEPROM_SER_UNKNOWN 2
    uchar	ser_eeprom_type;			// serial eeprom type

#define SER_EEPROM_IN_USE_I2C         0x00
#define SER_EEPROM_IN_USE_ERROR       0x05
#define SER_EEPROM_IN_USE_TOO_SMALL   0x10
#define SER_EEPROM_IN_USE_DONT_SAVE   0x20
#define SER_EEPROM_IN_USE_RAMCACHE    0xAA
#define SER_EEPROM_IN_USE_NO          0xFF

    uchar	ser_eeprom_in_use;	    // use to determine non-volatile memory configuration

    mchf_touchscreen_t *tp;

    bool	show_tp_coordinates;	// show coordinates on LCD
    bool	rfmod_present;			// 0 = not present
    bool	vhfuhfmod_present;		// 0 = not present
    uchar	multi;					// actual translate factor
    uchar	tune_power_level;		// TX power in antenna tuning function
    uchar	power_temp;				// temporary tx power if tune is different from actual tx power
    uchar	cat_band_index;			// buffered bandindex before first CAT command arrived
    uchar	xlat;					// CAT <> IQ-Audio
    ulong	notch_frequency;		// frequency of the manual notch filter
    ulong	peak_frequency;			// frequency of the manual peak filter
    int		bass_gain;				// gain of the low shelf EQ filter
    int		treble_gain;			// gain of the high shelf EQ filter
    int		tx_bass_gain;			// gain of the TX low shelf EQ filter
    int		tx_treble_gain;			// gain of the TX high shelf EQ filter

    bool	AM_experiment;			// for AM demodulation experiments, not for "public" use
//    bool	dBm_Hz_Test;			// for testing only
//    ulong	dBm_count;				// timer for calculating RX dBm
    uchar 	display_dbm;			// display dbm or dbm/Hz or OFF
    uchar	s_meter;				// defines S-Meter style/configuration
	uint8_t	meter_colour_up;
	uint8_t	meter_colour_down;
	uchar   iq_auto_correction;     // switch variable for automatic IQ correction
	bool	display_rx_iq;
	uint8_t twinpeaks_tested;
	uint8_t agc_wdsp;
	uint8_t agc_wdsp_mode;
	uint8_t agc_wdsp_slope;
	uint8_t agc_wdsp_hang_enable;
	int     agc_wdsp_thresh;
	int     agc_wdsp_hang_thresh;
	int agc_wdsp_hang_time;
	uint8_t agc_wdsp_action;
	uint8_t agc_wdsp_switch_mode;
	uint8_t agc_wdsp_hang_action;
	int dbm_constant;
	int agc_wdsp_tau_decay[6];
	int agc_wdsp_tau_hang_decay;

#define DISPLAY_S_METER_STD   0
#define DISPLAY_S_METER_DBM   1
#define DISPLAY_S_METER_DBMHZ 2

//    #define TX_FILTER_NONE			0
    #define TX_FILTER_SOPRANO		1
    #define TX_FILTER_TENOR			2
    #define TX_FILTER_BASS			3
    uchar	tx_filter;				// which TX filter has been chosen?


    mchf_display_t*     display;

    uint32_t audio_int_counter;		// used for encoder timing - test DL2FW
    bool encoder3state;
    int bc_band;
    uchar c_line;					// position of center line

    Si570_ResultCodes last_lo_result;			// used in dynamic tuning to hold frequency color

    TuneToneMode tune_tone_mode;

	uint16_t ramsize; // in KB, this is used to distinguish  between 192 and 256 kB models.

	uint8_t stream_tx_audio; // send tx audio via usb back
#define STREAM_TX_AUDIO_OFF     0  // send nothing
#define STREAM_TX_AUDIO_SRC     1  // send source audio stream (from CODEC)
#define STREAM_TX_AUDIO_FILT    2  // send processed audio stream (after filtering)
#define STREAM_TX_AUDIO_DIGIQ   3  // send final IQ signal
#define STREAM_TX_AUDIO_NUM   4  // how many choices

	// Freedv Test DL2FW
	bool	FDV_TX_encode_ready;
	int	FDV_TX_samples_ready;
	uint16_t FDV_TX_out_start_pt;
	uint16_t FDV_TX_in_start_pt;

    bool    digi_lsb;                 // flag used to indicate that mcHF is to operate in LSB when TRUE

    bool dial_moved; // dial was moved, used to communicate with spectrum display code


    uint32_t i2c_speed[2]; // store comm speed for the 2 I2C buses
#define I2C_BUS_1 0
#define I2C_BUS_2 1


    bool rtc_present; // a supported rtc was found and is active
    int16_t rtc_calib; // ppm variation value, unit 1 ppm
    bool vbat_present; // we detected a working vbat mod
    bool codec_present; // we detected a working codec
	bool new_nb; // new noise blanker
} TransceiverState;
//
extern __IO TransceiverState ts;

//DL2FW UGLY test for FREEDV - some globals :-(

#define FDV_BUFFER_SIZE     320
#define FDV_RX_AUDIO_SIZE_MAX     360

// this is kind of variable unfortunately, see freedv_api.h/.c for FREEDV1600 it is 360
#define FDV_BUFFER_AUDIO_NUM   3
#define FDV_BUFFER_IQ_NUM  3

typedef struct {
    int16_t samples[FDV_BUFFER_SIZE]; // this is kind of variable unfortunately, see freedv_api.h/.c for FREEDV1600 it is 360
}  FDV_Audio_Buffer;

typedef struct {
   COMP samples[FDV_BUFFER_SIZE];
}  FDV_IQ_Buffer;


extern struct freedv *f_FREEDV;
extern FDV_Audio_Buffer fdv_audio_buff[FDV_BUFFER_AUDIO_NUM];
extern FDV_IQ_Buffer fdv_iq_buff[FDV_BUFFER_IQ_NUM];


//end DL2FW UGLY test for FREEDV - some globals :-(

#define	POWERDOWN_DELAY_COUNT	30	// Delay in main service loop for the "last second" before power-down - to allow EEPROM write to complete

//#define CODEC_USE_SPI

#define DEBUG_COM                        USART1

/**
 * @brief Introduces about 40ms of delay (load dependent, since interrupt eats some of the time.
 */
// TODO: Measure raw time for this loop

#define non_os_delay()						\
do {							\
  register unsigned int i;				\
  for (i = 0; i < 1000000; ++i)				\
    __asm__ __volatile__ ("nop\n\t":::"memory");	\
} while (0)

/**
 * @brief Introduces about 400ms of delay (load dependent, since interrupt eats some of the time.
 */
// TODO: Measure raw time for this loop
#define non_os_delay_a()						\
do {							\
  register unsigned int i;				\
  for (i = 0; i < 10000000; ++i)				\
    __asm__ __volatile__ ("nop\n\t":::"memory");	\
} while (0)

/**
 * @brief Introduces about (count * 400ms) of delay (load dependent, since interrupt eats some of the time.
 */
// TODO: Measure raw time for this loop
#define non_os_delay_multi(count)                        \
{ int idx; for (idx = 0; idx < count; idx++) {                            \
  register unsigned int i;              \
  for (i = 0; i < 10000000; ++i)                \
    __asm__ __volatile__ ("nop\n\t":::"memory");    \
} }



// ------------------------------------------------------------------
// Exports
typedef enum {
    LED_STATE_OFF = 0,
    LED_STATE_ON = 1,
    LED_STATE_TOGGLE = 2
} ledstate_t;

inline void MchfBoard_GreenLed(ledstate_t state)
{
    switch(state)
    {
    case LED_STATE_ON:
        GPIO_SetBits(GREEN_LED_PIO, GREEN_LED);
        break;
    case LED_STATE_OFF:
        GPIO_ResetBits(GREEN_LED_PIO, GREEN_LED);
        break;
    default:
        GPIO_ToggleBits(GREEN_LED_PIO, GREEN_LED);
        break;
    }
}

inline void MchfBoard_RedLed(ledstate_t state)
{
    switch(state)
    {
    case LED_STATE_ON:
        GPIO_SetBits(RED_LED_PIO, RED_LED);
        break;
    case LED_STATE_OFF:
        GPIO_ResetBits(RED_LED_PIO, RED_LED);
        break;
    default:
        GPIO_ToggleBits(RED_LED_PIO, RED_LED);
        break;
    }
}

#ifdef STM32F7
inline void MchfBoard_BlueLed(ledstate_t state)
{
    switch(state)
    {
    case LED_STATE_ON:
        GPIO_SetBits(BLUE_LED_PIO, BLUE_LED);
        break;
    case LED_STATE_OFF:
        GPIO_ResetBits(BLUE_LED_PIO, BLUE_LED);
        break;
    default:
        GPIO_ToggleBits(BLUE_LED_PIO, BLUE_LED);
        break;
    }
}
#endif
/**
 * @brief sets the hw ptt line and by this switches the mcHF board signal path between rx and tx configuration
 * @param tx_enable true == TX Paths, false == RX Paths
 */
inline void MchfBoard_EnableTXSignalPath(bool tx_enable)
{
    // to make switching as noiseless as possible, make sure the codec lineout is muted/produces zero output before switching
    if (tx_enable)
    {
        GPIO_SetBits(PTT_CNTR_PIO,PTT_CNTR);     // TX on and switch CODEC audio paths
        // Antenna Direction Output
        // BPF Direction Output (U1,U2)
        // PTT Optocoupler LED On (ACC Port) (U6)
        // QSD Mixer Output Disable (U15)
        // QSE Mixer Output Enable (U17)
        // Codec LineIn comes from mcHF LineIn Socket (U3)
        // Codec LineOut connected to QSE mixer (IQ Out) (U3a)
    }
    else
    {
        GPIO_ResetBits(PTT_CNTR_PIO,PTT_CNTR); // TX off
        // Antenna Direction Input
        // BPF Direction Input (U1,U2)
        // PTT Optocoupler LED Off (ACC Port) (U6)
        // QSD Mixer Output Enable (U15)
        // QSE Mixer Output Disable (U17)
        // Codec LineIn comes from RF Board QSD mixer (IQ In) (U3)
        // Codec LineOut disconnected from QSE mixer  (IQ Out) (U3a)
    }
}

/**
 * @brief set PA bias at the LM2931CDG (U18) using DAC Channel 2
 */
inline void MchfBoard_SetPaBiasValue(uint16_t bias)
{
    // Set DAC Channel 1 DHR12L register
    // DAC_SetChannel2Data(DAC_Align_8b_R,bias);
    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_8B_R, bias);

}

void MchfBoard_HandlePowerDown();

void MchfBoard_SelectLpfBpf(uint8_t group);

void mchf_board_init(void);
void mchf_board_post_init(void);
void mchf_reboot();
void mchf_powerdown();


/**
 * Is the hardware contact named DAH pressed
 */
inline bool mchf_ptt_dah_line_pressed() {
    return  !HAL_GPIO_ReadPin(PADDLE_DAH_PIO,PADDLE_DAH);
}

/**
 * Is the hardware contact named DIT pressed
 */
inline bool mchf_dit_line_pressed() {
    return  !HAL_GPIO_ReadPin(PADDLE_DIT_PIO,PADDLE_DIT);
}

unsigned int mchf_board_get_ramsize();
void mchf_board_detect_ramsize();
void mchf_board_touchscreen_init();

// in main.c
void CriticalError(ulong error);

bool is_vfo_b();

inline bool is_ssb_tx_filter_enabled() {
	return (ts.tx_filter != 0);
	//    return (ts.flags1 & FLAGS1_SSB_TX_FILTER_DISABLE) == false;
}

inline bool is_ssb(const uint32_t dmod_mode) {
    return (dmod_mode == DEMOD_LSB || dmod_mode == DEMOD_USB);
}

inline bool is_splitmode()
{
    return (ts.vfo_mem_mode & VFO_MEM_MODE_SPLIT) != 0;
}


#define STM32_GetRevision()     (*(uint16_t *) (UID_BASE + 2))
#define STM32_GetSignature()    ((*(uint16_t *) (DBGMCU_BASE)) & 0x0FFF)
#define STM32_GetFlashSize()    (*(uint16_t *) (FLASHSIZE_BASE))
#define STM32_UUID ((uint32_t *)UID_BASE)


#endif
