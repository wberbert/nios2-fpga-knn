/*
 * Copyright (C) 2018 Intel Corporation. All rights reserved
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/firewall_s10.h>
#include <asm/arch/smmu_s10.h>
#include <asm/arch/system_manager.h>

DECLARE_GLOBAL_DATA_PTR;

static struct socfpga_system_manager *sysmgr_regs =
	(struct socfpga_system_manager *)SOCFPGA_SYSMGR_ADDRESS;

static const struct smmu_stream_id dev_stream_id[] = {
	{SYSMGR_EMAC0_SID_ADDR, 0x01, EMAC_W_OFST, EMAC_R_OFST},
	{SYSMGR_EMAC1_SID_ADDR, 0x02, EMAC_W_OFST, EMAC_R_OFST},
	{SYSMGR_EMAC2_SID_ADDR, 0x03, EMAC_W_OFST, EMAC_R_OFST},
	{SYSMGR_NAND_SID_ADDR,  0x04, NAND_W_OFST, NAND_R_OFST},
	{SYSMGR_SDMMC_SID_ADDR, 0x05, SDMMC_OFST, SDMMC_OFST},
	{SYSMGR_USB0_SID_ADDR,  0x06, USB_OFST, USB_OFST},
	{SYSMGR_USB1_SID_ADDR,  0x07, USB_OFST, USB_OFST},
	{SYSMGR_DMA_SID_ADDR,   0x08, DMA_W_OFST, DMA_R_OFST},
	{SYSMGR_ETR_SID_ADDR,   0x09, ETR_W_OFST, ETR_R_OFST},
};

static void set_smmu_streamid(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dev_stream_id); i++) {
		u32 mask = SMMU_SET_STREAMID(0x3FF,
					 dev_stream_id[i].r_bit_ofst,
					 dev_stream_id[i].w_bit_ofst);
		u32 value = SMMU_SET_STREAMID(dev_stream_id[i].sid,
					 dev_stream_id[i].r_bit_ofst,
					 dev_stream_id[i].w_bit_ofst);

		clrbits_le32(dev_stream_id[i].addr, mask);
		setbits_le32(dev_stream_id[i].addr, value);
	}
}

/*
 * Need to set the Secure bit (to make it non-secure) on each peripheral
 * so that SMMU can access the peripheral
 */
static void set_smmu_accessible_reg(void)
{
	setbits_le32(&sysmgr_regs->emac0, BIT(27) | BIT(25));
	setbits_le32(&sysmgr_regs->emac1, BIT(27) | BIT(25));
	setbits_le32(&sysmgr_regs->emac2, BIT(27) | BIT(25));
	setbits_le32(&sysmgr_regs->nandgrp_l3master, BIT(21) | BIT(17));
	setbits_le32(&sysmgr_regs->sdmmcgrp_l3master, BIT(5));
	setbits_le32(&sysmgr_regs->usb0_l3master, BIT(9));
	setbits_le32(&sysmgr_regs->usb1_l3master, BIT(9));
}

static inline void setup_smmu_firewall(void)
{
	/* Enable nonsecure SMMU accesses */
	writel(FIREWALL_L4_DISABLE_ALL, SOCFPGA_FIREWALL_TCU);
}

void socfpga_init_smmu(void)
{
	setup_smmu_firewall();
	set_smmu_streamid();
	set_smmu_accessible_reg();
}
