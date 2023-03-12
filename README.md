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
 - [`qemu`](https://www.qemu.org/) - Virtualization, for testing the OS without rebooting. _(optional)_
<!----
  - [`GRUB & grub-mkrescue`](https://git.savannah.gnu.org/cgit/grub.git/) - Building the ISO, you also need the i386 version of grub.
### 🔧 Testing

Option 1: Using `qemu`:
```sh
git clone https://github.com/RedsonBr140/BlobOS.git
cd BlobOS
meson setup build # Create the build directory
meson compile -C build run.bin # Runs the BIN file in qemu.
```
Option 2: Real hardware:
```sh
git clone https://github.com/RedsonBr140/BlobOS.git
cd BlobOS
meson setup build # Create the build directory
meson compile -C build # Compile the project.
dd if=build/BlobOS.iso of=/dev/yourFlashDrive status=progress
```
> ⚠️ dd is a dangerous command, make sure that you didn't set `of` to any disk with important data, also, it will overwrite anything on the disk, including partitions.-->
