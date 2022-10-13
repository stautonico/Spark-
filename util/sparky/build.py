from .io import BLUE, YELLOW, RESET, error, info, warn, success, print_colored, debug
import subprocess
import os
from .const import *
import requests


def run_command(cmd, verbose=False):
    """Runs a command and print verbose output if needed"""
    if verbose:
        print(f"{BLUE}[ RUN ]{RESET} {cmd}")

    return subprocess.call(
        cmd.split(), stdout=subprocess.DEVNULL if not verbose else None,
        stderr=subprocess.DEVNULL if not verbose else None)


def check(ret_code, error_msg):
    """Checks the return code of a command and prints an error message if needed"""
    if ret_code != 0:
        error(error_msg)
        exit(1)


def build_toolchain(_args):
    """Builds the toolchain"""
    # Get our args we'll need
    toolchain_output_dir = _args.output_dir
    overwrite = _args.overwrite
    no_cache = _args.no_cache
    clear_cache = _args.clear_cache
    gcc_version = _args.gcc_version
    binutils_version = _args.binutils_version
    gcc_url = _args.gcc_url or DEFAULT_GCC_URL.replace("<GCC_VERSION>", gcc_version)
    binutils_url = _args.binutils_url or DEFAULT_BINUTILS_URL.replace("<BINUTILS_VERSION>", binutils_version)
    target_arch = _args.target_arch
    verbose = _args.verbose
    jobs = _args.jobs
    no_gcc = _args.no_gcc
    no_binutils = _args.no_binutils

    info("Starting toolchain build")

    # Make sure the build directory exists
    if os.path.exists(toolchain_output_dir):
        if not overwrite:
            warn(f"Build directory already exists: {toolchain_output_dir}")
            print_colored("Use --overwrite to force build or remove existing toolchain", YELLOW)
            return
    else:
        os.makedirs(toolchain_output_dir)

    # Make the temporary build directory
    if not os.path.exists(TOOLCHAIN_TEMP_DIR):
        os.makedirs(TOOLCHAIN_TEMP_DIR)
    else:
        # If we have clear cache enabled, remove the exiting build directory and recreate it
        if clear_cache:
            info("Clearing build cache")
            os.system(f"rm -rf {TOOLCHAIN_TEMP_DIR}")
            os.makedirs(TOOLCHAIN_TEMP_DIR)
        else:
            # Otherwise, we just warn that we're using the existing temporary build directory
            warn(f"Using existing build cache")

    os.chdir(TOOLCHAIN_TEMP_DIR)

    if not no_binutils:
        # Download and extract binutils
        info("Downloading Binutils")
        if not clear_cache and os.path.exists(f"binutils.tar.gz"):
            warn("Using existing Binutils archive")
        else:
            r = requests.get(binutils_url)
            # Confirm the download was successful
            if r.status_code != 200:
                error(f"Failed to download Binutils: HTTP {r.status_code}")

            with open("binutils.tar.gz", "wb") as f:
                f.write(r.content)

            info("Extracting Binutils")
            check(run_command("tar -xzvf binutils.tar.gz", verbose), "Failed to extract Binutils")

    if not no_gcc:
        # Download and extract gcc
        info("Downloading GCC")

        # Check if we have the archive already, and we don't have clear cache enabled
        if not clear_cache and os.path.exists(f"gcc.tar.gz"):
            warn("Using existing GCC archive")
        else:
            r = requests.get(gcc_url)
            # Confirm the download was successful
            if r.status_code != 200:
                error(f"Failed to download GCC: HTTP {r.status_code}")
                exit(1)

            with open("gcc.tar.gz", "wb") as f:
                f.write(r.content)

            info("Extracting GCC")
            check(run_command("tar -xzvf gcc.tar.gz", verbose), "Failed to extract GCC")

    if not no_binutils:
        # Build binutils
        info("Building binutils (this may take a while)")
        # Remove existing binutils build directory
        if os.path.exists("binutils-build") and not clear_cache:
            run_command(f"rm -rvf binutils-build", verbose)

        if not os.path.exists("binutils-build"):
            os.mkdir("binutils-build")

        os.chdir("binutils-build")

        check(run_command(
            f"./../binutils-{binutils_version}/configure --target={target_arch}-elf --prefix={toolchain_output_dir} --with-sysroot --disable-nls --disable-werror",
            verbose), "Failed to configure binutils")

        check(run_command(f"make -j{jobs}", verbose), "Failed to build binutils")
        check(run_command(f"make install", verbose), "Failed to install binutils")

        info("Verifying binutils installation")

        # Verify that binutils was built correctly
        # Check that the toolchain/bin directory exists and isn't empty
        if not os.path.exists(f"{toolchain_output_dir}/bin"):
            error(f"Binutils build failed: {toolchain_output_dir}/bin does not exist")
            exit(1)
        if not os.listdir(f"{toolchain_output_dir}/bin"):
            error(f"Binutils build failed: {toolchain_output_dir}/bin is empty")
            exit(1)
        else:
            success("Binutils build successful")

        os.chdir("..")

    if not no_gcc:
        # Build gcc
        info("Building GCC (this may take a while)")
        # Remove existing gcc build directory
        if os.path.exists("gcc-build") and not clear_cache:
            run_command(f"rm -rvf gcc-build", verbose)

        if not os.path.exists("gcc-build"):
            os.mkdir("gcc-build")

        os.chdir("gcc-build")

        check(run_command(
            f"./../gcc-{gcc_version}/configure --target={target_arch}-elf --prefix={toolchain_output_dir} --disable-nls --enable-languages=c,c++ --without-headers",
            verbose), "Failed to configure GCC")
        check(run_command(f"make all-gcc -j{jobs}", verbose), "Failed to build GCC")
        check(run_command(f"make all-target-libgcc -j{jobs}", verbose), "Failed to build GCC")
        check(run_command(f"make install-gcc", verbose), "Failed to install GCC")
        check(run_command(f"make install-target-libgcc", verbose), "Failed to install GCC")

        # Verify that gcc was built correctly
        # Run newly built gcc --version
        info("Verifying GCC installation")
        # You need to ./ here because we're running a local file, not in path
        os.chdir(f"{toolchain_output_dir}/bin")
        check(run_command(f"./{target_arch}-elf-gcc --version", verbose),
              "Failed to install GCC or GCC was built incorrectly")

    success("Successfully built toolchain")


