#include "core.h"
#include <iostream>
#include <thread>
#include<qprocess.h>
#include <cstdint>

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <QString>
#include <QProcess>
#include <QtDebug>
//QProcess::execute("google-chrome");


// Date constructor
CoreProcessing::CoreProcessing()
{
    UseCore = std::thread::hardware_concurrency();//Retourne le nombre de coeur sur la machine et mettre dans UseCore
}

unsigned int CoreProcessing::CPUThreadCount(){
    return std::thread::hardware_concurrency();//Retourne le nombre de coeur sur la machine
}

std::string CurrentFileOpen(){
    return "";
}

void CoreProcessing::exec(){
    std::thread *tt = new std::thread[UseCore];//On créer les Threads
    for (unsigned int i = 0; i < UseCore; ++i) {
        tt[i] = std::thread(&CoreProcessing::call_from_thread,this,i);
    }
    for (unsigned int i = 0; i < UseCore; ++i){
        tt[i].join();
    }
    delete [] tt;//On nettoie la Memoire

}

[[ noreturn ]] void CoreProcessing::call_from_thread(int tid) {
        //std::thread::id this_id = std::this_thread::get_id();
        int random = std::rand();
        qDebug() << "Launched by thread " << tid;
        qDebug() << "Thread ID: " << random;

        //for(;;){}
}




/*
QProcess process;
process.start("google-chrome");
process.waitForFinished(-1); // will wait forever until finished

QString stdout = process.readAllStandardOutput();
QString stderr = process.readAllStandardError();
qDebug() << stdout;
qDebug() << "*************************";
qDebug() << stderr;
*/

/*
QString exec(const char* cmd) {//https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix

    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return "";
}
*/