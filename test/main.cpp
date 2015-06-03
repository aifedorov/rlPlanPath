#include <iostream>
#include <QProcess>

using namespace std;

int main()
{
    QProcess process;
    process.start("/home/user/rlPlanPath/rlPlanDemo/bin/rlPlanDemo", QStringList() << "/home/user/rlPlanPath/kuka_kr_10_r1100_sixx/rlplan/kuka_kr10_r1100_sixx.xml" << "--enable-quit" << "--disable-viewer" << "--disable-wait" << "--height=1 --width=1");

    // Wait for it to start
    if(!process.waitForStarted())
        return 0;

    // Continue reading the data until EOF reached
    QByteArray data;

    while(process.waitForReadyRead())
        data.append(process.readAll());

    // Output the data
    qDebug(data.data());
    qDebug("Done!");

    int begin = data.indexOf("[");
    int end = data. lastIndexOf("]");

    for (int i = begin+1; i < end; ++i){
        cout << data[i];
    }
    return 0;
}

