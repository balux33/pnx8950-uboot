/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * This file contains the configuration parameters for the pollin stb810 board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_MIPS32		1	/* MIPS32 CPU core	*/
#define CONFIG_MIPS_CPU_PR4450	1	/* Philips PR4450 implementation */
#define CONFIG_SYS_MIPS_CACHE_MODE CONF_CM_UNCACHED	/* run uncached, slow as hell, but natsemi breaks otherwise */

#ifdef CONFIG_POLLINUX_FLASHER
#  define CONFIG_BOOTDELAY	-1	/* autoboot after 2 seconds	*/
#else
#  define CONFIG_BOOTDELAY 2
#endif

#define CONFIG_BAUDRATE		38400

/* valid baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 50, 75, 110, 134.5, 150, 300, 600, 1200, 2400, \
				  	  4800, 9600, 19200, 38400, 57600, 115200, 230400 }

#define	CONFIG_TIMESTAMP		/* Print image info with timestamp */
#define	CONFIG_BOOTARGS			\
	"console=ttyS0,38400n8 "		\
	"panic=15 "		\
	""

#ifndef CONFIG_POLLINUX_FLASHER
#  define	CONFIG_EXTRA_ENV_SETTINGS					\
	"la=80100000\0"								\
	"ld=loadb $(la);sleep 5;go $(la)\0"					\
	"rootpath=/pollinux/nandfs\0"						\
	"loadaddr=0x82000000\0"							\
	""									\
	"nfsargs=setenv bootargs $(bootargs) root=/dev/nfs rw "			\
		"nfsroot=$(serverip):$(rootpath)\0"				\
	"ideargs=setenv bootargs $(bootargs) root=$(rootdev) rw\0"		\
	"addip=setenv bootargs $(bootargs) ip=$(ipaddr)\0"			\
	"nfsboot=nfs \"$(serverip):$(bootfile)\";"				\
		"run nfsargs addip;bootm\0"					\
	"ideboot=sata init;ext2load sata 0:1 $(loadaddr) $(bootfile);"		\
		"run ideargs addip;bootm\0"					\
	"bootcmd=run ideboot\0" \
	"nandboot=nboot Linux;run ideargs addip;bootm\0" \
	"poweroff=mw.l bbf04010 10000000;mw.l bbf04010 10001000\0" \
	""

#else
#  define CONFIG_EXTRA_ENV_SETTINGS					\
	"loadaddr=0x82000000\0"							\
	""
#endif

/* Boot from NFS root */
#define CONFIG_BOOTCOMMAND	"run nfsboot"

/*-----------------------------------------------------------------------
 * Miscellaneous configurable options
 */
#ifdef CONFIG_POLLINUX_FLASHER
#  undef CONFIG_SYS_LONGHELP
#  define CONFIG_SYS_PROMPT			"flasher# "
#else
#  define CONFIG_SYS_LONGHELP				/* undef to save memory      */
#  define CONFIG_SYS_PROMPT			"# "	/* Monitor Command Prompt    */
#endif
#define CONFIG_CMDLINE_EDITING			1
#define	CONFIG_SYS_CBSIZE			256		/* Console I/O Buffer Size   */
#define	CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)  /* Print Buffer Size */
#define	CONFIG_SYS_MAXARGS			16		/* max number of command args*/

#define CONFIG_SYS_MALLOC_LEN		(1024*1024)

#define CONFIG_SYS_BOOTPARAMS_LEN	(128*1024)

#define CONFIG_SYS_MIPS_TIMER_FREQ	250000000
#define CONFIG_SYS_HZ				1000

#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_MONITOR_LEN		(192 << 10)		/* No more then 192KiB */
#define CONFIG_ENV_ADDR				0x80004000

#define CONFIG_SYS_INIT_SP_OFFSET	0x00400000

#define CONFIG_SYS_SDRAM_BASE		0x80000000	/* Cached addr */
#define	CONFIG_SYS_LOAD_ADDR		0x82000000	/* default load address	*/
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		0x87000000

/*-----------------------------------------------------------------------
 * Flash and environment organization
 */
#define CONFIG_NAND_PNX8550
#define CONFIG_NAND_DETECT
#define CONFIG_NAND_BBT

#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_MTD_DEBUG
#define CONFIG_MTD_DEBUG_VERBOSE MTD_DEBUG_LEVEL0

/* MTD partitions (not usable with the elecard kernel */
#define MTDIDS_DEFAULT		"nand0=nxp-0"
#define MTDPARTS_DEFAULT	"mtdparts=nxp-0:" 		\
								"16k(FlashReader)ro,"	\
								"512k(U-Boot)ro,"		\
								"32k(Env),"			\
								"32k(bbt),"			\
								"6576k(Linux),"		\
								"53M(ROMFS),"		\
								"4080k@0x3c00000(WinCE)ro,"	\
								"16k(info)ro"		\
								""

/* JFFS2 */
#define CONFIG_JFFS2_NAND			1
#define NAND_CACHE_PAGES			16
#define CONFIG_JFFS2_PART_SIZE			0x03300000
#define CONFIG_JFFS2_PART_OFFSET		0x00894000

