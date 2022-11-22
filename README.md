<h1 align=center><code>BlobOS</code></h1>
<p align=center>My Operating System</p>

## 💡 About
The only point with this project is to learn Assembly, I don't want to create something huge.

## 🚀 Setup
### 🧾 Dependencies
 - [`nasm`](https://nasm.us/) - Assembler, you need for build the OS.
 - [`qemu`](https://www.qemu.org/) - Virtualization, for testing the OS without rebooting. _(optional)_

### 🔧 Testing

Option 1: Using `qemu`:
```sh
git clone https://github.com/RedsonBr140/BlobOS.git
cd BlobOS
make run # This build and run the project using QEMU.
```
Option 2: Real hardware:
```sh
git clone https://github.com/RedsonBr140/BlobOS.git
cd BlobOS
make floppy_image # Build the floppy disk
dd if=build/main_floppy.img of=/dev/yourFlashDrive status=progress
```
> ⚠️ dd is a dangeours command, make sure that you didn't set `of` to any disk with important information, also, it will overwrite anything on the disk, including partitions.
