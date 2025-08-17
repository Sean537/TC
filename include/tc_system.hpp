#ifndef TC_SYSTEM
#define TC_SYSTEM

// 平台特定头文件包含 | Platform-specific header includes
#ifdef _WIN32 // Windows平台特定代码 | Windows platform specific code
    #include <windows.h> // Windows API函数和数据类型 | Windows API functions and data types
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
#define OS_WINDOWSNT3   103  // Windows NT 3.x
#define OS_WINDOWSNT4   104  // Windows NT 4.0
#define OS_WINDOWSNT5   105  // Windows 2000/XP/2003 (NT 5.x)
#define OS_WINDOWSNT6   106  // Windows Vista/7/8/8.1 (NT 6.x)
#define OS_WINDOWSNT10  110  // Windows 10 (NT 10.0)
#define OS_WINDOWSNT11  111  // Windows 11 (NT 10.0 build 22000+)
#define OS_WIN95        195  // Windows 95
#define OS_WIN98        198  // Windows 98
#define OS_WINME        199  // Windows ME
#define OS_WINCE        120  // Windows CE

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
// 现代macOS和Mac OS X版本 | Modern macOS and Mac OS X versions
#define OS_MACOS        300  // 通用macOS标识 | Generic macOS identifier
#define OS_MACOS_SONOMA 301  // macOS 14 Sonoma (2023)
#define OS_MACOS_VENTURA 302 // macOS 13 Ventura (2022)
#define OS_MACOS_MONTEREY 303 // macOS 12 Monterey (2021)
#define OS_MACOS_BIGSUR 304  // macOS 11 Big Sur (2020)
#define OS_MACOS_CATALINA 305 // macOS 10.15 Catalina (2019)
#define OS_MACOS_MOJAVE 306  // macOS 10.14 Mojave (2018)
#define OS_MACOS_HIGHSIERRA 307 // macOS 10.13 High Sierra (2017)
#define OS_MACOS_SIERRA 308  // macOS 10.12 Sierra (2016)
#define OS_OSX_ELCAPITAN 309 // OS X 10.11 El Capitan (2015)
#define OS_OSX_YOSEMITE 310  // OS X 10.10 Yosemite (2014)
#define OS_OSX_MAVERICKS 311 // OS X 10.9 Mavericks (2013)
#define OS_OSX_MOUNTAINLION 312 // OS X 10.8 Mountain Lion (2012)
#define OS_OSX_LION     313  // Mac OS X 10.7 Lion (2011)
#define OS_OSX_SNOWLEOPARD 314 // Mac OS X 10.6 Snow Leopard (2009)
#define OS_OSX_LEOPARD  315  // Mac OS X 10.5 Leopard (2007)
#define OS_OSX_TIGER    316  // Mac OS X 10.4 Tiger (2005)
#define OS_OSX_PANTHER  317  // Mac OS X 10.3 Panther (2003)
#define OS_OSX_JAGUAR   318  // Mac OS X 10.2 Jaguar (2002)
#define OS_OSX_PUMA     319  // Mac OS X 10.1 Puma (2001)
#define OS_OSX_CHEETAH  320  // Mac OS X 10.0 Cheetah (2001)
#define OS_OSX_BETA     321  // Mac OS X Public Beta (2000)

// 经典Macintosh系统 | Classic Macintosh systems
#define OS_MACOS9       330  // Mac OS 9 (1999)
#define OS_MACOS8       331  // Mac OS 8 (1997)
#define OS_MACOS7       332  // System 7 (1991)
#define OS_MACOS6       333  // System 6 (1988)
#define OS_MACOS5       334  // System 5 (1987)
#define OS_MACOS4       335  // System 4 (1987)
#define OS_MACOS3       336  // System 3 (1986)
#define OS_MACOS2       337  // System 2 (1985)
#define OS_MACOS1       338  // System 1 (1984)

