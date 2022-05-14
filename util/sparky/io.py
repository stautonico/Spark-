# Colors
BLACK = "\033[30m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
CYAN = "\033[36m"
WHITE = "\033[37m"
RESET = "\033[0m"


def colored_string(msg, color):
    """Returns a colored string"""
    return f"{color}{msg}{RESET}"


def print_colored(msg, color):
    """Prints a message in a given color"""
    print(f"{color}{msg}{RESET}")


def debug(msg):
    """Prints a debug message"""
    print_colored(f"{CYAN}[ DEBUG ]{RESET} {msg}", CYAN)


def info(msg):
    """Prints an info message"""
    print(f"{BLUE}[ INFO ]{RESET} {msg}")


def warn(msg):
    """Prints a warning message"""
    print(f"{YELLOW}[ WARN ]{RESET} {msg}")


def success(msg):
    """Prints a success message"""
    print_colored(f"{GREEN}[ SUCCESS ]{RESET} {msg}", GREEN)


def error(msg):
    """Prints an error message"""
    print_colored(f"{RED}[ ERROR ]{RESET} {msg}", RED)


def confirm(msg, color=RED):
    """Asks the user to confirm an action"""
    print(f"{color}[ CONFIRM ]{RESET} {msg}")
    return input(f"{color}[ CONFIRM ]{RESET} [ Y/n ] ").lower() == "y"
