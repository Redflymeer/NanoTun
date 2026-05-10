// ---------------ВНИМАНИЕ----------------
// Если вы морально не устойчивы, то не читайте этот код

#define LOG_STR "[LOG] "
#define ERR_STR "[ERROR] "

#include <iostream>
#include <gtkmm.h>
#include <memory>
#include "src/json.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <charconv>
#include <exception>




using json = nlohmann::json;




// Is var empty?
static Glib::ustring trim(const Glib::ustring& s) {
    auto start = s.find_first_not_of(" \t\n\r");
    if (start == Glib::ustring::npos) return {};
    auto end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}




// Settings Window
class SettingsWindow : public Gtk::Window {
public:
   SettingsWindow() {
     
      std::ifstream language_file{ "src/json-dir/language.json" };
      std::string language_str;

      language_file.seekg(0, std::ios::end);
      auto size = language_file.tellg();
      language_file.seekg(0, std::ios::beg);
      

      language_str.resize(static_cast<size_t>(size));
      if (size > 0) {
         language_file.read(&language_str[0], size);
      } 


      // If string is returned error / empty 
      if (!language_file || language_str.empty()) {
         language_str.clear();
      }
      

      // if json is not returned error 
      std::string lang = "";

      
      try {
         if (!language_str.empty()) {
            auto language_parse = json::parse(language_str);
            lang = language_parse.value("language", "");
         }
      }  catch (const json::parse_error& e) {
            std::cout << LOG_STR << ERR_STR << "Failed with parse json, e.what log: " << e.what() << "\n";
            close();
            return;
         }
     
      // If ok
      if (lang == "english") {
         set_title("Settings");
         std::cout << LOG_STR << "Succefuly renamed Settings Window to english\n";
         language_label.set_text("Language");
         std::cout << LOG_STR << "Succefuly renamed DropDown label to english\n";
      } else if (lang == "russian") {
         set_title("Настройки");
         std::cout << LOG_STR << "Succefuly renamed Settings Window to russian\n";
         language_label.set_text("Языки");
         std::cout << LOG_STR << "Succefuly renamed DropDown label to russian\n";
      } else {
         set_title("Settings");
         std::cout << LOG_STR << "Nothing in language.json, setted default\n";
         language_label.set_label("Language");
      }


      set_default_size(1000, 700);


      // Appends
      box.append(language_label);
      box.append(language);


      // Languages 
      const std::vector<Glib::ustring> langs {
         "English", "Russia"
      };
      

      // DropDown
      langlist = Gtk::StringList::create(langs); 
      language.set_model(langlist);
      language.set_selected(0);

      language.property_selected().signal_changed().connect(
         sigc::mem_fun(*this, &SettingsWindow::language_changed) // Если язык изменился
      );
      

      // Styles 
      language.set_size_request(100, -1);
      language.set_expand(false);
      

      // Boxes
      box.set_spacing(6);
      box.set_orientation(Gtk::Orientation::VERTICAL);
      set_child(box);
   }

private:
   // Gtk elements
   Gtk::Box box{Gtk::Orientation::VERTICAL, 6};
   Gtk::DropDown language;
   Glib::RefPtr<Gtk::StringList> langlist;
   Gtk::Label language_label;
   


   // Functions
   void language_changed() {
      // Elements
      const auto row = language.get_selected();
      std::ofstream language_file{ "src/json-dir/language.json" };
      
      // if english 
      if (row == 0) {
         json language_json = {
            {"language", "english"}
         };

         
         language_file << language_json << "\n";
         std::cout << LOG_STR << "Language setted english!\n";
      } else {
         json language_json = {
            {"language", "russian"}
         };


         language_file << language_json << "\n";
         std::cout << LOG_STR << "Language setted russian!\n";
      }
      language_file.close();
   }
};

