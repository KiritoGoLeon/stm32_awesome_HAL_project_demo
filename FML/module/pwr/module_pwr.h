#ifndef __MODULE_PWR_H_
#define __MODULE_PWR_H_

void module_pwr_init(void);
void module_pwr_handle(void);
void module_pwr_exit(void);

void module_pwr_enter_sleep_mode(void);
void module_pwr_enter_stop_mode(void);
void module_pwr_stop_mode_wake(void);
void module_pwr_enter_standby_mode(void);
#endif

