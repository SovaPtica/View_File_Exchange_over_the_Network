#include "mainFrame.h"
#include <wx/dirdlg.h>
#include <wx/generic/dirctrlg.h>
#include <wx/generic/panelg.h>
#include <wx/wx.h>

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Hello World") {
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                   "Help string shown in status bar for this menu item");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar(menuBar);

  // Создаем wxGenericDirCtrl без начального пути
  dirCtrl =
      new wxGenericDirCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                           wxDefaultSize, wxDIRCTRL_3D_INTERNAL);

  // Создаем wxListCtrl для правой колонки
  listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                            wxLC_REPORT);
  listCtrl->InsertColumn(0, "Name", wxLIST_FORMAT_LEFT, 200);
  listCtrl->InsertColumn(1, "Size", wxLIST_FORMAT_RIGHT, 100);
  listCtrl->InsertColumn(2, "Type", wxLIST_FORMAT_LEFT, 100);

  // Компоновка: разделяем окно на две части
  wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
  mainSizer->Add(dirCtrl, 1, wxEXPAND | wxALL, 5);  // Левая колонка
  mainSizer->Add(listCtrl, 1, wxEXPAND | wxALL, 5); // Правая колонка
  SetSizer(mainSizer);

  // Привязываем событие выбора папки в дереве
  dirCtrl->Bind(wxEVT_DIRCTRL_SELECTIONCHANGED,
                &MainFrame::OnDirSelectionChanged, this);

  // При открытии приложения показываем диалог выбора папки
  ShowFolderDialog();

  Bind(wxEVT_MENU, &MainFrame::OnHello, this, ID_Hello);
  Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
}
