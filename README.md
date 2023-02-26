<h1 align=center><code>BlobOS</code></h1>
<p align=center>My Operating System</p>

## 💡 About
The point with this project is to learn about operating systems and computers, I don't want to create something huge.

## 🚀 Setup
### 🧾 Dependencies
 - [`nasm`](https://nasm.us/) - Assembler, you need for build the OS.
 - [`qemu`](https://www.qemu.org/) - Virtualization, for testing the OS without rebooting. _(optional)_
  - [`GRUB & grub-mkrescue`](https://git.savannah.gnu.org/cgit/grub.git/) - Building the ISO, you also need the i386 version of grub, or just use `make run-bin` _(optional)_

### 🔧 Testing

Option 1: Using `qemu`:
```sh
git clone https://github.com/RedsonBr140/BlobOS.git
cd BlobOS
make run # This builds and runs the project using QEMU.
```
Option 2: Real hardware:
```sh
git clone https://github.com/RedsonBr140/BlobOS.git
cd BlobOS
make buildISO # Build the ISO Image.
dd if=build/BlobOS.iso of=/dev/yourFlashDrive status=progress
```
> ⚠️ dd is a dangerous command, make sure that you didn't set `of` to any disk with important data, also, it will overwrite anything on the disk, including partitions.
