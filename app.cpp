// ------------------- ВНИМАНИЕ ---------------------
// Если вы морально не устойчевы, то не читайте этот код, потому что я сам от него схожу
// сума


#include <iostream>
#include <gtkmm.h>
#include <memory>

// [ОКНО НАСТРОЕК]
class SettingsWindow : public Gtk::Window {
public:
   SettingsWindow() {
      set_title("Settings");
      set_default_size(1000,1000);
   }
};


class GroupsWindow : public Gtk::Window {
public:
   GroupsWindow() {
      set_title("Groups");
      set_default_size(1000,1000);
   }
};



// [ОКНО КОНФИГОВ]
class ConfigWindow : public Gtk::Window {
public:
   ConfigWindow() {
      set_title("Configuration Window");
      set_default_size(1000,1000);
      

       // [АППЕНДЫ]
      vbox.append(frame2add);
      frame2add.set_child(add);


      // [КНОПКИ]
      add.set_label("+");
      add.signal_clicked().connect(sigc::mem_fun(*this, &ConfigWindow::add_signal));
      // [ПЛЭЙС ХОЛДЕРЫ]
       
      // [ФРЭЙМЫ]
      frame2add.set_size_request(50,50);
      frame2add.set_halign(Gtk::Align::END);
      frame2add.set_expand(false);


     

      // [БОКСЫ]
      vbox.set_orientation(Gtk::Orientation::VERTICAL);
      vbox.set_spacing(6);
      set_child(vbox);
   }
private:
   Gtk::Button add;
   Gtk::Button check;
   Gtk::Box vbox{Gtk::Orientation::VERTICAL, 6};
   Gtk::Frame frame2add;

   // [ADD SIGNAL]
   void add_signal () {
      std::cout << "[LOG] " << "Add button toggled\n";
   }
};



// Основное окно
class Window : public Gtk::Window {
public:
   Window() {
      // Базовые настройки
      set_name("NanoTun 290426");
      set_default_size(712, 712);
      

      // [АППЕНД]
      auto actions = Gio::SimpleActionGroup::create();
      auto menu_model = Gio::Menu::create();
      vbox.append(topbar);
      topbar.append(menu_button);
      menu_model->append("Settings", "win.settings");
      menu_model->append("Groups", "win.groups"); 
      menu_model->append("Conf Screen", "win.confscreen");
      vbox.append(frame2connect);




      // [МЕНЮ]
      menu_button.set_label("#");
      menu_button.set_popover(menu_popover);
      insert_action_group("win", actions);

      // Добавляем действия 
      actions->add_action("settings", sigc::mem_fun(*this, &Window::settings));
      actions->add_action("groups", sigc::mem_fun(*this, &Window::groups));
      actions->add_action("confscreen", sigc::mem_fun(*this, &Window::confscreen));
      menu_popover.set_menu_model(menu_model);

      
      // [КОННЕКТ]
      button2connect.set_label("N");
      // Сигнал на переключение
      button2connect.signal_toggled().connect(sigc::mem_fun(*this, &Window::connect));
      
      
      // [ФРЭЙМ]
      frame2connect.set_size_request(200, 200);
      frame2connect.set_halign(Gtk::Align::CENTER);
      frame2connect.set_expand(false);
      frame2connect.set_child(button2connect);

      // [БОКСЫ]
      // VBOX
      vbox.set_spacing(6);
      vbox.set_orientation(Gtk::Orientation::VERTICAL);
      set_child(vbox);
      // TOPBAR
      topbar.set_orientation(Gtk::Orientation::HORIZONTAL);
      topbar.set_spacing(6);
   }

private:
   // [ОПРЕДЕЛЕНИЕ]
   Gtk::Box vbox{Gtk::Orientation::VERTICAL, 6}, topbar{Gtk::Orientation::HORIZONTAL, 6};
   Gtk::Frame frame2connect;
   Gtk::ToggleButton button2connect;
   Gtk::MenuButton menu_button;
   Gtk::PopoverMenu menu_popover;

   // [КОМАНДЫ]
   void settings() { 
      std::cout << log << "Settings opened\n";
      // Окно настроек (забрал у иишки)
      auto settings_win = std::make_unique<SettingsWindow>();
      settings_win->set_transient_for(*this);
      settings_win->show();
      // Сейв окна
      screenwin_save = std::move(settings_win);
   }

   
   std::unique_ptr<SettingsWindow> screenwin_save;


   void groups() { 
      std::cout << log << "Groups opened\n"; 
      // Окно групп
      auto groups_win = std::make_unique<GroupsWindow>();
      groups_win->set_transient_for(*this);
      groups_win->show();
      // Сейв окна
      groupswin_save = std::move(groups_win);
   }

   std::unique_ptr<GroupsWindow> groupswin_save;

   void confscreen() { 
      std::cout << log << "Conf screen opened\n"; 
      // Окно конфигов
      auto confscreen_win = std::make_unique<ConfigWindow>();
      confscreen_win->set_transient_for(*this);
      confscreen_win->show();
      // Сейвим окно
      confwin_save = std::move(confscreen_win);
   }


   void connect() {
      if (button2connect.get_active()) {
         std::cout << log << "Connect button toggled (connecting)\n";
      } else {
         std::cout << log << "Connect button toggled (disconnecting)\n";
      }
   }

   std::unique_ptr<ConfigWindow> confwin_save;

   // [НЕ GTKMM]
   std::string log = "[LOG] ";
};




// Мэйн, запускатор
int main(int argc, char* argv[]) {
   auto app = Gtk::Application::create("testing.nanotun.vpn");
   // Запускаем
   return app->make_window_and_run<Window>(argc,argv);
}
