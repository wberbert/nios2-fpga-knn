/*
 *  Copyright (C) 2016-2018 Intel Corporation <www.intel.com>
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include <common.h>
#include <asm/io.h>
#include <asm/u-boot.h>
#include <asm/utils.h>
#include <image.h>
#include <asm/arch/reset_manager.h>
#include <spl.h>
#include <asm/arch/system_manager.h>
#include <asm/arch/clock_manager.h>
#include <asm/arch/sdram_s10.h>
#include <asm/arch/mailbox_s10.h>
#include <asm/arch/firewall_s10.h>
#include <watchdog.h>
#include <asm/arch/smmu_s10.h>

DECLARE_GLOBAL_DATA_PTR;

static const struct socfpga_firwall_l4_per *firwall_l4_per_base =
	(struct socfpga_firwall_l4_per *)SOCFPGA_FIREWALL_L4_PER;
static const struct socfpga_firwall_l4_sys *firwall_l4_sys_base =
	(struct socfpga_firwall_l4_sys *)SOCFPGA_FIREWALL_L4_SYS;
static struct socfpga_system_manager *sysmgr_regs =
	(struct socfpga_system_manager *)SOCFPGA_SYSMGR_ADDRESS;

u32 spl_boot_device(void)
{
	/* TODO: Get from SDM or handoff */
/* #ifdef CONFIG_CADENCE_QSPI*/
#if 0
	return BOOT_DEVICE_SPI;
#else
	return BOOT_DEVICE_MMC1;
#endif
}

#ifdef CONFIG_SPL_MMC_SUPPORT
u32 spl_boot_mode(const u32 boot_device)
{
#if defined(CONFIG_SPL_FAT_SUPPORT) || defined(CONFIG_SPL_EXT_SUPPORT)
	return MMCSD_MODE_FS;
#else
	return MMCSD_MODE_RAW;
#endif
}
#endif

