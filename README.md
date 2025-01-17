# Устройство Приточного Клапана

## Описание

Устройство приточного клапана предназначено для поддержания качества воздуха в помещениях. Оно управляется шаговым мотором и включает в себя различные режимы работы. Клапан обеспечивает изменение степени открытия, а также управляет скоростью вентилятора с двумя режимами: медленной и быстрой. В устройстве также установлен датчик температуры и концевой выключатель для отслеживания полного закрытия клапана. Если возникает ошибка, загорается синий индикатор.

## Основные компоненты

- **Шаговый мотор:** Управляет открытием и закрытием клапана для регулирования потока воздуха.
- **Концевой выключатель:** Отслеживает, закрыт ли клапан полностью.
- **Вентилятор:** Осуществляет принудительный воздухозабор с двумя скоростями работы (медленная и быстрая).
- **Датчик температуры:** Позволяет отслеживать температуру в помещении.
- **Wi-Fi и MQTT:** Используются для передачи данных о состоянии устройства и управления им через облако.

## Принцип работы

1. **Запуск и инициализация:**
   - При включении система выполняет инициализацию и калибровку положения клапана с помощью шагового мотора.
   
2. **Режимы работы:**
   - Устройство может работать в нескольких режимах: автоматическом, минимальном, максимальном и пользовательском.
   - В автоматическом режиме управление выполняется на основе показаний уровня загрязнения воздуха (CO2) и температуры.

3. **Управление вентилятором:**
   - Вентилятор поддерживает два режима работы. Скорость вентилятора регулируется в зависимости от потребностей в очистке воздуха.

4. **Обработка ошибок:**
   - Система отслеживает наличие ошибок. В случае возникновения ошибки (например, ненадлежащее состояние клапана) загорается синий индикатор.

5. **Коммуникация:**
   - Устройство использует протокол MQTT для обмена данными и управления через сети Wi-Fi. 

## MQTT Топики

- **Управление открытостью:** `Home_67/vozduh/openness`
- **Текущая открытость:** `Home_67/vozduh/openness/state`
- **Управление программой:** `Home_67/vozduh/programm`
- **Текущая программа:** `Home_67/vozduh/programm/state`
- **Скорость вентилятора:** `Home_67/vozduh/speed`
- **Текущая скорость вентилятора:** `Home_67/vozduh/speed/state`
- **Состояние закрытого положения клапана:** `Home_67/vozduh/closed/state`
- **Качество воздуха (CO2):** `Home_67/vozduh/CO2`
- **Температура в помещении:** `Home_67/vozduh/temperature/state`

## Подключение

Для работы устройства требуется подключение к Wi-Fi. Настройте параметры подключения в коде:

- **SSID и пароль Wi-Fi**
- **MQTT сервер и учетные данные**

## Заключение

Это устройство позволяет значительно улучшить качество воздуха в помещениях, делая это автоматически и с учетом различных факторов, таких как температура и уровень загрязнения.
