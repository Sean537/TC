/*
 * tc_system.hpp - TC库系统检测模块
 * TC System Detection Module
 *
 * 这个文件包含了TC库中的系统检测功能，包括：
 * - 操作系统类型宏定义
 * - 运行时系统检测函数
 * - 系统版本信息获取
 * - 跨平台系统识别支持
 *
 * This file contains system detection functionality in the TC library, including:
 * - Operating system type macro definitions
 * - Runtime system detection functions
 * - System version information retrieval
 * - Cross-platform system identification support
 *
 * 版本 Version: 1.1.2 Beta
 * 作者 Author: 537 Studio
 * 许可 License: MIT
 */

#ifndef TC_SYSTEM
#define TC_SYSTEM

// 平台特定头文件包含 | Platform-specific header includes
// Windows平台特定代码 | Windows platform specific code
#ifdef _WIN32
    #include <windows.h>

    #if !defined(__CYGWIN__)
        #define popen _popen
        #define pclose _pclose
    #endif
#else
// Linux/Unix 平台相关头文件
#include <sys/utsname.h>
#include <unistd.h>
#endif

// --- 系统环境宏定义 | System environment macro definitions ---
/**
 * 操作系统类型常量
 * Operating system type constants
 *
 * 这些宏定义了各种操作系统的标识符，用于systemCheck函数的返回值。
 * 每个操作系统类型都有一个唯一的数字代码。
 *
 * These macros define identifiers for various operating systems,
 * used as return values for the systemCheck function.
 * Each OS type has a unique numeric code.
 */

// 未知操作系统 | Unknown operating system
#define OS_UNKNOWN      0    // 无法识别的操作系统 | Unrecognized operating system

// Windows系列 | Windows family
#define OS_WINDOWS      100  // 通用Windows标识 | Generic Windows identifier
#define OS_WINDOWSNT6   108  // Windows 7/8/8.1 (NT 6.x)
#define OS_WINDOWSNT10  109  // Windows 10 (NT 10.0)
#define OS_WINDOWSNT11  110  // Windows 11 (NT 10.0 build 22000+)

// Linux发行版 | Linux distributions
#define OS_LINUX        200  // 通用Linux标识 | Generic Linux identifier
#define OS_UBUNTU       201  // Ubuntu Linux
#define OS_DEBIAN       202  // Debian Linux
#define OS_FEDORA       203  // Fedora Linux
#define OS_CENTOS       204  // CentOS Linux
#define OS_REDHAT       205  // Red Hat Enterprise Linux
#define OS_SUSE         206  // SUSE/openSUSE Linux
#define OS_ARCH         207  // Arch Linux
#define OS_GENTOO       208  // Gentoo Linux
#define OS_SLACKWARE    209  // Slackware Linux
#define OS_ANDROID      210  // Android (基于Linux | Based on Linux)
#define OS_KALI         211  // Kali Linux
#define OS_MINT         212  // Linux Mint
#define OS_MANJARO      213  // Manjaro Linux
#define OS_ALPINE       214  // Alpine Linux
#define OS_RASPBIAN     215  // Raspbian
#define OS_DEEPIN       216  // Deepin Linux
#define OS_ELEMENTARY   217  // Elementary OS
#define OS_ZORIN        218  // Zorin OS
#define OS_POPOS        219  // Pop!_OS
#define OS_CHROMEOS     220  // Chrome OS/Chromium OS

// Apple操作系统 | Apple operating systems
#define OS_MACOS            300  // 通用macOS标识 | Generic macOS identifier

// Mac OS X和现代macOS版本（XNU内核） | Mac OS X and Modern macOS versions (XNU kernel)
#define OS_MACOS_HIGHSIERRA 324  // macOS 10.13 High Sierra (2017)
#define OS_MACOS_MOJAVE     325  // macOS 10.14 Mojave (2018)
#define OS_MACOS_CATALINA   326  // macOS 10.15 Catalina (2019)
#define OS_MACOS_BIGSUR     327  // macOS 11 Big Sur (2020)
#define OS_MACOS_MONTEREY   328  // macOS 12 Monterey (2021)
#define OS_MACOS_VENTURA    329  // macOS 13 Ventura (2022)
#define OS_MACOS_SONOMA     330  // macOS 14 Sonoma (2023)
#define OS_MACOS_SEQUOIA    331  // macOS 15 Sequoia (2024)
#define OS_MACOS_TAHOE      332  // macOS 26 Tahoe (2025)

