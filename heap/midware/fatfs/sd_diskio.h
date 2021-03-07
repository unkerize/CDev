//******************************************************************************
//
//******************************************************************************
#ifndef __SD_DISKIO_H
#define __SD_DISKIO_H

#ifdef __cplusplus
 extern "C" {
#endif
//******************************************************************************
// Assign pins for SD IO
//******************************************************************************
#define SD_CS_LOW()  pin_clr(GPIOB,12)
#define SD_CS_HIGH() pin_set(GPIOB,12)

//#define _SD_USE_DETECT              // define for use SD detection

#ifdef _SD_USE_DETECT
#define SD_DETECT() ( pin_read(GPIOA,1) == 0 )
#endif

//******************************************************************************
extern Diskio_drvTypeDef  SD_Driver;


//******************************************************************************
#define MSD_OK         0x00
#define MSD_ERROR      0x01


typedef enum
{
  SD_RESPONSE_NO_ERROR      = (0x00),
  SD_IN_IDLE_STATE          = (0x01),
  SD_ERASE_RESET            = (0x02),
  SD_ILLEGAL_COMMAND        = (0x04),
  SD_COM_CRC_ERROR          = (0x08),
  SD_ERASE_SEQUENCE_ERROR   = (0x10),
  SD_ADDRESS_ERROR          = (0x20),
  SD_PARAMETER_ERROR        = (0x40),
  SD_RESPONSE_FAILURE       = (0xFF),

  SD_DATA_OK                = (0x05),
  SD_DATA_CRC_ERROR         = (0x0B),
  SD_DATA_WRITE_ERROR       = (0x0D),
  SD_DATA_OTHER_ERROR       = (0xFF)
}SD_Info;

typedef struct
{
  __IO uint8_t  CSDStruct;            /* CSD structure */
  __IO uint8_t  SysSpecVersion;       /* System specification version */
  __IO uint8_t  Reserved1;            /* Reserved */
  __IO uint8_t  TAAC;                 /* Data read access-time 1 */
  __IO uint8_t  NSAC;                 /* Data read access-time 2 in CLK cycles */
  __IO uint8_t  MaxBusClkFrec;        /* Max. bus clock frequency */
  __IO uint16_t CardComdClasses;      /* Card command classes */
  __IO uint8_t  RdBlockLen;           /* Max. read data block length */
  __IO uint8_t  PartBlockRead;        /* Partial blocks for read allowed */
  __IO uint8_t  WrBlockMisalign;      /* Write block misalignment */
  __IO uint8_t  RdBlockMisalign;      /* Read block misalignment */
  __IO uint8_t  DSRImpl;              /* DSR implemented */
  __IO uint8_t  Reserved2;            /* Reserved */
  __IO uint32_t DeviceSize;           /* Device Size */
  __IO uint8_t  MaxRdCurrentVDDMin;   /* Max. read current @ VDD min */
  __IO uint8_t  MaxRdCurrentVDDMax;   /* Max. read current @ VDD max */
  __IO uint8_t  MaxWrCurrentVDDMin;   /* Max. write current @ VDD min */
  __IO uint8_t  MaxWrCurrentVDDMax;   /* Max. write current @ VDD max */
  __IO uint8_t  DeviceSizeMul;        /* Device size multiplier */
  __IO uint8_t  EraseGrSize;          /* Erase group size */
  __IO uint8_t  EraseGrMul;           /* Erase group size multiplier */
  __IO uint8_t  WrProtectGrSize;      /* Write protect group size */
  __IO uint8_t  WrProtectGrEnable;    /* Write protect group enable */
  __IO uint8_t  ManDeflECC;           /* Manufacturer default ECC */
  __IO uint8_t  WrSpeedFact;          /* Write speed factor */
  __IO uint8_t  MaxWrBlockLen;        /* Max. write data block length */
  __IO uint8_t  WriteBlockPaPartial;  /* Partial blocks for write allowed */
  __IO uint8_t  Reserved3;            /* Reserded */
  __IO uint8_t  ContentProtectAppli;  /* Content protection application */
  __IO uint8_t  FileFormatGrouop;     /* File format group */
  __IO uint8_t  CopyFlag;             /* Copy flag (OTP) */
  __IO uint8_t  PermWrProtect;        /* Permanent write protection */
  __IO uint8_t  TempWrProtect;        /* Temporary write protection */
  __IO uint8_t  FileFormat;           /* File Format */
  __IO uint8_t  ECC;                  /* ECC code */
  __IO uint8_t  CSD_CRC;              /* CSD CRC */
  __IO uint8_t  Reserved4;            /* always 1*/
} SD_CSD;

typedef struct
{
  __IO uint8_t  ManufacturerID;       /* ManufacturerID */
  __IO uint16_t OEM_AppliID;          /* OEM/Application ID */
  __IO uint32_t ProdName1;            /* Product Name part1 */
  __IO uint8_t  ProdName2;            /* Product Name part2*/
  __IO uint8_t  ProdRev;              /* Product Revision */
  __IO uint32_t ProdSN;               /* Product Serial Number */
  __IO uint8_t  Reserved1;            /* Reserved1 */
  __IO uint16_t ManufactDate;         /* Manufacturing Date */
  __IO uint8_t  CID_CRC;              /* CID CRC */
  __IO uint8_t  Reserved2;            /* always 1 */
} SD_CID;

typedef struct
{
  SD_CSD Csd;
  SD_CID Cid;
  uint32_t CardCapacity;  /* Card Capacity */
  uint32_t CardBlockSize; /* Card Block Size */
} SD_CardInfo;

#define SD_BLOCK_SIZE    0x200

#define SD_START_DATA_SINGLE_BLOCK_READ    0xFE  /* Data token start byte, Start Single Block Read */
#define SD_START_DATA_MULTIPLE_BLOCK_READ  0xFE  /* Data token start byte, Start Multiple Block Read */
#define SD_START_DATA_SINGLE_BLOCK_WRITE   0xFE  /* Data token start byte, Start Single Block Write */
#define SD_START_DATA_MULTIPLE_BLOCK_WRITE 0xFD  /* Data token start byte, Start Multiple Block Write */
#define SD_STOP_DATA_MULTIPLE_BLOCK_WRITE  0xFD  /* Data toke stop byte, Stop Multiple Block Write */

#define SD_PRESENT               ((uint8_t)0x01)
#define SD_NOT_PRESENT           ((uint8_t)0x00)

#define SD_CMD_GO_IDLE_STATE          0   /* CMD0 = 0x40 */
#define SD_CMD_SEND_OP_COND           1   /* CMD1 = 0x41 */
#define SD_CMD_SEND_CSD               9   /* CMD9 = 0x49 */
#define SD_CMD_SEND_CID               10  /* CMD10 = 0x4A */
#define SD_CMD_STOP_TRANSMISSION      12  /* CMD12 = 0x4C */
#define SD_CMD_SEND_STATUS            13  /* CMD13 = 0x4D */
#define SD_CMD_SET_BLOCKLEN           16  /* CMD16 = 0x50 */
#define SD_CMD_READ_SINGLE_BLOCK      17  /* CMD17 = 0x51 */
#define SD_CMD_READ_MULT_BLOCK        18  /* CMD18 = 0x52 */
#define SD_CMD_SET_BLOCK_COUNT        23  /* CMD23 = 0x57 */
#define SD_CMD_WRITE_SINGLE_BLOCK     24  /* CMD24 = 0x58 */
#define SD_CMD_WRITE_MULT_BLOCK       25  /* CMD25 = 0x59 */
#define SD_CMD_PROG_CSD               27  /* CMD27 = 0x5B */
#define SD_CMD_SET_WRITE_PROT         28  /* CMD28 = 0x5C */
#define SD_CMD_CLR_WRITE_PROT         29  /* CMD29 = 0x5D */
#define SD_CMD_SEND_WRITE_PROT        30  /* CMD30 = 0x5E */
#define SD_CMD_SD_ERASE_GRP_START     32  /* CMD32 = 0x60 */
#define SD_CMD_SD_ERASE_GRP_END       33  /* CMD33 = 0x61 */
#define SD_CMD_UNTAG_SECTOR           34  /* CMD34 = 0x62 */
#define SD_CMD_ERASE_GRP_START        35  /* CMD35 = 0x63 */
#define SD_CMD_ERASE_GRP_END          36  /* CMD36 = 0x64 */
#define SD_CMD_UNTAG_ERASE_GROUP      37  /* CMD37 = 0x65 */
#define SD_CMD_ERASE                  38  /* CMD38 = 0x66 */

#define _SD_SPI_BR spioBR2

void fat_set_rts(uint8_t rtsh);


#ifdef __cplusplus
}
#endif


#endif /* __SD_DISKIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
