
#include "MyApp.h"
#include "mainFrame.h"

bool MyApp::OnInit() {
  MainFrame *frame = new MainFrame();
  frame->Show(true);
  return true;
}

void MainFrame::OnExit(wxCommandEvent &event) { Close(true); }

void MainFrame::OnAbout(wxCommandEvent &event) {
  wxMessageBox("This is a wxWidgets Hello World example", "About Hello World",
               wxOK | wxICON_INFORMATION);
}

void MainFrame::OnHello(wxCommandEvent &event) {
  wxLogMessage("Hello world from wxWidgets!");
}

void MainFrame::ShowFolderDialog() {
  // Показываем диалог выбора папки
  wxDirDialog dirDialog(this, "Choose a folder", wxEmptyString,
                        wxDD_DEFAULT_STYLE);
  if (dirDialog.ShowModal() == wxID_OK) {
    rootPath = dirDialog.GetPath(); // Сохраняем корневую папку
    dirCtrl->SetPath(rootPath);     // Устанавливаем текущую папку
    dirCtrl->ReCreateTree();        // Перестраиваем дерево
    UpdateFileList(rootPath);       // Обновляем содержимое в wxListCtrl
  } else {
    // Если пользователь не выбрал папку, закрываем приложение
    Close(true);
  }
}

void MainFrame::OnDirSelectionChanged(wxCommandEvent &event) {
  // Получаем путь выбранной папки
  wxString selectedPath = dirCtrl->GetPath();

  // Проверяем, не пытается ли пользователь выйти за пределы rootPath
  if (!selectedPath.IsEmpty() && !selectedPath.StartsWith(rootPath)) {
    // Возвращаем к rootPath, если попытка выйти выше
    dirCtrl->SetPath(rootPath);
    return;
  }

  UpdateFileList(selectedPath);
}

void MainFrame::UpdateFileList(const wxString &path) {
  // Очищаем текущий список
  listCtrl->DeleteAllItems();

  // Открываем директорию
  wxDir dir(path);
  if (!dir.IsOpened())
    return;

  // Перебираем файлы и папки
  wxString filename;
  long index = 0;
  bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES | wxDIR_DIRS);
  while (cont) {
    listCtrl->InsertItem(index, filename);

    // Определяем тип (папка или файл)
    wxString type =
        wxDirExists(path + wxFILE_SEP_PATH + filename) ? "Folder" : "File";
    listCtrl->SetItem(index, 2, type);

    // Получаем размер файла (для папок оставляем пустым)
    if (type == "File") {
      wxStructStat stat;
      wxStat(path + wxFILE_SEP_PATH + filename, &stat);
      listCtrl->SetItem(index, 1,
                        wxString::Format("%lld KB", stat.st_size / 1024));
    } else {
      listCtrl->SetItem(index, 1, "");
    }

    index++;
    cont = dir.GetNext(&filename);
  }
}