// 其他Apple操作系统 | Other Apple operating systems feat. crazy 537
#define OS_IOS          350  // iOS (iPhone/iPod touch)
#define OS_IPADOS       351  // iPadOS (iPad)
#define OS_WATCHOS      352  // watchOS (Apple Watch)
#define OS_TVOS         353  // tvOS (Apple TV)
#define OS_VISIONOS     354  // visionOS (Apple Vision Pro)
#define OS_BRIDGEOS     355  // bridgeOS (Apple T2芯片 | Apple T2 chip)
#define OS_AUDIOOS      356  // audioOS (HomePod)

// BSD系列 | BSD family
#define OS_BSD          400  // 通用BSD标识 | Generic BSD identifier
#define OS_FREEBSD      404  // FreeBSD

// Unix系列 | Unix family
#define OS_UNIX         500  // 通用Unix标识 | Generic Unix identifier

// 新兴操作系统 | Emerging operating systems
#define OS_FUCHSIA      950  // Google Fuchsia
#define OS_HARMONYOS    952  // Harmony OS

// 其它操作系统 | Other operating systems
#define OS_REACTOS      1000  // ReactOS

// --- systemCheck 函数 | systemCheck function ---
/**
 * 系统检测相关功能
 * System detection functionality
 */
#include <string>     // 字符串处理 | String processing
#include <algorithm>  // 算法函数 | Algorithm functions
#include <memory>     // 智能指针 | Smart pointers
#include <cstdio>     // C标准输入输出 | C standard I/O
#include <cstring>    // C字符串处理 | C string handling

namespace tc {
    /**
     * 执行系统命令并获取输出
     * Execute system command and get output
     *
     * 这个函数执行指定的系统命令并返回其输出。
     * This function executes the specified system command and returns its output.
     *
     * @param cmd 要执行的命令 | Command to execute
     * @return 命令的输出 | Command output
     */
    inline std::string executeCommand(const char* cmd) {
        std::string result;
        using pipe_ptr = std::unique_ptr<FILE, int(*)(FILE*)>;
#ifdef _MSC_VER
        pipe_ptr pipe(_popen(cmd, "r"), _pclose);   //MSVC实现
#else
        pipe_ptr pipe(popen(cmd, "r"), pclose);
#endif

        if (!pipe) {
            return "";
        }

        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
            result += buffer;
        }

        // 移除末尾的换行符
        if (!result.empty() && result[result.length()-1] == '\n') {
            result.erase(result.length()-1);
        }