// Add group window 
class AddGroupWindow : public Gtk::Window {
public:
   AddGroupWindow() {
      std::ifstream language_file{ "src/json-dir/language.json" };
      std::string language_str;

      language_file.seekg(0, std::ios::end);
      auto size = language_file.tellg();
      language_file.seekg(0, std::ios::beg);
      

      language_str.resize(static_cast<size_t>(size));
      if (size > 0) {
         language_file.read(&language_str[0], size);
      } 


      // If string returned error / empty
      if (!language_file || language_str.empty()) {
         language_str.clear();
      }
      

      // If json is not returned error
      std::string lang = "";

      
      try {
         if (!language_str.empty()) {
            auto language_parse = json::parse(language_str);
            lang = language_parse.value("language", "");
         }
      }  catch (const json::parse_error& e) {
            std::cout << LOG_STR << ERR_STR << "Failed with parse json, e.what log: " << e.what() << "\n";
            close();
            return;
         }

      if (lang == "english") {
         set_title("Add Group");
         std::cout << LOG_STR << "Succefly renamed Add Groups Window to english\n";


         // Entry
         Entry_Name.set_placeholder_text("example: My Subscribe");
         Entry_Url.set_placeholder_text("Url");


         // Label
         Label_Name.set_text("Name of group*");
         Label_Url.set_text("Url to your VPN");
         Label_Auto_Update.set_text("Auto Update");
         Label_Auto_Update_Interval.set_text("Auto Update interval* (Only if you setted Auto Update Yes)");
         

         // Confirm button
         Confirm.set_label("Confirm");


         // DropDown list
         const std::vector <Glib::ustring> Auto_Update_Choice {
            "No", "Yes"
         };
         
         Auto_Update_List = Gtk::StringList::create(Auto_Update_Choice);

      }  else if (lang == "russian") {
         set_title("Добавить группу");
         std::cout << LOG_STR << "Succefly renamed Add Group Window to russian\n";


         // Entry
         Entry_Name.set_placeholder_text("пример: Моя Подписка");
         Entry_Url.set_placeholder_text("Ссылка");
      

         // Label
         Label_Name.set_text("Имя группы*");
         Label_Url.set_text("Ссылка на твой ВПН"); 
         Label_Auto_Update.set_text("Авто обновление");
         Label_Auto_Update_Interval.set_text("Интервал авто обновления* (Только если ты выбрал в Авто обновлении Да)");


         // Confirm Button
         Confirm.set_label("Подтвердить");


         // DropDown list
         const std::vector <Glib::ustring> Auto_Update_Choice {
            "Нет", "Да"
         };
         

         Auto_Update_List = Gtk::StringList::create(Auto_Update_Choice);

      }  else {
         set_title("Add Group");
         std::cout << LOG_STR << "Nothing in language.json, setted default\n";


         // Entry
         Entry_Name.set_placeholder_text("example: My Subscribe");
         Entry_Url.set_placeholder_text("Url");


         // Label
         Label_Name.set_text("Name of group*");
         Label_Url.set_text("Url to your VPN");
         Label_Auto_Update.set_text("Auto Update");
         Label_Auto_Update_Interval.set_text("Auto Update interval* (Only if you setted Auto Update Yes)");
         

         // Confirm button
         Confirm.set_label("Confirm");


         // DropDown list
         const std::vector <Glib::ustring> Auto_Update_Choice {
            "No", "Yes"
         };
         
         Auto_Update_List = Gtk::StringList::create(Auto_Update_Choice);
      }

      set_default_size(500, 500);
      set_resizable(false);


      // Appends
      box.append(Label_Name);
      box.append(Entry_Name);
      box.append(Label_Url);
      box.append(Entry_Url);
      box.append(Label_Auto_Update);
      box.append(Auto_Update_Drop_Down);
      box.append(Label_Auto_Update_Interval);
      box.append(Entry_Auto_Update_Interval);
      box.append(Confirm);
      

      // Entry
      Entry_Auto_Update_Interval.set_placeholder_text("5");
      

      // Confirm Button
      Confirm.set_expand(false);
      Confirm.set_size_request(200, 50);
      Confirm.set_halign(Gtk::Align::CENTER);
      

      // Confirm Button Signal
      Confirm.signal_clicked().connect(
         sigc::mem_fun(*this, &AddGroupWindow::confirm_moves)
      );
      

      
      // DropDown
      Auto_Update_Drop_Down.set_model(Auto_Update_List);
      Auto_Update_Drop_Down.set_selected(0);
      Auto_Update_Drop_Down.set_expand(false);
      

      // DropDown Signal
      Auto_Update_Drop_Down.property_selected().signal_changed().connect(
         sigc::mem_fun(*this, &AddGroupWindow::drop_down_selected)
      );
      

      // Boxes
      box.set_orientation(Gtk::Orientation::VERTICAL);
      box.set_spacing(6);
      set_child(box);
   }

private:
   // Gtk elements
   Gtk::Box box{Gtk::Orientation::VERTICAL, 6};
   Gtk::Entry Entry_Name;
   Gtk::Entry Entry_Url;
   Gtk::DropDown Auto_Update_Drop_Down;
   Glib::RefPtr<Gtk::StringList> Auto_Update_List;
   Gtk::Entry Entry_Auto_Update_Interval;
   Gtk::Label Label_Name;
   Gtk::Label Label_Url;
   Gtk::Label Label_Auto_Update;
   Gtk::Label Label_Auto_Update_Interval;
   Gtk::Button Confirm;
   


