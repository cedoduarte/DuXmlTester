#include "Widget.h"
#include "ui_Widget.h"
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <QDomElement>

#define XML_FILE "administradores.xml"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QFile xmlFile(XML_FILE);
    xmlFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter xout(&xmlFile);
    xout.setAutoFormatting(true);
    xout.writeStartDocument();

    xout.writeStartElement("administradores");
    QStringList administradores { "Carlos",
                                "Luis",
                                "Ramón" };
    QStringList niveles { "7", "8", "9" };
    QStringList puntos { "-1", "-2", "-3" };

    int i = 0;
    for (const auto &ix : administradores) {
        xout.writeStartElement("administrador");
        xout.writeStartElement("datos");
        xout.writeAttribute("nombre", ix);
        xout.writeAttribute("equipo", QString::number(i + 1));
        xout.writeStartElement("nivel");
        xout.writeCharacters(niveles[i]);
        xout.writeEndElement();
        xout.writeStartElement("puntos");
        xout.writeCharacters(puntos[i]);
        xout.writeEndElement();
        xout.writeEndElement();
        xout.writeEndElement();
        ++i;
    }
    xout.writeEndElement();
    xout.writeEndDocument();

    xmlFile.flush();
    xmlFile.close();
    xmlFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream tin(&xmlFile);
    ui->plainTextEdit->setPlainText(tin.readAll());
    xmlFile.close();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QFile xmlFile(XML_FILE);
    xmlFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QDomDocument doc;
    doc.setContent(&xmlFile);
    xmlFile.close();

    auto root = doc.documentElement();
    auto ix = root.firstChild().toElement();
    while (!ix.isNull()) {
        auto iy = ix.firstChild().toElement();
        if (iy.attribute("equipo") == ui->equipoSpinBox->text()) {
            auto nombre = iy.attribute("nombre");
            auto nivel = iy.firstChild().toElement().text();
            iy = iy.firstChild().nextSibling().toElement();
            auto puntos = iy.toElement().text();
            ui->nombreLineEdit->setText(nombre);
            ui->nivelLineEdit->setText(nivel);
            ui->puntosLineEdit->setText(puntos);
            return;
        }
        ix = ix.nextSibling().toElement();
    }
}
