#include <iostream>
#include <memory>
#include <format>

struct IPaymentStrategy {
    virtual ~IPaymentStrategy() = default;
    virtual void pay(double amount) const = 0;
};

struct CreditCardStrategy final: public IPaymentStrategy {
    void pay(double amount) const override {
        std::cout << std::format("Paying {:.2f} using Credit Card\n", amount);
    }
};

class PayPalStrategy final: public IPaymentStrategy {
  public:
    void pay(double amount) const override {
        std::cout << std::format("Paying {:.2f} using PayPal\n", amount);
    }
};

class PaymentProcessor {
    std::unique_ptr<IPaymentStrategy> strategy_ = nullptr;
  public:
    void set_strategy(std::unique_ptr<IPaymentStrategy> new_strategy) {
        strategy_ = std::move(new_strategy);
    }

    void execute_payment(double amount) const {
        if (strategy_ == nullptr) {
            return;
        }
        strategy_->pay(amount);
    }
};

int main() {
    PaymentProcessor processor;

    auto strategy = std::make_unique<PayPalStrategy>();
    processor.set_strategy(std::move(strategy));
    processor.execute_payment(100.33333);

    processor.set_strategy(std::make_unique<CreditCardStrategy>());
    processor.execute_payment(200.33333);
}
