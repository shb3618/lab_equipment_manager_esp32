/*
 * ntp.h
 *
 *  Created on: 2018-02-16 17:50
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_USER_NTP_H_
#define INC_USER_NTP_H_

extern void ntp_task(void *pvParameter);
extern void ntp_sync_time(void);

#endif /* INC_USER_NTP_H_ */
