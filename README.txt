== Navi ==

Navi is an entire operating system, containing of a monolithic kernel, its own
toolchain (c to ir - intermediate representation -, navilang to ir and ir to x86
assembly, assembler and linker) and network protocol.

Navi is based on the operating system shown in the anime Serial Experiments
Lain, I didn't call this project Copland because it's an old apple product and
well, as it existed, using that name might lead to problems.

The following is a TODO list for the project:

- Kernel
  - [X] Simple Bootloader (to get started it could be a BIOS bootloader)
  - [X] Showing stuff to screen using text mode
  - [X] Heap
  - [P] Paging
  - [ ] ATA driver
  - [ ] FAT Filesystem (it could be FAT16 to get started)
  - [ ] User land
  - [ ] Tasks
  - [ ] Int 0x80
  - [ ] Keyboard driver
  - [ ] Elf support
  - [ ] C Stdlib
  - [ ] Shell
  - [ ] Multithreading
  - [ ] Networking Support
  - [ ] Protocol 7
    - It's basically an own network protocol, think of freenet, for example
  - [ ] Cryptography
  - [ ] Multi user
  - [ ] Audio driver
  - [ ] Video mode support
  - [ ] Mouse driver
  - [ ] GUI
    - [ ] Login system
    - [ ] Window manager
    - [ ] Some other utilities
      - [ ] File manager
      - [ ] Text editor
      - [ ] Protocol 7 browser
      - [ ] System monitor
      - [ ] Video player
      - [ ] Image viewer
- Toolchain
  - Refer to `toolchain/README.txt'

Note: Even though I intend to take this project seriously and - hopefully - be
able to develop the entirety of what I want to achieve, I am doing this mainly
for learning purporses, so there might be some things that probably won't be
implemented in the most efficient way, or a lack of other functionalities and
that, with time I will improve everything!

I hope this is also useful for you!

== Directory Structure ==

There are already a lot of folders in the navi source code - and there are still
a lot of things pendant to implement - so this is a brief summary of what's in
every directory:

- boot: bootloader's source
- drivers: drivers that are used in the navi kernel
- idt: interrupt descriptor table implementation
- io: input/output related code
- mm: memory management code (such as heap and paging)
- string: string related functions
- toolchain: the navi toolchain (there's another readme you might want to read)