        return result;
    }

    /**
     * 检测当前操作系统类型
     * Detect current operating system type
     *
     * 这个函数通过各种平台特定的API和检测方法，
     * 识别操作系统类型和版本。
     *
     * This function identifies the operating system type and version
     * through various platform-specific APIs and detection methods.
     *
     * @return 操作系统类型代码（如OS_WINDOWS, OS_LINUX等） | Operating system type code (e.g., OS_WINDOWS, OS_LINUX, etc.)
     */
    inline int systemCheck() {
        // Windows 平台检测
        #ifdef _WIN32
            // 检测ReactOS (基于Windows NT的开源操作系统)
            char buf[256] = {0};
            DWORD size = sizeof(buf);
            if (RegGetValueA(HKEY_LOCAL_MACHINE, "SOFTWARE\\ReactOS", "Version", RRF_RT_REG_SZ, NULL, buf, &size) == ERROR_SUCCESS) {
                return OS_REACTOS;
            }

            // 优先用RtlGetVersion获取真实主版本号（可以绕过应用程序兼容性检查）
            typedef LONG (WINAPI *RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);
            HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");
            if (hMod) {
                RtlGetVersionPtr fx = (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");
                if (fx) {
                    RTL_OSVERSIONINFOW rovi;
                    rovi.dwOSVersionInfoSize = sizeof(rovi);
                    if (fx(&rovi) == 0) {
                        // 细分Windows主版本号
                        if (rovi.dwMajorVersion == 6)  return OS_WINDOWSNT6;
                        if (rovi.dwMajorVersion == 10) {
                            // Win10/11区分：Win11为10.0.22000及以上
                            if (rovi.dwBuildNumber >= 22000) return OS_WINDOWSNT11;
                            else return OS_WINDOWSNT10;
                        }
                        if (rovi.dwMajorVersion > 10) return OS_WINDOWS; // 未来主版本
                    }
                }
            }

            // 兼容老方案（注意：在较新的Windows上可能会受到应用程序兼容性影响）
            OSVERSIONINFOEX osvi;
            osvi.dwOSVersionInfoSize = sizeof(osvi);
            #pragma warning(push)
            #pragma warning(disable: 4996) // 禁用GetVersionEx弃用警告
            if (GetVersionEx((OSVERSIONINFO*)&osvi)) {
                if (osvi.dwMajorVersion == 6)  return OS_WINDOWSNT6;
                if (osvi.dwMajorVersion == 10) {
                    if (osvi.dwBuildNumber >= 22000) return OS_WINDOWSNT11;
                    else return OS_WINDOWSNT10;
                }
                if (osvi.dwMajorVersion > 10) return OS_WINDOWSNT11;
            }
            #pragma warning(pop)

            // 如果上述方法都失败，尝试使用PowerShell命令获取系统版本
            std::string psOutput = executeCommand("powershell -Command \"(Get-CimInstance -ClassName Win32_OperatingSystem).Version\"");
            if (!psOutput.empty()) {
                // 解析版本号，格式为: 10.0.19045.0
                int majorVersion = 0, minorVersion = 0, buildNumber = 0;
                if (sscanf(psOutput.c_str(), "%d.%d.%d", &majorVersion, &minorVersion, &buildNumber) >= 3) {
                    if (majorVersion == 6) return OS_WINDOWSNT6;
                    if (majorVersion == 10) {
                        if (buildNumber >= 22000) return OS_WINDOWSNT11;
                        else return OS_WINDOWSNT10;
                    }
                    if (majorVersion > 10) return OS_WINDOWS;
                }
            }

            return OS_WINDOWS;

        // macOS/iOS 平台检测
        #elif defined(__APPLE__)
            #include <TargetConditionals.h>

            // 首先尝试使用系统命令获取设备类型和操作系统信息
            std::string deviceType = executeCommand("uname -m");
            std::string productType = executeCommand("sw_vers -productName 2>/dev/null");

            // 检查是否为macOS
            if (productType.find("Mac") != std::string::npos) {
                std::string swVers = executeCommand("sw_vers -productVersion");
                if (!swVers.empty()) {
                    // 解析版本号，格式为: 14.3.1 或 10.15.7
                    int majorVersion = 0, minorVersion = 0;
                    if (sscanf(swVers.c_str(), "%d.%d", &majorVersion, &minorVersion) >= 2) {
                        if (majorVersion >= 14) return OS_MACOS_SONOMA;
                        if (majorVersion == 13) return OS_MACOS_VENTURA;
                        if (majorVersion == 12) return OS_MACOS_MONTEREY;
                        if (majorVersion == 11) return OS_MACOS_BIGSUR;
                        if (majorVersion == 10) {
                            if (minorVersion == 15) return OS_MACOS_CATALINA;
                            if (minorVersion == 14) return OS_MACOS_MOJAVE;
                            if (minorVersion == 13) return OS_MACOS_HIGHSIERRA;
                        }
                    }
                }

                // 如果系统命令失败，回退到使用sysctlbyname
                #include <sys/sysctl.h>
                char str[256];
                size_t size = sizeof(str);
                int ret = sysctlbyname("kern.osrelease", str, &size, NULL, 0);

                if (ret == 0) {
                    // 解析内核版本号，格式为: 22.5.0 (macOS 13.4 Ventura)
                    int kernel_major = 0;
                    sscanf(str, "%d", &kernel_major);

                    // 根据Darwin内核版本映射到macOS版本
                    switch (kernel_major) {
                        case 25: return OS_MACOS_TAHOE;      // macOS 26 Tahoe (Darwin 25.x)
                        case 24: return OS_MACOS_SEQUOIA;    // macOS 15 Sequoia (Darwin 24.x)
                        case 23: return OS_MACOS_SONOMA;     // macOS 14 Sonoma (Darwin 23.x)
                        case 22: return OS_MACOS_VENTURA;    // macOS 13 Ventura (Darwin 22.x)
                        case 21: return OS_MACOS_MONTEREY;   // macOS 12 Monterey (Darwin 21.x)
                        case 20: return OS_MACOS_BIGSUR;     // macOS 11 Big Sur (Darwin 20.x)
                        case 19: return OS_MACOS_CATALINA;   // macOS 10.15 Catalina (Darwin 19.x)
                        case 18: return OS_MACOS_MOJAVE;     // macOS 10.14 Mojave (Darwin 18.x)
                        case 17: return OS_MACOS_HIGHSIERRA; // macOS 10.13 High Sierra (Darwin 17.x)
                        default: return OS_MACOS;            // 默认macOS
                    }
                }
                return OS_MACOS; // 默认macOS
            }

            // 检查是否为iOS/iPadOS/watchOS/tvOS等

            // 使用sysctl获取设备型号和系统信息
            #include <sys/sysctl.h>
            char buffer[256];
            size_t size = sizeof(buffer);

            // 获取硬件型号
            if (sysctlbyname("hw.machine", buffer, &size, NULL, 0) == 0) {
                std::string machine = buffer;

                // 根据设备型号前缀判断设备类型
                // iPhone: "iPhone"
                // iPad: "iPad"
                // iPod touch: "iPod"
                // Apple TV: "AppleTV"
                // Apple Watch: "Watch"
                // HomePod: "AudioAccessory"
                // Vision Pro: "RealityDevice"

                if (machine.find("iPhone") == 0) {
                    return OS_IOS;
                } else if (machine.find("iPad") == 0) {
                    // iOS 13及以上的iPad被认为运行iPadOS
                    // 获取系统版本
                    size = sizeof(buffer);
                    if (sysctlbyname("kern.osversion", buffer, &size, NULL, 0) == 0) {
                        std::string version = buffer;
                        // 简单判断iOS版本，如果是13.x或更高，则为iPadOS
                        if (version[0] >= '1' && version[1] >= '3') {
                            return OS_IPADOS;
                        }
                    }
                    return OS_IOS; // 默认为iOS
                } else if (machine.find("iPod") == 0) {
                    return OS_IOS;
                } else if (machine.find("Watch") == 0) {
                    return OS_WATCHOS;
                } else if (machine.find("AppleTV") == 0) {
                    return OS_TVOS;
                } else if (machine.find("AudioAccessory") == 0) {
                    return OS_AUDIOOS;
                } else if (machine.find("RealityDevice") == 0) {
                    return OS_VISIONOS;
                } else if (machine.find("Macmini") == 0 ||
                           machine.find("MacBook") == 0 ||
                           machine.find("iMac") == 0 ||
                           machine.find("Mac") == 0) {
                    // 如果是Mac但使用Apple Silicon，可能会有不同的标识
                    return OS_MACOS;
                }
            }

            // 如果无法确定具体类型，尝试使用kern.ostype
            size = sizeof(buffer);
            if (sysctlbyname("kern.ostype", buffer, &size, NULL, 0) == 0) {
                std::string ostype = buffer;
                if (ostype == "Darwin") {
                    // 获取内核版本，尝试判断是哪种Apple操作系统
                    size = sizeof(buffer);
                    if (sysctlbyname("kern.osrelease", buffer, &size, NULL, 0) == 0) {
                        std::string release = buffer;
                        int kernel_major = 0;
                        sscanf(buffer, "%d", &kernel_major);

                        // 根据内核版本大致判断
                        if (kernel_major >= 20) {
                            // 可能是iOS 14+, macOS 11+, watchOS 7+, tvOS 14+
                            // 由于无法确定具体是哪种系统，默认返回macOS
                            return OS_MACOS;
                        }
                    }
                }
            }

            // 默认返回macOS
            return OS_MACOS;

        // Linux 平台检测
        #elif defined(__linux__)
            // 检查是否为Android
            #ifdef __ANDROID__
                return OS_ANDROID;
            #else
                // 运行时检测Linux发行版
                // ...existing code...

                // 首先尝试使用lsb_release命令获取发行版信息
                std::string lsbRelease = executeCommand("lsb_release -i -s 2>/dev/null");
                if (!lsbRelease.empty()) {
                    std::transform(lsbRelease.begin(), lsbRelease.end(), lsbRelease.begin(), ::tolower);

                    if (lsbRelease.find("ubuntu") != std::string::npos) return OS_UBUNTU;
                    if (lsbRelease.find("debian") != std::string::npos) return OS_DEBIAN;
                    if (lsbRelease.find("fedora") != std::string::npos) return OS_FEDORA;
                    if (lsbRelease.find("centos") != std::string::npos) return OS_CENTOS;
                    if (lsbRelease.find("redhat") != std::string::npos || lsbRelease.find("red hat") != std::string::npos) return OS_REDHAT;
                    if (lsbRelease.find("suse") != std::string::npos) return OS_SUSE;
                    if (lsbRelease.find("arch") != std::string::npos) return OS_ARCH;
                    if (lsbRelease.find("gentoo") != std::string::npos) return OS_GENTOO;
                    if (lsbRelease.find("slackware") != std::string::npos) return OS_SLACKWARE;
                    if (lsbRelease.find("kali") != std::string::npos) return OS_KALI;
                    if (lsbRelease.find("linuxmint") != std::string::npos || lsbRelease.find("mint") != std::string::npos) return OS_MINT;
                    if (lsbRelease.find("manjaro") != std::string::npos) return OS_MANJARO;
                    if (lsbRelease.find("alpine") != std::string::npos) return OS_ALPINE;
                    if (lsbRelease.find("raspbian") != std::string::npos) return OS_RASPBIAN;
                    if (lsbRelease.find("deepin") != std::string::npos) return OS_DEEPIN;
                    if (lsbRelease.find("elementary") != std::string::npos) return OS_ELEMENTARY;
                    if (lsbRelease.find("zorin") != std::string::npos) return OS_ZORIN;
                    if (lsbRelease.find("pop") != std::string::npos) return OS_POPOS;
                    if (lsbRelease.find("chromeos") != std::string::npos || lsbRelease.find("chrome os") != std::string::npos) return OS_CHROMEOS;
                }

                // 如果lsb_release命令失败，尝试读取/etc/os-release文件
                FILE* fp = fopen("/etc/os-release", "r");
                if (fp) {
                    char line[256];
                    std::string id, name;

                    while (fgets(line, sizeof(line), fp)) {
                        if (strncmp(line, "ID=", 3) == 0) {
                            id = line + 3;
                            // 移除引号和换行符
                            id.erase(std::remove(id.begin(), id.end(), '"'), id.end());
                            id.erase(std::remove(id.begin(), id.end(), '\n'), id.end());
                        }
                        else if (strncmp(line, "NAME=", 5) == 0) {
                            name = line + 5;
                            // 移除引号和换行符
                            name.erase(std::remove(name.begin(), name.end(), '"'), name.end());
                            name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
                        }
                    }
                    fclose(fp);

                    // 根据ID或NAME识别发行版
                    if (!id.empty()) {
                        if (id == "ubuntu" || name.find("Ubuntu") != std::string::npos)
                            return OS_UBUNTU;
                        else if (id == "debian" || name.find("Debian") != std::string::npos)
                            return OS_DEBIAN;
                        else if (id == "fedora" || name.find("Fedora") != std::string::npos)
                            return OS_FEDORA;
                        else if (id == "centos" || name.find("CentOS") != std::string::npos)
                            return OS_CENTOS;
                        else if (id == "rhel" || name.find("Red Hat") != std::string::npos)
                            return OS_REDHAT;
                        else if (id == "opensuse" || id == "suse" || name.find("SUSE") != std::string::npos)
                            return OS_SUSE;
                        else if (id == "arch" || name.find("Arch") != std::string::npos)
                            return OS_ARCH;
                        else if (id == "gentoo" || name.find("Gentoo") != std::string::npos)
                            return OS_GENTOO;
                        else if (id == "slackware" || name.find("Slackware") != std::string::npos)
                            return OS_SLACKWARE;
                        else if (id == "kali" || name.find("Kali") != std::string::npos)
                            return OS_KALI;
                        else if (id == "linuxmint" || name.find("Linux Mint") != std::string::npos)
                            return OS_MINT;
                        else if (id == "manjaro" || name.find("Manjaro") != std::string::npos)
                            return OS_MANJARO;
                        else if (id == "alpine" || name.find("Alpine") != std::string::npos)
                            return OS_ALPINE;
                        else if (id == "raspbian" || name.find("Raspbian") != std::string::npos)
                            return OS_RASPBIAN;
                        else if (id == "deepin" || name.find("Deepin") != std::string::npos)
                            return OS_DEEPIN;
                        else if (id == "elementary" || name.find("Elementary") != std::string::npos)
                            return OS_ELEMENTARY;
                        else if (id == "zorin" || name.find("Zorin") != std::string::npos)
                            return OS_ZORIN;
                        else if (id == "pop" || name.find("Pop!_OS") != std::string::npos)
                            return OS_POPOS;
                        else if (id == "chromeos" || name.find("Chrome OS") != std::string::npos)
                            return OS_CHROMEOS;
                    }
                }

                // 尝试其他方法检测发行版
                if (access("/etc/kali-release", F_OK) != -1)
                    return OS_KALI;
                else if (access("/etc/lsb-release", F_OK) != -1) {
                    FILE* fp = fopen("/etc/lsb-release", "r");
                    if (fp) {
                        char line[256];
                        while (fgets(line, sizeof(line), fp)) {
                            if (strstr(line, "DISTRIB_ID=Ubuntu"))
                                return OS_UBUNTU;
                        }
                        fclose(fp);
                    }
                }
                else if (access("/etc/debian_version", F_OK) != -1)
                    return OS_DEBIAN;
                else if (access("/etc/fedora-release", F_OK) != -1)
                    return OS_FEDORA;
                else if (access("/etc/centos-release", F_OK) != -1)
                    return OS_CENTOS;
                else if (access("/etc/redhat-release", F_OK) != -1)
                    return OS_REDHAT;

                // 使用uname获取更多系统信息
                struct utsname un;
                if (uname(&un) == 0) {
                    // 可以进一步分析un.sysname, un.release等
                    std::string release = un.release;
                    std::transform(release.begin(), release.end(), release.begin(), ::tolower);

                    if (release.find("ubuntu") != std::string::npos) return OS_UBUNTU;
                    if (release.find("debian") != std::string::npos) return OS_DEBIAN;
                    if (release.find("fedora") != std::string::npos) return OS_FEDORA;
                    if (release.find("centos") != std::string::npos) return OS_CENTOS;
                    if (release.find("redhat") != std::string::npos) return OS_REDHAT;
                    if (release.find("suse") != std::string::npos) return OS_SUSE;
                    if (release.find("arch") != std::string::npos) return OS_ARCH;
                    if (release.find("gentoo") != std::string::npos) return OS_GENTOO;
                    if (release.find("slackware") != std::string::npos) return OS_SLACKWARE;
                }

                // 默认返回通用Linux
                return OS_LINUX;
            #endif

        // BSD系列检测
        #elif defined(__FreeBSD__)
            // 尝试使用系统命令获取FreeBSD版本
            std::string freebsdVer = executeCommand("freebsd-version 2>/dev/null");
            if (!freebsdVer.empty()) {
                // 可以进一步解析版本号
                return OS_FREEBSD;
            }

            // 如果命令失败，使用uname
            std::string unameOutput = executeCommand("uname -s");
            if (unameOutput.find("FreeBSD") != std::string::npos) {
                return OS_FREEBSD;
            }

            return OS_BSD;

        // 默认情况：未知操作系统
        #else
            // 尝试使用uname命令获取系统信息
            std::string unameOutput = executeCommand("uname -s");
            if (!unameOutput.empty()) {
                std::transform(unameOutput.begin(), unameOutput.end(), unameOutput.begin(), ::toupper);

                if (unameOutput.find("LINUX") != std::string::npos) return OS_LINUX;
                if (unameOutput.find("DARWIN") != std::string::npos) return OS_MACOS;
                if (unameOutput.find("FREEBSD") != std::string::npos) return OS_FREEBSD;
                if (unameOutput.find("NETBSD") != std::string::npos) return OS_NETBSD;
                if (unameOutput.find("OPENBSD") != std::string::npos) return OS_OPENBSD;
                if (unameOutput.find("DRAGONFLY") != std::string::npos) return OS_DRAGONFLY;
                if (unameOutput.find("SUNOS") != std::string::npos || unameOutput.find("SOLARIS") != std::string::npos) return OS_SOLARIS;
                if (unameOutput.find("HP-UX") != std::string::npos) return OS_HPUX;
                if (unameOutput.find("AIX") != std::string::npos) return OS_AIX;

                // 如果是某种UNIX变体
                if (unameOutput.find("BSD") != std::string::npos) return OS_BSD;
                if (unameOutput.find("UNIX") != std::string::npos) return OS_UNIX;
            }

            return OS_UNKNOWN;
        #endif
    } // systemCheck

    /**
     * 获取操作系统名称
     * Get operating system name
     *
     * 根据操作系统代码返回对应的操作系统名称。
     * Returns the corresponding operating system name based on the OS code.
     *
     * @param osCode 操作系统代码（由systemCheck函数返回） | Operating system code (returned by systemCheck function)
     * @return 操作系统名称字符串 | Operating system name string
     */
    inline const char* getOSName(int osCode) {
        switch(osCode) {
            // 未知操作系统 | Unknown operating system
            case OS_UNKNOWN: return "Unknown OS";

            // Windows系列 | Windows family
            case OS_WINDOWS: return "Windows";
            case OS_WINDOWSNT6: return "Windows 7/8/8.1";
            case OS_WINDOWSNT10: return "Windows 10";
            case OS_WINDOWSNT11: return "Windows 11";

            // Linux发行版 | Linux distributions
            case OS_LINUX: return "Linux";
            case OS_UBUNTU: return "Ubuntu Linux";
            case OS_DEBIAN: return "Debian Linux";
            case OS_FEDORA: return "Fedora Linux";
            case OS_CENTOS: return "CentOS Linux";
            case OS_REDHAT: return "Red Hat Enterprise Linux";
            case OS_SUSE: return "SUSE/openSUSE Linux";
            case OS_ARCH: return "Arch Linux";
            case OS_GENTOO: return "Gentoo Linux";
            case OS_SLACKWARE: return "Slackware Linux";
            case OS_KALI: return "Kali Linux";
            case OS_MINT: return "Linux Mint";
            case OS_MANJARO: return "Manjaro Linux";
            case OS_ALPINE: return "Alpine Linux";
            case OS_RASPBIAN: return "Raspbian";
            case OS_DEEPIN: return "Deepin Linux";
            case OS_ELEMENTARY: return "Elementary OS";
            case OS_ZORIN: return "Zorin OS";
            case OS_POPOS: return "Pop!_OS";
            case OS_CHROMEOS: return "Chrome OS/Chromium OS";
            case OS_ANDROID: return "Android";

            // macOS和Mac OS X版本 | macOS and Mac OS X versions
            case OS_MACOS: return "macOS";
            case OS_MACOS_SONOMA: return "macOS 14 Sonoma";
            case OS_MACOS_VENTURA: return "macOS 13 Ventura";
            case OS_MACOS_MONTEREY: return "macOS 12 Monterey";
            case OS_MACOS_BIGSUR: return "macOS 11 Big Sur";
            case OS_MACOS_CATALINA: return "macOS 10.15 Catalina";
            case OS_MACOS_MOJAVE: return "macOS 10.14 Mojave";
            case OS_MACOS_HIGHSIERRA: return "macOS 10.13 High Sierra";

            // 其他Apple操作系统 | Other Apple operating systems
            case OS_IOS: return "iOS";
            case OS_IPADOS: return "iPadOS";
            case OS_WATCHOS: return "watchOS";
            case OS_TVOS: return "tvOS";
            case OS_VISIONOS: return "visionOS";
            case OS_BRIDGEOS: return "bridgeOS";
            case OS_AUDIOOS: return "audioOS";

            // BSD系列 | BSD family
            case OS_BSD: return "BSD";
            case OS_FREEBSD: return "FreeBSD";

            // 其他操作系统 | Other operating systems
            case OS_UNIX: return "UNIX";

            // 新兴操作系统 | Emerging operating systems
            case OS_FUCHSIA: return "Google Fuchsia";
            case OS_HARMONYOS: return "Harmony OS";

            // 其它操作系统 | Other operating systems
            case OS_REACTOS: return "ReactOS";

            // 默认情况 | Default case
            default: return "Unknown OS";
        }
    }

    /**
     * 获取操作系统版本信息
     * Get operating system version information
     *
     * 获取当前操作系统的详细版本信息。
     * Get detailed version information of the current operating system.
     *
     * @return 操作系统版本信息字符串 | Operating system version information string
     */
    inline std::string getOSVersionInfo() {
        std::string versionInfo;

        #ifdef _WIN32
            // Windows版本信息
            typedef LONG (WINAPI *RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);
            HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");
            if (hMod) {
                RtlGetVersionPtr fx = (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");
                if (fx) {
                    RTL_OSVERSIONINFOW rovi;
                    rovi.dwOSVersionInfoSize = sizeof(rovi);
                    if (fx(&rovi) == 0) {
                        char buffer[256];
                        sprintf(buffer, "Windows %lu.%lu.%lu",
                                rovi.dwMajorVersion,
                                rovi.dwMinorVersion,
                                rovi.dwBuildNumber);
                        versionInfo = buffer;
                    }
                }
            }

            // 如果上述方法失败，尝试使用PowerShell命令
            if (versionInfo.empty()) {
                std::string psOutput = executeCommand("powershell -Command \"(Get-CimInstance -ClassName Win32_OperatingSystem).Caption\"");
                if (!psOutput.empty()) {
                    versionInfo = psOutput;
                }
            }
        #elif defined(__APPLE__)
            // macOS版本信息
            std::string swVers = executeCommand("sw_vers -productVersion");
            std::string buildVers = executeCommand("sw_vers -buildVersion");
            if (!swVers.empty()) {
                versionInfo = "macOS " + swVers;
                if (!buildVers.empty()) {
                    versionInfo += " (Build " + buildVers + ")";
                }
            }
        #elif defined(__linux__)
            // Linux版本信息
            #ifdef __ANDROID__
                // Android版本
                versionInfo = "Android";
                // 可以尝试获取更详细的Android版本信息
            #else
                // 尝试使用lsb_release获取发行版信息
                std::string lsbDesc = executeCommand("lsb_release -d -s 2>/dev/null");
                if (!lsbDesc.empty()) {
                    versionInfo = lsbDesc;
                } else {
                    // 尝试读取/etc/os-release文件
                    FILE* fp = fopen("/etc/os-release", "r");
                    if (fp) {
                        char line[256];
                        std::string prettyName;

                        while (fgets(line, sizeof(line), fp)) {
                            if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
                                prettyName = line + 12;
                                // 移除引号和换行符
                                prettyName.erase(std::remove(prettyName.begin(), prettyName.end(), '"'), prettyName.end());
                                prettyName.erase(std::remove(prettyName.begin(), prettyName.end(), '\n'), prettyName.end());
                                break;
                            }
                        }
                        fclose(fp);

                        if (!prettyName.empty()) {
                            versionInfo = prettyName;
                        }
                    }
                }

                // 如果上述方法都失败，使用uname
                if (versionInfo.empty()) {
                    struct utsname un;
                    if (uname(&un) == 0) {
                        versionInfo = std::string(un.sysname) + " " + un.release;
                    }
                }
            #endif
        #elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
            // BSD版本信息
            struct utsname un;
            if (uname(&un) == 0) {
                versionInfo = std::string(un.sysname) + " " + un.release;
            }
        #else
            // 其他操作系统，尝试使用uname
            struct utsname un;
            if (uname(&un) == 0) {
                versionInfo = std::string(un.sysname) + " " + un.release;
            } else {
                versionInfo = "Unknown OS Version";
            }
        #endif

        return versionInfo;
    }
}   // namespace tc

#endif
