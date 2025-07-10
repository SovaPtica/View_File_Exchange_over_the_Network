#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/dir.h>
#include <wx/dirctrl.h>

class MainFrame : public wxFrame
{

      wxGenericDirCtrl* dirCtrl;
      wxListCtrl* listCtrl;
      wxString rootPath; // Храним корневую папку


      void OnHello(wxCommandEvent& event);
      void OnExit (wxCommandEvent& event);
      void OnAbout(wxCommandEvent& ecent);

      void OnDirSelectionChanged(wxCommandEvent& event);
      void ShowFolderDialog();
      void UpdateFileList(const wxString& path);



 

   public:
      MainFrame();
};

enum 
{
   ID_Hello =1
};
