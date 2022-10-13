import os
import sys

__VERSION__ = "0.1.0"

SCRIPT_PATH = os.path.abspath(sys.argv[0])
PROJECT_ROOT = os.path.dirname(SCRIPT_PATH)

DEFAULT_CMAKE_TOOLCHAIN_FILE = os.path.join(PROJECT_ROOT, "CMake", "toolchain.cmake")
DEFAULT_TOOLCHAIN_PATH = os.path.join(PROJECT_ROOT, "toolchain")
TOOLCHAIN_TEMP_DIR = os.path.join(PROJECT_ROOT, ".toolchain_build")

DEFAULT_GCC_VERSION = "12.2.0"
DEFAULT_BINUTILS_VERSION = "2.39"

DEFAULT_GCC_URL = "https://ftp.gnu.org/gnu/gcc/gcc-<GCC_VERSION>/gcc-<GCC_VERSION>.tar.gz"
DEFAULT_BINUTILS_URL = "https://ftp.gnu.org/gnu/binutils/binutils-<BINUTILS_VERSION>.tar.gz"

DEFAULT_ARCH = "i686"
