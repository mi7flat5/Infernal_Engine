#include "stdafx.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QFile>
#include "ActorCreationWindow.h"
#include "InfernalEditor.h"
#include <QContextMenuEvent>
#include <QSpinBox>
#include"SHObject/Object3D.h"
#include"SHObject/TransformComponent.h"
#include"SHObject/RenderComponent.h"


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

	ui.gridLayout->setColumnStretch(0, 3);
	int b = ui.gridLayout->columnCount();

	//IEventManager::Get()->VAddListener(fastdelegate::MakeDelegate(this, &InfernalEditor::SetSelectedNode), EvtData_EvtRayHit::sk_EventType);
	IEventManager::Get()->VAddListener(fastdelegate::MakeDelegate(this, &InfernalEditor::Log_event), EvtData_Log_Data::sk_EventType);

	XselectAxis = INVALID_OBJECT_ID;
	YselectAxis = INVALID_OBJECT_ID;
	ZselectAxis = INVALID_OBJECT_ID;

}

InfernalEditor::~InfernalEditor()
{
	m_pSelectedNode.reset();
	//IEventManager::Get()->VRemoveListener(fastdelegate::MakeDelegate(this, &InfernalEditor::SetSelectedNode), EvtData_EvtRayHit::sk_EventType);
	IEventManager::Get()->VRemoveListener(fastdelegate::MakeDelegate(this, &InfernalEditor::Log_event), EvtData_Log_Data::sk_EventType);
}

