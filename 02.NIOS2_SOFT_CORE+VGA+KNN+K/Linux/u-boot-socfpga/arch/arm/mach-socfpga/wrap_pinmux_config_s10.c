/*
 * Copyright (C) 2016-2017 Intel Corporation <www.intel.com>
 *
 * SPDX-License-Identifier:    GPL-2.0
 */

#include <common.h>
#include <errno.h>
#include <asm/io.h>
#include <asm/arch/handoff_s10.h>

static void sysmgr_pinmux_handoff_read(void *handoff_address,
				const u32 **table, unsigned int *table_len)
{
	unsigned int handoff_entry = (swab32(readl(handoff_address +
					CONFIG_HANDOFF_OFFSET_LENGTH)) -
					CONFIG_HANDOFF_OFFSET_DATA) /
					sizeof(unsigned int);
	unsigned int handoff_chunk[handoff_entry], temp, i;

	if (swab32(readl(CONFIG_HANDOFF_MUX)) == CONFIG_HANDOFF_MAGIC_MUX) {
		/* using handoff from Quartus tools if exists */
		for (i = 0; i < handoff_entry; i++) {
			temp = readl(handoff_address +
				     CONFIG_HANDOFF_OFFSET_DATA + (i * 4));
			handoff_chunk[i] = swab32(temp);
		}
		*table = handoff_chunk;
		*table_len = ARRAY_SIZE(handoff_chunk);
	}
}

void sysmgr_pinmux_table_sel(const u32 **table, unsigned int *table_len)
{
	sysmgr_pinmux_handoff_read((void *)CONFIG_HANDOFF_MUX, table, table_len);
}

void sysmgr_pinmux_table_ctrl(const u32 **table, unsigned int *table_len)
{
	sysmgr_pinmux_handoff_read((void *)CONFIG_HANDOFF_IOCTL, table, table_len);
}

void sysmgr_pinmux_table_fpga(const u32 **table, unsigned int *table_len)
{
	sysmgr_pinmux_handoff_read((void *)CONFIG_HANDOFF_FPGA, table, table_len);
}

void sysmgr_pinmux_table_delay(const u32 **table, unsigned int *table_len)
{
	sysmgr_pinmux_handoff_read((void *)CONFIG_HANODFF_DELAY, table, table_len);
}