   // Functions
   void drop_down_selected() {
      const auto selected = Auto_Update_Drop_Down.get_selected();
      std::cout << LOG_STR << "Auto Update Drop Down changed on row: " << selected << std::endl;
   }



   // 144
   void confirm_moves() {
      // Gtk elements
      Glib::ustring name_ustring = Entry_Name.get_text();
      Glib::ustring url_ustring = Entry_Url.get_text();
      Glib::ustring auto_update_interval_ustring = Entry_Auto_Update_Interval.get_text();
      const auto dropdown_row = Auto_Update_Drop_Down.get_selected();
      int auto_update_interval_int = 0;
      std::ofstream groups_file("src/json-dir/groups.json", std::ios::app);
      json add_group_json;
      

      // DropDown
      // If auto update turned 
      if (dropdown_row == 1) {
         if (!auto_update_interval_ustring.empty()) {
            // Elements if function
            auto str = std::string_view(std::string(auto_update_interval_ustring));
            auto [ptr, ec] = std::from_chars(
               str.data(), str.data() + str.size(), auto_update_interval_int
            );
            // if is more than integer(2147483647) or non correct input
            if (ec != std::errc()) {
               std::cout << LOG_STR << ERR_STR << "Non correct input or more then int\n";
               close();
               return;
            }
         }
         

         // if interval is less than 0 or equals 0
         if (auto_update_interval_int <= 0) {
            std::cout << LOG_STR << ERR_STR << "0 is not good variant for auto update\n";
            close();
            return;
         }


         // If name of group is empty
         auto name = trim(Entry_Name.get_text());
         if (name.empty()) {
            std::cout << LOG_STR << ERR_STR << "Name is empty\n";
            close();
            return;
         }
         

         // Making .json
         add_group_json = {
            {"name", std::string(name_ustring)},
            {"url", std::string(url_ustring)},
            {"autoupdate", true},
            {"autoupdateinterval", auto_update_interval_int}
         };
      } else { // if auto update is turned off
         auto name = trim(Entry_Name.get_text());


         // If name of group is empty
         if (name.empty()) {
            std::cout << LOG_STR << ERR_STR << "Name is empty\n";
            close();
            return;
         }
         

         // Making .json
         add_group_json = {
            {"name", std::string(name_ustring)},
            {"url", std::string(url_ustring)},
            {"autoupdate", false},
            {"autoupdateinterval", "none"}
         };
         std::cout << LOG_STR << "Succefuly created group without autoupdate in groups.json\n";
      }
      

      // Apendding changes to file
      groups_file << add_group_json << "\n";
      groups_file.close();
      // closing window 
      close();
   }
};




