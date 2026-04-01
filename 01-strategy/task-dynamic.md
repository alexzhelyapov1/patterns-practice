### Задание: "Система оплаты (Payment Processing)"

**Бизнес-кейс:**
Ты разрабатываешь бэкенд для платежного шлюза. Система должна поддерживать разные способы оплаты, и пользователь выбирает способ в момент оформления заказа.

**Твоя задача:**
1.  Создай интерфейс `IPaymentStrategy` с чисто виртуальным методом `void pay(double amount) const`.
2.  Реализуй две конкретные стратегии:
    *   `CreditCardStrategy`: выводит "Paying [amount] using Credit Card".
    *   `PayPalStrategy`: выводит "Paying [amount] using PayPal".
3.  Создай класс-контекст `PaymentProcessor`:
    *   Он должен владеть стратегией через `std::unique_ptr`.
    *   Должен быть метод `set_strategy(std::unique_ptr<IPaymentStrategy> new_strategy)` для смены способа оплаты "на лету".
    *   Метод `execute_payment(double amount)`, который делегирует работу текущей стратегии.
4.  **Важное условие:** Продумай защиту от "пустой" стратегии (если метод `execute_payment` вызван до `set_strategy`).

**Требования к коду:**
*   Используй `std::unique_ptr`.
*   Не забудь про виртуальный деструктор.
*   Используй `override` и `const`.
*   По возможности избегай `std::endl`, используй `\n`.
