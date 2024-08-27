#include "include/arch.h"

const char* get_architecture(void) {
    #if defined(__x86_64__) || defined(_M_X64)
        return "x86_64";
    #elif defined(__i386) || defined(_M_IX86)
        return "i386";
    #elif defined(__aarch64__)
        return "ARM64";
    #elif defined(__arm__) || defined(_M_ARM)
        return "ARM";
    #elif defined(__powerpc64__) || defined(__ppc64__)
        return "PowerPC64";
    #elif defined(__powerpc__) || defined(__ppc__)
        return "PowerPC";
    #elif defined(__mips__) || defined(__mips)
        return "MIPS";
    #elif defined(__riscv)
        return "RISC-V";
    #elif defined(__SH4__)
        return "SH4";
    #elif defined(__alpha__)
        return "Alpha";
    #else
        return "Unknown";
    #endif
}

const char* get_os(void) {
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

const char* get_compiler(void) {
    #if defined(__GNUC__) || defined(__GNUG__)
        return "GCC";
    #elif defined(__ICC) || defined(__INTEL_COMPILER)
        return "Intel ICC/ICL";
    #elif defined(__ICC) || defined(__INTEL_LLVM_COMPILER)
        return "Intel ICX";
    #elif defined(__clang__)
        return "Clang";
    #elif defined(_MSC_VER)
        return "MSVC";
    #else
        return "Unknown";
    #endif
}

const char* get_libc(void) {
    #if defined(__GLIBC__) || defined(__GLIBC_MINOR__)
        return "Glibc";
    #elif defined(__musl__)
        return "Musl";
    #elif defined(__BIONIC__)
        return "Bionic";
    #elif defined(__NEWLIB__)
        return "newlib";
    #elif defined(_MSC_VER)
        return "MSVCRT"
    #elif defined(__MINGW32__)
        return "MinGW";
    #else
        return "Unkown";
    #endif
}