// Groups Window
class GroupsWindow : public Gtk::Window {
public:
   GroupsWindow() {
      std::ifstream language_file{ "src/json-dir/language.json" };
      std::string language_str;

      language_file.seekg(0, std::ios::end);
      auto size = language_file.tellg();
      language_file.seekg(0, std::ios::beg);
      

      language_str.resize(static_cast<size_t>(size));
      if (size > 0) {
         language_file.read(&language_str[0], size);
      } 


      // If string returned error / empty
      if (!language_file || language_str.empty()) {
         language_str.clear();
      }
      

      // If json is not returned error
      std::string lang = "";

      
      try {
         if (!language_str.empty()) {
            auto language_parse = json::parse(language_str);
            lang = language_parse.value("language", "");
         }
      }  catch (const json::parse_error& e) {
            std::cout << LOG_STR << ERR_STR << "Failed with parse json, e.what log: " << e.what() << "\n";
            close();
            return;
         }

      if (lang == "english") {
         set_title("Groups");
         std::cout << LOG_STR << "Renamed Group Window title to english\n";
      } else if (lang == "russian") {
         set_title("Группы");
         std::cout << LOG_STR << "Renamed Group Window title to russian\n";
      } else {
         set_title("Groups");
         std::cout << LOG_STR << "Nothing in language.json, setted default\n";
      }


      set_default_size(1000, 700);
      

      // Appends
      box.append(add_group);
      scroll.set_child(box);
      
      
      // Making .json file and writting 
      json_create("src/json-dir/groups.json");
      

      // Add Group Button
      add_group.set_label("+");
      add_group.set_size_request(50, 50);
      add_group.set_expand(false);
      add_group.set_halign(Gtk::Align::END);


      // Add Group Button Signal
      add_group.signal_clicked().connect(
         sigc::mem_fun(*this, &GroupsWindow::add_group_connect)
      );
      
      // Boxes
      box.set_orientation(Gtk::Orientation::VERTICAL);
      box.set_spacing(6);


      // Scroll
      set_child(scroll);
   }



   // 273
   void json_create(const std::string& path) {
      // Reading file
      std::ifstream groups_file("src/json-dir/groups.json");


      // If file is non exists
      if (!groups_file.is_open()) {
         std::cout << LOG_STR << ERR_STR << "groups.json doesn't exist\n";
         std::cout << LOG_STR << "Creating groups.json\n";
         std::ofstream groups_file_ofstream("src/json-dir/groups.json", std::ios::app);
         groups_file_ofstream.close();
         groups_file.open("src/json-dir/groups.json");
         std::cout << LOG_STR << "File created groups.json!\n";
      }

      
      // lines
      std::string line;
      std::size_t lines_read = 0;
      

      // Getting from .json name of group and url 
      while (std::getline(groups_file, line)) {
         // If line is empty
         if (line.empty()) continue;


         // If lines is more than 1000
         if (++lines_read > 1000) break;
         

         // Main function of cycle
         try {
            // string of parsed line
            json item = json::parse(line);
            

            // Elements
            std::string name = item.value("name", "");
            std::string url = item.value("url", "");
           
            // Making elements only for it line
            auto* url_label = Gtk::make_managed<Gtk::Label>();
            auto* delete_button = Gtk::make_managed<Gtk::Button>();
            auto* change_button = Gtk::make_managed<Gtk::Button>();
            auto* frame = Gtk::make_managed<Gtk::Frame>();
            auto* cbox = Gtk::make_managed<Gtk::Box>(
               Gtk::Orientation::HORIZONTAL, 6
            );
            

            // Making text
            url_label->set_text(url);
            delete_button->set_label("-");
            change_button->set_label("✎");
            frame->set_label(name);


            // Frame
            frame->set_label_align(Gtk::Align::CENTER);
            frame->set_margin(10);
            

            // Append
            cbox->append(*url_label);
            cbox->append(*delete_button);
            cbox->append(*change_button);
            box.append(*frame);

            // Child
            frame->set_child(*cbox);

            // Delete Button Signal
            delete_button->signal_clicked().connect(
               [this, line = line]() {
                  this->delete_line(line);
               }
            );

         } catch (...) {
            // If parsing return error
            std::cout << LOG_STR << ERR_STR << "Dont correct parsing\n";
            return;
         }
      }
   }



   // Deleting line function 
   void delete_line(std::string_view line_to_delete) {
      // Elements
      std::ifstream groups_file("src/json-dir/groups.json");
      std::vector<std::string> preserved;
      std::string line;


      // Cycle of deleting line 
      while (std::getline(groups_file, line)) {
         if (line.empty()) continue;


         // if line is line to delete 
         if (line != line_to_delete) {
            preserved.push_back(line);
         }
      }
      

      // Writting
      std::ofstream groups_file_out("src/json-dir/groups.json");


      for (const auto& saved : preserved) {
         groups_file_out << saved << "\n";
      }


      // Closining
      groups_file_out.close();
      

      // LOG
      std::cout << LOG_STR << "Line deleted from file\n";
   }


private:
   // Gtk Elements
   Gtk::ScrolledWindow scroll;
   Gtk::Button add_group;
   Gtk::Box box{Gtk::Orientation::VERTICAL, 6};
   


