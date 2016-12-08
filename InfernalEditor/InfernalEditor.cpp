#include "stdafx.h"
#include "InfernalEditor.h"


InfernalEditor::InfernalEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	ui.openGLWidget->setOwner(this);
	ui.textBrowser->append(QString("owner set"));
}
void InfernalEditor::registerDelegate()
{
	
	IEventManager* evman = IEventManager::Get();

	evman->VAddListener(fastdelegate::MakeDelegate(this, &InfernalEditor::Log_event), EvtData_Log_Data::sk_EventType);
	ui.textBrowser->append(QString("delegate registered"));
}
void InfernalEditor::Log_event(IEventDataPtr pEventData)
{
	std::shared_ptr<EvtData_Log_Data> pCastEventData = std::static_pointer_cast<EvtData_Log_Data>(pEventData);
	
	ui.textBrowser->append(QString(pCastEventData->getLog()));
	
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
#ifndef QT_NO_CONTEXTMENU
void InfernalEditor::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	menu.addAction(cutAct);
	menu.addAction(copyAct);
	menu.addAction(pasteAct);
	menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void InfernalEditor::newFile()
{
	
}

void InfernalEditor::open()
{
	
}

void InfernalEditor::save()
{
	
}

void InfernalEditor::print()
{
	
}

void InfernalEditor::undo()
{
	
}

void InfernalEditor::redo()
{
	
}

void InfernalEditor::cut()
{
	
}

void InfernalEditor::copy()
{
	
}

void InfernalEditor::paste()
{
	
}

void InfernalEditor::bold()
{
	
}

void InfernalEditor::italic()
{
	
}

void InfernalEditor::leftAlign()
{
	
}

void InfernalEditor::rightAlign()
{
	
}

void InfernalEditor::justify()
{
	
}

void InfernalEditor::center()
{
	
}

void InfernalEditor::setLineSpacing()
{
	
}

void InfernalEditor::setParagraphSpacing()
{
	
}

void InfernalEditor::about()
{
	
	QMessageBox::about(this, tr("About Menu"),
		tr("The <b>Menu</b> example shows how to create "
			"menu-bar menus and context menus."));
}

void InfernalEditor::aboutQt()
{
	
}

void InfernalEditor::createActions()
{
	newAct = new QAction(tr("&New"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip(tr("Create a new file"));
	connect(newAct, &QAction::triggered, this, &InfernalEditor::newFile);

	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, &QAction::triggered, this, &InfernalEditor::open);

	saveAct = new QAction(tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save the document to disk"));
	connect(saveAct, &QAction::triggered, this, &InfernalEditor::save);

	printAct = new QAction(tr("&Print..."), this);
	printAct->setShortcuts(QKeySequence::Print);
	printAct->setStatusTip(tr("Print the document"));
	connect(printAct, &QAction::triggered, this, &InfernalEditor::print);

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, &QAction::triggered, this, &QWidget::close);

	undoAct = new QAction(tr("&Undo"), this);
	undoAct->setShortcuts(QKeySequence::Undo);
	undoAct->setStatusTip(tr("Undo the last operation"));
	connect(undoAct, &QAction::triggered, this, &InfernalEditor::undo);

	redoAct = new QAction(tr("&Redo"), this);
	redoAct->setShortcuts(QKeySequence::Redo);
	redoAct->setStatusTip(tr("Redo the last operation"));
	connect(redoAct, &QAction::triggered, this, &InfernalEditor::redo);

	cutAct = new QAction(tr("Cu&t"), this);
	cutAct->setShortcuts(QKeySequence::Cut);
	cutAct->setStatusTip(tr("Cut the current selection's contents to the "
		"clipboard"));
	connect(cutAct, &QAction::triggered, this, &InfernalEditor::cut);

	copyAct = new QAction(tr("&Copy"), this);
	copyAct->setShortcuts(QKeySequence::Copy);
	copyAct->setStatusTip(tr("Copy the current selection's contents to the "
		"clipboard"));
	connect(copyAct, &QAction::triggered, this, &InfernalEditor::copy);

	pasteAct = new QAction(tr("&Paste"), this);
	pasteAct->setShortcuts(QKeySequence::Paste);
	pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
		"selection"));
	connect(pasteAct, &QAction::triggered, this, &InfernalEditor::paste);

	boldAct = new QAction(tr("&Bold"), this);
	boldAct->setCheckable(true);
	boldAct->setShortcut(QKeySequence::Bold);
	boldAct->setStatusTip(tr("Make the text bold"));
	connect(boldAct, &QAction::triggered, this, &InfernalEditor::bold);

	QFont boldFont = boldAct->font();
	boldFont.setBold(true);
	boldAct->setFont(boldFont);

	italicAct = new QAction(tr("&Italic"), this);
	italicAct->setCheckable(true);
	italicAct->setShortcut(QKeySequence::Italic);
	italicAct->setStatusTip(tr("Make the text italic"));
	connect(italicAct, &QAction::triggered, this, &InfernalEditor::italic);

	QFont italicFont = italicAct->font();
	italicFont.setItalic(true);
	italicAct->setFont(italicFont);

	setLineSpacingAct = new QAction(tr("Set &Line Spacing..."), this);
	setLineSpacingAct->setStatusTip(tr("Change the gap between the lines of a "
		"paragraph"));
	connect(setLineSpacingAct, &QAction::triggered, this, &InfernalEditor::setLineSpacing);

	setParagraphSpacingAct = new QAction(tr("Set &Paragraph Spacing..."), this);
	setParagraphSpacingAct->setStatusTip(tr("Change the gap between paragraphs"));
	connect(setParagraphSpacingAct, &QAction::triggered,
		this, &InfernalEditor::setParagraphSpacing);

	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, &QAction::triggered, this, &InfernalEditor::about);

	aboutQtAct = new QAction(tr("About &Qt"), this);
	aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
	connect(aboutQtAct, &QAction::triggered, this, &InfernalEditor::aboutQt);

	leftAlignAct = new QAction(tr("&Left Align"), this);
	leftAlignAct->setCheckable(true);
	leftAlignAct->setShortcut(tr("Ctrl+L"));
	leftAlignAct->setStatusTip(tr("Left align the selected text"));
	connect(leftAlignAct, &QAction::triggered, this, &InfernalEditor::leftAlign);

	rightAlignAct = new QAction(tr("&Right Align"), this);
	rightAlignAct->setCheckable(true);
	rightAlignAct->setShortcut(tr("Ctrl+R"));
	rightAlignAct->setStatusTip(tr("Right align the selected text"));
	connect(rightAlignAct, &QAction::triggered, this, &InfernalEditor::rightAlign);

	justifyAct = new QAction(tr("&Justify"), this);
	justifyAct->setCheckable(true);
	justifyAct->setShortcut(tr("Ctrl+J"));
	justifyAct->setStatusTip(tr("Justify the selected text"));
	connect(justifyAct, &QAction::triggered, this, &InfernalEditor::justify);

	centerAct = new QAction(tr("&Center"), this);
	centerAct->setCheckable(true);
	centerAct->setShortcut(tr("Ctrl+E"));
	centerAct->setStatusTip(tr("Center the selected text"));
	connect(centerAct, &QAction::triggered, this, &InfernalEditor::center);

	alignmentGroup = new QActionGroup(this);
	alignmentGroup->addAction(leftAlignAct);
	alignmentGroup->addAction(rightAlignAct);
	alignmentGroup->addAction(justifyAct);
	alignmentGroup->addAction(centerAct);
	leftAlignAct->setChecked(true);
}

void InfernalEditor::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(printAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(undoAct);
	editMenu->addAction(redoAct);
	editMenu->addSeparator();
	editMenu->addAction(cutAct);
	editMenu->addAction(copyAct);
	editMenu->addAction(pasteAct);
	editMenu->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);

	formatMenu = editMenu->addMenu(tr("&Format"));
	formatMenu->addAction(boldAct);
	formatMenu->addAction(italicAct);
	formatMenu->addSeparator()->setText(tr("Alignment"));
	formatMenu->addAction(leftAlignAct);
	formatMenu->addAction(rightAlignAct);
	formatMenu->addAction(justifyAct);
	formatMenu->addAction(centerAct);
	formatMenu->addSeparator();
	formatMenu->addAction(setLineSpacingAct);
	formatMenu->addAction(setParagraphSpacingAct);
}