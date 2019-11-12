

# Early Boot: Old (BIOS) Plan

 - Processor starts @ BIOS
 - BIOS selects boot disk
 - Read partition table.
   - Limit: 4 partitions
 - Reads MBR, loads 1st stage bootloader
   - Limit: Max disk size = 2TB.
 - 1st stage loads second stage
 - 2nd stage loads kernel
 - kernel boots normally into OS

# Modern Early boot: (UEFI)

 - Management engine starts the processor
 - Processor starts @ UEFI code
 - UEFI selects boot disk / OS
 - Loads 1st stage bootloader, verifies signature.
 - 1st stage loads second stage, verifies signature
 - 2nd stage loads kernel, (optionally) verifies signature
 - kernel boots normally 

# UEFI Secure Boot

The idea:

 - Some viruses worked by overwriting the MBR.
 - Other malware: Trojans, Keyloggers
 - Custom OS can bypass some security measures.
 - If you can create a "chain of trust" for the software running on a PC, you
   can make secure assertions to software like "Netflix, no screen capture
   software is running right now".

Happens on phones, called a "locked bootloader".

Pretty common on modern machines.

Who's signature? The OS vendor.

 - On mobile phones, it's the vendor key.
 - On PCs with Windows preinstalled, it's Microsoft's key.

When I boot Debian on this thinkpad, Microsoft's key verifies a
signature of Debian's bootloader.

Some machines let the user load their own secure boot keys, which means you get
to sign your own bootloader.

=
# Management Engine

 - Purpose: Enterprise Remote Administration
 - Has full access to system hardware, including RAM, disks
   and network interface.
 - This functionality isn't optional.
 - Potential remote backdoor, running unknown code that can't be modified.
 - There have been a couple of serious security holes, including local network
   remote code execution attack.

 - There was an interesting leak from Intel: Custom functionality requested by
   the NSA. They didn't like this ME stuff and wanted to be able to turn it off.
 - For some Intel chips (including Skylake) setting a particular bit at the
   right time will cause the management engine to delete most of itself after
   boot
   
 - AMD has similar functionality, called the PSP.
 - Most ARM chips have some similar story, the Raspberry Pi boots its
   proprietary GPU first.

Companies with solutions:

 - Purism
 - Raptor Engineering








 
 
 
