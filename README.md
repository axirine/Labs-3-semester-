```mermaid
graph TD;
    A(Начало) --> B{Итерации (5 раз)}
    B -->|Да| C(Обнуление счетчиков)
    C --> D{Итерации (EXPERIMENTS раз)}
    D -->|Да| E[Вызов simulate()]
    E --> F(Обновление статистики)
    F --> D
    D -->|Нет| G(Вычисление средних значений)
    G --> H(Вывод текущих результатов)
    H --> B
    B -->|Нет| I(Вычисление итоговых средних значений)
    I --> J(Вывод итоговых значений)
    J --> K(Конец)