// 其他Apple操作系统 | Other Apple operating systems
#define OS_IOS          350  // iOS (iPhone/iPod touch)
#define OS_IPADOS       351  // iPadOS (iPad)
#define OS_WATCHOS      352  // watchOS (Apple Watch)
#define OS_TVOS         353  // tvOS (Apple TV)
#define OS_VISIONOS     354  // visionOS (Apple Vision Pro)
#define OS_BRIDGEOS     355  // bridgeOS (Apple T2芯片 | Apple T2 chip)
#define OS_AUDIOOS      356  // audioOS (HomePod)

// BSD系列 | BSD family
#define OS_BSD          400  // 通用BSD标识 | Generic BSD identifier
#define OS_DRAGONFLY    401  // DragonFly BSD
#define OS_NETBSD       402  // NetBSD
#define OS_OPENBSD      403  // OpenBSD
#define OS_FREEBSD      404  // FreeBSD

// Unix系列 | Unix family
#define OS_UNIX         500  // 通用Unix标识 | Generic Unix identifier
#define OS_HURD         501  // GNU Hurd
#define OS_XENIX        502  // Xenix

// DOS和其他系统 | DOS and other systems
#define OS_DOS          600  // DOS
#define OS_PLAN9        601  // Plan 9
#define OS_INFERNO      602  // Inferno

// BeOS系列 | BeOS family
#define OS_BEOS         700  // BeOS
#define OS_HAIKU        701  // Haiku
#define OS_SYLLABLE     702  // Syllable
#define OS_MENUETOS     703  // MenuetOS
#define OS_REACTOS      704  // ReactOS
#define OS_KOLIBRIOS    705  // KolibriOS

// 商业Unix系统 | Commercial Unix systems
#define OS_AIX          800  // IBM AIX
#define OS_SOLARIS      810  // Oracle Solaris
#define OS_MINIX        820  // MINIX
#define OS_QNX          830  // QNX
#define OS_VMS          840  // VMS
#define OS_ZOS          841  // IBM z/OS
#define OS_OS400        842  // IBM OS/400
#define OS_TPF          843  // IBM TPF

// 其他操作系统 | Other operating systems
#define OS_AMIGAOS      850  // AmigaOS
#define OS_MORPHOS      851  // MorphOS
#define OS_FREEMINT     852  // FreeMiNT
#define OS_HPUX         860  // HP-UX
#define OS_IRIX         861  // IRIX
#define OS_SCO          862  // SCO
#define OS_OPENVMS      863  // OpenVMS
#define OS_RISCOS       870  // RISC OS
#define OS_OS2          900  // OS/2
#define OS_NEXTSTEP     910  // NeXTSTEP

// 嵌入式操作系统 | Embedded operating systems
#define OS_NUTTX        920  // NuttX
#define OS_ZEPHYR       921  // Zephyr
#define OS_CONTIKI      922  // Contiki
#define OS_RIOT         923  // RIOT

// 新兴操作系统 | Emerging operating systems
#define OS_FUCHSIA      950  // Google Fuchsia
#define OS_REDOX        951  // Redox OS
#define OS_HARMONY      952  // Harmony OS
#define OS_XJ380        953  // XJ380

// 嵌入式/实时操作系统 | Embedded/Real-time operating systems
#define OS_VXWORKS      1000 // VxWorks
#define OS_RTEMS        1001 // RTEMS
#define OS_FREERTOS     1002 // FreeRTOS
#define OS_THREADX      1003 // ThreadX
#define OS_INTEGRITY    1004 // INTEGRITY
#define OS_NUCLEUS      1005 // Nucleus RTOS
#define OS_UCOSII       1006 // μC/OS-II
#define OS_UCOSIII      1007 // μC/OS-III
#define OS_PSOS         1008 // pSOS
#define OS_ECOS         1009 // eCos

// --- systemCheck 函数 | systemCheck function ---
/**
 * 系统检测相关功能
 * System detection functionality
 */
#include <string>     // 字符串处理 | String processing
#include <algorithm>  // 算法函数 | Algorithm functions

