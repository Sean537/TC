# 操作系统支持与系统检测

本文档描述了 tc_system.hpp 中的操作系统支持和系统检测功能。

## 操作系统宏定义

以下是 tc_system.hpp 中定义的操作系统宏，按类型分类：

### 未知操作系统

| 宏定义 | 数值 | 描述 |
|-------|------|------|
| OS_UNKNOWN | 0 | 无法识别的操作系统 |

### Windows 系列

| 宏定义 | 数值 | 描述 |
|-------|------|------|
| OS_WINDOWS | 100 | 通用Windows标识 |
| OS_WINDOWSNT6 | 108 | Windows 7/8/8.1 (NT 6.x) |
| OS_WINDOWSNT10 | 109 | Windows 10 (NT 10.0) |
| OS_WINDOWSNT11 | 110 | Windows 11 (NT 10.0 build 22000+) |

### Linux 发行版

| 宏定义 | 数值 | 描述 |
|-------|------|------|
| OS_LINUX | 200 | 通用Linux标识 |
| OS_UBUNTU | 201 | Ubuntu Linux |
| OS_DEBIAN | 202 | Debian Linux |
| OS_FEDORA | 203 | Fedora Linux |
| OS_CENTOS | 204 | CentOS Linux |
| OS_REDHAT | 205 | Red Hat Enterprise Linux |
| OS_SUSE | 206 | SUSE/openSUSE Linux |
| OS_ARCH | 207 | Arch Linux |
| OS_GENTOO | 208 | Gentoo Linux |
| OS_SLACKWARE | 209 | Slackware Linux |
| OS_ANDROID | 210 | Android (基于Linux) |
| OS_KALI | 211 | Kali Linux |
| OS_MINT | 212 | Linux Mint |
| OS_MANJARO | 213 | Manjaro Linux |
| OS_ALPINE | 214 | Alpine Linux |
| OS_RASPBIAN | 215 | Raspbian |
| OS_DEEPIN | 216 | Deepin Linux |
| OS_ELEMENTARY | 217 | Elementary OS |
| OS_ZORIN | 218 | Zorin OS |
| OS_POPOS | 219 | Pop!_OS |
| OS_CHROMEOS | 220 | Chrome OS/Chromium OS |

### Apple 操作系统

| 宏定义 | 数值 | 描述 |
|-------|------|------|
| OS_MACOS | 300 | 通用macOS标识 |
| OS_MACOS_HIGHSIERRA | 324 | macOS 10.13 High Sierra (2017) |
| OS_MACOS_MOJAVE | 325 | macOS 10.14 Mojave (2018) |
| OS_MACOS_CATALINA | 326 | macOS 10.15 Catalina (2019) |
| OS_MACOS_BIGSUR | 327 | macOS 11 Big Sur (2020) |
| OS_MACOS_MONTEREY | 328 | macOS 12 Monterey (2021) |
| OS_MACOS_VENTURA | 329 | macOS 13 Ventura (2022) |
| OS_MACOS_SONOMA | 330 | macOS 14 Sonoma (2023) |
| OS_MACOS_SEQUOIA | 331 | macOS 15 Sequoia (2024) |
| OS_MACOS_TAHOE | 332 | macOS 26 Tahoe (2025) |

### 其他 Apple 操作系统

| 宏定义 | 数值 | 描述 |
|-------|------|------|
| OS_IOS | 350 | iOS (iPhone/iPod touch) |
| OS_IPADOS | 351 | iPadOS (iPad) |
| OS_WATCHOS | 352 | watchOS (Apple Watch) |
| OS_TVOS | 353 | tvOS (Apple TV) |
| OS_VISIONOS | 354 | visionOS (Apple Vision Pro) |
| OS_BRIDGEOS | 355 | bridgeOS (Apple T2芯片) |
| OS_AUDIOOS | 356 | audioOS (HomePod) |

### BSD 系列

| 宏定义 | 数值 | 描述 |
|-------|------|------|
| OS_BSD | 400 | 通用BSD标识 |
| OS_FREEBSD | 404 | FreeBSD |

### Unix 系列

