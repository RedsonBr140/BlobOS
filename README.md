> :warning: **Rewriting!** The project is transitioning to Rust now.

<p align="center">
  <img src="docs/assets/BlobOS_without_border.png" width="128" height="128"/>
</p>
<p align=center>My Operating System</p>

## 💡 About
The point with this project is to learn about operating systems and computers, I don't want to create something huge.

## 🚀 Setup
### 🧾 Dependencies
 - [`rustup`](https://rustup.rs/) - Installer for the Rust programming language.
 - `rust-nightly` - The latest version of Rust.
 - `rust-src` - A rustup component
 - `llvm-tools-preview` - Another component, this time for bootimage
 - `bootimage` - To link the kernel and the bootloader
 - [`qemu`](https://www.qemu.org/) - Virtualization, for testing the OS without rebooting. _(optional)_
--
Option 1: Using `qemu`:
```sh
git clone https://github.com/RedsonBr140/BlobOS.git
cd BlobOS
cargo run
```
Option 2: Real hardware:
```sh
git clone https://github.com/RedsonBr140/BlobOS.git
cd BlobOS
cargo bootimage # Build with --release if you want
dd if=target/x86_64-BlobOS/debug/bootimage-blob_os.bin of=/dev/yourFlashDrive status=progress
```
> ⚠️ dd is a dangerous command, make sure that you didn't set `of` to any disk with important data, also, it will overwrite anything on the disk, including partitions.
