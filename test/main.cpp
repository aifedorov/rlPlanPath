#include <iostream>
#include <QtCore>
#include <QtXml>

using namespace std;

int updateXML(QString fileName);
QByteArray initProcess(QString appPlanePath, QString filePlanePath);

int main()
{
    QByteArray path;
    if (updateXML("/home/user/rlPlanPath/test/kuka_kr10_r1100_sixx.xml"))
    {
       path = initProcess("/home/user/rlPlanPath/rlPlanDemo/bin/rlPlanDemo", "/home/user/rlPlanPath/kuka_kr_10_r1100_sixx/rlplan/kuka_kr10_r1100_sixx.xml");
    } else {
        std::cerr << "Error: Cannot update xml file " << std::endl;
        return 0;
    }

    for (int i = 0; i < path.size(); i++){
        cout << path[i];
    }
    return 0;
}
QByteArray initProcess(QString appPlanePath, QString filePlanePath){

    QProcess process;
    process.start(appPlanePath, QStringList() << filePlanePath << "--enable-quit" << "--disable-viewer" << "--disable-wait" << "--height=1 --width=1");

    if(!process.waitForStarted())
    {
        std::cerr << "Error: Cannot launch PlanePath application  " << std::endl;
        return 0;
    }

    QByteArray data;
    while(process.waitForReadyRead())
        data.append(process.readAll());

//    qDebug(data.data());
//    qDebug("Done!");

    int begin = data.indexOf("[");
    int end = data. lastIndexOf("]");

    QByteArray result;
    for (int i = begin+1, j = -1; i < end; ++i, ++j){
        result[j] = data[i];
    }
    return result;
}

int updateXML(QString fileName){

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            std::cerr << "Error: Cannot read file " << std::endl;
            return 0;
        }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
            file.close();
            std::cerr << "Error: Parse error " << std::endl;
            return 0;
    }
    file.close();

    QDomNodeList elems = doc.elementsByTagName("q");
    int n = elems.count();

    if (!elems.isEmpty())
    {
        // удаляем значение обобщеных координат
        for (int i = 0; i < n;  i++){
             QDomElement el = elems.at(i).toElement();
             el.removeChild(el.firstChild());
        }
    }

    // записываем свои значения обобщеных координат
    for (int i = 0; i < n; i++)
    {
             QDomElement el = elems.at(i).toElement();
             QDomText newNodeText = doc.createTextNode(QString("5"));
             el.appendChild(newNodeText);
    }

    QByteArray xml = doc.toByteArray();
    QFile fileOut(fileName);
    if (!fileOut.open(QIODevice::WriteOnly))
    {
           std::cerr << "Error: Cannot write file " << std::endl;
           return 0;
    }

    fileOut.write(xml);
    file.close();
    fileOut.close();

    return 1;
}
