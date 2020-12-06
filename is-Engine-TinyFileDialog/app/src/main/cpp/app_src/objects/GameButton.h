#ifndef GAMEBUTTON_H_INCLUDED
#define GAMEBUTTON_H_INCLUDED

#include "../../isEngine/ext_lib/TinyFileDialogs/TinyDialogBox.h"
#include "../../isEngine/system/entity/Button.h"

class GameButton : public is::Button
{
public:
    GameButton(float x, float y, std::string const &title, std::string const &name, is::GameDisplay *scene):
        Button(scene->GRMgetTexture("button"), x, y, title, name, true, scene) {}

    void onClick()
    {
        // Type of file to load / save (only these files will be visible in the dialog box)
        // The type of the variable changes depending on the operating system
        tinyString filterPatterns[2] = {
                                         #if !defined(SFML_SYSTEM_LINUX)
                                         L"*.sav", L"*.save" // Windows (wchar_t)
                                         #else
                                         "*.sav", "*.save" // Linux (char)
                                         #endif
                                         };

        ////////////////////////////////////////////////////////////
        // For each button name we perform a different action
        //
        // Functions which load / save files return an empty string ("") in case of error
        ////////////////////////////////////////////////////////////

        if (m_strName == "save_file")
        {
            // We display a dialog box to save a file
            std::string filePath = is::TinyDialogBox::showFileDialogBox(is::TinyDialogBox::FileDialogType::SAVE_FILE,
                                                                        "Save File",
                                                                        filterPatterns,
                                                                        "Default file name",
                                                                        "Error message!",
                                                                        "Error dialog");
            // Dialog box that displays the path of the saved file
            is::TinyDialogBox::showDialogBox("Save File Path",
                                             "The path of your file: " + filePath,
                                             is::TinyDialogBox::DialogType::OK,
                                             is::TinyDialogBox::IconType::INFO);
        }

        if (m_strName == "load_file")
        {
            // We display a dialog box to load a file
            std::string filePath = is::TinyDialogBox::showFileDialogBox(is::TinyDialogBox::FileDialogType::LOAD_FILE,
                                                                        "Load File",
                                                                        filterPatterns);

            // Dialog box that displays the path of the loaded file
            is::TinyDialogBox::showDialogBox("Load File Path",
                                             "The path of your file: " + filePath,
                                             is::TinyDialogBox::DialogType::OK,
                                             is::TinyDialogBox::IconType::INFO);
        }

        if (m_strName == "ok_dialog")
        {
            // Dialog box that displays information
            is::TinyDialogBox::showDialogBox("OK Dialog", "Hello World !",
                                             is::TinyDialogBox::DialogType::OK,
                                             is::TinyDialogBox::IconType::INFO);
        }

        if (m_strName == "okcancel_dialog")
        {
            // Dialog box that displays a question with a WARNING icon
            int answer = is::TinyDialogBox::showDialogBox("OK-Cancel Dialog",
                                                          "Do you want to cancel this operation?",
                                                          is::TinyDialogBox::DialogType::OKCANCEL,
                                                          is::TinyDialogBox::IconType::WARNING);

            // Dialog box that displays the answer
            is::TinyDialogBox::showDialogBox("Your answer is", (answer == 1 ? "Ok" : "Cancel"),
                                             is::TinyDialogBox::DialogType::OK,
                                             is::TinyDialogBox::IconType::INFO);
        }

        if (m_strName == "yesno_dialog")
        {
            // Dialog box that displays a question with a QUESTION icon
            int answer = is::TinyDialogBox::showDialogBox("YES-NO Dialog",
                                             "Do you like creating video games?",
                                             is::TinyDialogBox::DialogType::YESNO,
                                             is::TinyDialogBox::IconType::QUESTION);

            // Dialog box that displays the answer
            is::TinyDialogBox::showDialogBox("Your answer is", (answer == 1 ? "Yes" : "No"),
                                             is::TinyDialogBox::DialogType::OK,
                                             is::TinyDialogBox::IconType::INFO);
        }

        if (m_strName == "folder")
        {
            // The default search directory changes depending on the operating system
            std::string defaultDir =
                                     #if !defined(SFML_SYSTEM_LINUX)
                                     "C:\\" // Windows
                                     #else
                                     "/usr/local" // Linux
                                     #endif
                                     ;

            // Dialog box to open a folder
            std::string folderPath = is::TinyDialogBox::showFolderDialogBox("Folder Dialog",
                                                                            defaultDir,
                                                                            "Error message!",
                                                                            "Error dialog");

            // Dialog box that displays the path of the open folder
            is::TinyDialogBox::showDialogBox("Folder Path",
                                             "The path of your folder: " + folderPath,
                                             is::TinyDialogBox::DialogType::OK,
                                             is::TinyDialogBox::IconType::INFO);
        }
    }
};

#endif // GAMEBUTTON_H_INCLUDED
