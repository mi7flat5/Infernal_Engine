#include "stdafx.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QFile>
#include "ActorCreationWindow.h"
#include "InfernalEditor.h"
#include <QContextMenuEvent>
#include <QSpinBox>
#include"SHObject/Object3D.h"
InfernalEditor::InfernalEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Init();
	VCreateGameAndView();
	


	ui.openGLWidget->setOwner(this);

	createMenus();

	m_pSceneTreeModel = new QStandardItemModel();
	m_pSceneViewRoot = new QStandardItem("Scene");
	m_pSceneViewRoot->setSelectable(false);
	m_pSceneViewRoot->setEnabled(false);

	m_pSceneTreeModel->setItem(0, m_pSceneViewRoot);

	ui.treeView->setModel(m_pSceneTreeModel);
	QStringList labels;
	labels.append("Object Name");
	labels.append("Object Type");

	m_pSceneTreeModel->setHorizontalHeaderLabels(labels);

	m_pCreationwindow = new ActorCreationWindow();
	m_pCreationwindow->SetOwner(this);

	connect(ui.pX, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &InfernalEditor::UpdateTransform);
	connect(ui.pY, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &InfernalEditor::UpdateTransform);
	connect(ui.pZ, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &InfernalEditor::UpdateTransform);
	connect(ui.rX, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &InfernalEditor::UpdateTransform);
	connect(ui.rY, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &InfernalEditor::UpdateTransform);
	connect(ui.rZ, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &InfernalEditor::UpdateTransform);
	connect(ui.sX, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &InfernalEditor::UpdateTransform);
	connect(ui.sY, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &InfernalEditor::UpdateTransform);
	connect(ui.sZ, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &InfernalEditor::UpdateTransform);




}
void InfernalEditor::UpdateTransform() {
	if (m_pSelectedNode)
	{
		mat4 translate = Transform::translate(ui.pX->value(), ui.pY->value(), ui.pZ->value());
		mat4 Rotate = Transform::RotateMat4(ui.rX->value(), vec3(1, 0, 0))*Transform::RotateMat4(ui.rY->value(), vec3(0, 1, 0))*Transform::RotateMat4(ui.rZ->value(), vec3(0, 0, 1));
		mat4 Matscale = Transform::scale(ui.sX->value(), ui.sY->value(), ui.sZ->value());
		mat4 transform = translate*Rotate*Matscale;
		m_pSelectedNode->SetVectorTransform(vec3(ui.pX->value(), ui.pY->value(), ui.pZ->value()),
			vec3(ui.rX->value(), ui.rY->value(), ui.rZ->value()),
			vec3(ui.sX->value(), ui.sY->value(), ui.sZ->value()));
		m_pSelectedNode->VSetTransform(&transform);
	}

}

void InfernalEditor::DeleteActor()
{

	QModelIndex index = ui.treeView->selectionModel()->currentIndex();
	QAbstractItemModel *model = ui.treeView->model();
	QVariant ID = model->index(index.row(), 2, index.parent()).data();

	if (model->removeRow(index.row(), index.parent()))
		ui.openGLWidget->UpdateContext();
	std::shared_ptr<EvtData_Destroy_Actor> pEvent(INFERNAL_NEW EvtData_Destroy_Actor(ID.toUInt()));

	IEventManager::Get()->VTriggerEvent(pEvent);
	//TODO set up delegate in Basegame logic to handle this
	m_pGame->VDestroyActor(ID.toUInt());

}
void InfernalEditor::loadfile(const QString &fileName)
{
	tinyxml2::XMLDocument inDoc;
	std::string s(fileName.toStdString());
	if (inDoc.LoadFile(s.c_str()))
	{
		EDITOR_LOG("File failed to load or is corrupt")
			return;

	}
	tinyxml2::XMLElement* pRoot = inDoc.FirstChildElement();

	QStandardItem* Name = new QStandardItem(pRoot->Value());
	QStandardItem* Type = new QStandardItem(pRoot->Attribute("type"));

	QList<QStandardItem *> NameAndType;

	NameAndType << Name;
	NameAndType << Type;

	AddObjectToScene(fileName.toStdString().c_str(), NameAndType);
	inDoc.Clear();

}

void InfernalEditor::SetSelectedNode(std::shared_ptr<SceneNode> inNode)
{
	m_pSelectedNode = inNode;


	vec3 pos, rot, scale;
	if (m_pSelectedNode)
		m_pSelectedNode->GetVectorTransform(pos, rot, scale);

	ui.pX->setValue(pos.x);
	ui.pY->setValue(pos.y);
	ui.pZ->setValue(pos.z);

	ui.rX->setValue(rot.x);
	ui.rY->setValue(rot.y);
	ui.rZ->setValue(rot.z);

	ui.sX->setValue(scale.x);
	ui.sY->setValue(scale.y);
	ui.sZ->setValue(scale.z);

}

void InfernalEditor::AddObjectToScene(const char* resourcePath, QList<QStandardItem*> inItems)
{
	ui.openGLWidget->UpdateContext();
	StrongObjectPtr pObject = g_pApp->GetGameLogic()->VCreateActor(resourcePath, INVALID_OBJECT_ID);
	std::string intStr = std::to_string((unsigned int)pObject->GetId());
	QStandardItem* IdBlock = new QStandardItem(intStr.c_str());
	IdBlock->setData(QVariant((unsigned int)pObject->GetId()));
	inItems.at(0)->setText(inItems.at(0)->text() + "_" + intStr.c_str());
	inItems << IdBlock;

	m_pSceneViewRoot->appendRow(inItems);

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

	deletObject = new QAction(tr("Delete Object"), this);
	connect(deletObject, &QAction::triggered, this, &InfernalEditor::DeleteActor);




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


//#ifndef QT_NO_CONTEXTMENU
void InfernalEditor::contextMenuEvent(QContextMenuEvent *event)
{
	contextMenu = new QMenu(this);
	contextMenu->addAction(deletObject);
	/*menu.addAction(cutAct);
	menu.addAction(copyAct);
	menu.addAction(pasteAct);*/
	contextMenu->exec(event->globalPos());


}
//#endif // QT_NO_CONTEXTMENU


void InfernalEditor::registerDelegate()
{
	ui.gridLayout->setColumnStretch(0, 3);
	int b = ui.gridLayout->columnCount();
		

	IEventManager::Get()->VAddListener(fastdelegate::MakeDelegate(this, &InfernalEditor::Log_event), EvtData_Log_Data::sk_EventType);
	ui.textBrowser->append(QString("delegate registered"));
}
void InfernalEditor::Log_event(IEventDataPtr pEventData)
{
	std::shared_ptr<EvtData_Log_Data> pCastEventData = std::static_pointer_cast<EvtData_Log_Data>(pEventData);

	ui.textBrowser->append(QString(pCastEventData->getLog()));


}
void InfernalEditor::newFile()
{

}

void InfernalEditor::open()
{



	QString fName = QFileDialog::getOpenFileName(this, tr("Open File"), QString("..//XML//"),
		tr("XML (*.xml);;"));
	QFileInfo fileInfo(fName.toStdString().c_str());
	QString fileName(fileInfo.fileName());
	if (!fileName.isEmpty())
		loadfile("..//XML//" + fileName);

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