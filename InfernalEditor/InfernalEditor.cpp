#include "stdafx.h"
#include "InfernalEditor.h"

InfernalEditor::InfernalEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	timer = new QTimer(this);
	
	connect(timer, &QTimer::timeout, this, &InfernalEditor::stdLogOut);
	//connect(timer, SIGNAL(timeout()), this, SLOT(stdLogOut()));
	timer->start();
}
void InfernalEditor::stdLogOut()
{
	
	//std::filebuf f;
	//f.open("output.txt", std::ios::out);
	//std::streambuf* o = std::cout.rdbuf(&f);
	//
	///*std::ostringstream ss;
	//ss << o;
	//std::string s = ss.str();*/
	//std::istream is(o);
	//std::string s;
	//std::getline(is, s);
	static int w;
	if (width() != w) 
	{
		ui.textBrowser->append(QString(QString::number(width())));
		w = width();
	}
	
}