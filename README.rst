fatls
=====

The fatls command can be used to display the short and long names of entries in
the directory of a FAT file system.

Build and install
-----------------

::

    make
    sudo make install

Synopsis
--------

::

   fatls <directory>

directory
    path to the directory

Example
-------

::

    $ fatls sct/mnt/

    Volume ID 9dc4-267b
    Directory sct/mnt/

    1970-01-01 00:00:00 <DIR>           .
    2021-01-30 15:07:44 <DIR>           ..
    2020-12-01 06:59:40             148 BOOT.SCR     boot.scr
    2020-12-01 06:59:40             171 STARTUP.NSH  startup.nsh
    2020-12-01 06:59:40               0 RUN          run
    2020-12-01 06:59:40 <DIR>           APPLIC~1     Application
    2020-12-01 06:59:40 <DIR>           DATA         Data
    2020-12-01 06:59:40 <DIR>           DEPEND~1     Dependency
    2020-12-01 06:59:40 <DIR>           ENTS         Ents
    2020-12-01 06:59:40 <DIR>           PROXY        Proxy
    2021-01-30 13:37:49 <DIR>           REPORT       Report
    2020-12-01 06:59:40 <DIR>           SCRT
    2020-12-01 06:59:40         341,312 SCT.EFI      SCT.efi
    2020-12-01 06:59:40 <DIR>           SEQUENCE     Sequence
    2020-12-01 06:59:40          16,320 STALLF~1.EFI StallForKey.efi
    2020-12-01 06:59:40 <DIR>           SUPPORT      Support
    2020-12-01 06:59:40 <DIR>           TEST         Test
    2020-12-26 16:07:54         961,632 SHELL.EFI    Shell.efi
    1980-01-01 00:00:00             136 UBOOTE~1.VAR ubootefi.var
    2020-12-28 14:16:00         557,449 HAIKU_~1.EFI haiku_loader.efi
    2021-01-29 00:49:31         445,952 GRUB_X64.EFI grub_x64.efi
                9 Files       2,323,120 bytes
               12 Directories