namespace tc {
    /**
     * 检测当前操作系统类型
     * Detect current operating system type
     * 
     * 这个函数通过各种平台特定的API和检测方法，
     * 识别当前运行的操作系统类型和版本。
     * 
     * This function identifies the current operating system type and version
     * through various platform-specific APIs and detection methods.
     * 
     * @return 操作系统类型代码（如OS_WINDOWS, OS_LINUX等） | Operating system type code (e.g., OS_WINDOWS, OS_LINUX, etc.)
     */
    inline int systemCheck() {
#if defined(_WIN32) || defined(_WIN64)
        // 检测ReactOS (基于Windows NT的开源操作系统)
        char buf[256] = {0};
        DWORD size = sizeof(buf);
        if (RegGetValueA(HKEY_LOCAL_MACHINE, "SOFTWARE\\ReactOS", "Version", RRF_RT_REG_SZ, NULL, buf, &size) == ERROR_SUCCESS) {
            return OS_REACTOS;
        }

        // 优先用RtlGetVersion获取真实主版本号
        typedef LONG (WINAPI *RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);
        HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");
        if (hMod) {
            RtlGetVersionPtr fx = (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");
            if (fx) {
                RTL_OSVERSIONINFOW rovi = {0};
                rovi.dwOSVersionInfoSize = sizeof(rovi);
                if (fx(&rovi) == 0) {
                    // 细分Windows主版本号
                    if (rovi.dwMajorVersion == 3)  return OS_WINDOWSNT3;
                    if (rovi.dwMajorVersion == 4)  return OS_WINDOWSNT4;
                    if (rovi.dwMajorVersion == 5)  return OS_WINDOWSNT5;
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
        // 兼容老方案
        OSVERSIONINFOEX osvi = {0};
        osvi.dwOSVersionInfoSize = sizeof(osvi);
        if (GetVersionEx((OSVERSIONINFO*)&osvi)) {
            if (osvi.dwMajorVersion == 3)  return OS_WINDOWSNT3;
            if (osvi.dwMajorVersion == 4)  return OS_WINDOWSNT4;
            if (osvi.dwMajorVersion == 5)  return OS_WINDOWSNT5;
            if (osvi.dwMajorVersion == 6)  return OS_WINDOWSNT6;
            if (osvi.dwMajorVersion == 10) {
                if (osvi.dwBuildNumber >= 22000) return OS_WINDOWSNT11;
                else return OS_WINDOWSNT10;
            }
            if (osvi.dwMajorVersion > 10) return OS_WINDOWSNT11;
            // 9x系列
            if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
                if (osvi.dwMinorVersion == 0) return OS_WIN95;
                if (osvi.dwMinorVersion == 10) return OS_WIN98;
                if (osvi.dwMinorVersion == 90) return OS_WINME;
            }
            // CE
            #ifdef VER_PLATFORM_WIN32_CE
                if (osvi.dwPlatformId == VER_PLATFORM_WIN32_CE) return OS_WINCE;
            #endif
        }
    return OS_WINDOWS;

#elif defined(__ANDROID__)
        return OS_ANDROID;

#elif defined(__HAIKU__)
        return OS_HAIKU;

#elif defined(__SYLLABLE__)
        return OS_SYLLABLE;

#elif defined(__REACTOS__)
        return OS_REACTOS;

#elif defined(__kolibri__) || defined(__KOLIBRI__)
        return OS_KOLIBRIOS;

#elif defined(_AIX) || defined(__AIX__)
        return OS_AIX;

#elif defined(__sun) && defined(__SVR4)
        return OS_SOLARIS;

#elif defined(__minix)
        return OS_MINIX;

#elif defined(__QNX__) || defined(__QNXNTO__)
        return OS_QNX;

#elif defined(__INTEGRITY)
        return OS_INTEGRITY;

#elif defined(__VMS) || defined(__VMS__)
        return OS_VMS;

#elif defined(__MVS__) || defined(__HOS_MVS__) || defined(__TOS_MVS__)
        return OS_ZOS;

#elif defined(__OS400__)
        return OS_OS400;

#elif defined(__amigaos__)
        return OS_AMIGAOS;

#elif defined(__MORPHOS__)
        return OS_MORPHOS;

#elif defined(__MINT__)
        return OS_FREEMINT;

#elif defined(__hpux) || defined(__hpux__)
        return OS_HPUX;

#elif defined(__sgi)
        return OS_IRIX;

#elif defined(__SCO_VERSION__)
        return OS_SCO;

#elif defined(__OPENVMS)
        return OS_OPENVMS;

#elif defined(__riscos) || defined(__riscos__)
        return OS_RISCOS;

#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    // 检测苹果各种操作系统
    #if defined(TARGET_OS_VISION) && TARGET_OS_VISION
        return OS_VISIONOS;  // visionOS (Apple Vision Pro)
    #elif defined(TARGET_OS_BRIDGE) && TARGET_OS_BRIDGE
        return OS_BRIDGEOS;  // bridgeOS (Apple T2芯片)
    #elif defined(TARGET_OS_WATCH) && TARGET_OS_WATCH
        return OS_WATCHOS;   // watchOS (Apple Watch)
    #elif defined(TARGET_OS_TV) && TARGET_OS_TV
        return OS_TVOS;      // tvOS (Apple TV)
    #elif defined(TARGET_OS_MACCATALYST) && TARGET_OS_MACCATALYST
        return OS_MACOS;     // Mac Catalyst (iPad应用运行在Mac上)
    #elif TARGET_OS_IPHONE
        // iOS设备进一步区分
        #if defined(TARGET_OS_IOS) && TARGET_OS_IOS
            // 检测是否为iPadOS (iOS 13+的iPad)
            #if defined(UI_USER_INTERFACE_IDIOM)
                if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
                    // iOS 13及以上的iPad被认为运行iPadOS
                    #if defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 130000
                        return OS_IPADOS;
                    #endif
                }
            #endif
            return OS_IOS;   // iOS (iPhone/iPod touch)
        #endif
        return OS_IOS;       // 默认iOS
    #elif defined(TARGET_OS_OSX) && TARGET_OS_OSX
        // macOS版本检测
        #include <sys/sysctl.h>
        char str[256];
        size_t size = sizeof(str);
        int ret = sysctlbyname("kern.osrelease", str, &size, NULL, 0);
        
        if (ret == 0) {
            // 解析内核版本号，格式为: 22.5.0 (macOS 13.4 Ventura)
            int kernel_major = 0;
            sscanf(str, "%d", &kernel_major);
            
            // 根据Darwin内核版本映射到macOS版本
            // 参考: https://en.wikipedia.org/wiki/Darwin_(operating_system)
            switch (kernel_major) {
                case 23: return OS_MACOS_SONOMA;     // macOS 14 Sonoma (Darwin 23.x)
                case 22: return OS_MACOS_VENTURA;    // macOS 13 Ventura (Darwin 22.x)
                case 21: return OS_MACOS_MONTEREY;   // macOS 12 Monterey (Darwin 21.x)
                case 20: return OS_MACOS_BIGSUR;     // macOS 11 Big Sur (Darwin 20.x)
                case 19: return OS_MACOS_CATALINA;   // macOS 10.15 Catalina (Darwin 19.x)
                case 18: return OS_MACOS_MOJAVE;     // macOS 10.14 Mojave (Darwin 18.x)
                case 17: return OS_MACOS_HIGHSIERRA; // macOS 10.13 High Sierra (Darwin 17.x)
                case 16: return OS_MACOS_SIERRA;     // macOS 10.12 Sierra (Darwin 16.x)
                case 15: return OS_OSX_ELCAPITAN;    // OS X 10.11 El Capitan (Darwin 15.x)
                case 14: return OS_OSX_YOSEMITE;     // OS X 10.10 Yosemite (Darwin 14.x)
                case 13: return OS_OSX_MAVERICKS;    // OS X 10.9 Mavericks (Darwin 13.x)
                case 12: return OS_OSX_MOUNTAINLION; // OS X 10.8 Mountain Lion (Darwin 12.x)
                case 11: return OS_OSX_LION;         // Mac OS X 10.7 Lion (Darwin 11.x)
                case 10: return OS_OSX_SNOWLEOPARD;  // Mac OS X 10.6 Snow Leopard (Darwin 10.x)
                case 9:  return OS_OSX_LEOPARD;      // Mac OS X 10.5 Leopard (Darwin 9.x)
                case 8:  return OS_OSX_TIGER;        // Mac OS X 10.4 Tiger (Darwin 8.x)
                case 7:  return OS_OSX_PANTHER;      // Mac OS X 10.3 Panther (Darwin 7.x)
                case 6:  return OS_OSX_JAGUAR;       // Mac OS X 10.2 Jaguar (Darwin 6.x)
                case 5:  return OS_OSX_PUMA;         // Mac OS X 10.1 Puma (Darwin 5.x)
                case 4:  return OS_OSX_CHEETAH;      // Mac OS X 10.0 Cheetah (Darwin 4.x)
                case 1:
                case 2:
                case 3:  return OS_OSX_BETA;         // Mac OS X Public Beta/Server (Darwin 1.x-3.x)
                default:
                    // 检查是否为经典Mac OS (非Darwin内核)
                    // 这部分在现代系统上不会执行，仅为完整性保留
                    if (kernel_major == 0) {
                        // 尝试获取系统版本
                        ret = sysctlbyname("kern.osversion", str, &size, NULL, 0);
                        if (ret == 0) {
                            int os_version = 0;
                            sscanf(str, "%d", &os_version);
                            
                            // 经典Mac OS版本
                            if (os_version >= 9) return OS_MACOS9;
                            else if (os_version >= 8) return OS_MACOS8;
                            else if (os_version >= 7) return OS_MACOS7;
                            else if (os_version >= 6) return OS_MACOS6;
                            else if (os_version >= 5) return OS_MACOS5;
                            else if (os_version >= 4) return OS_MACOS4;
                            else if (os_version >= 3) return OS_MACOS3;
                            else if (os_version >= 2) return OS_MACOS2;
                            else if (os_version >= 1) return OS_MACOS1;
                        }
                    }
                    return OS_MACOS; // 默认macOS
            }
        }
        
        // 如果sysctlbyname失败，尝试使用Gestalt API (仅适用于旧版Mac OS)
        #if defined(MAC_OS_X_VERSION_MIN_REQUIRED) && MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_8
        #include <CoreServices/CoreServices.h>
        SInt32 gestaltVersion;
        if (Gestalt(gestaltSystemVersion, &gestaltVersion) == noErr) {
            // Gestalt返回的版本格式为: 0x0ABC，其中A=主版本，B=次版本，C=修订版本
            int major = (gestaltVersion >> 8) & 0xF;
            
            switch (major) {
                case 9: return OS_MACOS9;
                case 8: return OS_MACOS8;
                case 7: return OS_MACOS7;
                case 6: return OS_MACOS6;
                case 5: return OS_MACOS5;
                case 4: return OS_MACOS4;
                case 3: return OS_MACOS3;
                case 2: return OS_MACOS2;
                case 1: return OS_MACOS1;
                default: break;
            }
        }
        #endif
        
        return OS_MACOS;     // 默认macOS
    #elif defined(TARGET_OS_EMBEDDED) && TARGET_OS_EMBEDDED
        // 可能是HomePod的audioOS
        return OS_AUDIOOS;   // audioOS (HomePod)
    #else
        return OS_MACOS;     // 默认macOS
    #endif

#elif defined(__DragonFly__)
        return OS_DRAGONFLY;

#elif defined(__NetBSD__)
        return OS_NETBSD;

#elif defined(__OpenBSD__)
        return OS_OPENBSD;

#elif defined(__FreeBSD__)
        return OS_FREEBSD;

#elif defined(__GNU__) || defined(__gnu_hurd__)
        return OS_HURD;

#elif defined(__CYGWIN__)
        return OS_UNIX; // Cygwin是类Unix环境

#elif defined(__XENIX__)
        return OS_XENIX;

#elif defined(__PLAN9__)
        return OS_PLAN9;

#elif defined(__INFERNO__)
        return OS_INFERNO;

#elif defined(__Fuchsia__)
        return OS_FUCHSIA;

#elif defined(__redox__)
        return OS_REDOX;

#elif defined(__HARMONY_OS__) || defined(HARMONY_OS)
        return OS_HARMONY;

#elif defined(__VXWORKS__)
        return OS_VXWORKS;

#elif defined(__RTEMS__)
        return OS_RTEMS;

#elif defined(__FreeRTOS__)
        return OS_FREERTOS;

#elif defined(__ThreadX__) || defined(TX_INCLUDE_USER_DEFINE_FILE)
        return OS_THREADX;

#elif defined(__NUCLEUS__)
        return OS_NUCLEUS;

#elif defined(__UCOS_II__)
        return OS_UCOSII;

#elif defined(__UCOS_III__)
        return OS_UCOSIII;

#elif defined(__PSOS__)
        return OS_PSOS;

#elif defined(__ECOS__)
        return OS_ECOS;

#elif defined(__NUTTX__)
        return OS_NUTTX;

#elif defined(ZEPHYR_VERSION_CODE)
        return OS_ZEPHYR;

#elif defined(CONTIKI)
        return OS_CONTIKI;

#elif defined(RIOT_VERSION)
        return OS_RIOT;

#elif defined(__XJ380__)
        return OS_XJ380;

#elif defined(__linux__)
        // 检查是否为特定Linux发行版
        #ifdef __ANDROID__
            return OS_ANDROID; // 再次检查Android
        #else
            // 通过读取/etc/os-release文件来识别具体的Linux发行版
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
            // 检查是否为Kali Linux
            if (access("/etc/kali-release", F_OK) != -1)
                return OS_KALI;
            // 检查是否为Ubuntu
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
            // 检查是否为Debian
            else if (access("/etc/debian_version", F_OK) != -1)
                return OS_DEBIAN;
            // 检查是否为Fedora
            else if (access("/etc/fedora-release", F_OK) != -1)
                return OS_FEDORA;
            // 检查是否为CentOS
            else if (access("/etc/centos-release", F_OK) != -1)
                return OS_CENTOS;
            // 检查是否为Red Hat
            else if (access("/etc/redhat-release", F_OK) != -1)
                return OS_REDHAT;
            
            // 默认返回通用Linux
            return OS_LINUX;
        #endif

#elif defined(__unix__) || defined(__unix)
        // 通用Unix检测
        #if defined(__FreeBSD__)
            return OS_FREEBSD;
        #elif defined(__NetBSD__)
            return OS_NETBSD;
        #elif defined(__OpenBSD__)
            return OS_OPENBSD;
        #elif defined(__DragonFly__)
            return OS_DRAGONFLY;
        #else
            return OS_UNIX;
        #endif

#elif defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
        return OS_DOS;

#elif defined(__BEOS__)
        return OS_BEOS;

#elif defined(__OS2__) || defined(_OS2) || defined(OS2)
        return OS_OS2;

#elif defined(__NeXT__)
        return OS_NEXTSTEP;

#else
    // 尝试通过uname等系统调用进一步识别
    #if defined(_POSIX_VERSION)
        return OS_UNIX; // POSIX兼容系统
    #else
        return OS_UNKNOWN;
    #endif
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
            case OS_WINDOWSNT3: return "Windows NT 3.x";
            case OS_WINDOWSNT4: return "Windows NT 4.0";
            case OS_WINDOWSNT5: return "Windows 2000/XP/2003";
            case OS_WINDOWSNT6: return "Windows Vista/7/8/8.1";
            case OS_WINDOWSNT10: return "Windows 10";
            case OS_WINDOWSNT11: return "Windows 11";
            case OS_WIN95: return "Windows 95";
            case OS_WIN98: return "Windows 98";
            case OS_WINME: return "Windows ME";
            case OS_WINCE: return "Windows CE";
            
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
            case OS_MACOS_SIERRA: return "macOS 10.12 Sierra";
            case OS_OSX_ELCAPITAN: return "OS X 10.11 El Capitan";
            case OS_OSX_YOSEMITE: return "OS X 10.10 Yosemite";
            case OS_OSX_MAVERICKS: return "OS X 10.9 Mavericks";
            case OS_OSX_MOUNTAINLION: return "OS X 10.8 Mountain Lion";
            case OS_OSX_LION: return "Mac OS X 10.7 Lion";
            case OS_OSX_SNOWLEOPARD: return "Mac OS X 10.6 Snow Leopard";
            case OS_OSX_LEOPARD: return "Mac OS X 10.5 Leopard";
            case OS_OSX_TIGER: return "Mac OS X 10.4 Tiger";
            case OS_OSX_PANTHER: return "Mac OS X 10.3 Panther";
            case OS_OSX_JAGUAR: return "Mac OS X 10.2 Jaguar";
            case OS_OSX_PUMA: return "Mac OS X 10.1 Puma";
            case OS_OSX_CHEETAH: return "Mac OS X 10.0 Cheetah";
            case OS_OSX_BETA: return "Mac OS X Public Beta";
            
            // 经典Macintosh系统 | Classic Macintosh systems
            case OS_MACOS9: return "Mac OS 9";
            case OS_MACOS8: return "Mac OS 8";
            case OS_MACOS7: return "System 7";
            case OS_MACOS6: return "System 6";
            case OS_MACOS5: return "System 5";
            case OS_MACOS4: return "System 4";
            case OS_MACOS3: return "System 3";
            case OS_MACOS2: return "System 2";
            case OS_MACOS1: return "System 1";
            
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
            case OS_DRAGONFLY: return "DragonFly BSD";
            case OS_NETBSD: return "NetBSD";
            case OS_OPENBSD: return "OpenBSD";
            case OS_FREEBSD: return "FreeBSD";
            
            // 其他操作系统 | Other operating systems
            case OS_UNIX: return "UNIX";
            case OS_HURD: return "GNU Hurd";
            case OS_XENIX: return "Xenix";
            case OS_DOS: return "DOS";
            case OS_PLAN9: return "Plan 9";
            case OS_INFERNO: return "Inferno";
            case OS_BEOS: return "BeOS";
            case OS_HAIKU: return "Haiku";
            case OS_SYLLABLE: return "Syllable";
            case OS_MENUETOS: return "MenuetOS";
            case OS_REACTOS: return "ReactOS";
            case OS_KOLIBRIOS: return "KolibriOS";
            case OS_AIX: return "AIX";
            case OS_SOLARIS: return "Solaris";
            case OS_MINIX: return "MINIX";
            case OS_QNX: return "QNX";
            case OS_VMS: return "VMS";
            case OS_ZOS: return "z/OS";
            case OS_OS400: return "OS/400";
            case OS_TPF: return "TPF";
            case OS_AMIGAOS: return "AmigaOS";
            case OS_MORPHOS: return "MorphOS";
            case OS_FREEMINT: return "FreeMiNT";
            case OS_HPUX: return "HP-UX";
            case OS_IRIX: return "IRIX";
            case OS_SCO: return "SCO";
            case OS_OPENVMS: return "OpenVMS";
            case OS_RISCOS: return "RISC OS";
            case OS_OS2: return "OS/2";
            case OS_NEXTSTEP: return "NeXTSTEP";
            
            // 嵌入式/实时操作系统 | Embedded/Real-time operating systems
            case OS_NUTTX: return "NuttX";
            case OS_ZEPHYR: return "Zephyr";
            case OS_CONTIKI: return "Contiki";
            case OS_RIOT: return "RIOT";
            case OS_VXWORKS: return "VxWorks";
            case OS_RTEMS: return "RTEMS";
            case OS_FREERTOS: return "FreeRTOS";
            case OS_THREADX: return "ThreadX";
            case OS_INTEGRITY: return "INTEGRITY";
            case OS_NUCLEUS: return "Nucleus RTOS";
            case OS_UCOSII: return "μC/OS-II";
            case OS_UCOSIII: return "μC/OS-III";
            case OS_PSOS: return "pSOS";
            case OS_ECOS: return "eCos";
            
            // 新兴操作系统 | Emerging operating systems
            case OS_FUCHSIA: return "Google Fuchsia";
            case OS_REDOX: return "Redox OS";
            case OS_HARMONY: return "Harmony OS";
            case OS_XJ380: return "XJ380";
        
            // 默认情况 | Default case
            default: return "Unknown OS";
        }
    }
} // namespace tc

#endif