   // Functions
   void add_group_connect() {
      // LOG
      std::cout << LOG_STR << "Add Group Window clicked\n";


      // Sabing window
      auto addgroup_win = std::make_unique<AddGroupWindow>();
      addgroup_win->set_transient_for(*this);
      addgroup_win->show();
      addgroup_win_save = std::move(addgroup_win);
   }

   std::unique_ptr<AddGroupWindow> addgroup_win_save;
};




// Configurations window
class ConfigWindow : public Gtk::Window {
public:
   ConfigWindow() {
      std::ifstream language_file{ "src/json-dir/language.json" };
      std::string language_str;

      language_file.seekg(0, std::ios::end);
      auto size = language_file.tellg();
      language_file.seekg(0, std::ios::beg);
      

      language_str.resize(static_cast<size_t>(size));
      if (size > 0) {
         language_file.read(&language_str[0], size);
      } 


      // If string is returned error / empty 
      if (!language_file || language_str.empty()) {
         language_str.clear();
      }
      

      // If json ok
      std::string lang = "";

      
      try {
         if (!language_str.empty()) {
            auto language_parse = json::parse(language_str);
            lang = language_parse.value("language", "");
         }
      }  catch (const json::parse_error& e) {
            std::cout << LOG_STR << ERR_STR << "Failed with parse json, e.what log: " << e.what() << "\n";
            close();
            return;
         }

      if (lang == "english") {
         set_title("Configurations menu");
         std::cout << LOG_STR << "Renamed Configurations Window title to english\n";
      } else if (lang == "russian") {
         set_title("Меню конфигов");
         std::cout << LOG_STR << "Renamed Configurations Window title to russian\n";
      } else {
         set_title("Configurations menu");
         std::cout << LOG_STR << "Nothing in language.json, setted default\n";
      }


      set_default_size(1000, 700);
      

      // Append
      vbox.append(add);
      

      // Add
      add.set_label("+");
      add.signal_clicked().connect(sigc::mem_fun(*this, &ConfigWindow::add_signal));
      
      
      // Boxes
      vbox.set_orientation(Gtk::Orientation::VERTICAL);
      vbox.set_spacing(6);
      set_child(vbox);
   }
   


   void add_signal() {
      std::cout << LOG_STR << "Add button toggled\n";
   }


private:
   // Gtk Elements
   Gtk::Button add;
   Gtk::Button check;
   Gtk::Box vbox{Gtk::Orientation::VERTICAL, 6};
};

