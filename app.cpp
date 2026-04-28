#include <iostream>
#include <gtkmm.h>
#include <memory>

// Окно настроек
class SettingsWindow : public Gtk::Window {
public:
   SettingsWindow() {
      set_title("Settings");
      set_default_size(1000,1000);
   }
};




// Основное окно
class Window : public Gtk::Window {
public:
   Window() {
      // Базовые настройки
      set_name("NanoTun 280426");
      set_default_size(712, 712);

      // Креэйты
      auto mmenu_model = Gio::Menu::create();
      auto mactions = Gio::SimpleActionGroup::create();
      
      // Кнопка
      mconnect.set_label("N");
      // Сигнал на переключение
      mconnect.signal_toggled().connect([this]() {
         if (mconnect.get_active()) {
            mconnect.set_label("И");
            std::cout << log << "Connecting\n";
         } else {
            mconnect.set_label("N");
            std::cout << log << "Disconnecting\n";
         }
      });
      


      // Фрэйм
      mframe.set_size_request(200, 200);
      mframe.set_halign(Gtk::Align::CENTER);
      mframe.set_hexpand(false);
      mframe.set_child(mconnect);
      mvbox.append(mframe);
      
      

      // Бокс
      mvbox.set_spacing(6);
      mvbox.set_orientation(Gtk::Orientation::VERTICAL);
      set_child(mvbox);

      // Меню !!!
      // топбар
      mtopbar.set_orientation(Gtk::Orientation::HORIZONTAL);
      mtopbar.set_spacing(6);
      mvbox.append(mtopbar);

      // Кнопка для меню
      mmenu_button.set_label("#");
      mmenu_popover.set_menu_model(mmenu_model);
      mmenu_button.set_popover(mmenu_popover);

      insert_action_group("win", mactions);


      // Добавляем действия 
      mactions->add_action("settings", sigc::mem_fun(*this, &Window::settings));
      mactions->add_action("groups", sigc::mem_fun(*this, &Window::groups));
      mactions->add_action("confscreen", sigc::mem_fun(*this, &Window::confscreen));
      

      // Аппендим 
      mmenu_model->append("Settings", "win.settings");
      mmenu_model->append("Groups", "win.groups");
      mmenu_model->append("Settings", "win.confscreen");
      mtopbar.append(mmenu_button);
   }

private:
   // Начальный экран
   Gtk::Box mvbox{Gtk::Orientation::VERTICAL, 6}, mtopbar{Gtk::Orientation::HORIZONTAL, 6};
   Gtk::Frame mframe;
   Gtk::ToggleButton mconnect;
   Gtk::MenuButton mmenu_button;
   Gtk::PopoverMenu mmenu_popover;

   // Действия 
   void settings() { 
      std::cout << log << "Settings opened\n";
      // Окно настроек (забрал у иишки)
      auto settings_win = std::make_unique<SettingsWindow>();
      settings_win->set_transient_for(*this);
      settings_win->show();
      // Сейв окна
      swin_save = std::move(settings_win);
   }

   
   std::unique_ptr<SettingsWindow> swin_save;


   void groups() { std::cout << log << "Groups opened\n"; }
   void confscreen() { std::cout << log << "Conf screen opened\n"; }

   // Прочее от gtkmm
   std::string log = "[LOG] ";
};




// Мэйн, запускатор
int main(int argc, char* argv[]) {
   auto app = Gtk::Application::create("testing.nanotun.vpn");
   // Запускаем
   return app->make_window_and_run<Window>(argc,argv);
}
