#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_InfernalEditor.h"
#include"EventSystem\Event.h"
#include"Core\InfernalKernel.h"
#include"Core\BaseGameLogic.h"
class ActorCreationWindow;

class InfernalEditor : public QMainWindow, public InfernalKernel
{
	Q_OBJECT
		QStandardItemModel *m_pSceneTreeModel;
	QStandardItem* m_pSceneViewRoot;
public:
	BaseGameLogic* VCreateGameAndView()override { m_pGame = new BaseGameLogic; m_pGame->Init(); return m_pGame; }
	InfernalEditor(QWidget *parent = Q_NULLPTR);
	void UpdateTransform();
	void SetLightPos(int);
	void SetSelectedNode(std::shared_ptr<SceneNode> inNode);
	void AddObjectToScene(const char* resourcePath, QList<QStandardItem*> inItems);
	void registerDelegate();
protected:
#ifndef QT_NO_CONTEXTMENU
	void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
#endif // QT_NO_CONTEXTMENU
	public slots :


		private slots :



		void Log_event(IEventDataPtr pEventData);

	void newFile();
	void open();
	void loadfile(const QString & fileName);
	void save();
	void DeleteActor();


	void about();
	void aboutQt();
protected:


private:
	Ui::InfernalEditorClass ui;
	std::shared_ptr<SceneNode> m_pSelectedNode;
	ActorCreationWindow* m_pCreationwindow;

	void createActions();
	void OpenCreationWindow();
	void createMenus();

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *ObjectMenu;
	QMenu *helpMenu;

	QMenu* contextMenu;

	QAction *createObject;
	QAction *addObject;
	QAction* deletObject;

	QActionGroup *alignmentGroup;

	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *printAct;
	QAction *exitAct;
	QAction *undoAct;
	QAction *redoAct;
	QAction *cutAct;
	QAction *copyAct;
	QAction *pasteAct;
	QAction *boldAct;
	QAction *italicAct;
	QAction *leftAlignAct;
	QAction *rightAlignAct;
	QAction *justifyAct;
	QAction *centerAct;
	QAction *setLineSpacingAct;
	QAction *setParagraphSpacingAct;
	QAction *aboutAct;
	QAction *aboutQtAct;

};