// Main window
class Window : public Gtk::Window {
public:
   Window() {
      // Making language json
      std::ifstream language_file{ "src/json-dir/language.json" };
      if (!language_file) {
         std::cout << LOG_STR << ERR_STR << "src/language.json is doesn't exist, creating\n";
         std::ofstream language_file_out{ "src/json-dir/language.json" };
         language_file_out.close();
         language_file.open("src/json-dir/language.json");
         std::cout << LOG_STR << "Created src/json-dir/language.json\n";
      }
      

      std::string language_str;

      language_file.seekg(0, std::ios::end);
      auto size = language_file.tellg();
      language_file.seekg(0, std::ios::beg);
      

      language_str.resize(static_cast<size_t>(size));
      if (size > 0) {
         language_file.read(&language_str[0], size);
      } 


      // If string is returned error / empty
      if (!language_file || language_str.empty()) {
         language_str.clear();
      }
      

      // If json ok
      std::string lang = "";

      
      try {
         if (!language_str.empty()) {
            auto language_parse = json::parse(language_str);
            lang = language_parse.value("language", "");
         }
      }  catch (const json::parse_error& e) {
            std::cout << LOG_STR << ERR_STR << "Failed with parse json, e.what log: " << e.what() << "\n";
            close();
            return;
         }
      
      
      

      

      // Main settings
      set_title("NanoTun Testing");
      set_default_size(712, 712);
      

      // Strings
      auto actions = Gio::SimpleActionGroup::create();
      auto menu_model = Gio::Menu::create();


      // Appends
      vbox.append(hbox);
      hbox.append(menu_button);

      if (lang == "english") {
         menu_model->append("Settings", "win.settings");
         menu_model->append("Groups", "win.groups");
         menu_model->append("Configurations", "win.configurations");

      }  else if (lang == "russian") { 
         menu_model->append("Настройки", "win.settings");
         menu_model->append("Группы", "win.groups");
         menu_model->append("Конфиги", "win.configurations");
      }  else { 
         menu_model->append("Settings", "win.settings");
         menu_model->append("Groups", "win.groups");
         menu_model->append("Configurations", "win.configurations");
      }
      

      // Center box Appends
      cbox.append(connect_button);
      vbox.append(cbox);
      

      // Menu Button
      menu_button.set_label("#");
      menu_button.set_popover(menu_popover);


      insert_action_group("win", actions);

      
      // Style
      menu_button.set_halign(Gtk::Align::START);
      menu_button.set_expand(false);
      

      // Actions
      actions->add_action("settings", sigc::mem_fun(*this, &Window::settings));
      actions->add_action("groups", sigc::mem_fun(*this, &Window::groups));
      actions->add_action("configurations", sigc::mem_fun(*this, &Window::configurations));      

      // Menu Popover
      menu_popover.set_menu_model(menu_model);
      

      // Connect_button
      connect_button.set_label("N");
      connect_button.signal_toggled().connect(sigc::mem_fun(*this, &Window::connect));
      connect_button.set_halign(Gtk::Align::CENTER);
      connect_button.set_expand(false);
      connect_button.set_size_request(200, 200);
      

      // Box
      // Vbox
      vbox.set_spacing(6);
      vbox.set_orientation(Gtk::Orientation::VERTICAL);
      set_child(vbox);
      

      // Hbox
      hbox.set_orientation(Gtk::Orientation::HORIZONTAL);
      hbox.set_spacing(6);
      

      // Cbox
      cbox.set_orientation(Gtk::Orientation::VERTICAL);
      cbox.set_spacing(6);
      cbox.set_hexpand(true);
      cbox.set_halign(Gtk::Align::CENTER);
   }



   // Making settings window
   void settings() {
      // LOG
      std::cout << LOG_STR << "Settings opened\n";


      // Making window
      auto settings_win = std::make_unique<SettingsWindow>();
      settings_win->set_transient_for(*this);
      settings_win->show();
      settings_win_save = std::move(settings_win);
   }
   


   // Making groups window
   void groups() {
      // LOG
      std::cout << LOG_STR << "Groups opened\n";


      // Making window
      auto groups_win = std::make_unique<GroupsWindow>();
      groups_win->set_transient_for(*this);
      groups_win->show();
      groups_win_save = std::move(groups_win);
   }


   // Making configuration screen
   void configurations() {
      // LOG
      std::cout << LOG_STR << "Conf screen opened\n";


      // Making window
      auto configure_screen_win = std::make_unique<ConfigWindow>();
      configure_screen_win->set_transient_for(*this);
      configure_screen_win->show();
      configure_win_save = std::move(configure_screen_win);
   }



   // Connect
   void connect() {
      if (connect_button.get_active()) {
         std::cout << LOG_STR << "Connect button toggled (connecting)\n";
         connect_button.set_label("И");
      } else {
         std::cout << LOG_STR << "Connect button toggled (disconnecting)\n";
         connect_button.set_label("N");
      }
   }

private:
   // Gtk Elements
   Gtk::Box vbox{Gtk::Orientation::VERTICAL, 6};
   Gtk::Box hbox{Gtk::Orientation::HORIZONTAL, 6};
   Gtk::Box cbox{Gtk::Orientation::VERTICAL, 6};
   Gtk::ToggleButton connect_button;
   Gtk::MenuButton menu_button;
   Gtk::PopoverMenu menu_popover;
   

   // Saving windows
   std::unique_ptr<SettingsWindow> settings_win_save;
   std::unique_ptr<GroupsWindow> groups_win_save;
   std::unique_ptr<ConfigWindow> configure_win_save;
};



// Starting
int main(int argc, char* argv[]) {
   auto app = Gtk::Application::create("testing.nanotun.vpn");
   return app->make_window_and_run<Window>(argc, argv);
}
