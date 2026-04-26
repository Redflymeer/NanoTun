#include <iostream>
#include <gtkmm.h>



// Основное окно
class Window : public Gtk::Window {
public:
   Window() {
      // Базовые настройки
      set_name("NanoTun 260426");
      set_default_size(712, 712);
      
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
   }

private:
   // Начальный экран
   Gtk::Box mvbox{Gtk::Orientation::VERTICAL, 6};
   Gtk::Frame mframe;
   Gtk::ToggleButton mconnect;

   // Прочее от gtkmm
   std::string log = "[LOG] ";
};



// Мэйн, запускатор
int main(int argc, char* argv[]) {
   auto app = Gtk::Application::create("testing.nanotun.vpn");
   // Запускаем
   return app->make_window_and_run<Window>(argc,argv);
}
