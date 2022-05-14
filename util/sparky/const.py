import os
import sys

__VERSION__ = "0.1.0"

SCRIPT_PATH = os.path.abspath(sys.argv[0])
SCRIPT_DIR = os.path.dirname(SCRIPT_PATH)

DEFAULT_CMAKE_TOOLCHAIN_FILE = os.path.join(SCRIPT_DIR, "CMake", "toolchain")
DEFAULT_TOOLCHAIN_PATH = os.path.join(SCRIPT_DIR, "toolchain")
TOOLCHAIN_TEMP_DIR = os.path.join(SCRIPT_DIR, ".toolchain_build")

DEFAULT_GCC_VERSION = "12.1.0"
DEFAULT_BINUTILS_VERSION = "2.38"

DEFAULT_GCC_URL = "https://ftp.gnu.org/gnu/gcc/gcc-<GCC_VERSION>/gcc-<GCC_VERSION>.tar.gz"
DEFAULT_BINUTILS_URL = "https://ftp.gnu.org/gnu/binutils/binutils-<BINUTILS_VERSION>.tar.gz"

DEFAULT_ARCH = "i686"
