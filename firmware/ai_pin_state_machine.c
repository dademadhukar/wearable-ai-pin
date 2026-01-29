#include <stdbool.h>
#include <stdint.h>

typedef enum {
    STATE_IDLE,
    STATE_LISTENING,
    STATE_ERROR
} system_state_t;

// Mock functions
bool is_button_pressed(void);
int get_battery_level(void);
void set_led_color(int color);
void start_audio_stream(void);
void stop_audio_stream(void);

#define LED_OFF   0
#define LED_GREEN 1
#define LED_RED   2
#define MAX_HOLD_TIME 30

void main_loop(void)
{
    system_state_t state = STATE_IDLE;
    uint32_t button_hold_time = 0;

    while (1)
    {
        switch (state)
        {
            case STATE_IDLE:
                set_led_color(LED_OFF);
                stop_audio_stream();

                if (is_button_pressed())
                {
                    if (get_battery_level() > 10)
                        state = STATE_LISTENING;
                    else
                        state = STATE_ERROR;

                    button_hold_time = 0;
                }
                break;

            case STATE_LISTENING:
                set_led_color(LED_GREEN);
                start_audio_stream();

                if (is_button_pressed())
                {
                    button_hold_time++;
                    if (button_hold_time > MAX_HOLD_TIME)
                        state = STATE_IDLE;
                }
                else
                {
                    state = STATE_IDLE;
                }
                break;

            case STATE_ERROR:
                set_led_color(LED_RED);
                stop_audio_stream();

                if (get_battery_level() > 10)
                    state = STATE_IDLE;
                break;

            default:
                state = STATE_IDLE;
                break;
        }
    }
}
