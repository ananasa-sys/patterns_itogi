#include <iostream>
#include <string>
using namespace std;

/*
* Adapter лучше изменения старого класса, т.к:
* Старый класс не модифицируется
* Сохраняет обратную совместимость со старым кодом
* Позволяет использовать готовые библиотеки без доступа к исходникам
* Адаптация отделена от логики
* Позволяет адаптировать несколько разных классов единообразно
*/

// Целевой интерфейс (новый ПК ожидает USB)
class USBPrinter {
public:
    virtual string printUSB(const string& data, int quality) = 0;
};

class USBScanner {
public:
    virtual string scanUSB(int quality) = 0;
};

// Старый принтер с LPT-портом (несовместимый)
class OldLPTPrinter {
public:
    string printLPT(const string& data) {
        return "Старый принтер печатает по LPT: " + data;
    }
};

// Старый сканер с LPT-портом
class OldLPTScanner {
public:
    string scanLPT() {
        return "Старый сканер сканирует по LPT";
    }
};

// Адаптер для принтера: Оборачивает старый принтер для USB-интерфейса
class LPTToUSBAdapter : public USBPrinter {
private:
    OldLPTPrinter* oldPrinter;
public:
    LPTToUSBAdapter(OldLPTPrinter* p) : oldPrinter(p) {}
    string printUSB(const string& data, int quality) override {
        string qualityStr = " (качество " + to_string(quality) + " dpi)";
        return oldPrinter->printLPT(data + qualityStr + " (адаптировано для USB)");
    }
};

// Адаптер для сканера: Оборачивает старый сканер для USB-интерфейса
class LPTScannerToUSBAdapter : public USBScanner {
private:
    OldLPTScanner* oldScanner;
public:
    LPTScannerToUSBAdapter(OldLPTScanner* s) : oldScanner(s) {}
    string scanUSB(int quality) override {
        return oldScanner->scanLPT() + " (качество " + to_string(quality) + " dpi, адаптировано для USB)";
    }
};

// class-adapter (множественное наследование)
class LPTToUSBClassAdapter : public USBPrinter, private OldLPTPrinter {
public:
    string printUSB(const string& data, int quality) override {
        string qualityStr = " (качество " + to_string(quality) + " dpi)";
        return printLPT(data + qualityStr + " (адаптировано для USB через class-adapter)");
    }
};

int main()
{
    setlocale(0, "");
    OldLPTPrinter oldPrinter;
    USBPrinter* printerAdapter = new LPTToUSBAdapter(&oldPrinter);
    cout << printerAdapter->printUSB("Документ", 300) << endl;

    OldLPTScanner oldScanner;
    USBScanner* scannerAdapter = new LPTScannerToUSBAdapter(&oldScanner);
    cout << scannerAdapter->scanUSB(600) << endl;

    LPTToUSBClassAdapter classAdapter;
    cout << classAdapter.printUSB("Важный документ", 1200) << endl;

    delete printerAdapter;
    delete scannerAdapter;

    return 0;
}

