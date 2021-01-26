/*  Build Command Runner
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <iostream>
#include <QFile>
#include <QMessageBox>
#include "SharedCpp/Unicode.h"
#include "Tools/PersistentSettings.h"
#include "Tools.h"

#if _WIN32
#include <Windows.h>

int build_hexfile(const std::string& mcu, const QString& program_name){
//    if (system("make -v") != 0){
//        QMessageBox box;
//        box.critical(nullptr, "Error", "make not found. Please install WinAVR.");
//        return;
//    }

    QString hex_file = settings.path + program_name + ("-" + mcu + ".hex").c_str();
    QString log_file = settings.path + LOG_FOLDER_NAME + "/" + program_name + ("-" + mcu).c_str() + ".log";

    QFile file(hex_file);
    file.remove();

    using PokemonAutomation::utf8_to_wstr;
    QString module;
    for (auto ch : settings.path + CONFIG_FOLDER_NAME + "/BuildWindows.cmd"){
        module += ch == '/' ? '\\' : ch;
    }

    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    QString command = module + " " + mcu.c_str() + " " + program_name + " > " + log_file + ".log 2>&1";
    bool ret = CreateProcessW(
        nullptr,
        &utf8_to_wstr(command.toUtf8().data())[0],
        nullptr,
        nullptr,
        false,
        CREATE_NO_WINDOW,
        nullptr,
        nullptr,
        &si,
        &pi
    );
    if (!ret){
        ret = GetLastError();
        std::cout << "error = " << ret << std::endl;
        run_on_main_thread([=]{
            QMessageBox box;
            box.critical(nullptr, "Error", "Unable to open: " + module);
        });
        return 1;
    }
    ret = WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return ret;
}

#elif __APPLE__
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int build_hexfile(const std::string& mcu, const QString& program_name){
//    if (system("make -v") != 0){
//        QMessageBox box;
//        box.critical(nullptr, "Error", "make not found. Please install WinAVR.");
//        return;
//    }

    QString hex_file = settings.path + program_name + ("-" + mcu + ".hex").c_str();
    QString log_file = settings.path + LOG_FOLDER_NAME + "/" + program_name + ("-" + mcu).c_str() + ".log";

    QString module_dir = settings.path + SOURCE_FOLDER_NAME;
    QString module = "./Scripts/BuildOneUnix.sh ";
    QString command =  module + mcu.c_str() + " " + program_name + " gui > " + log_file + " 2>&1";

    // Since most macs will have the avr tools installed in /usr/local/bin, add it to the path now
    QString path = "/usr/local/bin:";
    path.append(getenv("PATH"));
    setenv("PATH", path.toUtf8(), 1);

    QFile file(hex_file);
    file.remove();

    // Saving our CWD to return to it later
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    // Move to our Device Source directory
    int cd_mod_dir = chdir(module_dir.toUtf8().data());
    if (cd_mod_dir !=0) {
        char msg[50];
        sprintf(msg, "chdir() to %s failed with code %d", module_dir.toUtf8().data(), cd_mod_dir);
        std::cout << msg;
        run_on_main_thread([=]{
            QMessageBox box;
            box.critical(nullptr, "Error", "Failed to change working directory to: " + module_dir);
        });
        return 1;
    }

    FILE* pipe = popen(command.toUtf8().data(), "r");
    if (!pipe) {
        std::cout << "Failed to create process with command " + command.toStdString();
        run_on_main_thread([=]{
            QMessageBox box;
            box.critical(nullptr, "Error", "Failed to create process for " + module);
        });
        return 1;
    };
    char buffer[262144];
    std::string data;
    std::string result;
    int dist=0;
    int size;

    //TIME_START
    while(!feof(pipe)) {
        size=(int)fread(buffer,1,262144, pipe); //cout<<buffer<<" size="<<size<<endl;
        data.resize(data.size()+size);
        memcpy(&data[dist],buffer,size);
        dist+=size;
    }
    //TIME_PRINT_
    int ret = pclose(pipe)/256;
    if (ret != 0) {
        std::cout << "error = " << data << std::endl;
        char msg[50];
        sprintf(msg, "Build process exited with code: %d", ret);
        run_on_main_thread([=]{
            QMessageBox box;
            box.critical(nullptr, "Error", msg);
        });
    }

    int cd_back = chdir(cwd);
    if ( cd_back !=0) {
        char msg[50];
        sprintf(msg, "Failed to change back to original working directory: code %d", cd_back);
        std::cout << msg;
        run_on_main_thread([=]{
            QMessageBox box;
            box.critical(nullptr, "Error", msg);
        });
    }
    return ret;
}
#else
#error "Platform not supported."
#endif
