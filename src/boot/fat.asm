;
;; Boot Record // FAT Header
;
br_oem:           db "MSWIN4.1" ; OEM identifier. The first 8 Bytes (3 - 10) is the version of DOS being used.
br_blocksize:     dw 512				; 512 bytes per sector.
br_sector:        db 1					; 1 Sector per cluster.
br_reserved:      dw 1					; Number of reserved sectors. The boot record sectors are included in this value.
br_fat_tables:    db 2					; Number of File Allocation Tables (FAT's) on the storage media.
br_root_entries:  dw 0xE0				; Number of root directory entries.
br_total_sectors: dw 2880				; The total sectors in the logical volume. 2880 * 512 = 1.44MB
br_descriptor:    db 0x0F0			; Media descriptor type.
br_sectors_fat:   dw 9					; Number of sectors per FAT. FAT12/FAT16 only.
br_sectors_track: dw 18					; Number of sectors per track.
br_heads_count:   dw 2					; Number of heads or sides on the storage media.
br_hidden_sector: dd 0					; Number of hidden sectors.
br_large_sector:  dd 0					; Large sector count. This field is set if there are more than 65535 sectors in the volume.

;
;; Extended boot record
;
ebr_drive_number: db 0					; Drive number. 0x00 for a floppy disk and 0x80 for hard disks.
	                db 0					; Windows NT Skill issue
ebr_signature:    db 0x29				; Signature. Always 0x28 or 0x29.
ebr_serial_id:    db 'DOOM'			; Serial ID Can be anything, DOOM then.
ebr_label:        db ' IS GOOD   ' ; Volume label.
ebr_system_id:    db 'FAT12   '	; System identifier string. This field is a string representation of the FAT file system type.

;; LBA address to CHS address
lba_to_chs:
