#pragma once

#include <wx/object.h>
#include <wx/wx.h>

class MyApp : public wxApp
{
   public:
      virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);