| 宏定义 | 数值 | 描述 |
|-------|------|------|
| OS_UNIX | 500 | 通用Unix标识 |

### 新兴操作系统

| 宏定义 | 数值 | 描述 |
|-------|------|------|
| OS_FUCHSIA | 950 | Google Fuchsia |
| OS_HARMONYOS | 952 | Harmony OS |

### 其它操作系统

| 宏定义 | 数值 | 描述 |
|-------|------|------|
| OS_REACTOS | 1000 | ReactOS (基于Windows NT的开源操作系统)|

## 已删除的操作系统

以下是已从 tc_system.hpp 中删除的操作系统宏，因为它们不支持本库需要的 C++17：

1. Windows 旧版本：
   - Windows 95 (OS_WIN95)
   - Windows 98 (OS_WIN98)
   - Windows ME (OS_WINME)
   - Windows CE (OS_WINCE)
   - Windows NT 3.x (OS_WINDOWSNT3)
   - Windows NT 4.0 (OS_WINDOWSNT4)
   - Windows 2000/XP/2003 (OS_WINDOWSNT5)
   - Windows Vista (包含在 OS_WINDOWSNT6 中，但已从检测代码中移除)

2. macOS 旧版本：
   - 经典 Mac OS 系统 (OS_MACOS1 到 OS_MACOS9)
   - Mac OS X 10.0 Cheetah 到 10.12 Sierra (OS_MACOSX_CHEETAH 到 OS_MACOS_SIERRA)
   - Mac OS X Server 系列

3. 其他已删除的操作系统：
   - DOS 系列 (OS_DOS)
   - BeOS 系列 (OS_BEOS, OS_HAIKU 等)
   - 旧 Unix 系统 (OS_HURD, OS_XENIX)
   - 商业 Unix 系统 (OS_AIX, OS_SOLARIS 等)
   - 嵌入式操作系统 (OS_NUTTX, OS_ZEPHYR 等)
   - 其他不支持 C++17 的操作系统

## 系统检测功能

tc_system.hpp 提供了以下系统检测相关的函数：

### systemCheck()

```cpp
inline int systemCheck();
```

此函数通过各种平台特定的API和检测方法，识别当前运行的操作系统类型和版本。它返回一个整数代码，对应于上述宏定义中的一个。

特点：
- 使用运行时检测而非仅依赖编译时宏
- 对于Windows系统，使用RtlGetVersion、GetVersionEx和PowerShell命令获取真实版本号
- 对于macOS系统，使用sw_vers命令和sysctlbyname获取版本信息
- 对于iOS/iPadOS/watchOS等系统，通过硬件型号(hw.machine)识别设备类型
- 对于Linux系统，使用lsb_release命令、/etc/os-release文件和uname命令识别发行版

### getOSName(int osCode)

```cpp
inline const char* getOSName(int osCode);
```

此函数根据systemCheck()返回的操作系统代码，返回对应的操作系统名称字符串。

### getOSVersionInfo()

```cpp
inline std::string getOSVersionInfo();
```

此函数获取当前操作系统的详细版本信息，包括版本号、构建号等。

## 使用示例

```cpp
#include "tc.hpp"
#include <iostream>

int main() {
    // 获取系统信息
    int osCode = tc::systemCheck();
    const char* osName = tc::getOSName(osCode);
    std::string osVersionInfo = tc::getOSVersionInfo();
    
    // 显示系统信息
    std::cout << "操作系统代码: " << osCode << std::endl;
    std::cout << "操作系统名称: " << osName << std::endl;
    std::cout << "操作系统版本: " << osVersionInfo << std::endl;
    
    return 0;
}
```

## 注意事项

1. 系统检测功能在运行时执行，因此能够准确识别当前运行的操作系统，而不仅仅依赖于编译时的宏定义。

2. 对于苹果设备，特别是在macOS上交叉编译的iOS/iPadOS应用，系统检测会通过硬件型号和系统特性进行识别，而不仅仅依赖于编译时的TARGET_OS_*宏。

3. 对于Linux系统，会尝试多种方法识别具体的发行版，包括lsb_release命令、/etc/os-release文件和特定发行版的标识文件。