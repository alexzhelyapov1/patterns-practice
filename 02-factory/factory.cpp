#include <iostream>
#include <memory>

struct IButton {
    virtual ~IButton() = default;
    virtual void render() const = 0;
};

struct WindowsButton final: IButton {
    void render() const override {
        std::cout << "Windows button\n";
    }
};

struct LinuxButton final: IButton {
    void render() const override {
        std::cout << "Linux button\n";
    }
};

class Dialog {
  protected:
    Dialog() = default;
  public:
    virtual ~Dialog() = default;
    [[nodiscard]] virtual std::unique_ptr<IButton> createButton() const = 0;

    void render() const {
        if (auto btn = createButton(); btn != nullptr) {
            btn->render();
        }
    }
};

struct WindowsDialog final: Dialog {
    [[nodiscard]] std::unique_ptr<IButton> createButton() const override {
        return std::make_unique<WindowsButton>();
    }
};

struct LinuxDialog final: Dialog {
    [[nodiscard]] std::unique_ptr<IButton> createButton() const override {
        return std::make_unique<LinuxButton>();
    }
};

int main() {
    WindowsDialog wd;
    wd.render();

    std::make_unique<LinuxDialog>()->render();
}