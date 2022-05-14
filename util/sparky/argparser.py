# Thanks Chase Seibert, this is alot better than using argparse on its own
# https://chase-seibert.github.io/blog/2014/03/21/python-multilevel-argparse.html
import argparse
import os.path
from argparse import Namespace
import sys
from .io import debug, info, warn, success, error, YELLOW, print_colored, colored_string, confirm
from .const import __VERSION__, DEFAULT_ARCH, DEFAULT_TOOLCHAIN_PATH, DEFAULT_GCC_VERSION, DEFAULT_BINUTILS_VERSION, \
    DEFAULT_CMAKE_TOOLCHAIN_FILE, PROJECT_ROOT
import util.sparky.build as build
import pprint

"""
Our CLI will be structured as follows:
top level commands:
    - build (component)
    - clean (component(s))
    - run
    - test

    build components:
        - build kernel modules (name | all)
        - build userland
        - build library (name | all)


clean components:
    - clean kernel
    - clean kernel modules
    - clean userland
    - clean library
"""


def merge_args(a, b):
    if isinstance(a, Namespace):
        a = vars(a)
    if isinstance(b, Namespace):
        b = vars(b)

    return Namespace(**{**a, **b})


class SparkyCLIArgparse:
    def __init__(self):
        parser = argparse.ArgumentParser(description="sparky - Spark++ build utility",
                                         add_help=False,
                                         usage="""sparky <command> [<args>]
                                         
Available commands:
    build <component> [<args>] - Builds a specific component (e.g. toolchain, kernel, etc.)
    clean <component> [<args>] - Cleans a specific component (e.g. toolchain, kernel, etc.)
    test <component> [<args>] - Runs tests for a specific component (e.g. toolchain, kernel, etc.)
    generate <component> [<args>] - Generates a specific component (e.g. toolchain, kernel, etc.)
    run [<args>] - Runs spark++
    
Other options:
    -h, --help - Prints this help message
    -v, --version - Prints the version of sparky
    -d, --debug - Prints debug information
""")
        parser.add_argument("--version", "-v", help="Show sparky version information and exit", action="store_true")
        parser.add_argument("command", help="Subcommand to run", nargs="?")

        # Args to pass down to subcommands
        parser.add_argument("--verbose", help="Show verbose output", action="store_true")
        parser.add_argument("--help", "-h", help="Show this help message and exit", action="store_true")
        parser.add_argument("--debug", "-d", help="Prints debug information", action="store_true")

        args = parser.parse_known_args(sys.argv[1:])[0]

        args_for_subcommand = Namespace(verbose=args.verbose, help=args.help, debug=args.debug)

        if args.help and not args.command:
            parser.print_usage()
            exit(0)

        if args.version:
            print(f"sparky - spark++ build helper\nv{__VERSION__}")
            exit()

        if not hasattr(self, args.command or ""):
            error("Invalid command")
            parser.print_help()
            exit(1)

        # Call subcommand by name
        getattr(self, args.command)(args_for_subcommand)

    def run(self, args):
        # TODO: Maybe add some arguments

        # Confirm that the build/spark.iso file exists
        if not os.path.exists(os.path.join(PROJECT_ROOT, "build", "spark.iso")):
            error("spark.iso not found. Run `sparky build kernel` to build spark.iso")
            exit(1)

        build.run_qemu(args)

    def build(self, parent_args):
        parser = argparse.ArgumentParser(description="Builds a specific component (e.g. toolchain, kernel, etc.)")
        parser.add_argument("component", help="Component to build", nargs="?")

        # Shared args
        parser.add_argument("--build-type", "-b", help="Build type (release or debug) (default: debug)",
                            choices=["release", "debug"], default="debug")
        parser.add_argument("--jobs", "-j", help="Number of jobs to run simultaneously (default: 1)", type=int,
                            default=1)
        parser.add_argument("--cmake-toolchain-file", help="Path to the CMake toolchain file to use",
                            default=DEFAULT_CMAKE_TOOLCHAIN_FILE)
        parser.add_argument("--target-arch", "-t", help="Target architecture (default: i686)", default=DEFAULT_ARCH)
        parser.add_argument("--use-make", help="Use make instead of ninja", action="store_true")
        parser.add_argument("--use-ninja", help="Use ninja instead of make", action="store_true")

        args = merge_args(parser.parse_known_args(sys.argv[2:])[0], parent_args)

        valid_components = ["toolchain", "kernel", "userland", "library", "test", "all"]

        if args.help and not args.component:
            parser.print_usage()
            exit(0)

        if not args.component:
            error(f"No component specified, valid components are: {', '.join(valid_components)}")
            exit(1)

        # Make sure 'use-make' and 'use-ninja' are mutually exclusive
        if args.use_make and args.use_ninja:
            error("Cannot use both --use-make and --use-ninja")
            exit(1)

        # If we have neither 'use-make' nor 'use-ninja', use ninja by default
        if not args.use_make and not args.use_ninja:
            args.use_ninja = True

        # Check that the component is valid
        if args.component not in valid_components:
            error(f"Invalid component: {args.component} (must be one of {', '.join(valid_components)})")
            exit(1)

        args_for_subcommand = Namespace(verbose=args.verbose, help=args.help, build_type=args.build_type,
                                        jobs=args.jobs, target_arch=args.target_arch, use_make=args.use_make,
                                        use_ninja=args.use_ninja, cmake_toolchain_file=args.cmake_toolchain_file)

        # Call subcommand by name
        getattr(self, "build_" + args.component)(args)

    def build_toolchain(self, parent_args=None):
        parser = argparse.ArgumentParser(description="Builds the toolchain")
        parser.add_argument("--clear-cache", help="Clear the cache before building (download and build)",
                            action="store_true")
        parser.add_argument("--no-cache", help="Don't use cached downloads to build the toolchain", action="store_true")
        parser.add_argument("--no-install", help="Don't install the toolchain", action="store_true")
        parser.add_argument("--output-dir",
                            help=f"The directory to output the built toolchain to (default: {DEFAULT_TOOLCHAIN_PATH})",
                            default=DEFAULT_TOOLCHAIN_PATH)
        parser.add_argument("--overwrite", help="Overwrite the output directory if it exists (confirm)",
                            action="store_true")
        parser.add_argument("--no-gcc", help="Don't build GCC", action="store_true")
        parser.add_argument("--no-binutils", help="Don't build binutils", action="store_true")
        parser.add_argument("--gcc-version", help="GCC version to build (default: {DEFAULT_GCC_VERSION})",
                            default=DEFAULT_GCC_VERSION)
        parser.add_argument("--binutils-version",
                            help=f"Binutils version to build (default: {DEFAULT_BINUTILS_VERSION})",
                            default=DEFAULT_BINUTILS_VERSION)
        parser.add_argument("--gcc-url", help="The URL to download the GCC archive from")
        parser.add_argument("--binutils-url", help="The URL to download the binutils archive from")

        args = merge_args(parser.parse_known_args(sys.argv[3:])[0], parent_args)

        warn(f"Note that this is not the OS targeted toolchain, it is just a generic {args.target_arch} compiler")
        print_colored(f"This will be replaced with the {args.target_arch}-spark compiler once libC is written.", YELLOW)
        build.build_toolchain(args)

    def build_kernel(self, parent_args=None):
        parser = argparse.ArgumentParser(description="Builds the kernel")
        parser.add_argument("--no-iso", help="Don't build the ISO", action="store_true")
        parser.add_argument("--clean-first", help="Clean the build directory before building (can resolve issues)", action="store_true")

        args = merge_args(parser.parse_known_args(sys.argv[3:])[0], parent_args)

        if args.clean_first:
            build.clean_kernel(args)

        build.build_kernel(args)
        if not args.no_iso:
            build.build_iso(args)

    def clean(self, parent_args):
        parser = argparse.ArgumentParser(description="Clean one or more components")
        parser.add_argument("components", help="Component(s) to clean", nargs="*")

        # Shared args
        parser.add_argument("--no-confirm", "-y", help="Don't ask for confirmation (destructive)", action="store_true")

        args = merge_args(parser.parse_known_args(sys.argv[2:])[0], parent_args)

        valid_components = ["toolchain", "temp", "kernel", "userland", "library", "test", "all"]

        if args.help and not args.components:
            parser.print_usage()
            exit(0)

        if not args.components:
            error(f"No component(s) specified, valid components are: {', '.join(valid_components)}")
            exit(1)

        # Check that the component is valid
        for component in args.components:
            if component not in valid_components:
                error(f"Invalid component: {args.components} (must be one of {', '.join(valid_components)})")
                exit(1)

        args_for_subcommand = Namespace(verbose=args.verbose, help=args.help, no_confirm=args.no_confirm,
                                        args_to_skip=len(args.components) - 1)

        # Call subcommand by name
        for component in args.components:
            getattr(self, "clean_" + component)(args_for_subcommand)

    def clean_toolchain(self, parent_args):
        parser = argparse.ArgumentParser(
            description=f"Clean the toolchain {colored_string('WARNING: DESTRUCTIVE', YELLOW)}")
        parser.add_argument("--toolchain-path",
                            help=f"The directory of the toolchain to clean (default: {DEFAULT_TOOLCHAIN_PATH})",
                            default=DEFAULT_TOOLCHAIN_PATH)

        args = merge_args(parser.parse_known_args(sys.argv[3 + parent_args.args_to_skip:])[0], parent_args)

        if not args.no_confirm:
            print_colored("Are you sure you want to clean the toolchain?", YELLOW)
            if not confirm(f"Rebuilding may be a lengthy process, are you sure you want to continue?"):
                info("Cancelling clean toolchain")
                exit(0)

        build.clean_toolchain(args)

    def clean_temp(self, parent_args):
        parser = argparse.ArgumentParser(
            description="Clean the toolchain temporary directory")

        args = merge_args(parser.parse_known_args(sys.argv[3 + parent_args.args_to_skip:])[0], parent_args)

        build.clean_toolchain_temp(args)

    def clean_kernel(self, parent_args):
        parser = argparse.ArgumentParser(
            description="Clean the kernel build directory")

        args = merge_args(parser.parse_known_args(sys.argv[3 + parent_args.args_to_skip:])[0], parent_args)

        build.clean_kernel(args)

    def generate(self, parent_args):
        parser = argparse.ArgumentParser(description="Generate something")
        parser.add_argument("component", help="The component to generate (e.g. cmake toolchain file)")

        args = merge_args(parser.parse_known_args(sys.argv[2:])[0], parent_args)

        print(args)
