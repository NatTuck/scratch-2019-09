

# Modern PC Booting

## Review of Old PC Early Boot

 - Processor Starts @ BIOS
 - BIOS selects boot disk
 - Reads partiiton table, selects boot partion.
   - Limited to 4 partitions.
 - Read MBR, loads 1st stage bootloader
   - Limit: 2TB disks
 - 1st stage loads second stage
 - Second stage sleects and loads kernel
 - Kernel is in control

## Modern System Early Boot

 - Management Engine starts processor
 - Processor starts @ UEFI
 - UEFI selects boot device or boot OS
 - Loads 1st stage bootloader, verifies signature
 - Transfers control to first stage.
 - Loads 2nd stage, verifes signature.
 - Loads OS kernel, optionally verifies signature.
 - OS kernel is in control. 

Two companies supply ME free computers:

 - Purism
 - Raptor Engineering

## "Secure Boot"

 - Some viruses really did overwrite the MBR
 - Deep software keyloggers / trojans can be written
   early in the boot sequence.
 - "Locked bootloader" on phones is the same thing.
 - This can allow "verified" software.
   - E.g. you can do "content protection" by having software
     assert that no screen capture software is running when you
     watch a video.

Signed by who?

 - The cryptographic keys used for verification are loaded by the
   device manufacturer.
 - For phones, it's a manufacturer key.
 - On machines with Windows preinstalled, it's a Microsoft key.
   - Microsoft reliably signs Linux bootloaders.
 - On some machines you can install your own keys and sign your own
   OS images.

The main thing secure boot does is protect from attacks by people with physical
access.

 - In general, physical access attacks always work.
 - The only real effect this has is inconveniencing the user.
 
# Result: We've Booted An OS kernel

 - Eventually the kernel runs PID 1.
 
 


