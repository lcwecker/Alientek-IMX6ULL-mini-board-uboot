/*
 * CoreChips PHY drivers
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 * Base code from drivers/net/phy/davicom.c
 *   Copyright 2010-2011 Freescale Semiconductor, Inc.
 *   author Andy Fleming
 *
 * Some code copied from linux kernel
 * Copyright (c) 2006 Herbert Valerio Riedel <hvr@gnu.org>
 */
 #include <miiphy.h>

/* This code does not check the partner abilities. */
static int corechips_parse_status(struct phy_device *phydev)
{
	int mii_reg;

	mii_reg = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMSR);

	if (mii_reg & (BMSR_100FULL | BMSR_100HALF))
		phydev->speed = SPEED_100;
	else
		phydev->speed = SPEED_10;

	if (mii_reg & (BMSR_10FULL | BMSR_100FULL))
		phydev->duplex = DUPLEX_FULL;
	else
		phydev->duplex = DUPLEX_HALF;

	return 0;
}

static int corechips_startup(struct phy_device *phydev)
{
	genphy_update_link(phydev);
	corechips_parse_status(phydev);
	return 0;
}

static struct phy_driver sr8201f_driver = {
	.name = "CoreChips SR8201F",
	.uid = 0x001CC816,
	.mask = 0xFFFFFF,
	.features = PHY_BASIC_FEATURES,
	.config = &genphy_config_aneg,
	.startup = &corechips_startup,
	.shutdown = &genphy_shutdown,
};

int phy_corechips_init(void)
{
	phy_register(&sr8201f_driver);

	return 0;
}
