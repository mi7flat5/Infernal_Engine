#include "stdafx.h"
#include "InfernalEditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	InfernalEditor* w = new InfernalEditor();
    w->show();
    return a.exec();
}