void InfernalEditor::UpdateTransform() {
	if (m_pSelectedNode)
	{
		StrongObjectPtr pObject =  MakeStrongPtr(g_pApp->GetGameLogic()->VGetActor(m_pSelectedNode->GetObjectId()));
		std::shared_ptr<TransformComponent> pTransform = MakeStrongPtr(pObject->GetComponent<TransformComponent>(TransformComponent::g_Name));
		pTransform->SetVecPosition(vec3(ui.pX->value(),ui.pY->value(),ui.pZ->value()));
		pTransform->SetVecRotation(vec3(ui.rX->value(), ui.rY->value(), ui.rZ->value()));
		pTransform->SetVecScaler(vec3(ui.sX->value(), ui.sY->value(), ui.sZ->value()));
		pTransform->BuildTransform();
		//m_pSelectedNode->VSetTransform(&pTransform->GetTransform());
		if (XselectAxis)
		{
			pObject = MakeStrongPtr(g_pApp->GetGameLogic()->VGetActor(XselectAxis));
			pTransform = MakeStrongPtr(pObject->GetComponent<TransformComponent>(TransformComponent::g_Name));
			pTransform->SetVecPosition(vec3(ui.pX->value(), ui.pY->value(), ui.pZ->value()));
			pTransform->BuildTransform();

			pObject = MakeStrongPtr(g_pApp->GetGameLogic()->VGetActor(YselectAxis));
			pTransform = MakeStrongPtr(pObject->GetComponent<TransformComponent>(TransformComponent::g_Name));
			pTransform->SetVecPosition(vec3(ui.pX->value(), ui.pY->value(), ui.pZ->value()));
			pTransform->BuildTransform();

			pObject = MakeStrongPtr(g_pApp->GetGameLogic()->VGetActor(ZselectAxis));
			pTransform = MakeStrongPtr(pObject->GetComponent<TransformComponent>(TransformComponent::g_Name));
			pTransform->SetVecPosition(vec3(ui.pX->value(), ui.pY->value(), ui.pZ->value()));
			pTransform->BuildTransform();
		}
	}
}
void InfernalEditor::LoadScene()
{
	
	QString fName = QFileDialog::getOpenFileName(this, tr("Open Scene File"), QString("..//XML//"),
		tr("Scene (*.rsc);"));
	QFileInfo fileInfo(fName.toStdString().c_str());
	QString fileName(fileInfo.fileName());

	tinyxml2::XMLDocument inDoc;
	if (inDoc.LoadFile(std::string("..//XML//" + fileName.toStdString()).c_str()))
	{
		EDITOR_LOG("Failed to load scene file  " + std::string("..//XML//" + fileName.toStdString()))
			return;
	}
	
	tinyxml2::XMLElement* pRoot = inDoc.FirstChildElement();
	ui.openGLWidget->makeCurrent();
	for (tinyxml2::XMLElement* pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
	{
	
		
		QList<QStandardItem *> NameAndType;
		NameAndType << new QStandardItem(pNode->Value());
		NameAndType << new QStandardItem(pNode->Attribute("type"));
		
		AddObjectToScene(pNode->Attribute("resource"),NameAndType);
		ui.openGLWidget->makeCurrent();
	}
	
		
}
void InfernalEditor::SaveScene()
{
	tinyxml2::XMLDocument sceneDoc;
	tinyxml2::XMLNode * pSceneRoot = sceneDoc.NewElement("Scene");
	tinyxml2::XMLNode* pElements;

	for (int i = 0;i < m_pSceneViewRoot->rowCount();++i)
	{
		std::string rscPath(m_pSceneViewRoot->child(i, 3)->data().toString().toStdString());
		if (sceneDoc.LoadFile(rscPath.c_str()))
		{
			EDITOR_LOG("Failed to load " + rscPath)
				return;
		}
		pElements = sceneDoc.RootElement();
	
		UpdateXML(rscPath.c_str(), m_pSceneViewRoot->child(i, 2)->data().toUInt());
		
		pSceneRoot->InsertFirstChild(pElements->ShallowClone(&sceneDoc));
				
		pElements = nullptr;
		sceneDoc.Clear();
	}
	
	sceneDoc.InsertFirstChild(pSceneRoot);
	tinyxml2::XMLError eResult = sceneDoc.SaveFile("..//XML/Scene.rsc");
	XMLCheckResult(eResult);

}
void InfernalEditor::UpdateXML(const char* resourcePath, ObjectId id) 
{
	tinyxml2::XMLDocument inDoc;
	if (inDoc.LoadFile(resourcePath))
	{
		EDITOR_LOG("Failed to load " + std::string(resourcePath))
			return;
	}


	StrongObjectPtr pObject = MakeStrongPtr(g_pApp->GetGameLogic()->VGetActor(id));
	std::shared_ptr<TransformComponent> pTransform = MakeStrongPtr(pObject->GetComponent<TransformComponent>(TransformComponent::g_Name));
	
	if(pTransform)
	{
	
		tinyxml2::XMLElement* pRoot = inDoc.FirstChildElement();

		for (tinyxml2::XMLElement* pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
		{

			tinyxml2::XMLElement* pPositionElement = pNode->FirstChildElement("Position");
			if (pPositionElement)
			{
				vec3 pos = pTransform->GetPosition();
				pPositionElement->SetAttribute("x", ToStr(pos.x).c_str());
				pPositionElement->SetAttribute("y", ToStr(pos.y).c_str());
				pPositionElement->SetAttribute("z", ToStr(pos.z).c_str());
			}
			
			tinyxml2::XMLElement* pRotationElement = pNode->FirstChildElement("Rotation");
			if (pRotationElement)
			{
				vec3 rot = pTransform->GetVecRotation();
				pRotationElement->SetAttribute("pitch", ToStr(rot.x).c_str());
				pRotationElement->SetAttribute("yaw", ToStr(rot.y).c_str());
				pRotationElement->SetAttribute("roll", ToStr(rot.z).c_str());
			}
			
			tinyxml2::XMLElement* pScaleElement = pNode->FirstChildElement("Scale");
			if (pScaleElement)
			{
				vec3 scale = pTransform->GetVecScale();
				pScaleElement->SetAttribute("x", ToStr(scale.x).c_str());
				pScaleElement->SetAttribute("y", ToStr(scale.y).c_str());
				pScaleElement->SetAttribute("z", ToStr(scale.z).c_str());
			}
		
		}
		
	}
	tinyxml2::XMLError eResult  = inDoc.SaveFile(resourcePath);
	XMLCheckResult(eResult);
	

}
void InfernalEditor::AddObjectToScene(const char* resourcePath, QList<QStandardItem*> inItems)
{
	ui.openGLWidget->UpdateContext();
	StrongObjectPtr pObject = g_pApp->GetGameLogic()->VCreateActor(resourcePath, INVALID_OBJECT_ID);
	std::string intStr = std::to_string((unsigned int)pObject->GetId());
	QStandardItem* IdBlock = new QStandardItem(intStr.c_str());
	IdBlock->setData(QVariant((unsigned int)pObject->GetId()));
	QStandardItem* rscPath = new QStandardItem(resourcePath);
	rscPath->setData(QVariant(resourcePath));
	inItems.at(0)->setText(inItems.at(0)->text() + "_" + intStr.c_str());
	inItems << IdBlock;
	inItems << rscPath;
	m_pSceneViewRoot->appendRow(inItems);

}
void InfernalEditor::DeleteActor()
{
	m_pSelectedNode.reset();
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

void InfernalEditor::SetSelectedNode(ObjectId id)
{
	
	if(!XselectAxis)
	{
		StrongObjectPtr pObject = g_pApp->GetGameLogic()->VCreateActor("..//XML//XAxis.xml", INVALID_OBJECT_ID);
		XselectAxis = pObject->GetId();
		
		pObject = g_pApp->GetGameLogic()->VCreateActor("..//XML//YAxis.xml", INVALID_OBJECT_ID);
		YselectAxis = pObject->GetId();
		pObject = g_pApp->GetGameLogic()->VCreateActor("..//XML//ZAxis.xml", INVALID_OBJECT_ID);
		ZselectAxis = pObject->GetId();
		ui.openGLWidget->Set3DCursor(XselectAxis,YselectAxis,ZselectAxis);
	}
	
	if (id != INVALID_OBJECT_ID&& id != XselectAxis)
	{
		ObjectId actorId = id;
		StrongObjectPtr pObject = MakeStrongPtr(g_pApp->GetGameLogic()->VGetActor(id));
	
		std::shared_ptr<MeshRenderComponent> pRenderComponent= MakeStrongPtr(pObject->GetComponent<MeshRenderComponent>(MeshRenderComponent::g_Name));
		
	

		if (pRenderComponent)
		{
			std::shared_ptr<ISceneNode> pSceneNode(pRenderComponent->VGetSceneNode());


			std::shared_ptr<SceneNode>	pNode = std::static_pointer_cast<SceneNode>(pSceneNode);
			m_pSelectedNode = pNode;
		}

		vec3 pos, rot, scale;
		if (m_pSelectedNode) {

			std::shared_ptr<TransformComponent> pTransform = MakeStrongPtr(pObject->GetComponent<TransformComponent>(TransformComponent::g_Name));

			pos = pTransform->GetPosition();
			rot = pTransform->GetVecRotation();
			scale = pTransform->GetVecScale();

			ui.pX->setValue(pos.x);
			ui.pY->setValue(pos.y);
			ui.pZ->setValue(pos.z);

			ui.rX->setValue(rot.x);
			ui.rY->setValue(rot.y);
			ui.rZ->setValue(rot.z);

			ui.sX->setValue(scale.x);
			ui.sY->setValue(scale.y);
			ui.sZ->setValue(scale.z);

			if (XselectAxis) 
			{
				 pObject = MakeStrongPtr(g_pApp->GetGameLogic()->VGetActor(XselectAxis));
				 pTransform = MakeStrongPtr(pObject->GetComponent<TransformComponent>(TransformComponent::g_Name));
				 pTransform->SetVecPosition(vec3(ui.pX->value(),ui.pY->value(),ui.pZ->value()));
				
				 pTransform->BuildTransform();

				 pObject = MakeStrongPtr(g_pApp->GetGameLogic()->VGetActor(YselectAxis));
				 pTransform = MakeStrongPtr(pObject->GetComponent<TransformComponent>(TransformComponent::g_Name));
				 pTransform->SetVecPosition(vec3(ui.pX->value(), ui.pY->value(), ui.pZ->value()));
				
				 pTransform->BuildTransform();

				 pObject = MakeStrongPtr(g_pApp->GetGameLogic()->VGetActor(ZselectAxis));
				 pTransform = MakeStrongPtr(pObject->GetComponent<TransformComponent>(TransformComponent::g_Name));
				 pTransform->SetVecPosition(vec3(ui.pX->value(), ui.pY->value(), ui.pZ->value()));
				
				 pTransform->BuildTransform();
			}
		}
	}
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

	saveScene = new QAction(tr("&Save Scene"), this);
	saveScene->setShortcuts(QKeySequence::Save);
	saveScene->setStatusTip(tr("Save Current Scene"));
	connect(saveScene, &QAction::triggered, this, &InfernalEditor::SaveScene);

	loadScene = new QAction(tr("&Load Scene"), this);
	loadScene->setShortcuts(QKeySequence::Save);
	loadScene->setStatusTip(tr("Load Scene From File"));
	connect(loadScene, &QAction::triggered, this, &InfernalEditor::LoadScene);

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
	fileMenu->addAction(saveScene);
	fileMenu->addAction(loadScene);
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


#ifndef QT_NO_CONTEXTMENU
void InfernalEditor::contextMenuEvent(QContextMenuEvent *event)
{
	contextMenu = new QMenu(this);
	contextMenu->addAction(deletObject);
	/*menu.addAction(cutAct);
	menu.addAction(copyAct);
	menu.addAction(pasteAct);*/
	contextMenu->exec(event->globalPos());

}
#endif // QT_NO_CONTEXTMENU


void InfernalEditor::registerDelegate()
{
	

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
		tr("XML (*.xml);"));
	QFileInfo fileInfo(fName.toStdString().c_str());
	QString fileName(fileInfo.fileName());
	if (!fileName.isEmpty())
		loadfile("..//XML//" + fileName);
}
void InfernalEditor::openScene()
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