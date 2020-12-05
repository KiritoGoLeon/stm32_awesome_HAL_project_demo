#ifndef __MODULE_LOG_H_
#define __MODULE_LOG_H_

void module_log_init(void);
void module_log_handle(void);
void module_log_exit(void);


void module_log_write_e(char *tag,char *fmt, ...);
void module_log_write_v(char *tag,char *fmt, ...);

#define Logv  module_log_write_v
#define Loge  module_log_write_e

#endif

