/***********************************************************************
 * fs_blockdev_spi_nor_driver.c
 *
 * Short description.
 * Copyright (C) 2015 QUALCOMM Technologies, Inc.
 *
 * Verbose Description
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who   what, where, why
----------   ---   ---------------------------------------------------------
2015-04-14   mj    Create

===========================================================================*/
#include "fs_hotplug_config_i.h"

#ifdef FEATURE_FS_HOTPLUG_SPI_NOR

#include "fs_blockdev_spi_nor_driver.h"
#include "assert.h"
#include "flash.h"
#include "DALSys.h"


/* Bump this for any code changes in the file */
#define SPI_NOR_DRIVER_VERSION            0x0001


/* Driver functions */
static void blockdev_spi_nor_driver_init (struct block_device **, uint16 *);
static void blockdev_spi_nor_driver_cleanup (void);


/* Declare the driver for this module, this will be the only thing
 * exposed to the blockdev layer above. */
blockdev_driver blockdev_spi_nor_driver =
{
  "BDEV_SPI_NOR_DRIVER",            /* char *name */
  BLOCKDEV_TYPE_SPI_NOR,            /* block_device_type */
  SPI_NOR_DRIVER_VERSION,           /* uint16 version */
  blockdev_spi_nor_driver_init,     /* init fn */
  blockdev_spi_nor_driver_cleanup   /* cleanup fn */
};


/* List of spi-nor block devices to manage */
static struct block_device spi_nor_devices[] =
{
  {"/hdev/spi-nor1", NULL, NULL, BLOCKDEV_TYPE_SPI_NOR, 0, 0xFF, NULL, CANARY},
};

#define SPI_NOR_NUM_DEVICES   \
          (sizeof (spi_nor_devices) / sizeof (spi_nor_devices[0]))


/*--------------------
 * SPI-NOR Driver functions
 *--------------------*/
 
/* This should populate the blockdev linked list */
static void
blockdev_spi_nor_driver_init (struct block_device **head, uint16 *dev_id)
{
  int i;
  blockdev_ops *spi_nor_ops;
  blockdev_spi_nor_device_data_init ();
  spi_nor_ops = blockdev_spi_nor_get_ops ();
  
  ASSERT (spi_nor_ops != NULL);
  
  /* Link the list of devices together */
  for (i=(SPI_NOR_NUM_DEVICES-1); i >= 0; i--)
  {
    struct block_device *bdev = &spi_nor_devices[i];
    bdev->device_id = (*dev_id)++;
    bdev->ops = spi_nor_ops;
    bdev->device_data = blockdev_spi_nor_get_device_data (i);
    /* Add device to beginning of the linked list */
    bdev->next = *head;
    *head = bdev;
  }
  
  /* Initialization is only done on the first call */
  DALSYS_InitMod(NULL);

}

static void
blockdev_spi_nor_driver_cleanup (void)
{
  /* Do nothing as of now */
}

#endif /* #ifdef FEATURE_FS_HOTPLUG_SPI_NOR */