def clean_toolchain(_args):
    """
    Clean the toolchain
    """
    info("Cleaning toolchain")

    # If the toolchain isn't in the project directory, we'll refuse to clean it
    # (just in case we delete something important)
    toolchain_path = os.path.abspath(_args.toolchain_path)

    if not toolchain_path.startswith(PROJECT_ROOT):
        error("Refusing to clean toolchain outside of project directory")
        exit(1)

    # Remove the toolchain directory
    check(run_command(f"stat {toolchain_path}", _args.verbose), "Failed to clean toolchain (does it exist?)")
    check(run_command(f"rm -rvf {toolchain_path}", _args.verbose), "Failed to clean toolchain (permissions?)")

    success("Successfully cleaned toolchain")


def clean_toolchain_temp(_args):
    """
    Clean the toolchain temp directory
    """
    info("Cleaning toolchain temp directory")

    if os.path.exists(TOOLCHAIN_TEMP_DIR):
        check(run_command(f"rm -rvf {TOOLCHAIN_TEMP_DIR}", _args.verbose),
              "Failed to clean toolchain temp directory")

    success("Successfully cleaned toolchain temp directory")


def clean_kernel(_args):
    """
    Clean the kernel
    """
    info("Cleaning kernel")

    # Check if the build directory exists
    if os.path.exists(os.path.join(PROJECT_ROOT, "build")):
        check(run_command(f"rm -rvf {os.path.join(PROJECT_ROOT, 'build')}", _args.verbose),
              "Failed to clean kernel (permissions?)")

    success("Successfully cleaned kernel")


def build_kernel(_args):
    """
    Build the kernel using CMake
    """
    info("Building kernel")

    # Make the build directory if it doesn't exist
    if not os.path.exists(os.path.join(PROJECT_ROOT, "build")):
        os.mkdir(os.path.join(PROJECT_ROOT, "build"))

    # Change to the build directory
    os.chdir(os.path.join(PROJECT_ROOT, "build"))

    # Build our cmake command to run
    cmake_command = f"cmake .."

    if _args.use_ninja:
        cmake_command += f" -GNinja"
    elif _args.use_make:
        cmake_command += f" -G\"Unix Makefiles\""

    cmake_command += f" -DCMAKE_TOOLCHAIN_FILE={_args.cmake_toolchain_file}"
    cmake_command += f" -DCMAKE_BUILD_TYPE={_args.build_type.title()}"
    cmake_command += f" -DTARGET_ARCH={_args.target_arch}"

    check(run_command(cmake_command, _args.verbose), "Failed to run CMake (try running with --clean-first)")

    if _args.use_ninja:
        check(run_command("ninja", _args.verbose),
              "Failed to build kernel (try running with --clean-first or --verbose for more info)")
    else:
        check(run_command("make", _args.verbose),
              "Failed to build kernel (try running with --clean-first or --verbose for more info)")

    # Make sure we reset our working directory
    os.chdir(PROJECT_ROOT)

    success("Successfully built kernel")


def build_iso(_args):
    """
    Make an ISO image
    """
    info("Making ISO image")

    check(run_command("mkdir -pv build/isodir/boot/grub", _args.verbose), "Failed to make grub build directory")
    check(run_command("cp -rv build/src/kernel/spark.bin build/isodir/boot", _args.verbose),
          "Failed to copy kernel to ISO directory")
    with open("build/isodir/boot/grub/grub.cfg", "w") as f:
        f.write("""
        menuentry \"spark++\" {
            multiboot /boot/spark.bin
        }
        """)

    check(run_command("grub-mkrescue -o build/spark.iso build/isodir", _args.verbose), "Failed to make ISO image")

    success("Successfully made ISO image (build/spark.iso)")


def run_qemu(_args):
    """
    Run the kernel in QEMU
    """
    info("Running spark++ in QEMU")

    # TODO: Automatically check architecture
    try:
        # We run this in verbose mode regardless of the user's choice
        # This is because we want to see the output of the serial port
        check(run_command("qemu-system-x86_64 -m 512 -serial stdio -cdrom build/spark.iso", True),
              "Failed to run kernel in QEMU")
    except KeyboardInterrupt:
        warn("You probably shouldn't force quit QEMU with Ctrl+C :/")

    success("Successfully shut down QEMU")

