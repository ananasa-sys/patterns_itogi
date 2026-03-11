#include <iostream>
#include <string>
using namespace std;

//Абстрактные продукты (семейство UI-элементов)
class Button
{
public:
    virtual ~Button() = default;
    virtual string render() = 0;
    virtual string interact() = 0;
};

class ScrollBar
{
public:
    virtual ~ScrollBar() = default;
    virtual string render() = 0;
    virtual string interact() = 0;
};

class CheckBox
{
public:
    virtual ~CheckBox() = default;
    virtual string render() = 0;
    virtual string interact() = 0;
};

// Конкретные продукты для Windows
class WinButton : public Button
{
public:
    string render() override { return "Windows Кнопка"; }
    string interact() override { return "Клик по Windows кнопке"; }
};

class WinScrollBar : public ScrollBar
{
public:
    string render() override { return "Windows Скроллбар"; }
    string interact() override { return "Прокрутка Windows скроллбара"; }
};

class WinCheckBox : public CheckBox
{
public:
    string render() override { return "Windows Чекбокс"; }
    string interact() override { return "Переключение Windows чекбокса"; }
};

// Конкретные продукты для macOS
class MacButton : public Button
{
public:
    string render() override { return "macOS Кнопка"; }
    string interact() override { return "Клик по macOS кнопке"; }
};

class MacScrollBar : public ScrollBar
{
public:
    string render() override { return "macOS Скроллбар"; }
    string interact() override { return "Прокрутка macOS скроллбара"; }
};

class MacCheckBox : public CheckBox
{
public:
    string render() override { return "macOS Чекбокс"; }
    string interact() override { return "Переключение macOS чекбокса"; }
};

// Конкретные продукты для Linux
class LinuxButton : public Button
{
public:
    string render() override { return "Linux Кнопка"; }
    string interact() override { return "Клик по Linux кнопке"; }
};

class LinuxScrollBar : public ScrollBar
{
public:
    string render() override { return "Linux Скроллбар"; }
    string interact() override { return "Прокрутка Linux скроллбара"; }
};

class LinuxCheckBox : public CheckBox
{
public:
    string render() override { return "Linux Чекбокс"; }
    string interact() override { return "Переключение Linux чекбокса"; }
};

// Абстрактная фабрика
class UIFactory
{
public:
    virtual ~UIFactory() = default;
    virtual Button* createButton() = 0;
    virtual ScrollBar* createScrollBar() = 0;
    virtual CheckBox* createCheckBox() = 0;
};

// Конкретные фабрики
class WinFactory : public UIFactory
{
public:
    Button* createButton() override { return new WinButton(); }
    ScrollBar* createScrollBar() override { return new WinScrollBar(); }
    CheckBox* createCheckBox() override { return new WinCheckBox(); }
};

class MacFactory : public UIFactory
{
public:
    Button* createButton() override { return new MacButton(); }
    ScrollBar* createScrollBar() override { return new MacScrollBar(); }
    CheckBox* createCheckBox() override { return new MacCheckBox(); }
};

class LinuxFactory : public UIFactory
{
public:
    Button* createButton() override { return new LinuxButton(); }
    ScrollBar* createScrollBar() override { return new LinuxScrollBar(); }
    CheckBox* createCheckBox() override { return new LinuxCheckBox(); }
};

// Функция для создания фабрики на основе строки
/*
* Abstract Factory лучше отдельных factory, т.к:
* Гарантирует совместимость элементов одной платформы
* Клиент работает с единым интерфейсом фабрики
* Для новой платформы один класс фабрики
* Логика создания всех продуктов в одном месте
* Добавление новых платформ без изменения существующего кода
*/
UIFactory* createFactory(const string& platform)
{
    if (platform == "win")
    {
        return new WinFactory();
    }
    else if (platform == "mac")
    {
        return new MacFactory();
    }
    else if (platform == "linux")
    {
        return new LinuxFactory();
    }
    else
    {
        cout << "Неизвестная платформа, используется Windows по умолчанию" << endl;
        return new WinFactory();
    }
}

int main()
{
    setlocale(0, "");
    string platform;
    cout << "Выберите платформу (win/mac/linux): ";
    cin >> platform;

    UIFactory* factory = createFactory(platform);

    Button* btn = factory->createButton();
    ScrollBar* sb = factory->createScrollBar();
    CheckBox* cb = factory->createCheckBox();

    cout << "\nОтрисовка элементов: " << endl;
    cout << btn->render() << endl;
    cout << sb->render() << endl;
    cout << cb->render() << endl;

    cout << "\nВзаимодействие с элементами: " << endl;
    cout << btn->interact() << endl;
    cout << sb->interact() << endl;
    cout << cb->interact() << endl;

    delete btn;
    delete sb;
    delete cb;
    delete factory;

    return 0;
}