void board_init_f(ulong dummy)
{
	const struct cm_config *cm_default_cfg = cm_get_default_config();

#ifdef CONFIG_HW_WATCHDOG
	/* Ensure watchdog is paused when debugging is happening */
	writel(SYSMGR_WDDBG_PAUSE_ALL_CPU, &sysmgr_regs->wddbg);

	/* Enable watchdog before initializing the HW */
	socfpga_per_reset(SOCFPGA_RESET(L4WD0), 1);
	socfpga_per_reset(SOCFPGA_RESET(L4WD0), 0);
	hw_watchdog_init();
#endif

	/* ensure all processors are not released prior Linux boot */
	writeq(0, CPU_RELEASE_ADDR);

	socfpga_per_reset(SOCFPGA_RESET(OSC1TIMER0), 0);
	timer_init();

	sysmgr_pinmux_init();

	/* configuring the HPS clocks */
	cm_basic_init(cm_default_cfg);

	/* enable console uart printing */
#if (CONFIG_SYS_NS16550_COM1 == SOCFPGA_UART0_ADDRESS)
	socfpga_per_reset(SOCFPGA_RESET(UART0), 0);
	/* enables nonsecure access to UART0 */
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->uart0);
#elif (CONFIG_SYS_NS16550_COM1 == SOCFPGA_UART1_ADDRESS)
	socfpga_per_reset(SOCFPGA_RESET(UART1), 0);
	/* enables nonsecure access to UART1 */
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->uart1);
#endif

	preloader_console_init();
	cm_print_clock_quick_summary();

	/* enable non-secure interface to DMA330 DMA and peripherals */
	writel(SYSMGR_DMA_IRQ_NS | SYSMGR_DMA_MGR_NS, &sysmgr_regs->dma);
	writel(SYSMGR_DMAPERIPH_ALL_NS, &sysmgr_regs->dma_periph);
	/* enable DMA330 DMA */
	socfpga_per_reset(SOCFPGA_RESET(DMA), 0);
	socfpga_per_reset(SOCFPGA_RESET(DMA_OCP), 0);

	/*
	 * The following lines of code will enable non-secure access
	 * to nand, usb, spi, emac, sdmmc, gpio, i2c, and timers. This
	 * is needed as most OS run in non-secure mode. Thus we need to
	 * enable non-secure access to these peripherals in order for the
	 * OS to use these peripherals.
	 */
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->nand);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->nand_data);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->usb0);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->usb1);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->spim0);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->spim1);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->emac0);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->emac1);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->emac2);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->sdmmc);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->sdmmc_ecc);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->gpio0);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->gpio1);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->i2c0);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->i2c1);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->i2c2);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->i2c3);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->i2c4);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->timer0);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_per_base->timer1);

	/* enables nonsecure access to clock mgr */
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->clock_manager);

	/* enables nonsecure access to reset mgr */
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->reset_manager);

	/* enables nonsecure access to system mgr */
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->system_manager);

	/* enables nonsecure access to OCRAM */
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->ocram_ecc);

	/* enables nonsecure access to all the emacs */
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->emac0rx_ecc);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->emac0tx_ecc);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->emac1rx_ecc);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->emac1tx_ecc);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->emac2rx_ecc);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->emac2tx_ecc);

	/* enables nonsecure access to all the eccs */
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->dma_ecc);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->nand_ecc);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->usb0_ecc);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->usb1_ecc);

	/* enables nonsecure access to SMMU */
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->io_manager);

	/* enables nonsecure access to watchdog */
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->watchdog0);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->watchdog1);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->watchdog2);
	writel(FIREWALL_L4_DISABLE_ALL, &firwall_l4_sys_base->watchdog3);

	/* enables SDMMC */
	socfpga_per_reset(SOCFPGA_RESET(SDMMC_OCP), 0);
	socfpga_per_reset(SOCFPGA_RESET(SDMMC), 0);
	/* enable usb0 and usb1 */
	socfpga_per_reset(SOCFPGA_RESET(USB0), 0);
	socfpga_per_reset(SOCFPGA_RESET(USB1), 0);
	socfpga_per_reset(SOCFPGA_RESET(USB0_OCP), 0);
	socfpga_per_reset(SOCFPGA_RESET(USB1_OCP), 0);
	/* enable SPIM1 */
	socfpga_per_reset(SOCFPGA_RESET(SPIM1), 0);

	/* disable lwsocf2fpga and soc2fpga bridge security */
	writel(FIREWALL_BRIDGE_DISABLE_ALL, SOCFPGA_FIREWALL_SOC2FPGA);
	writel(FIREWALL_BRIDGE_DISABLE_ALL, SOCFPGA_FIREWALL_LWSOC2FPGA);

	/* Setup and Initialize SMMU */
	socfpga_init_smmu();

	/* disable ocram security at CCU for non secure access */
	clrbits_le32(CCU_CPU0_MPRT_ADMASK_MEM_RAM0_ADDR,
		     CCU_ADMASK_P_MASK | CCU_ADMASK_NS_MASK);
	clrbits_le32(CCU_IOM_MPRT_ADMASK_MEM_RAM0_ADDR,
		     CCU_ADMASK_P_MASK | CCU_ADMASK_NS_MASK);

	/* enable i2c1 */
	socfpga_per_reset(SOCFPGA_RESET(I2C1), 0);

	/* Take GPIO0 & GPIO1 out of reset */
	socfpga_per_reset(SOCFPGA_RESET(GPIO0), 0);
	socfpga_per_reset(SOCFPGA_RESET(GPIO1), 0);

	/* enable SPIM0 and SPIM1 */
	socfpga_per_reset(SOCFPGA_RESET(SPIM0), 0);
	socfpga_per_reset(SOCFPGA_RESET(SPIM1), 0);

	puts("DDR: Initializing Hard Memory Controller\n");
	if (sdram_mmr_init_full(0)) {
		puts("DDR: Initialization failed.\n");
		hang();
	}

#ifdef CONFIG_SOCFPGA_SDRAM_SBE_ECC_CHECKING
	sdram_sbe_ecc_checking();
#endif

#ifdef CONFIG_SOCFPGA_SDRAM_DBE_ECC_CHECKING
	sdram_dbe_ecc_checking();
#endif

#ifdef CONFIG_SOCFPGA_SDRAM_ADDR_MISMATCH_ECC_CHECKING
	sdram_addr_mismatch_ecc_checking();
#endif

	gd->ram_size = sdram_calculate_size();
	printf("DDR: %d MiB\n", (int)(gd->ram_size >> 20));

	/* Sanity check ensure correct SDRAM size specified */
	puts("DDR: Running SDRAM size sanity check\n");
	if (get_ram_size(0, gd->ram_size) != gd->ram_size) {
		puts("DDR: SDRAM size check failed!\n");
		hang();
	}
	puts("DDR: SDRAM size check passed!\n");

#ifdef CONFIG_CADENCE_QSPI
	mbox_init();
	mbox_qspi_open();
#endif
}

/* board specific function prior loading SSBL / U-Boot */
void spl_board_prepare_for_boot(void)
{
	mbox_hps_stage_notify(HPS_EXECUTION_STATE_SSBL);
}
