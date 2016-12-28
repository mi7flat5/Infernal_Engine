#include "stdafx.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QFile>
#include "ActorCreationWindow.h"
#include "InfernalEditor.h"


InfernalEditor::InfernalEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	ui.openGLWidget->setOwner(this);
	ui.textBrowser->append(QString("owner set"));
	createMenus();
	

	m_pSceneTreeModel = new QStandardItemModel();
	
	m_pSceneViewRoot = new QStandardItem("Scene");
	
	
	QStandardItem* description = new QStandardItem("Scene is the container for all items currently in the world.");
	m_pSceneTreeModel->setItem(0,m_pSceneViewRoot);

	
	ui.treeView->setModel(m_pSceneTreeModel);
	QStringList labels;
	labels.append("Object Name");
	labels.append("Object Type");



	m_pSceneTreeModel->setHorizontalHeaderLabels(labels);
	/*int column = ui.treeView->selectionModel()->currentIndex().column();
	m_pSceneTreeModel->insertColumn(column + 1);*/

	m_pCreationwindow = new ActorCreationWindow();
	m_pCreationwindow->SetOwner(this);
	
}
void InfernalEditor::AddObjectToScene(const char* resourcePath, QList<QStandardItem*> inItems) 
{
	m_pSceneViewRoot->appendRow(inItems);
	ui.textBrowser->append(resourcePath);
	ui.openGLWidget->AddObjectToScene(resourcePath);

}
void InfernalEditor::createActions()
{
	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, &QAction::triggered, this, &InfernalEditor::open);
	
	createObject = new QAction(tr("&Create Object..."), this);
	connect(createObject, &QAction::triggered, this, &InfernalEditor::OpenCreationWindow);
	
	addObject = new QAction(tr("&Add Object"), this);
	connect(addObject, &QAction::triggered, this, &InfernalEditor::open);
}
void InfernalEditor::OpenCreationWindow() 
{	
	m_pCreationwindow->show();

}
void InfernalEditor::createMenus()
{
	createActions();
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAct);

	ObjectMenu = menuBar()->addMenu(tr("&Scene"));
	ObjectMenu->addAction(addObject);
	ObjectMenu->addAction(createObject);
	

	/*fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(printAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);*/ //TODO IMPLEMENT THESE
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

#ifndef QT_NO_CONTEXTMENU
void InfernalEditor::contextMenuEvent(QContextMenuEvent *event)
{
	//QMenu menu(this);
	//menu.addAction(cutAct);
	//menu.addAction(copyAct);
	//menu.addAction(pasteAct);
	////menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void InfernalEditor::newFile()
{
	
}

void InfernalEditor::open()
{
	QStringList filter;
	filter.append(QString("*.xml"));
	
	
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString("..//XML//"),
		tr("XML (*.xml);;"));
		if (!fileName.isEmpty())
			loadfile(fileName);
	
}
void InfernalEditor::loadfile(const QString &fileName)
{
	QList<QStandardItem *> NameAndType;
	NameAndType << new QStandardItem("filler");
	NameAndType << new QStandardItem("more filler");
	AddObjectToScene(fileName.toStdString().c_str(),NameAndType);



}
void InfernalEditor::save()
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



