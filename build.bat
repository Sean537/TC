@echo off
REM TC 项目构建脚本

echo 检查构建环境...
cmake --version >nul 2>&1
if %errorlevel% neq 0 (
    echo 错误: CMake 未安装或不在 PATH 中
    echo 请先安装 CMake: https://cmake.org/download/
    pause
    exit /b 1
)

echo ✓ CMake 可用

set BUILD_DIR=build
set EXAMPLE_DIR=bin\examples

echo.
echo 选择构建选项:
echo 1. Release 构建 (推荐)
echo 2. Debug 构建
echo 3. 清理构建产物
echo 4. 退出

set /p choice=请输入选项 (1-4): 

if "%choice%"=="1" goto release
if "%choice%"=="2" goto debug
if "%choice%"=="3" goto clean
if "%choice%"=="4" goto exit
echo 无效选项
pause
exit /b 1

:release
echo.
echo 开始 Release 构建...
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cmake -S . -B "%BUILD_DIR%" -DCMAKE_BUILD_TYPE=Release
if %errorlevel% neq 0 (
    echo CMake 配置失败
    pause
    exit /b 1
)
cmake --build "%BUILD_DIR%" --config Release
if %errorlevel% neq 0 (
    echo 构建失败
    pause
    exit /b 1
)
echo ✓ Release 构建完成！
echo 可执行文件在 %EXAMPLE_DIR% 目录
goto success

:debug
echo.
echo 开始 Debug 构建...
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cmake -S . -B "%BUILD_DIR%" -DCMAKE_BUILD_TYPE=Debug
if %errorlevel% neq 0 (
    echo CMake 配置失败
    pause
    exit /b 1
)
cmake --build "%BUILD_DIR%" --config Debug
if %errorlevel% neq 0 (
    echo 构建失败
    pause
    exit /b 1
)
echo ✓ Debug 构建完成！
echo 可执行文件在 %EXAMPLE_DIR% 目录
goto success

:clean
echo.
echo 清理构建产物...
if exist "%BUILD_DIR%" rmdir /S /Q "%BUILD_DIR%" 2>nul && echo 清理 build 目录
if exist "%EXAMPLE_DIR%" rmdir /S /Q "%EXAMPLE_DIR%" 2>nul && echo 清理 examples 目录
echo ✓ 清理完成
goto success

:success
echo.
echo 构建脚本执行完成！
pause
exit /b 0

:exit
echo 退出构建脚本
exit /b 0