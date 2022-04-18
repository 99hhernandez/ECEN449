## OBJECTIVE
The purpose of lab this week is to get Linux up and running on the ZYBO Z7-10 board. There are
many advantages to running an Operating System (OS) in an embedded processor environment, and Linux
provides a nice open-source OS platform for us to build upon. This week, you will use Vivado to build
a Zynq(ARM Cortex A9) based microprocessor system suitable for running Linux, and you will also use
open source tools to compile the Linux kernel based on the specification of your custom microprocessor
system. You will then combine the bit stream with FSBL(First Stage Boot Loader) and u-boot(Universal
Boot Loader) to create Zynq Boot Image. FSBL initialize the Processing System(PS) with configuration
data and initializes u-boot. u-boot is the boot loader that holds the instructions to boot the Linux Kernel. we
need a RAMDISK, a temporary file system that is mounted during Kernel boot. The boot loader needs a
device tree which has information about the physical devices in the system and this information is stored in
’device tree blob’. We will use all these files to boot Linux on ZYBO Z7-10 board using a SD card.