#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		0xB0000000

#define CONFIG_SYS_NO_FLASH
#define CONFIG_ENV_IS_IN_NAND		1
#define CONFIG_ENV_OFFSET			0x84000			// Env1 offset
#define CONFIG_ENV_OFFSET_REDUND	0x88000			// Env2 offset
#define CONFIG_SYS_ENV_SECT_SIZE	0x04000			// 16 KB
#define CONFIG_ENV_SIZE				0x01000			// 4KB


/*-----------------------------------------------------------------------
 * Serial configuration
 */
#define CONFIG_IP0107_SERIAL			/* Has an IP0107 on SoC */
#define CONFIG_SERIAL_PORT_1	IP0107_1
#define CONFIG_SERIAL_PORT_2	IP0107_2
#define CONFIG_SERIAL_PORT_3	IP0107_3
#define CONFIG_CONSOLE_PORT	CONFIG_SERIAL_PORT_1
#define CONFIG_IP0107_CLOCK	3692300


/*-----------------------------------------------------------------------
 * USB configuration
 */
#if 0
#define CONFIG_CMD_USB

#define CONFIG_USB_OHCI_NEW
#define CONFIG_SYS_USB_OHCI_MAX_ROOT_PORTS	15
#define CONFIG_PCI_OHCI
#define CONFIG_PCI_EHCI_DEVNO			0
#define CONFIG_SYS_USB_OHCI_SLOT_NAME		"ohci_pci"
#endif

/*-----------------------------------------------------------------------
 * PCI configuration
 */
#define	CONFIG_PCI
#define CONFIG_PCI_PNP
#undef	CONFIG_PCI_SCAN_SHOW
#define	CONFIG_IPA051_PCIXIO

/*-----------------------------------------------------------------------
 * SATA configuration
 */
#ifndef CONFIG_POLLINUX_FLASHER
#  define CONFIG_SATA_SIL3512
#  define CONFIG_SYS_SATA_MAX_DEVICE	2
#  define CONFIG_LIBATA
#  define CONFIG_LBA48
#  define CONFIG_DOS_PARTITION
#endif

/*-----------------------------------------------------------------------
 * Network configuration
 */
#ifndef CONFIG_POLLINUX_FLASHER
#  define CONFIG_NATSEMI
#  define CONFIG_MII
#  define CONFIG_NET_MULTI

#  define CONFIG_PREBOOT	"echo;echo Welcome to the pollinux board v1.1;echo"
#  define CONFIG_IPADDR		192.168.1.15
#  define CONFIG_ETHADDR		00:00:00:00:00:00
#  define CONFIG_SERVERIP		192.168.1.16
#  define CONFIG_NETMASK		255.255.255.0
#  define CONFIG_HOSTNAME		pollinux
#  define CONFIG_BOOTFILE		/boot/linux
#endif

/*-----------------------------------------------------------------------
 * I2C Configuration
 */
#if 0
#define CONFIG_HARD_I2C			/* To enable I2C support	*/
#define CONFIG_NXP_I2C
#define CONFIG_NXP_I2C_IP0105
#define CONFIG_NXP_I2C_IP3203
#define CONFIG_SYS_I2C_SPEED		(150000)	/* I2C speed and slave address	*/
#define CONFIG_SYS_I2C_SLAVE		0
#define CONFIG_SYS_EEPROM_ADDR_LEN	1
#define CONFIG_I2C_CMD_TREE
#define CONFIG_I2C_MULTI_BUS
#endif

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CONFIG_SYS_DCACHE_SIZE		16384
#define CONFIG_SYS_ICACHE_SIZE		16384
#define CONFIG_SYS_CACHELINE_SIZE	32

/*-----------------------------------------------------------------------
 * Command line configuration.
 */
#ifndef CONFIG_POLLINUX_FLASHER
#  include <config_cmd_default.h>
#  define CONFIG_CMD_ELF
#  define CONFIG_CMD_MII
#  define CONFIG_CMD_PING
#  define CONFIG_CMD_PCI
/* NAND Stuff */
#  define CONFIG_CMD_NAND
#  define CONFIG_CMD_NAND_TRIMFFS
#  define CONFIG_CMD_JFFS2
#  define CONFIG_CMD_MTDPARTS
#  define CONFIG_CMD_SAVEENV
/* SATA stuff */
#  define CONFIG_CMD_SATA
#  define CONFIG_CMD_EXT2
#else
#  define CONFIG_CMD_EDITENV
#  define CONFIG_CMD_LOADB
#  define CONFIG_CMD_MTDPARTS
#  define CONFIG_CMD_NAND
#  define CONFIG_CMD_PCI
#  define CONFIG_CMD_SAVEENV
#endif

#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_FLASH
#undef CONFIG_CMD_IDE
#undef CONFIG_CMD_SETGETDCR
#undef CONFIG_CMD_XIMG

#endif	/* __CONFIG_H */
