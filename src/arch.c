#include "include/arch.h"

const char* get_architecture() {

    #if defined(__x86_64__) || defined(_M_X64)
        return "x86_64";

    #elif defined(__i386) || defined(_M_IX86)
        return "i386";

    #elif defined(__aarch64__)
        return "ARM64";

    #elif defined(__arm__) || defined(_M_ARM)
        return "ARM";

    #elif defined(__powerpc64__) || defined(__ppc64__)
        return "PowerPC 64-bit";

    #elif defined(__powerpc__) || defined(__ppc__)
        return "PowerPC";

    #elif defined(__mips__) || defined(__mips)
        return "MIPS";

    #elif defined(__riscv)
        return "RISC-V";

    #else
        return "Unknown";

    #endif

}

const char* get_os() {
    #if defined(_WIN32) || defined(_WIN64)
        return "Windows";
    #elif defined(__APPLE__) || defined(__MACH__)
        return "macOS";
    #elif defined(__linux__)
        return "Linux";
    #elif defined(__FreeBSD__)
        return "FreeBSD";
    #elif defined(__NetBSD__)
        return "NetBSD";
    #elif defined(__OpenBSD__)
        return "OpenBSD";
    #elif defined(__unix__) || defined(__unix)
        return "Unix";
    #else
        return "Unknown";
    #endif
}
