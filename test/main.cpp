#include <iostream>
#include <QtCore>
#include <QtXml>

using namespace std;

int main()
{
//    QProcess process;
//    process.start("/home/user/rlPlanPath/rlPlanDemo/bin/rlPlanDemo", QStringList() << "/home/user/rlPlanPath/kuka_kr_10_r1100_sixx/rlplan/kuka_kr10_r1100_sixx.xml" << "--enable-quit" << "--disable-viewer" << "--disable-wait" << "--height=1 --width=1");

//    // Wait for it to start
//    if(!process.waitForStarted())
//        return 0;

//    // Continue reading the data until EOF reached
//    QByteArray data;

//    while(process.waitForReadyRead())
//        data.append(process.readAll());

//    // Output the data
//    qDebug(data.data());
//    qDebug("Done!");

//    int begin = data.indexOf("[");
//    int end = data. lastIndexOf("]");

//    for (int i = begin+1; i < end; ++i){
//        cout << data[i];
//    }


    QString fileName = "/home/user/rlPlanPath/test/kuka_kr10_r1100_sixx.xml";
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


    QDomNodeList nodes = doc.elementsByTagName("q");
    qDebug() << nodes.count();
    for (int i = 0; i < nodes.count(); ++i)
    {
            QDomNode node = nodes.at(i).toElement();
            if (!node.isNull())
            {
                qDebug() << node.toElement();
            }
    }

//    QDomNodeList elems = doc.elementsByTagName("goal");
//    if (!elems.isEmpty())
//    {
//        QDomElement el = elems.at(0).toElement();
//        QDomNode child = el.firstChild();

//        while (!child.isNull()) {
//                qDebug() << child.toElement().text();

//                // create a new node with a QDomText child
//                QDomElement newNodeTag = doc.createElement(QString("q"));
//                newNodeTag.setAttribute("unit","deg");
//                QDomText newNodeText = doc.createTextNode(QString("8"));
//                newNodeTag.appendChild(newNodeText);

//                // replace existing node with new node
//                el.replaceChild(newNodeTag, child.toElement());
//                child = child.nextSiblingElement("q");
//        }

//    }

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

    return 0;
}

