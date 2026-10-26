struct Config
{
    // Pins
    static constexpr uint8_t BUTTON_PIN = 16;
    static constexpr uint8_t LED_YELLOW_PIN = 17;
    static constexpr uint8_t LDR_PIN = 4;

    // Button timing
    static constexpr uint32_t BUTTON_PERIOD_MS = 50;
    static constexpr uint32_t SHORT_PRESS_MS = 500;
    static constexpr uint32_t LONG_PRESS_MS = 2000;

    // LDR filtering
    static constexpr float LDR_ALPHA = 0.1f;
};

enum class led_state: u8_t {
    NO_ACTIVE,
    BLINK,
    ON
}
