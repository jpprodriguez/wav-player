/*-----------------------------------------------------------------------*/
/* MMCv3/SDv1/SDv2 (in SPI mode) control module  (C)ChaN, 2007           */
/*-----------------------------------------------------------------------*/
/* Only rcvr_spi(), xmit_spi(), disk_timerproc() and some macros         */
/* are platform dependent.                                               */
/*-----------------------------------------------------------------------*/


#include "lpc17xx_ssp.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "diskio.h"

/* Pins */
#define SSELPIN		6
#define SSELPORT	0
#define CARDDETECTPIN	11
#define CARDDETECTPORT  2

/* Definitions for MMC/SDC command */
#define CMD0	(0x40+0)	/* GO_IDLE_STATE */
#define CMD1	(0x40+1)	/* SEND_OP_COND (MMC) */
#define	ACMD41	(0xC0+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(0x40+8)	/* SEND_IF_COND */
#define CMD9	(0x40+9)	/* SEND_CSD */
#define CMD10	(0x40+10)	/* SEND_CID */
#define CMD12	(0x40+12)	/* STOP_TRANSMISSION */
#define ACMD13	(0xC0+13)	/* SD_STATUS (SDC) */
#define CMD16	(0x40+16)	/* SET_BLOCKLEN */
#define CMD17	(0x40+17)	/* READ_SINGLE_BLOCK */
#define CMD18	(0x40+18)	/* READ_MULTIPLE_BLOCK */
#define CMD23	(0x40+23)	/* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	(0xC0+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(0x40+24)	/* WRITE_BLOCK */
#define CMD25	(0x40+25)	/* WRITE_MULTIPLE_BLOCK */
#define CMD55	(0x40+55)	/* APP_CMD */
#define CMD58	(0x40+58)	/* READ_OCR */

/* Card type flags (CardType) */
#define CT_MMC				0x01	/* MMC ver 3 */
#define CT_SD1				0x02	/* SD ver 1 */
#define CT_SD2				0x04	/* SD ver 2 */
#define CT_SDC				(CT_SD1|CT_SD2)	/* SD */
#define CT_BLOCK			0x08	/* Block addressing */

/* Port Controls  (Platform dependent) */
#define CS_LOW()    GPIO_ClearValue( SSELPORT, 1<<SSELPIN )
#define CS_HIGH()   GPIO_SetValue(SSELPORT, 1<<SSELPIN)

/* Speed control macros */
#define	FCLK_SLOW()		LPC_SSP1->CPSR = 0xFA					/* Set slow clock (100k-400k) */
#define	FCLK_FAST()		LPC_SSP1->CPSR = 0x04					/* Set fast clock (depends on the CSD) */

/* SD/MMC function prototypes */
DSTATUS SDMMC_disk_initialize (BYTE drv);
DSTATUS SDMMC_disk_status (BYTE drv);
DRESULT SDMMC_disk_read (BYTE drv,BYTE *buff,DWORD sector,BYTE count);
DRESULT SDMMC_disk_write (BYTE drv,	const BYTE *buff,DWORD sector,BYTE count);
DRESULT SDMMC_disk_ioctl (BYTE drv,BYTE ctrl,void *buff);

void disk_timerproc (void);
